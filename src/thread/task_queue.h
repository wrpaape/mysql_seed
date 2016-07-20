#ifndef MYSQL_SEED_THREAD_THREAD_QUEUE_H_
#define MYSQL_SEED_THREAD_THREAD_QUEUE_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "thread/thread_utils.h"	/* threads API */

/* typedefs, struct declarations
 *─────────────────────────────────────────────────────────────────────────── */
struct TaskNode {
	struct ProcedureClosure task;
	struct TaskNode *prev;
	struct TaskNode *next;
};

struct TaskStore {
	struct TaskNode *restrict head;
	struct TaskNode *restrict last;
};

struct TaskQueue {
	Mutex lock;
	ThreadCond node_ready;
	ThreadCond empty;
	struct TaskNode *restrict head;
	struct TaskNode *restrict last;
};


/* initialize
 *─────────────────────────────────────────────────────────────────────────── */
inline struct TaskNode *
task_nodes_init_mfma(struct TaskNode *restrict node,
		     Procedure *const *task_fun,
		     void **task_arg,
		     const size_t count)
{
	struct TaskNode *restrict next;
	struct TaskNode *const restrict last = node
					     + (count - 1l);
	last->next = NULL;
	node->prev = NULL;

	while (1) {
		node->task.fun = *task_fun;
		node->task.arg = *task_arg;

		if (node == last)
			return last;

		next = node + 1l;

		node->next = next;
		next->prev = node;

		node = next;

		++task_arg;
		++task_fun;
	}
}

inline struct TaskNode *
task_nodes_init_sfma(struct TaskNode *restrict node,
		     Procedure *const task_fun,
		     void **task_arg,
		     const size_t count)
{
	struct TaskNode *restrict next;
	struct TaskNode *const restrict last = node
					     + (count - 1l);
	last->next = NULL;
	node->prev = NULL;

	while (1) {
		node->task.fun = task_fun;
		node->task.arg = *task_arg;

		if (node == last)
			return last;

		next = node + 1l;

		node->next = next;
		next->prev = node;

		node = next;

		++task_arg;
	}
}

inline struct TaskNode *
task_nodes_init_tasks(struct TaskNode *restrict node,
		      const struct ProcedureClosure *restrict task,
		      const size_t count)
{
	struct TaskNode *restrict next;
	struct TaskNode *const restrict last = node
					     + (count - 1l);
	last->next = NULL;
	node->prev = NULL;

	while (1) {
		node->task = *task;

		if (node == last)
			return last;

		next = node + 1l;

		node->next = next;
		next->prev = node;

		node = next;

		++task;
	}
}


inline void
task_store_init_mfma(struct TaskStore *const restrict store,
		     struct TaskNode *const restrict nodes,
		     Procedure *const *const task_funs,
		     void **task_args,
		     const size_t count)
{
	store->head = nodes;
	store->last = task_nodes_init_mfma(nodes,
					   task_funs,
					   task_args,
					   count);
}

inline void
task_store_init_sfma(struct TaskStore *const restrict store,
		     struct TaskNode *const restrict nodes,
		     Procedure *const task_fun,
		     void **task_args,
		     const size_t count)
{
	store->head = nodes;
	store->last = task_nodes_init_sfma(nodes,
					   task_fun,
					   task_args,
					   count);
}

inline void
task_store_init_tasks(struct TaskStore *const restrict store,
		      struct TaskNode *const restrict nodes,
		      const struct ProcedureClosure *const restrict tasks,
		      const size_t count)
{
	store->head = nodes;
	store->last = task_nodes_init_tasks(nodes,
					    tasks,
					    count);
}

inline void
task_queue_init(struct TaskQueue *const restrict queue)
{
	mutex_init(&queue->lock);

	thread_cond_init(&queue->node_ready);

	thread_cond_init(&queue->empty);
}

