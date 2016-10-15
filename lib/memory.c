#include <stdio.h>

//create a chunk of memory for the use of new stack
//return the end of the newly allocated space as stack pointer
void *_malloc(size_t size){
  hole_t *temp_holes_table[2];
  hole_t *temp_h = NULL;
	hole_t *h = NULL;
  size_t *p_start_addr = NULL;
	size_t start = 0;
	size_t hole_length = 0;

	do{
		h = hole_dequeue(unused_holes);
    if (h != NULL) {
      printf("hole start 0x%x, size %d\n",h->start,(int)(h->length) );
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
  }

  //if no hole size  that is big enough is found in the unused_holes list,
  //it's gonna call sbrk to allocate a new chunk of memory
  if (h == NULL) {
      printf("call sbrk\n" );
      p_start_addr = (size_t*)sbrk(size);
      //if there is enough space
      if (p_start_addr != NULL) {
        h = hole_dequeue(pending_holes);
        h->start = *p_start_addr;
        h->length = size;
        printf("new hole start 0x%x, size %d\n",h->start,(int)(h->length) );
        hole_enqueue_tail(used_holes,h);
        return p_start_addr;
      }else{
        //if there is not enough space for sbrk
        return NULL;
      }

  }else{ //if there is a hole that is big enough

    if (h->length >= size) {
        p_start_addr = (void *)h->start;
        printf("new hole start 0x%x, size %d\n",h->start,(int)(h->length) );
        if (h->length > size) {
          temp_h = hole_dequeue(pending_holes);
          temp_h->start = *(p_start_addr + size);
          temp_h->length = h->length - size;
          hole_enqueue_tail(unused_holes,temp_h);
          printf("remaining hole start 0x%x, size %d\n",temp_h->start,(int)(temp_h->length) );
        } //h->length == size
          //h is no longer useful , add it back to the pending_holes
          h->start = 0;
          h->length = 0;
          h->next = NULL;
          hole_enqueue_tail(pending_holes,h);

        return p_start_addr;
    }else{ //this shouldn't happen
      printf("this shouldn't happen h==null but h->length < size" );
      return NULL;
    }

  }


	return NULL;
}
