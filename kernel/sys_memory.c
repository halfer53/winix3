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