inline void
task_queue_init_empty(struct TaskQueue *const restrict queue)
{
	task_queue_init(queue);

	queue->head = NULL;
	queue->last = NULL;
}

inline void
task_queue_init_store(struct TaskQueue *const restrict queue,
		      const struct TaskStore *const restrict store)
{
	task_queue_init(queue);

	queue->head = store->head;
	queue->last = store->last;
}


/* multiple functions, mutliple args */
inline void
task_queue_init_mfma(struct TaskQueue *const restrict queue,
		     struct TaskNode *const restrict nodes,
		     Procedure *const *const task_funs,
		     void **task_args,
		     const size_t count)
{
	task_queue_init(queue);

	queue->head = nodes;
	queue->last = task_nodes_init_mfma(nodes,
					   task_funs,
					   task_args,
					   count);
}

/* single function, mutliple args */
inline void
task_queue_init_sfma(struct TaskQueue *const restrict queue,
		     struct TaskNode *const restrict nodes,
		     Procedure *const task_fun,
		     void **task_args,
		     const size_t count)
{
	task_queue_init(queue);

	queue->head = nodes;
	queue->last = task_nodes_init_sfma(nodes,
					   task_fun,
					   task_args,
					   count);
}

inline void
task_queue_init_tasks(struct TaskQueue *const restrict queue,
		      struct TaskNode *const restrict nodes,
		      const struct ProcedureClosure *const restrict tasks,
		      const size_t count)
{
	task_queue_init(queue);

	queue->head = nodes;
	queue->last = task_nodes_init_tasks(nodes,
					    tasks,
					    count);
}


/* LIFO peek
 *─────────────────────────────────────────────────────────────────────────── */
inline void
task_queue_peek(struct TaskQueue *const restrict queue,
		struct TaskNode *restrict *const restrict node_ptr)
{
	*node_ptr = queue->head;
}


/* LIFO push
 *─────────────────────────────────────────────────────────────────────────── */
inline void
task_queue_push_muffle(struct TaskQueue *const restrict queue,
		       struct TaskNode *const restrict node)
{
	mutex_lock_try_catch_open(&queue->lock);

	mutex_lock_muffle(&queue->lock);

	node->next = NULL;
	node->prev = queue->last;

	if (queue->last == NULL) {
		queue->head = node;
		queue->last = node;

		thread_cond_signal_muffle(&queue->node_ready);
	} else {
		queue->last->next = node;
		queue->last	  = node;
	}

	mutex_unlock_muffle(&queue->lock);

	mutex_lock_try_catch_close();
}


inline void
task_queue_push_handle_cl(struct TaskQueue *const restrict queue,
			  struct TaskNode *const restrict node,
			  const struct HandlerClosure *const restrict fail_cl)
{
	mutex_lock_try_catch_open(&queue->lock);

	mutex_lock_handle_cl(&queue->lock,
			     fail_cl);

	node->next = NULL;
	node->prev = queue->last;

	if (queue->last == NULL) {
		queue->head = node;
		queue->last = node;

		thread_cond_signal_handle_cl(&queue->node_ready,
					     fail_cl);
	} else {
		queue->last->next = node;
		queue->last	  = node;
	}

	mutex_unlock_handle_cl(&queue->lock,
			       fail_cl);

	mutex_lock_try_catch_close();
}


/* LIFO pop
 *─────────────────────────────────────────────────────────────────────────── */
inline void
task_queue_pop_muffle(struct TaskQueue *const restrict queue,
			struct TaskNode *restrict *const restrict node_ptr)
{
	mutex_lock_try_catch_open(&queue->lock);

	mutex_lock_muffle(&queue->lock);

	while (queue->head == NULL)
		thread_cond_await_muffle(&queue->node_ready,
					 &queue->lock);

	/* more than one node may be dumped into queue atomically, must check
	 * if queue will be empty even after popping a fresh head */

	*node_ptr   = queue->head;
	queue->head = (*node_ptr)->next;

