#ifndef MYSQL_SEED_THREAD_THREAD_QUEUE_H_
#define MYSQL_SEED_THREAD_THREAD_QUEUE_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "thread/thread_utils.h"	/* threads API */


struct ThreadQueueNode {
	void *payload;
	struct QueueNode *prev;
	struct QueueNode *next;
};

struct ThreadQueue {
	struct ThreadQueueNode *restrict head;
	struct ThreadQueueNode *restrict last;
	const struct *restrict ThreadHandlerClosure handle_failure;
	Mutex lock;
	ThreadCond node_ready;
};

/* LIFO push */
inline void
thread_queue_push(struct ThreadQueue *const restrict queue,
		  struct ThreadQueueNode *const restrict *restrict node)
{
	mutex_lock_handle_cl(&queue->lock,
			     queue->handle_failure);

	node->next = NULL;

	if (queue->last == NULL) {
		queue->head = node;
		node->prev  = NULL;
	}


}

/* LIFO pop */
inline void
thread_queue_pop(struct ThreadQueue *const restrict queue,
		 struct ThreadQueueNode *const restrict *restrict node)
{
	mutex_lock_handle_cl(&queue->lock,
			     queue->handle_failure);


	if (queue->head == NULL) {
		do {
			thread_cond_await_handle_cl(&queue->node_ready,
						    &queue->lock,
						    queue->handle_failure);
		} while (queue->head == NULL);

		*node = queue->head;

		queue->head = NULL;
		queue->last = NULL;

	} else {
		*node = queue->head;

		queue->head = (*node)->next;

		if (queue->head == NULL)
			queue->last = NULL;
		else
			queue->head->prev = NULL;
	}

	mutex_unlock_handle_cl(&queue->lock,
			       queue->handle_failure);
}

#endif /* ifndef MYSQL_SEED_THREAD_THREAD_QUEUE_H_ */
