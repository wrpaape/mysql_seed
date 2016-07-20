#include "thread/task_queue.h"

/* initialize
 *─────────────────────────────────────────────────────────────────────────── */
extern inline struct TaskNode *
task_nodes_init_mfma(struct TaskNode *restrict node,
		     Procedure *const *task_fun,
		     void **task_arg,
		     const size_t count);
extern inline struct TaskNode *
task_nodes_init_sfma(struct TaskNode *restrict node,
		     Procedure *const task_fun,
		     void **task_arg,
		     const size_t count);
extern inline struct TaskNode *
task_nodes_init_tasks(struct TaskNode *restrict node,
		      const struct ProcedureClosure *restrict task,
		      const size_t count);
extern inline void
task_store_init_mfma(struct TaskStore *const restrict store,
		     struct TaskNode *const restrict nodes,
		     Procedure *const *const task_funs,
		     void **task_args,
		     const size_t count);
extern inline void
task_store_init_sfma(struct TaskStore *const restrict store,
		     struct TaskNode *const restrict nodes,
		     Procedure *const task_fun,
		     void **task_args,
		     const size_t count);
extern inline void
task_store_init_tasks(struct TaskStore *const restrict store,
		      struct TaskNode *const restrict nodes,
		      const struct ProcedureClosure *const restrict tasks,
		      const size_t count);
extern inline void
task_queue_init(struct TaskQueue *const restrict queue);

extern inline void
task_queue_init_empty(struct TaskQueue *const restrict queue);

extern inline void
task_queue_init_store(struct TaskQueue *const restrict queue,
		      const struct TaskStore *const restrict store);
extern inline void
task_queue_init_mfma(struct TaskQueue *const restrict queue,
		     struct TaskNode *const restrict nodes,
		     Procedure *const *const task_funs,
		     void **task_args,
		     const size_t count);
extern inline void
task_queue_init_sfma(struct TaskQueue *const restrict queue,
		     struct TaskNode *const restrict nodes,
		     Procedure *const task_fun,
		     void **task_args,
		     const size_t count);
extern inline void
task_queue_init_tasks(struct TaskQueue *const restrict queue,
		      struct TaskNode *const restrict nodes,
		      const struct ProcedureClosure *const restrict tasks,
		      const size_t count);

/* LIFO peek
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
task_queue_peek(struct TaskQueue *const restrict queue,
		struct TaskNode *restrict *const restrict node_ptr);

/* LIFO push
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
task_queue_push_muffle(struct TaskQueue *const restrict queue,
		       struct TaskNode *const restrict node);
extern inline void
task_queue_push_handle_cl(struct TaskQueue *const restrict queue,
			  struct TaskNode *const restrict node,
			  const struct HandlerClosure *const restrict fail_cl);


/* LIFO pop
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
task_queue_pop_muffle(struct TaskQueue *const restrict queue,
		      struct TaskNode *restrict *const restrict node_ptr);
extern inline void
task_queue_pop_handle_cl(struct TaskQueue *const restrict queue,
			 struct TaskNode *restrict *const restrict node_ptr,
			 const struct HandlerClosure *const restrict fail_cl);

/* atomically pop head from queue1, point node at it, then push into queue2
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
task_queue_pop_push_muffle(struct TaskQueue *const restrict queue1,
			   struct TaskQueue *const restrict queue2,
			   struct TaskNode *restrict *const restrict node_ptr);
extern inline void
task_queue_pop_push_handle_cl(struct TaskQueue *const restrict queue1,
			      struct TaskQueue *const restrict queue2,
			      struct TaskNode *restrict *const restrict node_ptr,
			      const struct HandlerClosure *const restrict fail_cl);

/* random access delete
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
task_queue_remove_muffle(struct TaskQueue *const restrict queue,
			 struct TaskNode *const restrict node);
extern inline void
task_queue_remove_handle_cl(struct TaskQueue *const restrict queue,
			    struct TaskNode *const restrict node,
			    const struct HandlerClosure *const restrict fail_cl);


/* block until emptied
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
task_queue_await_empty_muffle(struct TaskQueue *const restrict queue);
extern inline void
task_queue_await_empty_handle_cl(struct TaskQueue *const restrict queue,
				 const struct HandlerClosure *const restrict fail_cl);

/* clear nodes
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
task_queue_clear_muffle(struct TaskQueue *const restrict queue);

extern inline void
task_queue_clear_handle_cl(struct TaskQueue *const restrict queue,
			   const struct HandlerClosure *const restrict fail_cl);

/* transfer all nodes from queue1 to queue2
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
task_queue_transfer_all_muffle(struct TaskQueue *const restrict queue1,
			       struct TaskQueue *const restrict queue2);
extern inline void
task_queue_transfer_all_handle_cl(struct TaskQueue *const restrict queue1,
				  struct TaskQueue *const restrict queue2,
				  const struct HandlerClosure *const restrict fail_cl);

/* load queue with 'nodes' from 'store' (queue is empty, store is not empty)
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
task_queue_reload_muffle(struct TaskQueue *const restrict queue,
			 struct TaskStore *const restrict store);
extern inline void
task_queue_reload_handle_cl(struct TaskQueue *const restrict queue,
			    struct TaskStore *const restrict store,
			    const struct HandlerClosure *const restrict fail_cl);

/* locked/unsignaled push
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
task_queue_push_quiet_muffle(struct TaskQueue *const restrict queue,
			     struct TaskNode *const restrict node);
extern inline void
task_queue_push_quiet_handle_cl(struct TaskQueue *const restrict queue,
				struct TaskNode *const restrict node,
				const struct HandlerClosure *const restrict fail_cl);

/* retrieve nodes
 *─────────────────────────────────────────────────────────────────────────── */
/* unlocked/unsignaled */
extern inline void
task_queue_retreive_cold_quiet(struct TaskQueue *const restrict queue,
			       struct TaskStore *const restrict store);
/* locked/unsignaled */
extern inline void
task_queue_retreive_hot_quiet_muffle(struct TaskQueue *const restrict queue,
				     struct TaskStore *const restrict store);
extern inline void
task_queue_retreive_hot_quiet_handle_cl(struct TaskQueue *const restrict queue,
					struct TaskStore *const restrict store,
					const struct HandlerClosure *const restrict fail_cl);

/* swap node stores
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
task_store_swap(struct TaskStore *const restrict store1,
		struct TaskStore *const restrict store2);
