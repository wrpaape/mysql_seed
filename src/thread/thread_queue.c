#include "thread/thread_queue.h"

/* initialize
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
thread_queue_init(struct ThreadQueue *const restrict queue);

extern inline void
thread_queue_init_empty(struct ThreadQueue *const restrict queue);

extern inline void
thread_queue_init_populated(struct ThreadQueue *const restrict queue,
			    struct ThreadQueueNode *restrict nodes,
			    void *restrict payloads,
			    const size_t payload_count,
			    const size_t payload_width);

/* Accessor, Mutator functions
 *─────────────────────────────────────────────────────────────────────────── */
/* locking the queue... */
extern inline bool
thread_queue_lock_status(struct ThreadQueue *const restrict queue);
extern inline void
thread_queue_lock_muffle(struct ThreadQueue *const restrict queue);
extern inline bool
thread_queue_lock_report(struct ThreadQueue *const restrict queue,
			 const char *restrict *const restrict failure);
extern inline void
thread_queue_lock_handle(struct ThreadQueue *const restrict queue,
			 Handler *const handle,
			 void *arg);
extern inline void
thread_queue_lock_handle_cl(struct ThreadQueue *const restrict queue,
			    const struct HandlerClosure *const restrict h_cl);

/* locking the queue (no block on failure) */
extern inline bool
thread_queue_try_lock_status(struct ThreadQueue *const restrict queue);
extern inline void
thread_queue_try_lock_muffle(struct ThreadQueue *const restrict queue);
extern inline enum ThreadFlag
thread_queue_try_lock_report(struct ThreadQueue *const restrict queue,
			     const char *restrict *const restrict failure);
extern inline void
thread_queue_try_lock_handle(struct ThreadQueue *const restrict queue,
			     Handler *const handle,
			     void *arg);
extern inline void
thread_queue_try_lock_handle_cl(struct ThreadQueue *const restrict queue,
				const struct HandlerClosure *const restrict h_cl);

/* unlocking the queue... */
extern inline bool
thread_queue_unlock_status(struct ThreadQueue *const restrict queue);
extern inline void
thread_queue_unlock_muffle(struct ThreadQueue *const restrict queue);
extern inline bool
thread_queue_unlock_report(struct ThreadQueue *const restrict queue,
			   const char *restrict *const restrict failure);
extern inline void
thread_queue_unlock_handle(struct ThreadQueue *const restrict queue,
			   Handler *const handle,
			   void *arg);

/* LIFO peek
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
thread_queue_peek(struct ThreadQueue *const restrict queue,
		  struct ThreadQueueNode *restrict *const restrict node_ptr);

/* LIFO push
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
thread_queue_push_muffle(struct ThreadQueue *const restrict queue,
			 struct ThreadQueueNode *const restrict node);
extern inline void
thread_queue_push_handle_cl(struct ThreadQueue *const restrict queue,
			    struct ThreadQueueNode *const restrict node,
			    const struct HandlerClosure *const restrict h_cl);


/* LIFO pop
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
thread_queue_pop_muffle(struct ThreadQueue *const restrict queue,
			struct ThreadQueueNode *restrict *const restrict node_ptr);
extern inline void
thread_queue_pop_handle_cl(struct ThreadQueue *const restrict queue,
			   struct ThreadQueueNode *restrict *const restrict node_ptr,
			   const struct HandlerClosure *const restrict h_cl);

/* atomically pop head from queue1, point node at it, then push into queue2
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
thread_queue_pop_push_muffle(struct ThreadQueue *const restrict queue1,
			     struct ThreadQueue *const restrict queue2,
			     struct ThreadQueueNode *restrict *const restrict node_ptr);
extern inline void
thread_queue_pop_push_handle_cl(struct ThreadQueue *const restrict queue1,
				struct ThreadQueue *const restrict queue2,
				struct ThreadQueueNode *restrict *const restrict node_ptr,
				const struct HandlerClosure *const restrict h_cl);

/* random access delete
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
thread_queue_remove_muffle(struct ThreadQueue *const restrict queue,
			   struct ThreadQueueNode *const restrict node);
extern inline void
thread_queue_remove_handle_cl(struct ThreadQueue *const restrict queue,
			      struct ThreadQueueNode *const restrict node,
			      const struct HandlerClosure *const restrict h_cl);


/* block until emptied
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
thread_queue_await_empty_muffle(struct ThreadQueue *const restrict queue);
extern inline void
thread_queue_await_empty_handle_cl(struct ThreadQueue *const restrict queue,
				   const struct HandlerClosure *const restrict h_cl);

/* clear nodes
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
thread_queue_clear_muffle(struct ThreadQueue *const restrict queue);

extern inline void
thread_queue_clear_handle_cl(struct ThreadQueue *const restrict queue,
			     const struct HandlerClosure *const restrict h_cl);

/* transfer all nodes from queue1 to queue2
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
thread_queue_transfer_all_muffle(struct ThreadQueue *const restrict queue1,
				 struct ThreadQueue *const restrict queue2);
extern inline void
thread_queue_transfer_all_handle_cl(struct ThreadQueue *const restrict queue1,
				    struct ThreadQueue *const restrict queue2,
				    const struct HandlerClosure *const restrict h_cl);
