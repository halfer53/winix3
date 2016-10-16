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
	hole_t *curr = q[HEAD];
	hole_t *prev = NULL;

	if(curr == NULL) { //Empty list
		assert(q[TAIL] == NULL, "delete: tail not null");
		return -1;
	}

	while(curr != h && curr != NULL){
		prev = curr;
		curr = curr->next;
	}
	if (curr != NULL) {
		if (prev == NULL) {
			q[HEAD] = q[TAIL] = NULL;
		}else{
			prev->next = curr->next;
		}
		return 1;
	}else{
		return -1;
	}

}


void Scan_FREE_MEM_BEGIN(){
	FREE_MEM_BEGIN = (size_t)&BSS_END;

	//Round up to the next 1k boundary
	FREE_MEM_BEGIN |= 0x03ff;
	FREE_MEM_BEGIN++;

	printf("\r\nfree memory begin 0x%x\r\n",FREE_MEM_BEGIN );
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
	//printf("free mem %x\n",FREE_MEM_BEGIN );
  return (void *)temp;
}



void *_malloc(size_t size){
  hole_t *temp_holes_table[2];
  hole_t *temp_h = NULL;
	hole_t *h = NULL;
  void *p_start_addr = NULL;
	size_t start = 0;
	size_t hole_length = 0;

	if (size == 0) {
		return NULL;
	}

  temp_holes_table[HEAD] = temp_holes_table[TAIL] = NULL;
	do{
		h = hole_dequeue(unused_holes);
    if (h != NULL) {
      //printf("unused hole start 0x%x, size %d\n",h->start,(int)(h->length) );
      //if the holes size is smaller than the required size
      if (h->length < size) {
  			hole_enqueue_head(temp_holes_table,h);
  		}else{
        break;
      }
    }
	}while(h != NULL);

  temp_h = hole_dequeue(temp_holes_table);
  while(temp_h != NULL){
    hole_enqueue_head(unused_holes,temp_h);
		temp_h = hole_dequeue(temp_holes_table);
  }

  //if no hole size  that is big enough is found in the unused_holes list,
  //it's gonna call sbrk to allocate a new chunk of memory
  if (h == NULL) {
      p_start_addr = _sbrk(size);
			//printf("call sbrk p addr %d, point at %d, deref val %d\n",&p_start_addr, p_start_addr,*(size_t *)p_start_addr);
      //if there is enough space
      if (p_start_addr != NULL) {
        h = hole_dequeue(pending_holes);

				if (h != NULL) {
					h->start = p_start_addr;
	        h->length = size;
					hole_enqueue_head(used_holes,h);
	        //printf("sbrk new hole start 0x%x, size %d\n\n",h->start,(int)(h->length) );
					//hole_overview(used_holes);
					//hole_overview(unused_holes);
	        return p_start_addr;
				}else{
					//TODO
					//if the hole_table has ran out, hole_dequeue would return NULL
					//in this case, dynamically allocating a new space hole_t is needed using sbrk() or malloc()
					//but since we don't have sizeof() implemented yet, (which is hard to implement)
					//we'll just assume that there is enough space
					return NULL;
				}

      }else{
				//if sbrk isn't successful, then there's no memory space overall available in the OS
        return NULL;
      }

  }else{ //if there is a hole that is big enough

    if (h->length >= size) {
        p_start_addr = h->start;
        //printf("new hole start 0x%x, size %d\n",h->start,(int)(h->length) );
        if (h->length > size) {
          temp_h = hole_dequeue(pending_holes);
          temp_h->start = (void *)((size_t *)h->start + size);
          temp_h->length = h->length - size;
          hole_enqueue_tail(unused_holes,temp_h);
          //printf("remaining hole start 0x%x, size %d\n",temp_h->start,(int)(temp_h->length) );
        } //h->length == size
          //h is no longer useful , add it back to the pending_holes
					h->length = size;
					// hole_overview(used_holes);
					// hole_overview(unused_holes);
        return p_start_addr;
    }else{ //this shouldn't happen
      printf("this shouldn't happen h==null but h->length < size" );
      return NULL;
    }

  }
	//return NULL;
}

