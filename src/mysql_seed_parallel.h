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
	struct SeedWorker *prev;
	struct SeedWorker *next;
};

struct SeedWorkerQueue {
	SeedMutex lock;
	struct SeedWorker *head;
	struct SeedWorker **last;
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


/* initialize
 *─────────────────────────────────────────────────────────────────────────── */
void
seed_worker_supervisor_init(void) __attribute__((constructor));




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
		  char *restrict *const restrict message_ptr)
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

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_PARALLEL_H_ */
