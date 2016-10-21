#include "winix.h"

hole_t hole_table[NUM_HOLES];

//Entries to the list of unallocated memory space in RAM
static hole_t *unused_holes[2];

//ENtries in the holes that are not in use, but can be added to the holes list
static hole_t *pending_holes[2];

static hole_t *used_holes[2];
//Linked lists are defined by a head and tail pointer.
#define HEAD 0
#define TAIL 1

/**
 * Adds a proc to the tail of a list.
 *
 * Parameters:
 *   q		An array containing a head and tail pointer of a linked list.
 *   proc	The proc struct to add to the list.
 **/
static void hole_enqueue_tail(hole_t **q, hole_t *hole) {
	if(q[HEAD] == NULL) {
		q[HEAD] = q[TAIL] = hole;
	}
	else {
		q[TAIL]->next = hole;
		q[TAIL] = hole;
	}
	hole->next = NULL;
}

/**
 * Adds a proc to the head of a list.
 *
 * Parameters:
 *   q		An array containing a head and tail pointer of a linked list.
 *   proc	The proc struct to add to the list.
 **/
static void hole_enqueue_head(hole_t **q, hole_t *hole) {
	if(q[HEAD] == NULL) {
		hole->next = NULL;
		q[HEAD] = q[TAIL] = hole;
	}
	else {
		hole->next = q[HEAD];
		q[HEAD] = hole;
	}
}

/**
 * Removes the head of a list.
 *
 * Parameters:
 *   q		An array containing a head and tail pointer of a linked list.
 *
 * Returns:
 *   The proc struct that was removed from the head of the list
 *   NULL if the list is empty.
 **/
static hole_t *hole_dequeue(hole_t **q) {
	hole_t *hole = q[HEAD];

	if(hole == NULL) { //Empty list
		assert(q[TAIL] == NULL, "deq: tail not null");
		return NULL;
	}

	if(q[HEAD] == q[TAIL]) { //Last item
		q[HEAD] = q[TAIL] = NULL;
	}
	else { //At least one remaining item
		q[HEAD] = hole->next;
	}
	hole->next = NULL;
	return hole;
}



static int hole_delete(hole_t **q, hole_t *h){
	register hole_t *curr = q[HEAD];
	register hole_t *prev = NULL;

	if(curr == NULL) { //Empty list
		assert(q[TAIL] == NULL, "delete: tail not null");
		return 0;
	}

	while(curr != h && curr != NULL){
		prev = curr;
		curr = curr->next;
	}
	if (curr != NULL) {
		if (prev == NULL) {
			if (q[HEAD] == q[TAIL]) {
				q[HEAD] = q[TAIL] = NULL;
			}else{
				q[HEAD] = curr->next;
			}
		}else{
			prev->next = curr->next;
		}
		return 1;
	}else{
		return 0;
	}
}

static int hole_delete2(hole_t **q, hole_t *prev, hole_t *curr){
	if (curr != NULL) {
		if (prev == NULL) {
			if (q[HEAD] == q[TAIL]) {
				q[HEAD] = q[TAIL] = NULL;
			}else{
				q[HEAD] = curr->next;
			}
		}else{
			prev->next = curr->next;
		}
		return 1;
	}
	return 0;
}


void Scan_FREE_MEM_BEGIN(){
	FREE_MEM_BEGIN = (size_t)&BSS_END;

	//Round up to the next 1k boundary
	FREE_MEM_BEGIN |= 0x03ff;
	FREE_MEM_BEGIN++;

	kprintf("\r\nfree memory begin 0x%x\r\n",FREE_MEM_BEGIN );
}

void *_sbrk(size_t size){
  size_t temp = FREE_MEM_BEGIN;
  if (FREE_MEM_END != 0) {
  	//if FREE_MEM_END is not null, then that means the OS is running
  	//otherwise it's initialising, thus FREE_MEM_END is not set yet
  	//we just assume there is enough memory during the start up
  	//since calculating FREE_MEM_END during the start up is gonna crash the system for some unknown reason
  	if (size + FREE_MEM_BEGIN > FREE_MEM_END) {
  		return NULL;
  	}
  }

  FREE_MEM_BEGIN += size;
	//kprintf("free mem %x\n",FREE_MEM_BEGIN );
  return (void *)temp;
}



