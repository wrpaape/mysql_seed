#ifndef MYSQL_SEED_MYSQL_SEED_PARALLEL_H_
#define MYSQL_SEED_MYSQL_SEED_PARALLEL_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <pthread.h>		/* threads API */
#include <errno.h>		/* error codes, errno */
#include <limits.h>		/* PTHREAD_THREADS_MAX */
#include <string.h>		/* memcpy */
#include <stdbool.h>		/* bool */
#include "mysql_seed_exit.h"	/* SeedExitSpec, string helper macros */

#define SEED_WORKERS_MAX 16u

#ifdef PTHREAD_THREADS_MAX
#	define SEED_THREADS_MAX PTHREAD_THREADS_MAX
#	define SEED_THREADS_MAX_STRING EXPAND_STRINGIFY(PTHREAD_THREADS_MAX)
#endif	/* ifdef PTHREADS_THREADS_MAX */

#ifdef PTHREAD_KEYS_MAX
#	define SEED_THREAD_KEYS_MAX PTHREAD_KEYS_MAX
#	define SEED_THREAD_KEYS_MAX_STRING EXPAND_STRINGIFY(PTHREAD_KEYS_MAX)
#endif	/* ifdef PTHREADS_THREADS_MAX */

/* typedefs
 *─────────────────────────────────────────────────────────────────────────── */
typedef pthread_mutex_t SeedMutex;

typedef pthread_cond_t SeedCondition;

typedef pthread_t SeedThread;

typedef pthread_key_t SeedKey;

typedef unsigned int SeedWorkerID;

typedef void *
SeedWorkerRoutine(void *);

typedef void
SeedWorkerHandler(void *);

struct SeedWorker {
	SeedWorkerID id;
	SeedKey key;
	SeedThread thread;
	SeedWorkerRoutine *routine;
	void *arg;
	struct SeedWorker *prev;
	struct SeedWorker *next;
};

struct SeedWorkerQueue {
	SeedMutex lock;
	struct SeedWorker *restrict head;
	struct SeedWorker *restrict last;
};


struct SeedSupervisor {
	struct SeedWorkerQueue dead;
	struct SeedWorkerQueue live;
	struct SeedWorker workers[SEED_WORKERS_MAX];
};


/* global variables
 *─────────────────────────────────────────────────────────────────────────── */
extern const SeedMutex seed_lock_prototype;

extern struct SeedSupervisor supervisor;


/* low-level threads API access
 *─────────────────────────────────────────────────────────────────────────── */
#define seed_thread_create_implementation(THREAD, ROUTINE, ARG)		\
pthread_create(THREAD, NULL, ROUTINE, ARG)

#define seed_thread_cancel_implementation(THREAD)			\
pthread_cancel(THREAD)

#define seed_key_create_implementation(KEY, WORKER_HANDLER)	\
pthread_key_create(KEY, WORKER_HANDLER)

#define seed_key_delete_implementation(KEY)			\
pthread_key_delete(KEY)

#define seed_mutex_lock_implementation(MUTEX)				\
pthread_mutex_lock(MUTEX)

#define seed_mutex_unlock_implementation(MUTEX)				\
pthread_mutex_unlock(MUTEX)

#define seed_mutex_init_implementation(MUTEX)				\
memcpy(MUTEX, &seed_lock_prototype, sizeof(seed_lock_prototype))

#define seed_worker_try_catch_open_implementation(CATCH_ROUTINE, ARG)	\
pthread_cleanup_push(CATCH_ROUTINE, ARG)

#define seed_worker_try_catch_close_implementation()			\
pthread_cleanup_pop(0)

#define seed_worker_try_ensure_open_implementation(ENSURE_ROUTINE, ARG)	\
pthread_cleanup_push(ENSURE_ROUTINE, ARG)

#define seed_worker_try_ensure_close_implementation()			\
pthread_cleanup_pop(1)

#define SEED_MUTEX_INITIALIZER		PTHREAD_MUTEX_INITIALIZER

#define SEED_CONDITION_INITIALIZER	PTHREAD_COND_INITIALIZER



/* SeedSupervisor operations
 *─────────────────────────────────────────────────────────────────────────── */
void
seed_supervisor_init(void)
__attribute__((constructor));

void
seed_supervisor_exit(const char *restrict failure)
__attribute__((noreturn));


/* SeedThread operations
 *─────────────────────────────────────────────────────────────────────────── */
