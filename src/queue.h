#ifndef MYSQL_SEED_LINK_NODE_QUEUE_H_
#define MYSQL_SEED_LINK_NODE_QUEUE_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "link_node.h"			/* struct LinkNode */


/* declarations
 *─────────────────────────────────────────────────────────────────────────── */
/* implemented as singly linked-list with a pointer to last element's tail */
struct LinkNodeQueue {
	struct LinkNode *head;
	struct LinkNode **last;
};


/* top-level functions
 *─────────────────────────────────────────────────────────────────────────── */
/* basic LIFO implementation */
inline void
link_node_queue_init(struct LinkNodeQueue *const restrict queue,
		     struct LinkNode *const restrict list)
{
	if (list == NULL) {
		queue->head = NULL;
		queue->last = NULL;
		return;
	}

	queue->head = list;
}

inline void
link_node_queue_push(struct LinkNodeQueue *const restrict queue,
		     struct LinkNode *const restrict node)
{
	node->link = NULL;

	if (queue->last == NULL) {
		queue->head = node;
	} else {
		*(queue->last) = node;
	}

	queue->last = &(node->link);
}

inline void *
link_node_queue_peek(const struct LinkNodeQueue *const restrict queue)
{
	return (queue->head == NULL) ? NULL : queue->head->data;
}

inline void *
link_node_queue_pop(struct LinkNodeQueue *const restrict queue)
{
	struct LinkNode *restrict node = queue->head;

	if (node == NULL)
		return NULL;

	void *data = node->data;

	queue->head = node->link;

	free(node);

	return data;
}

inline void
link_node_queue_clear(struct LinkNodeQueue *const restrict queue)
{
	while (link_node_queue_pop(queue) != NULL);
}

inline void
link_node_queue_destroy(struct LinkNodeQueue *restrict queue)
{
	link_node_queue_clear(queue);
	free(queue);
}

#endif /* ifndef MYSQL_SEED_LINK_NODE_QUEUE_H_ */