	if (queue->head == NULL) {
		queue->last = NULL;

		thread_cond_signal_muffle(&queue->empty);
	} else {
		queue->head->prev = NULL;
	}

	mutex_unlock_muffle(&queue->lock);

	mutex_lock_try_catch_close();
}

inline void
task_queue_pop_handle_cl(struct TaskQueue *const restrict queue,
			 struct TaskNode *restrict *const restrict node_ptr,
			 const struct HandlerClosure *const restrict fail_cl)
{
	mutex_lock_try_catch_open(&queue->lock);

	mutex_lock_handle_cl(&queue->lock,
			     fail_cl);

	while (queue->head == NULL)
		thread_cond_await_handle_cl(&queue->node_ready,
					    &queue->lock,
					    fail_cl);

	/* more than one node may be dumped into queue atomically, must check
	 * if queue will be empty even after popping a fresh head */

	*node_ptr   = queue->head;
	queue->head = (*node_ptr)->next;

	if (queue->head == NULL) {
		queue->last = NULL;

		thread_cond_signal_handle_cl(&queue->empty,
					     fail_cl);
	} else {
		queue->head->prev = NULL;
	}

	mutex_unlock_handle_cl(&queue->lock,
			       fail_cl);

	mutex_lock_try_catch_close();
}


/* random access delete
 *─────────────────────────────────────────────────────────────────────────── */
inline void
task_queue_remove_muffle(struct TaskQueue *const restrict queue,
			 struct TaskNode *const restrict node)
{
	mutex_lock_try_catch_open(&queue->lock);

	mutex_lock_muffle(&queue->lock);

	if (node->prev == NULL) {
		if (node->next == NULL) {
			queue->head = NULL;
			queue->last = NULL;

			thread_cond_signal_muffle(&queue->empty);
		} else {
			queue->head	  = node->next;
			queue->head->prev = NULL;
		}
	} else {
		node->prev->next = node->next;

		if (node->next == NULL)
			queue->last	 = node->prev;
		else
			node->next->prev = node->prev;
	}

	mutex_unlock_muffle(&queue->lock);

	mutex_lock_try_catch_close();
}

inline void
task_queue_remove_handle_cl(struct TaskQueue *const restrict queue,
			    struct TaskNode *const restrict node,
			    const struct HandlerClosure *const restrict fail_cl)
{
	mutex_lock_try_catch_open(&queue->lock);

	mutex_lock_handle_cl(&queue->lock,
			     fail_cl);

	if (node->prev == NULL) {
		if (node->next == NULL) {
			queue->head = NULL;
			queue->last = NULL;

			thread_cond_signal_handle_cl(&queue->empty,
						     fail_cl);
		} else {
			node->next->prev = NULL;
			queue->head	 = node->next;
		}
	} else {
		node->prev->next = node->next;

		if (node->next == NULL)
			queue->last	 = node->prev;
		else
			node->next->prev = node->prev;
	}

	mutex_unlock_handle_cl(&queue->lock,
			       fail_cl);

	mutex_lock_try_catch_close();
}

/* atomically pop head from queue1, point node at it, then push into queue2
 *─────────────────────────────────────────────────────────────────────────── */
inline void
task_queue_pop_push_muffle(struct TaskQueue *const restrict queue1,
			   struct TaskQueue *const restrict queue2,
			   struct TaskNode *restrict *const restrict node_ptr)
{
	struct TaskNode *restrict node;

	mutex_lock_try_catch_open(&queue1->lock);

	mutex_lock_muffle(&queue1->lock);

	while (queue1->head == NULL)
		thread_cond_await_muffle(&queue1->node_ready,
					 &queue1->lock);

	node = queue1->head;

	queue1->head = node->next;

	if (queue1->head == NULL) {
		queue1->last = NULL;

		thread_cond_signal_muffle(&queue1->empty);
	} else {
		queue1->head->prev = NULL;

		node->next = NULL;
	}

