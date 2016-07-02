#ifndef MYSQL_SEED_THREAD_THREAD_QUEUE_H_
#define MYSQL_SEED_THREAD_THREAD_QUEUE_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "thread/thread_utils.h"	/* threads API */


/* typedefs, struct declarations
 *─────────────────────────────────────────────────────────────────────────── */
struct ThreadQueueNode {
	void *payload;
	struct QueueNode *prev;
	struct QueueNode *next;
};

struct ThreadQueue {
	struct ThreadQueueNode *restrict head;
	struct ThreadQueueNode *restrict last;
	const struct *restrict ThreadHandlerClosure handle_fail;
	Mutex lock;
	ThreadCond node_ready;
	ThreadCond empty;
};

/* initialize
 *─────────────────────────────────────────────────────────────────────────── */
inline void
thread_queue_init(struct ThreadQueue *const restrict queue,
		  const struct *const restrict ThreadHandlerClosure handle_fail)
{
	mutex_init(&queue->lock);

	thread_cond_init(&queue->node_ready);
	thread_cond_init(&queue->empty);

	queue->handle_fail = handle_fail;
}

inline void
thread_queue_init_empty(struct ThreadQueue *const restrict queue,
			const struct *const restrict ThreadHandlerClosure handle_fail)
{
	thread_queue_init(queue,
			  handle_fail);

	queue->head = NULL;
	queue->last = NULL;
}

inline void
thread_queue_init_populated(struct ThreadQueue *const restrict queue,
			    const struct *const restrict ThreadHandlerClosure handle_fail,
			    struct ThreadQueueNode *restrict nodes,
			    void *restrict payloads,
			    const size_t payload_count,
			    const size_t payload_width)
{
	struct ThreadQueueNode *restrict next;

	thread_queue_init(queue,
			  handle_fail);

	struct ThreadQueueNode *const restrict last = nodes
						    + (payload_count - 1l);
	last->next  = NULL;
	queue->last = last;

	nodes->prev = NULL;
	queue->head = nodes;


	while (1) {
		nodes->payload = payloads;

		if (nodes == last)
			return;

		next = nodes + 1l;

		nodes->next = next;
		next->prev  = nodes;

		nodes = next;

		payloads = ((char *restrict) payloads) + payload_width;
	}
}


/* LIFO push
 *─────────────────────────────────────────────────────────────────────────── */
inline void
thread_queue_push(struct ThreadQueue *const restrict queue,
		  struct ThreadQueueNode *const restrict *restrict node)
{
	mutex_lock_handle_cl(&queue->lock,
			     queue->handle_fail);

	node->next = NULL;

	if (queue->last == NULL) {
		node->prev  = NULL;
		queue->head = node;
		queue->last = node;

		thread_cond_signal_handle_cl(&queue->node_ready,
					     queue->handle_fail);
	} else {
		node->prev	  = queue->last;
		queue->last->next = node;
		queue->last	  = node;
	}

	mutex_unlock_handle_cl(&queue->lock,
			       queue->handle_fail);
}

/* LIFO pop
 *─────────────────────────────────────────────────────────────────────────── */
inline void
thread_queue_pop(struct ThreadQueue *const restrict queue,
		 struct ThreadQueueNode *const restrict *restrict node)
{
	mutex_lock_handle_cl(&queue->lock,
			     queue->handle_fail);

	if (queue->head == NULL) {
		do {
			thread_cond_await_handle_cl(&queue->node_ready,
						    &queue->lock,
						    queue->handle_fail);
		} while (queue->head == NULL);

		*node = queue->head;

		queue->head = NULL;
		queue->last = NULL;

		thread_cond_signal_handle_cl(&queue->empty,
					     queue->handle_fail);
	} else {
		*node = queue->head;

		queue->head = (*node)->next;

		if (queue->head == NULL) {
			queue->last = NULL;

			thread_cond_signal_handle_cl(&queue->empty,
						     queue->handle_fail);
		} else {
			queue->head->prev = NULL;
		}
	}

	mutex_unlock_handle_cl(&queue->lock,
			       queue->handle_fail);
}


/* random access delete
 *─────────────────────────────────────────────────────────────────────────── */
inline void
thread_queue_remove(struct ThreadQueue *const restrict queue,
		    struct ThreadQueueNode *const restrict *restrict node)
{
	mutex_lock_handle_cl(&queue->lock,
			     queue->handle_fail);

	if (node->prev == NULL) {
		if (node->next == NULL) {
			queue->head = NULL;
			queue->last = NULL;

			thread_cond_signal_handle_cl(&queue->empty,
						     queue->handle_fail);
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
			       queue->handle_fail);
}

/* block until emptied
 *─────────────────────────────────────────────────────────────────────────── */
inline void
thread_queue_await_empty(struct ThreadQueue *const restrict queue)
{
	if (queue->head == NULL)
		return;

	mutex_lock_handle_cl(&queue->lock,
			     queue->handle_fail);

	do {
		thread_cond_await_handle_cl(&queue->empty,
					    &queue->lock,
					    queue->handle_fail);
	} while (queue->head != NULL);

	mutex_unlock_handle_cl(&queue->lock,
			       queue->handle_fail);
}

#endif /* ifndef MYSQL_SEED_THREAD_THREAD_QUEUE_H_ */
