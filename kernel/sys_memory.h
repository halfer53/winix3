typedef struct _hole{
  void *start;
  unsigned long length;
  struct _hole *next;
}hole_t;

#define NUM_HOLES 100

static void hole_enqueue_tail(hole_t **q, hole_t *hole);
static void hole_enqueue_head(hole_t **q, hole_t *hole);
static hole_t *hole_dequeue(hole_t **q);
void Scan_FREE_MEM_BEGIN();
void *_sbrk(size_t size);
void *_malloc(size_t size);
void init_memory();