	mutex_lock_try_catch_open(&queue2->lock);

	mutex_lock_muffle(&queue2->lock);

	node->prev = queue2->last;

	if (queue2->last == NULL) {
		queue2->head   = node;
		queue2->last   = node;

		thread_cond_signal_muffle(&queue2->node_ready);
	} else {
		queue2->last->next = node;
		queue2->last	   = node;
	}

	*node_ptr = node;

	mutex_unlock_muffle(&queue2->lock);

	mutex_lock_try_catch_close();

	mutex_unlock_muffle(&queue1->lock);

	mutex_lock_try_catch_close();
}

inline void
task_queue_pop_push_handle_cl(struct TaskQueue *const restrict queue1,
			      struct TaskQueue *const restrict queue2,
			      struct TaskNode *restrict *const restrict node_ptr,
			      const struct HandlerClosure *const restrict fail_cl)
{
	struct TaskNode *restrict node;

	mutex_lock_try_catch_open(&queue1->lock);

	mutex_lock_handle_cl(&queue1->lock,
			     fail_cl);

	while (queue1->head == NULL)
		thread_cond_await_handle_cl(&queue1->node_ready,
					    &queue1->lock,
					    fail_cl);

	node = queue1->head;

	queue1->head = node->next;

	if (queue1->head == NULL) {
		queue1->last = NULL;

		thread_cond_signal_handle_cl(&queue1->empty,
					     fail_cl);
	} else {
		queue1->head->prev = NULL;

		node->next = NULL;
	}

	mutex_lock_try_catch_open(&queue2->lock);

	mutex_lock_handle_cl(&queue2->lock,
			     fail_cl);

	node->prev = queue2->last;

	if (queue2->last == NULL) {
		queue2->head   = node;
		queue2->last   = node;

		thread_cond_signal_handle_cl(&queue2->node_ready,
					     fail_cl);
	} else {
		queue2->last->next = node;
		queue2->last	   = node;
	}

	*node_ptr = node;

	mutex_unlock_handle_cl(&queue2->lock,
			       fail_cl);

	mutex_lock_try_catch_close();

	mutex_unlock_handle_cl(&queue1->lock,
			       fail_cl);

	mutex_lock_try_catch_close();
}


/* block until emptied
 *─────────────────────────────────────────────────────────────────────────── */
inline void
task_queue_await_empty_muffle(struct TaskQueue *const restrict queue)
{
	mutex_lock_try_catch_open(&queue->lock);

	mutex_lock_muffle(&queue->lock);

	while (queue->head != NULL)
		thread_cond_await_muffle(&queue->empty,
					 &queue->lock);

	mutex_unlock_muffle(&queue->lock);

	mutex_lock_try_catch_close();
}

inline void
task_queue_await_empty_handle_cl(struct TaskQueue *const restrict queue,
				 const struct HandlerClosure *const restrict fail_cl)
{
	mutex_lock_try_catch_open(&queue->lock);

	mutex_lock_handle_cl(&queue->lock,
			     fail_cl);

	while (queue->head != NULL)
		thread_cond_await_handle_cl(&queue->empty,
					    &queue->lock,
					    fail_cl);

	mutex_unlock_handle_cl(&queue->lock,
			       fail_cl);

	mutex_lock_try_catch_close();
}

/* clear nodes
 *─────────────────────────────────────────────────────────────────────────── */
inline void
task_queue_clear_muffle(struct TaskQueue *const restrict queue)
{
	mutex_lock_try_catch_open(&queue->lock);

	mutex_lock_muffle(&queue->lock);

	/* do nothing if queue is empty */
	if (queue->head != NULL) {

		queue->head = NULL;
		queue->last = NULL;

		thread_cond_signal_muffle(&queue->empty);
	}

	mutex_unlock_muffle(&queue->lock);

	mutex_lock_try_catch_close();
}