void *proc_malloc(size_t size){
  register hole_t *prev = NULL;
	register hole_t *h = unused_holes[HEAD];
  size_t *p_start_addr = NULL;
	size_t *old_base = 0;

	if (size == 0) {
		return NULL;
	}
	while(h != NULL && h->length < size){
		prev = h;
		h = h->next;
	}
  //if no hole size  that is big enough is found in the unused_holes list,
  //it's gonna call sbrk to allocate a new chunk of memory
  if (h != NULL) {
		//if we've found a hole taht is big enough
		old_base = h->start;
		if (h->length == size) {
			hole_delete2(unused_holes,prev,h);
			hole_enqueue_head(used_holes,h);
		}else{
			h->start += size;
			h->length -= size;
			h = hole_dequeue(pending_holes);
			h->start = old_base;
			h->length = size;
			hole_enqueue_head(used_holes,h);
		}
		//kprintf("malloc: curr hole start 0x%x, length %d\n",old_base,h->length );
		return (void *)old_base;
  }else{
		if ((p_start_addr = (size_t *)_sbrk(size)) != NULL) {
			if (h = hole_dequeue(pending_holes)) {
				h->start = p_start_addr;
				h->length = size;
				//kprintf("malloc: sbrk start 0x%x, length %d\n",h->start,h->length );
				hole_enqueue_head(used_holes,h);
				return p_start_addr;
			}
			//else if hole table ran out
		}//else if sbrk fails
  }
	return NULL;
}

void proc_free(void *ptr_parameter){
	register size_t *p = (size_t *)ptr_parameter;
	register hole_t *h = used_holes[HEAD];
	int i = 0;
	size_t start = 0;
	size_t hole_length = 0;

	while(h!=NULL && h->start!=p){
		h = h->next;
	}
	if (h != NULL) {
		//kprintf("free: found start 0x%x, length %d\n",h->start,h->length );
		for ( i = 0; i < h->length; i++) {
			*p = DEFAULT_MEM_VALUE;
			p++;
		}

		if (hole_delete(used_holes, h)) {
			if (merge_holes(unused_holes,h)) {
				//kprintf("holes merged\n" );
			}
		}

	}else{
		//kprintf("nothing found to be freed at addr %x\n",ptr_parameter );
	}
}

//h must be a hole_t that doesn't below to any
int merge_holes(hole_t **merging_holes_list,hole_t *h){

		register hole_t *curr = merging_holes_list[HEAD];

		if (h->start + h->length == (size_t *)FREE_MEM_BEGIN) {
			//kprintf("free mem %x, start %x, length %d, total %x\n",FREE_MEM_BEGIN,h->start,h->length,(size_t)(h->start + h->length) );
			FREE_MEM_BEGIN -= h->length;
			hole_enqueue_head(pending_holes,h);
			return 1;
		}
		while(curr != NULL){
			if (curr->start + curr->length == h->start) {
				//kprintf("before start 0x%x, length %d start 0x%x, length %d\n",h->start,h->length,curr->start,curr->length);
				curr->length += h->length;
				//kprintf("merged hole, start 0x%x, length %d\n",curr->start,curr->length);
				break;
			}else if(h->start + h->length == curr->start){
				//kprintf("before start 0x%x, length %d start 0x%x, length %d\n",h->start,h->length,curr->start,curr->length);
				curr->start -= h->length;
				curr->length += h->length;
				//kprintf("merged hole, start 0x%x, length %d\n",curr->start,curr->length);
				break;
			}
			curr = curr->next;
		}

	if (curr != NULL) {
		hole_enqueue_head(pending_holes,h);
		return 1;
	}else{
		hole_enqueue_head(unused_holes,h);
		return 0;
	}
}

void hole_list_overview(){
	hole_t *curr = unused_holes[HEAD];
	if (curr == NULL) {
		kprintf("unused hole empty\n" );
	}
	while (curr != NULL) {
		kprintf("unused hole start %x, length %d\n",curr->start,curr->length );
		curr = curr->next;
	}

	curr = used_holes[HEAD];
	if (curr == NULL) {
		kprintf("used holes empty\n" );
	}
	while (curr != NULL) {
		kprintf("used hole start %x, length %d\n",curr->start,curr->length );
		curr = curr->next;
	}

}

void *memcpy(void *s1, const void *s2, register size_t n)
{
        register char *p1 = s1;
        register const char *p2 = s2;

        if (n) {
                n++;
                while (--n > 0) {
                        *p1++ = *p2++;
                }
         }
        return s1;
}

void init_memory(){
  hole_t *h = NULL;
  int i = 0;
	unused_holes[HEAD] = unused_holes[TAIL] = NULL;
	used_holes[HEAD] = used_holes[TAIL] = NULL;
	pending_holes[HEAD] = pending_holes[TAIL] = NULL;

	for ( i = 0; i < NUM_HOLES; i++) {
		h = &hole_table[i];
		h->start = 0;
		h->length = 0;
		h->next = NULL;
		hole_enqueue_head(pending_holes,h);
	}
}

int sizeof_hole_t(){
	hole_t arr[2];
	int size = (char*)&arr[1] - (char*)&arr[0];
	return size;
}
