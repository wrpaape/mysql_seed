#ifndef MYSQL_SEED_MYSQL_SEED_PARALLEL_H_
#define MYSQL_SEED_MYSQL_SEED_PARALLEL_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <pthread.h>		/* pthread API */
#include <errno.h>		/* error codes, errno */
#include <limits.h>		/* PTHREAD_THREADS_MAX */
#include <string.h>		/* memcpy */
#include <stdbool.h>		/* bool */
#include "mysql_seed_exit.h"	/* SeedExitSpec */

#define SEED_WORKERS_MAX 16u
#define SEED_THREADS_MAX PTHREAD_THREADS_MAX

/* typedefs
 *─────────────────────────────────────────────────────────────────────────── */
typedef pthread_mutex_t SeedMutex;

typedef pthread_t SeedThread;

typedef unsigned int SeedWorkerID;

typedef void *
SeedWorkerRoutine(void *);

typedef void
SeedWorkerTryCatch(void *);

struct SeedWorker {
	SeedWorkerID id;
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


/* helper macros
 *─────────────────────────────────────────────────────────────────────────── */
#define SEED_MUTEX_INITIALIZER PTHREAD_MUTEX_INITIALIZER


/* global variables
 *─────────────────────────────────────────────────────────────────────────── */
extern const SeedMutex seed_lock_prototype;

extern struct SeedSupervisor supervisor;


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
	switch (pthread_create(thread,
			       NULL,
			       routine,
			       arg)) {
	case 0:
		return true;

	case EAGAIN:
		*message_ptr = "seed_thread_create failure:\n"
			       "The system lacked the necessary resources to "
			       "create another thread, or the system-imposed "
			       "limit on the total number of threads in a "
			       "process, 'SEED_THREADS_MAX', would be exceeded."
			       "\n";
		return false;

	default:
		*message_ptr = "seed_thread_create failure:\n"
			       "unknown\n";
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
	switch (pthread_cancel(thread)) {
	case 0:
		return true;

	case ESRCH:
		*message_ptr = "seed_thread_cancel failure:\n"
			       "No thread could be found corresponding to that "
			       "specified by the given SeedThread 'thread'\n";
		return false;

	default:
		*message_ptr = "seed_thread_cancel failure:\n"
			       "unknown\n";
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
		const char *restrict *const restrict message_ptr)
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


/* apply 'ARG' to 'CATCH_TRY' if exit in block */
#define seed_worker_try_open(CATCH_TRY, ARG)		\
pthread_cleanup_push(CATCH_TRY, ARG)

#define seed_worker_try_close()				\
pthread_cleanup_pop(0)


/* apply 'ARG' to 'CATCH_ENSURE' if exit in block or upon completing block */
#define seed_worker_ensure_open(CATCH_ENSURE, ARG)	\
pthread_cleanup_push(CATCH_ENSURE, ARG)

#define seed_worker_ensure_close()			\
pthread_cleanup_pop(1)


inline void
seed_worker_exit_clean_up(void *worker)
{
	worker_queue_handle_remove(&supervisor.live,
				   (struct SeedWorker *const restrict) worker);

	worker_queue_handle_push(&supervisor.dead,
				 (struct SeedWorker *const restrict) worker);
}



void *
seed_worker_start_routine(void *worker);


inline SeedWorkerID
seed_worker_start(SeedWorkerRoutine *const routine,
		  void *arg)
{
	struct SeedWorker *const restrict
	worker = worker_queue_handle_pop(&supervisor.dead);

	const SeedWorkerID id = worker->id;

	worker->routine = routine;
	worker->arg	= arg;

	seed_thread_handle_create(&worker->thread,
				  &seed_worker_start_routine,
				  worker);

	return id;
}


#endif /* ifndef MYSQL_SEED_MYSQL_SEED_PARALLEL_H_ */