inline bool
seed_thread_create(SeedThread *const restrict thread,
		   SeedWorkerRoutine *const routine,
		   void *arg,
		   const char *restrict *const restrict message_ptr)
{
	switch (seed_thread_create_implementation(thread,
						  routine,
						  arg)) {
	case 0:
		return true;

	case EAGAIN:
		*message_ptr = "seed_thread_create failure:\n"
			       "\tThe system lacked the necessary resources to "
			       "create another thread"
#ifdef SEED_THREADS_MAX
			       ", or the system-imposed "
			       "limit on the total number of threads in a "
			       "process, ('SEED_THREADS_MAX' = "
			       SEED_THREADS_MAX_STRING "), would be exceeded"
#endif /* ifdef SEED_THREADS_MAX */
			       ".\n";
		return false;

	default:
		*message_ptr = "seed_thread_create failure:\n"
			       "\tunknown\n";
		return false;
	}
}


inline void
seed_thread_handle_create(SeedThread *const restrict thread,
			  SeedWorkerRoutine *const routine,
			  void *arg)
{
	const char *restrict failure;

	if (!seed_thread_create(thread,
				routine,
				arg,
				&failure))
		seed_supervisor_exit(failure);
}


inline bool
seed_thread_cancel(SeedThread thread,
		   const char *restrict *const restrict message_ptr)
{
	switch (seed_thread_cancel_implementation(thread)) {
	case 0:
		return true;

	case ESRCH:
		*message_ptr = "seed_thread_cancel failure:\n"
			       "\tNo thread could be found corresponding to that "
			       "specified by the given SeedThread 'thread'\n";
		return false;

	default:
		*message_ptr = "seed_thread_cancel failure:\n"
			       "\tunknown\n";
		return false;
	}
}

inline void
seed_thread_handle_cancel(SeedThread thread)
{
	const char *restrict failure;

	if (!seed_thread_cancel(thread,
				&failure))
		seed_supervisor_exit(failure);
}


inline bool
seed_key_create(SeedKey *const key,
		SeedWorkerHandler *const handle,
		const char *restrict *const restrict message_ptr)
{
	switch (seed_key_create_implementation(key,
						      handle)) {
	case 0:
		return true;

	case EAGAIN:
		*message_ptr = "seed_key_create failure:\n"
			       "\tThe system lacked the necessary resources to"
			       " create another thread-specific data key"
#ifdef SEED_THREAD_KEYS_MAX
			       ", or the system-imposed limit on the total "
			       "number of keys per process, ('"
			       "SEED_THREAD_KEYS_MAX' = "
			       SEED_THREAD_KEYS_MAX_STRING "), would be "
			       "exceeded"
#endif /* ifdef SEED_THREAD_KEYS_MAX */
			       ".\n";
		return false;

	case ENOMEM:
		*message_ptr = "seed_key_create failure:\n"
			       "\tInsufficient memory exists to create "
			       "SeedKey, 'key'.\n";
		return false;

	default:
		*message_ptr = "seed_key_create failure:\n"
			       "\tunknown\n";
		return false;
	}
}

inline void
seed_key_handle_create(SeedKey *const key,
		       SeedWorkerHandler *const handle)
{
	const char *restrict failure;

	if (!seed_key_create(key,
			     handle,
			     &failure))
		seed_supervisor_exit(failure);
}

inline bool
seed_key_delete(SeedKey key,
		const char *restrict *const restrict message_ptr)
{
	switch (seed_key_delete_implementation(key)) {
	case 0:
		return true;

	case EINVAL:
		*message_ptr = "seed_key_delete failure:\n"
			       "\tthe value of SeedThread 'key' is invalid.\n";
		return false;

	default:
		*message_ptr = "seed_key_delete failure:\n"
			       "\tunknown\n";
		return false;
	}
}

inline void
seed_key_handle_delete(SeedKey key)
{
	const char *restrict failure;

	if (!seed_key_delete(key,
			     &failure))
		seed_supervisor_exit(failure);
}



/* SeedMutex operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
seed_mutex_init(SeedMutex *const restrict lock)
{
	seed_mutex_init_implementation(lock);
}

inline bool
seed_mutex_lock(SeedMutex *const lock,
		const char *restrict *const restrict message_ptr)
{
	switch (seed_mutex_lock_implementation(lock)) {
	case 0:
		return true;

	case EDEADLK:
		*message_ptr = "seed_mutex_lock failure:\n"
			       "\tA deadlock would occur if the thread blocked "
			       "waiting for SeedMutex 'lock'.";
		return false;

	case EINVAL:
		*message_ptr = "seed_mutex_lock failure:\n"
			       "\tThe value specified by SeedMutex 'lock' is "
			       "invalid.\n";
		return false;


	default:
		*message_ptr = "seed_mutex_lock failure:\n"
			       "\tunknown\n";
		return false;
	}
}

inline bool
seed_mutex_unlock(SeedMutex *const lock,
		  const char *restrict *const restrict message_ptr)
{
	switch (seed_mutex_unlock_implementation(lock)) {
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
			       "\tunknown\n";
		return false;
	}
}

inline void
seed_mutex_handle_lock(SeedMutex *const restrict lock)
{
	const char *restrict failure;

	if (!seed_mutex_lock(lock,
			       &failure))
		seed_supervisor_exit(failure);
}

inline void
seed_mutex_handle_unlock(SeedMutex *const restrict lock)
{
	const char *restrict failure;

	if (!seed_mutex_unlock(lock,
			       &failure))
		seed_supervisor_exit(failure);
}


/* SeedWorkerQueue operations
 *─────────────────────────────────────────────────────────────────────────── */