void _free(void *ptr){

	hole_t *temp_holes_table[2];
  hole_t *temp_h = NULL;
	hole_t *h = NULL;
  size_t *p= NULL;
	int i = 0;
	size_t start = 0;
	size_t hole_length = 0;


	temp_holes_table[HEAD] = temp_holes_table[TAIL] = NULL;
	do{
		h = hole_dequeue(used_holes);
    if (h != NULL) {
      //printf("free: hole start 0x%x, size %d\n",h->start,(int)(h->length) );
      //if the holes size is smaller than the required size
      if (h->start != ptr) {
  			hole_enqueue_head(temp_holes_table,h);
  		}else{
        break;
      }
    }
	}while(h != NULL);

  temp_h = hole_dequeue(temp_holes_table);
  while(temp_h != NULL){
    hole_enqueue_head(used_holes,temp_h);
		temp_h = hole_dequeue(temp_holes_table);
  }

	if (h != NULL) {
		printf("free: found start 0x%x, length %d\n\n",h->start,h->length );
		p = (size_t *)ptr;
		for ( i = 0; i < h->length; i++) {
			*p = DEFAULT_MEM_VALUE;
			p++;
		}

		//merging ajacent holes
		if (merge_holes(h)!=-1) {
			hole_enqueue_head(unused_holes,h);
		}
		//clear this hole from the used table

	}
	// hole_overview(used_holes);
	// hole_overview(unused_holes);

}

//h must be a hole_t that doesn't below to any
int merge_holes(hole_t *h){
	hole_t *temp_h = unused_holes[HEAD];
	while(temp_h != NULL){
		size_t *temp_h_next = (size_t *)(temp_h->start) + temp_h->length;
		size_t *h_next = (size_t *)(h->start) + h->length;

		if ((size_t)h_next == FREE_MEM_BEGIN) {
			FREE_MEM_BEGIN -= h->length;
			hole_enqueue_tail(pending_holes,h);
			return -1;
		}
		if (temp_h_next == h->start) {
			if (hole_delete(unused_holes,temp_h) != -1) { //upon successful deletion

				//delete the adjacent hole, merge them together, and add the deleted one to the pending hole
				h->start = (void *)((size_t *)h->start - temp_h->length);
				h->length += temp_h->length;
				temp_h->start = NULL;
				temp_h->length = 0;
				hole_enqueue_head(pending_holes,temp_h);
				break;
			}else{
				printf("delete unsuccessful\n" );
				return -1;
			}
		}else if(h_next == temp_h->start){
			if (hole_delete(unused_holes,temp_h) != -1) {
				h->length += temp_h->length;
				temp_h->start = NULL;
				temp_h->length = 0;
				hole_enqueue_head(pending_holes,temp_h);
				break;
			}else{
				printf("delete unsuccessful\n" );
				return -1;
			}
		}
	}

	return 1;
}

void hole_overview(hole_t **q){
	hole_t *curr = q[HEAD];
	while (curr != NULL) {
		printf("hole start %x, length %d\n",(size_t *)curr->start,curr->length );
		curr = curr->next;
	}
}

void used_hole_overview(char *s){
	printf("%s\n",s );
	hole_overview(used_holes);
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



void wipe_mem(void *start,size_t length){

	hole_t *h = NULL;
	int i=0;
	size_t *ptr = (size_t *)start;
	printf("wipe start %x length %d\n",(size_t *)start,length );
	for (i = 0; i < length; i++) {
		*ptr = DEFAULT_MEM_VALUE;
		ptr++;
	}
	h = hole_dequeue(pending_holes);
	h->start = start;
	h->length = length;
	printf("wipe hole start %x length %d\n",(size_t *)start,length );
	if (merge_holes(h) != -1) {
		hole_enqueue_head(unused_holes,h);
	}

}

void *load_BinRecord_Mem(size_t *lines,size_t length){
	int i = 0;
	size_t *temp = NULL;
	size_t *p = (size_t *)_malloc(length);
	printf("new malloced start %x, length %d\n",p,length);
	temp = p;
	for (i = 0; i < length; i++) {
		*p  = lines[i];
		p++;
	}
	return (void *)temp;
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
