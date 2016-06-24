#include "link_node_queue.h"

/* basic LIFO queue interface */

extern inline void
link_node_queue_init(struct LinkNodeQueue *const restrict queue);


extern inline void
link_node_queue_push(struct LinkNodeQueue *const restrict queue,
		     struct LinkNode *const restrict node);

extern inline void *
link_node_queue_peek(const struct LinkNodeQueue *const restrict queue);

extern inline void *
link_node_queue_pop(struct LinkNodeQueue *const restrict queue);

inline void
link_node_queue_clear(struct LinkNodeQueue *const restrict queue);

extern inline void
queue_destroy(struct LinkNodeQueue *restrict queue);
