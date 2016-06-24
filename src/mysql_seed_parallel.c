#include "mysql_seed_parallel.h"

/* helper macros
 *─────────────────────────────────────────────────────────────────────────── */
#define SEED_WORKER_LINK(WORKER, PREV, NEXT)		\
WORKER->PREV = PREV;					\
WORKER->NEXT = NEXT


const SeedMutex seed_lock_prototype = SEED_MUTEX_INITIALIZER;

struct SeedWorkerSupervisor supervisor = {
	.dead = { .lock = SEED_MUTEX_INITIALIZER, .head = NULL, .last = NULL },
	.live = { .lock = SEED_MUTEX_INITIALIZER, .head = NULL, .last = NULL },
	.map = {
		.lock	 = SEED_MUTEX_INITIALIZER,
		.workers = {
			[ 0u] = { .id  =  0u, .prev = NULL, .next = NULL },
			[ 1u] = { .id  =  1u, .prev = NULL, .next = NULL },
			[ 2u] = { .id  =  2u, .prev = NULL, .next = NULL },
			[ 3u] = { .id  =  3u, .prev = NULL, .next = NULL },
			[ 4u] = { .id  =  4u, .prev = NULL, .next = NULL },
			[ 5u] = { .id  =  5u, .prev = NULL, .next = NULL },
			[ 6u] = { .id  =  6u, .prev = NULL, .next = NULL },
			[ 7u] = { .id  =  7u, .prev = NULL, .next = NULL },
			[ 8u] = { .id  =  8u, .prev = NULL, .next = NULL },
			[ 9u] = { .id  =  9u, .prev = NULL, .next = NULL },
			[10u] = { .id  = 10u, .prev = NULL, .next = NULL },
			[11u] = { .id  = 11u, .prev = NULL, .next = NULL },
			[12u] = { .id  = 12u, .prev = NULL, .next = NULL },
			[13u] = { .id  = 13u, .prev = NULL, .next = NULL },
			[14u] = { .id  = 14u, .prev = NULL, .next = NULL },
			[15u] = { .id  = 15u, .prev = NULL, .next = NULL }
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
	struct SeedWorker *const restrict worker0  = &supervisor.map.workers[0];
	struct SeedWorker *const restrict worker1  = worker0  + 1l;
	struct SeedWorker *const restrict worker2  = worker1  + 1l;
	struct SeedWorker *const restrict worker3  = worker2  + 1l;
	struct SeedWorker *const restrict worker4  = worker3  + 1l;
	struct SeedWorker *const restrict worker5  = worker4  + 1l;
	struct SeedWorker *const restrict worker6  = worker5  + 1l;
	struct SeedWorker *const restrict worker7  = worker6  + 1l;
	struct SeedWorker *const restrict worker8  = worker7  + 1l;
	struct SeedWorker *const restrict worker9  = worker8  + 1l;
	struct SeedWorker *const restrict worker10 = worker9  + 1l;
	struct SeedWorker *const restrict worker11 = worker10 + 1l;
	struct SeedWorker *const restrict worker12 = worker11 + 1l;
	struct SeedWorker *const restrict worker13 = worker12 + 1l;
	struct SeedWorker *const restrict worker14 = worker13 + 1l;
	struct SeedWorker *const restrict worker15 = worker14 + 1l;

	SEED_WORKER_LINK(worker0,  NULL,     worker1);
	SEED_WORKER_LINK(worker1,  worker0,  worker2);
	SEED_WORKER_LINK(worker2,  worker1,  worker3);
	SEED_WORKER_LINK(worker3,  worker2,  worker4);
	SEED_WORKER_LINK(worker4,  worker3,  worker5);
	SEED_WORKER_LINK(worker5,  worker4,  worker6);
	SEED_WORKER_LINK(worker6,  worker5,  worker7);
	SEED_WORKER_LINK(worker7,  worker6,  worker8);
	SEED_WORKER_LINK(worker8,  worker7,  worker9);
	SEED_WORKER_LINK(worker9,  worker8,  worker10);
	SEED_WORKER_LINK(worker10, worker9,  worker11);
	SEED_WORKER_LINK(worker11, worker10, worker12);
	SEED_WORKER_LINK(worker12, worker11, worker13);
	SEED_WORKER_LINK(worker13, worker12, worker14);
	SEED_WORKER_LINK(worker14, worker13, worker15);
	SEED_WORKER_LINK(worker15, worker14, NULL);

	supervisor.idle.head = worker0;
	supervisor.idle.last = worker15;
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