inline void
task_queue_clear_handle_cl(struct TaskQueue *const restrict queue,
			     const struct HandlerClosure *const restrict fail_cl)

{
	mutex_lock_try_catch_open(&queue->lock);

	mutex_lock_handle_cl(&queue->lock,
			     fail_cl);

	/* do nothing if queue is empty */
	if (queue->head != NULL) {

		queue->head = NULL;
		queue->last = NULL;

		thread_cond_signal_handle_cl(&queue->empty,
					     fail_cl);
	}

	mutex_unlock_handle_cl(&queue->lock,
			       fail_cl);

	mutex_lock_try_catch_close();
}


/* transfer all nodes from queue1 to queue2
 *─────────────────────────────────────────────────────────────────────────── */
inline void
task_queue_transfer_all_muffle(struct TaskQueue *const restrict queue1,
			       struct TaskQueue *const restrict queue2)
{
	mutex_lock_try_catch_open(&queue1->lock);

	mutex_lock_muffle(&queue1->lock);

	/* do nothing if queue1 is empty */
	if (queue1->head != NULL) {

		mutex_lock_try_catch_open(&queue2->lock);

		mutex_lock_muffle(&queue2->lock);

		if (queue2->last == NULL) {
			/* transfer_all head and last pointers, signal node_ready */
			queue2->head = queue1->head;
			queue2->last = queue1->last;

			thread_cond_signal_muffle(&queue2->node_ready);
		} else {
			/* concat queues */
			queue1->head->prev = queue2->last;
			queue2->last->next = queue1->head;
		}

		mutex_unlock_muffle(&queue2->lock);

		mutex_lock_try_catch_close();

		/* clear queue1, signal empty */
		queue1->head = NULL;
		queue1->last = NULL;

		thread_cond_signal_muffle(&queue1->empty);
	}

	mutex_unlock_muffle(&queue1->lock);

	mutex_lock_try_catch_close();
}

inline void
task_queue_transfer_all_handle_cl(struct TaskQueue *const restrict queue1,
				  struct TaskQueue *const restrict queue2,
				  const struct HandlerClosure *const restrict fail_cl)
{
	mutex_lock_try_catch_open(&queue1->lock);

	mutex_lock_handle_cl(&queue1->lock,
			     fail_cl);

	/* do nothing if queue1 is empty */
	if (queue1->head != NULL) {

		mutex_lock_try_catch_open(&queue2->lock);

		mutex_lock_handle_cl(&queue2->lock,
				     fail_cl);

		if (queue2->last == NULL) {
			/* transfer_all head and last pointers, signal node_ready */
			queue2->head = queue1->head;
			queue2->last = queue1->last;

			thread_cond_signal_handle_cl(&queue2->node_ready,
						     fail_cl);
		} else {
			/* concat queues */
			queue1->head->prev = queue2->last;
			queue2->last->next = queue1->head;
		}

		mutex_unlock_handle_cl(&queue2->lock,
				       fail_cl);

		mutex_lock_try_catch_close();

		/* clear queue1, signal empty */
		queue1->head = NULL;
		queue1->last = NULL;

		thread_cond_signal_handle_cl(&queue1->empty,
					     fail_cl);
	}

	mutex_unlock_handle_cl(&queue1->lock,
			       fail_cl);

	mutex_lock_try_catch_close();
}


/* load queue with 'nodes' from 'store' (queue is empty, store is not empty)
 *─────────────────────────────────────────────────────────────────────────── */
inline void
task_queue_reload_muffle(struct TaskQueue *const restrict queue,
			 struct TaskStore *const restrict store)
{
	mutex_lock_try_catch_open(&queue->lock);

	mutex_lock_muffle(&queue->lock);

	queue->head = store->head;
	queue->last = store->last;

	thread_cond_signal_muffle(&queue->node_ready);

