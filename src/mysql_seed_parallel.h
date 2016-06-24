#ifndef MYSQL_SEED_MYSQL_SEED_PARALLEL_H_
#define MYSQL_SEED_MYSQL_SEED_PARALLEL_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <pthread.h>	/* pthread API */
#include <errno.h>	/* error codes, errno */
#include <string.h>	/* memcpy */
#include <stdbool.h>	/* bool */

#define SEED_WORKERS_MAX 4u

/* typedefs
 *─────────────────────────────────────────────────────────────────────────── */
typedef pthread_mutex_t SeedMutex;
typedef pthread_t SeedThread;


struct SeedWorker {
	SeedThread thread;
	unsigned int key;
	const struct SeedWorker *prev;
	const struct SeedWorker *next;
};

struct SeedWorkerQueue {
	SeedMutex lock;
	const struct SeedWorker *restrict head;
	const struct SeedWorker *restrict last;
};

struct SeedWorkerMap {
	SeedMutex lock;
	struct SeedWorker workers[SEED_WORKERS_MAX];
};

struct SeedWorkerSupervisor {
	struct SeedWorkerQueue idle;
	struct SeedWorkerQueue active;
	struct SeedWorkerMap map;
};


/* helper macros
 *─────────────────────────────────────────────────────────────────────────── */
#define SEED_LOCK_INITIALIZER PTHREAD_MUTEX_INITIALIZER


/* global variables
 *─────────────────────────────────────────────────────────────────────────── */
extern const SeedMutex seed_lock_prototype;

extern SeedWorkerSupervisor supervisor;




/* SeedMutex operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
seed_mutex_init(SeedMutex *const restrict lock)
{
	memcpy(lock,
	       &seed_lock_prototype,
	       sizeof(seed_lock_prototype));
}

inline bool
seed_mutex_lock(SeedMutex *const lock,
		char *restrict *const restrict message_ptr)
{
	switch (pthread_mutex_lock(lock)) {
	case 0:
		return true;

	case EDEADLK:
		*message_ptr = "seed_mutex_lock failure:\n"
			       "A deadlock would occur if the thread blocked "
			       "waiting for SeedMutex 'lock'.";
		return false;

	case EINVAL:
		*message_ptr = "seed_mutex_lock failure:\n"
			       "\tThe value specified by SeedMutex 'lock' is "
			       "invalid.\n";
		return false;


	default:
		*message_ptr = "seed_mutex_lock failure:\n"
			       "unknown\n";
		return false;
	}
}

inline bool
seed_mutex_unlock(SeedMutex *const lock,
		  const char *restrict *const restrict message_ptr)
{
	switch (pthread_mutex_unlock(lock)) {
	case 0:
		return true;

	case EINVAL:
		*message_ptr = "seed_mutex_unlock failure:\n"
			       "\tThe value specified by SeedMutex 'lock' is "
			       "invalid.\n";
		return false;

	case EPERM:
		*message_ptr = "seed_mutex_unlock failure:\n"
			       "\tThe current thread does not hold a lock on "
			       "SeedMutex 'lock'.\n";
		return false;

	default:
		*message_ptr = "seed_mutex_unlock failure:\n"
			       "unknown\n";
		return false;
	}
}

inline void
seed_mutex_handle_lock(SeedMutex *const restrict lock)
{
	const char *restrict failure;

	if (!seed_mutex_lock(lock,
			       &failure))
		worker_supervisor_exit(failure);
}

inline void
seed_mutex_handle_unlock(SeedMutex *const restrict lock)
{
	const char *restrict failure;

	if (!seed_mutex_unlock(lock,
			       &failure))
		worker_supervisor_exit(failure);
}


/* SeedWorkerQueue LIFO operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
worker_queue_push(struct SeedWorkerQueue *const restrict queue,
		  struct SeedWorker *const restrict worker)
{
	seed_mutex_handle_lock(queue->lock);	/* exit on lock failure */

	worker->next = NULL;

	if (queue->last == NULL) {
		queue->head  = worker;
		worker->prev = NULL;
		worker->next = NULL;
	} else {
		worker->prev	  = queue->last;
		queue->last->next = worker;
	}

	queue->last = worker;

	seed_mutex_handle_unlock(queue->lock);	/* exit on unlock failure */
}

inline struct SeedWorker *
worker_queue_pop(struct SeedWorkerQueue *const restrict queue)
{
	seed_mutex_handle_lock(queue->lock);	/* exit on lock failure */

	const struct SeedWorker *const restrict worker = queue->head;

	if (worker == NULL)
		return NULL;

	queue->head = worker->next;

	if (queue->head == NULL)
		queue->last = NULL
	else
		queue->head->prev = NULL;

	seed_mutex_handle_unlock(queue->lock);	/* exit on unlock failure */

	return worker;
}


/* SeedWorkerSupervisor operations
 *─────────────────────────────────────────────────────────────────────────── */
void
seed_worker_supervisor_init(void) __attribute__((constructor));

void
worker_supervisor_exit(const char *restrict failure) __attribute__((noreturn));



#endif /* ifndef MYSQL_SEED_MYSQL_SEED_PARALLEL_H_ */
