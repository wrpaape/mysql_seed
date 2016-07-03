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

/* Accessor, Mutator functions
 *─────────────────────────────────────────────────────────────────────────── */
/* locking the queue... */
extern inline void
thread_queue_lock(struct ThreadQueue *const restrict queue);
extern inline bool
thread_queue_lock_status(struct ThreadQueue *const restrict queue);
extern inline void
thread_queue_lock_muffle(struct ThreadQueue *const restrict queue);
extern inline bool
thread_queue_lock_report(struct ThreadQueue *const restrict queue,
			 const char *restrict *const restrict failure);
extern inline void
thread_queue_lock_handle(struct ThreadQueue *const restrict queue,
			 ThreadHandler *const handle,
			 void *arg);
extern inline void
thread_queue_lock_handle_cl(struct ThreadQueue *const restrict queue,
			    struct ThreadHandlerClosure *const restrict cl);

/* locking the queue (no block on failure) */
extern inline void
thread_queue_try_lock(struct ThreadQueue *const restrict queue);
extern inline bool
thread_queue_try_lock_status(struct ThreadQueue *const restrict queue);
extern inline void
thread_queue_try_lock_muffle(struct ThreadQueue *const restrict queue);
extern inline enum ThreadFlag
thread_queue_try_lock_report(struct ThreadQueue *const restrict queue,
			     const char *restrict *const restrict failure);
extern inline void
thread_queue_try_lock_handle(struct ThreadQueue *const restrict queue,
			     ThreadHandler *const handle,
			     void *arg);
extern inline void
thread_queue_try_lock_handle_cl(struct ThreadQueue *const restrict queue,
				struct ThreadHandlerClosure *const restrict cl);

/* unlocking the queue... */
extern inline void
thread_queue_unlock(struct ThreadQueue *const restrict queue);
extern inline bool
thread_queue_unlock_status(struct ThreadQueue *const restrict queue);
extern inline void
thread_queue_unlock_muffle(struct ThreadQueue *const restrict queue);
extern inline bool
thread_queue_unlock_report(struct ThreadQueue *const restrict queue,
			   const char *restrict *const restrict failure);
extern inline void
thread_queue_unlock_handle(struct ThreadQueue *const restrict queue,
			   ThreadHandler *const handle,
			   void *arg);

/* LIFO peek
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
thread_queue_peek(struct ThreadQueue *const restrict queue,
		  struct ThreadQueueNode *const restrict node);

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