	mutex_unlock_muffle(&queue->lock);

	mutex_lock_try_catch_close();
}

inline void
task_queue_reload_handle_cl(struct TaskQueue *const restrict queue,
			    struct TaskStore *const restrict store,
			    const struct HandlerClosure *const restrict fail_cl)
{
	mutex_lock_try_catch_open(&queue->lock);

	mutex_lock_handle_cl(&queue->lock,
			     fail_cl);

	queue->head = store->head;
	queue->last = store->last;

	thread_cond_signal_handle_cl(&queue->node_ready,
				     fail_cl);

	mutex_unlock_handle_cl(&queue->lock,
			       fail_cl);

	mutex_lock_try_catch_close();
}

/* locked/unsignaled push
 *─────────────────────────────────────────────────────────────────────────── */
inline void
task_queue_push_quiet_muffle(struct TaskQueue *const restrict queue,
			     struct TaskNode *const restrict node)
{
	mutex_lock_try_catch_open(&queue->lock);

	mutex_lock_muffle(&queue->lock);

	node->next = NULL;
	node->prev = queue->last;

	if (queue->last == NULL) {
		queue->head = node;
		queue->last = node;
	} else {
		queue->last->next = node;
		queue->last	  = node;
	}

	mutex_unlock_muffle(&queue->lock);

	mutex_lock_try_catch_close();
}

inline void
task_queue_push_quiet_handle_cl(struct TaskQueue *const restrict queue,
				struct TaskNode *const restrict node,
				const struct HandlerClosure *const restrict fail_cl)
{
	mutex_lock_try_catch_open(&queue->lock);

	mutex_lock_handle_cl(&queue->lock,
			     fail_cl);

	node->next = NULL;
	node->prev = queue->last;

	if (queue->last == NULL) {
		queue->head = node;
		queue->last = node;
	} else {
		queue->last->next = node;
		queue->last	  = node;
	}

	mutex_unlock_handle_cl(&queue->lock,
			       fail_cl);

	mutex_lock_try_catch_close();
}

/* retrieve nodes
 *─────────────────────────────────────────────────────────────────────────── */
/* unlocked/unsignaled */
inline void
task_queue_retreive_cold_quiet(struct TaskQueue *const restrict queue,
			       struct TaskStore *const restrict store)
{
	store->head = queue->head;
	queue->head = NULL;
	store->last = queue->last;
	queue->last = NULL;
}

/* locked/unsignaled */
inline void
task_queue_retreive_hot_quiet_muffle(struct TaskQueue *const restrict queue,
				     struct TaskStore *const restrict store)
{
	mutex_lock_try_catch_open(&queue->lock);

	mutex_lock_muffle(&queue->lock);

	task_queue_retreive_cold_quiet(queue,
				       store);

	mutex_unlock_muffle(&queue->lock);

	mutex_lock_try_catch_close();
}

inline void
task_queue_retreive_hot_quiet_handle_cl(struct TaskQueue *const restrict queue,
					struct TaskStore *const restrict store,
					const struct HandlerClosure *const restrict fail_cl)
{
	mutex_lock_try_catch_open(&queue->lock);

	mutex_lock_handle_cl(&queue->lock,
			     fail_cl);

	task_queue_retreive_cold_quiet(queue,
				       store);

	mutex_unlock_handle_cl(&queue->lock,
			       fail_cl);

	mutex_lock_try_catch_close();
}

/* swap node stores
 *─────────────────────────────────────────────────────────────────────────── */
inline void
task_store_swap(struct TaskStore *const restrict store1,
		struct TaskStore *const restrict store2)
{
	struct TaskNode *restrict swap;

	swap = store1->head;
	store1->head = store2->head;
	store2->head = swap;

	swap = store1->last;
	store1->last = store2->last;
	store2->last = swap;
}

#endif /* ifndef MYSQL_SEED_THREAD_THREAD_QUEUE_H_ */
