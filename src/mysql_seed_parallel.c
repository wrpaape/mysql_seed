#include "mysql_seed_parallel.h"

/* helper macros
 *─────────────────────────────────────────────────────────────────────────── */
#define SEED_WORKER_LINK(WORKER, PREV, NEXT)		\
WORKER->PREV = PREV;					\
WORKER->NEXT = NEXT


const SeedMutex seed_lock_prototype = SEED_LOCK_INITIALIZER;

struct SeedWorkerSupervisor supervisor = {
	.idle   = { .lock = SEED_LOCK_INITIALIZER, .head = NULL, .last = NULL },
	.active = { .lock = SEED_LOCK_INITIALIZER, .head = NULL, .last = NULL },
	.map = {
		.lock	 = SEED_LOCK_INITIALIZER,
		.workers = {
			[0u] = { .key  = 0u, .prev = NULL, .next = NULL },
			[1u] = { .key  = 1u, .prev = NULL, .next = NULL },
			[2u] = { .key  = 2u, .prev = NULL, .next = NULL },
			[3u] = { .key  = 3u, .prev = NULL, .next = NULL }
		}
	}
};


/* SeedMutex operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
seed_mutex_init(SeedMutex *const restrict lock);

extern inline bool
seed_mutex_lock(SeedMutex *const lock,
		char *const *restrict message_ptr);

extern inline bool
seed_mutex_unlock(SeedMutex *const lock,
		  const char *restrict *const restrict message_ptr);

extern inline void
seed_mutex_handle_lock(SeedMutex *const restrict lock);

extern inline void
seed_mutex_handle_unlock(SeedMutex *const restrict lock);


/* SeedWorkerSupervisor operations
 *─────────────────────────────────────────────────────────────────────────── */
void
seed_worker_supervisor_init(void)
{
	struct SeedWorker *const restrict worker0 = &supervisor.map.workers[0u];
	struct SeedWorker *const restrict worker1 = worker0 + 1l;
	struct SeedWorker *const restrict worker2 = worker1 + 1l;
	struct SeedWorker *const restrict worker3 = worker2 + 1l;

	SEED_WORKER_LINK(worker0, NULL,    worker1);
	SEED_WORKER_LINK(worker1, worker0, worker2);
	SEED_WORKER_LINK(worker2, worker1, worker3);
	SEED_WORKER_LINK(worker3, worker2, NULL);


	supervisor.idle.last = worker3;
	supervisor.idle.head = worker0;
}

void
worker_supervisor_exit(const char *restrict failure)
{
	/* TODO */
}


/* SeedWorkerQueue LIFO operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
worker_queue_push(struct SeedWorkerQueue *const restrict queue,
		  struct SeedWorker *const restrict worker);

extern inline struct SeedWorker *
worker_queue_pop(struct SeedWorkerQueue *const restrict queue);
