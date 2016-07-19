#include "thread/task_queue.h"

/* initialize
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
task_queue_init(struct TaskQueue *const restrict queue);

extern inline void
task_queue_init_empty(struct TaskQueue *const restrict queue);

extern inline void
task_queue_init_populated(struct TaskQueue *const restrict queue,
			  struct TaskQueueNode *restrict node,
			  struct ProcedureClosure *restrict task,
			  const size_t count);

/* Accessor, Mutator functions
 *─────────────────────────────────────────────────────────────────────────── */
/* locking the queue... */
extern inline bool
task_queue_lock_status(struct TaskQueue *const restrict queue);
extern inline void
task_queue_lock_muffle(struct TaskQueue *const restrict queue);
extern inline bool
task_queue_lock_report(struct TaskQueue *const restrict queue,
		       const char *restrict *const restrict failure);
extern inline void
task_queue_lock_handle(struct TaskQueue *const restrict queue,
		       Handler *const handle,
		       void *arg);
extern inline void
task_queue_lock_handle_cl(struct TaskQueue *const restrict queue,
			  const struct HandlerClosure *const restrict h_cl);

/* locking the queue (no block on failure) */
extern inline bool
task_queue_try_lock_status(struct TaskQueue *const restrict queue);
extern inline void
task_queue_try_lock_muffle(struct TaskQueue *const restrict queue);
extern inline enum ThreadFlag
task_queue_try_lock_report(struct TaskQueue *const restrict queue,
			   const char *restrict *const restrict failure);
extern inline void
task_queue_try_lock_handle(struct TaskQueue *const restrict queue,
			   Handler *const handle,
			   void *arg);
extern inline void
task_queue_try_lock_handle_cl(struct TaskQueue *const restrict queue,
			      const struct HandlerClosure *const restrict h_cl);

/* unlocking the queue... */
extern inline bool
task_queue_unlock_status(struct TaskQueue *const restrict queue);
extern inline void
task_queue_unlock_muffle(struct TaskQueue *const restrict queue);
extern inline bool
task_queue_unlock_report(struct TaskQueue *const restrict queue,
			 const char *restrict *const restrict failure);
extern inline void
task_queue_unlock_handle(struct TaskQueue *const restrict queue,
			 Handler *const handle,
			 void *arg);

/* LIFO peek
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
task_queue_peek(struct TaskQueue *const restrict queue,
		struct TaskQueueNode *restrict *const restrict node_ptr);

/* LIFO push
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
task_queue_push_muffle(struct TaskQueue *const restrict queue,
		       struct TaskQueueNode *const restrict node);
extern inline void
task_queue_push_handle_cl(struct TaskQueue *const restrict queue,
			  struct TaskQueueNode *const restrict node,
			  const struct HandlerClosure *const restrict h_cl);


/* LIFO pop
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
task_queue_pop_muffle(struct TaskQueue *const restrict queue,
		      struct TaskQueueNode *restrict *const restrict node_ptr);
extern inline void
task_queue_pop_handle_cl(struct TaskQueue *const restrict queue,
			 struct TaskQueueNode *restrict *const restrict node_ptr,
			 const struct HandlerClosure *const restrict h_cl);

/* atomically pop head from queue1, point node at it, then push into queue2
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
task_queue_pop_push_muffle(struct TaskQueue *const restrict queue1,
			   struct TaskQueue *const restrict queue2,
			   struct TaskQueueNode *restrict *const restrict node_ptr);
extern inline void
task_queue_pop_push_handle_cl(struct TaskQueue *const restrict queue1,
			      struct TaskQueue *const restrict queue2,
			      struct TaskQueueNode *restrict *const restrict node_ptr,
			      const struct HandlerClosure *const restrict h_cl);

/* random access delete
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
task_queue_remove_muffle(struct TaskQueue *const restrict queue,
			 struct TaskQueueNode *const restrict node);
extern inline void
task_queue_remove_handle_cl(struct TaskQueue *const restrict queue,
			    struct TaskQueueNode *const restrict node,
			    const struct HandlerClosure *const restrict h_cl);


/* block until emptied
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
task_queue_await_empty_muffle(struct TaskQueue *const restrict queue);
extern inline void
task_queue_await_empty_handle_cl(struct TaskQueue *const restrict queue,
				 const struct HandlerClosure *const restrict h_cl);

/* clear nodes
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
task_queue_clear_muffle(struct TaskQueue *const restrict queue);

extern inline void
task_queue_clear_handle_cl(struct TaskQueue *const restrict queue,
			   const struct HandlerClosure *const restrict h_cl);

/* transfer all nodes from queue1 to queue2
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
task_queue_transfer_all_muffle(struct TaskQueue *const restrict queue1,
			       struct TaskQueue *const restrict queue2);
extern inline void
task_queue_transfer_all_handle_cl(struct TaskQueue *const restrict queue1,
				  struct TaskQueue *const restrict queue2,
				  const struct HandlerClosure *const restrict h_cl);