/* LIFO push */
inline void
worker_queue_push(struct SeedWorkerQueue *const restrict queue,
		  struct SeedWorker *const restrict worker)
{
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
}

inline void
worker_queue_handle_push(struct SeedWorkerQueue *const restrict queue,
			 struct SeedWorker *const restrict worker)
{
	seed_mutex_handle_lock(&queue->lock);	/* exit on lock failure */

	worker_queue_push(queue,
			  worker);

	seed_mutex_handle_unlock(&queue->lock);	/* exit on unlock failure */
}


/* LIFO pop */
inline struct SeedWorker *
worker_queue_pop(struct SeedWorkerQueue *const restrict queue)
{
	struct SeedWorker *const restrict worker = queue->head;

	if (worker == NULL)
		return NULL;

	queue->head = worker->next;

	if (queue->head == NULL)
		queue->last = NULL;
	else
		queue->head->prev = NULL;

	return worker;
}

inline struct SeedWorker *
worker_queue_handle_pop(struct SeedWorkerQueue *const restrict queue)
{
	seed_mutex_handle_lock(&queue->lock);	/* exit on lock failure */

	struct SeedWorker *const restrict worker = worker_queue_pop(queue);

	seed_mutex_handle_unlock(&queue->lock);	/* exit on unlock failure */

	return worker;
}

/* random access delete */
inline void
worker_queue_remove(struct SeedWorkerQueue *const restrict queue,
		    struct SeedWorker *const restrict worker)
{
	if (worker->prev == NULL) {
		if (worker->next == NULL) {
			queue->head = NULL;
			queue->last = NULL;
		} else {
			worker->next->prev = NULL;
			queue->head	   = worker->next;
		}
	} else {
		worker->prev->next = worker->next;

		if (worker->next == NULL)
			queue->last	   = worker->prev;
		else
			worker->next->prev = worker->prev;
	}
}

inline void
worker_queue_handle_remove(struct SeedWorkerQueue *const restrict queue,
			   struct SeedWorker *const restrict worker)
{
	seed_mutex_handle_lock(&queue->lock);	/* exit on lock failure */

	worker_queue_remove(queue,
			    worker);

	seed_mutex_handle_unlock(&queue->lock);	/* exit on unlock failure */
}

/* SeedWorker operations
 *─────────────────────────────────────────────────────────────────────────── */
inline struct SeedWorker *
seed_worker_fetch(const SeedWorkerID id)
{
	return &supervisor.workers[id];
}


/* apply 'ARG' to 'CATCH_ROUTINE' if exit in block */
#define seed_worker_try_catch_open(CATCH_ROUTINE, ARG)			\
seed_worker_try_catch_open_implementation(CATCH_ROUTINE, ARG)

#define seed_worker_try_catch_close()					\
seed_worker_try_catch_close_implementation()

/* apply 'ARG' to 'ENSURE_ROUTINE' if exit in block or upon completing block */
#define seed_worker_try_ensure_open(ENSURE_ROUTINE, ARG)		\
seed_worker_try_ensure_open_implementation(ENSURE_ROUTINE, ARG)

#define seed_worker_try_ensure_close()					\
seed_worker_try_ensure_close_implementation()



inline void
seed_worker_exit_clean_up(void *arg)
{
	struct SeedWorker *const restrict
	worker = (struct SeedWorker *const restrict) arg;

	seed_key_handle_delete(worker->key);

	worker_queue_handle_remove(&supervisor.live,
				    worker);

	worker_queue_handle_push(&supervisor.dead,
				 worker);
}



void *
seed_worker_start_routine(void *arg);


inline SeedWorkerID
seed_worker_start(SeedWorkerRoutine *const routine,
		  void *arg)
{
	struct SeedWorker *const restrict
	worker = worker_queue_handle_pop(&supervisor.dead);

	const SeedWorkerID id = worker->id;

	worker->key	= (SeedKey) worker;
	worker->routine = routine;
	worker->arg	= arg;

	seed_thread_handle_create(&worker->thread,
				  &seed_worker_start_routine,
				  worker);

	return id;
}


#endif /* ifndef MYSQL_SEED_MYSQL_SEED_PARALLEL_H_ */
