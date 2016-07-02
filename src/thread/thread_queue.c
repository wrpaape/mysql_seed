#include "thread/thread_queue.h"

/* initialize
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
thread_queue_init(struct ThreadQueue *const restrict queue,
		  const struct ThreadHandlerClosure *const restrict handle_fail);

extern inline void
thread_queue_init_empty(struct ThreadQueue *const restrict queue,
			const struct ThreadHandlerClosure *const restrict handle_fail);

extern inline void
thread_queue_init_populated(struct ThreadQueue *const restrict queue,
			    const struct ThreadHandlerClosure *const restrict handle_fail,
			    struct ThreadQueueNode *restrict nodes,
			    void *restrict payloads,
			    const size_t payload_count,
			    const size_t payload_width);


/* LIFO push
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
thread_queue_push(struct ThreadQueue *const restrict queue,
		  struct ThreadQueueNode *const restrict node);


/* LIFO pop
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
thread_queue_pop(struct ThreadQueue *const restrict queue,
		 struct ThreadQueueNode *restrict *const restrict node);


/* random access delete
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
thread_queue_remove(struct ThreadQueue *const restrict queue,
		    struct ThreadQueueNode *const restrict node);


/* block until emptied
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
thread_queue_await_empty(struct ThreadQueue *const restrict queue);
