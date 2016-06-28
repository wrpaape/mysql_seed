#ifndef MYSQL_SEED_MYSQL_SEED_PARALLEL_H_
#define MYSQL_SEED_MYSQL_SEED_PARALLEL_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <pthread.h>		/* threads API */
#include <errno.h>		/* error codes, errno */
#include <limits.h>		/* PTHREAD_THREADS_MAX */
#include <string.h>		/* memcpy */
#include <stdbool.h>		/* bool */
#include "time/time_utils.h"	/* timespec, time utils */
#include "mysql_seed_exit.h"	/* SeedExitSpec, string helper macros */

#define SEED_WORKERS_MAX 16u


/* typedefs
 *─────────────────────────────────────────────────────────────────────────── */
typedef pthread_mutex_t SeedMutex;

typedef pthread_cond_t SeedThreadCond;

typedef pthread_t SeedThread;

typedef pthread_attr_t SeedThreadAttr;

typedef pthread_key_t SeedThreadKey;

typedef unsigned int SeedWorkerID;

typedef void *
SeedWorkerRoutine(void *);

typedef void
SeedWorkerHandler(void *);

struct SeedWorker {
	SeedWorkerID id;
	SeedThreadKey key;
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
extern const SeedMutex seed_mutex_prototype;
extern const SeedThreadCond seed_thread_cond_prototype;
extern SeedThreadAttr seed_thread_attr_prototype;

extern struct SeedSupervisor supervisor;


/* low-level threads API access
 *─────────────────────────────────────────────────────────────────────────── */
#define seed_thread_create_imp(THREAD, ROUTINE, ARG)		\
pthread_create(THREAD, &seed_thread_attr_prototype, ROUTINE, ARG)

#define seed_thread_cancel_imp(THREAD)				\
pthread_cancel(THREAD)

#define seed_thread_key_create_imp(KEY, WORKER_HANDLER)		\
pthread_key_create(KEY, WORKER_HANDLER)

#define seed_thread_key_delete_imp(KEY)				\
pthread_key_delete(KEY)

#define seed_mutex_lock_imp(MUTEX)				\
pthread_mutex_lock(MUTEX)

#define seed_mutex_unlock_imp(MUTEX)				\
pthread_mutex_unlock(MUTEX)

#define seed_mutex_init_imp(MUTEX)				\
memcpy(MUTEX, &seed_mutex_prototype, sizeof(seed_mutex_prototype))

#define seed_thread_attr_init_imp(ATTR)				\
pthread_attr_init(ATTR)

#define seed_thread_attr_set_detach_state_imp(ATTR, STATE)	\
pthread_attr_setdetachstate(ATTR, STATE)

#define seed_thread_attr_destroy_imp(ATTR)			\
pthread_attr_destroy(ATTR)

#define seed_thread_cond_init_imp(COND)				\
memcpy(COND, &seed_thread_cond_prototype, sizeof(seed_thread_cond_prototype))

#define seed_thread_cond_signal_imp(COND)			\
pthread_cond_signal(COND)

#define seed_thread_cond_broadcast_imp(COND)			\
pthread_cond_broadcast(COND)

#define seed_thread_cond_await_imp(COND, MUTEX)			\
pthread_cond_wait(COND, MUTEX)

#define seed_thread_cond_await_limit_imp(COND, MUTEX, LIMIT)	\
pthread_cond_timedwait(COND, MUTEX, LIMIT)

#define seed_worker_try_catch_open_imp(CATCH_ROUTINE, ARG)	\
pthread_cleanup_push(CATCH_ROUTINE, ARG)

#define seed_worker_try_catch_close_imp()			\
pthread_cleanup_pop(0)

#define seed_worker_try_ensure_open_imp(ENSURE_ROUTINE, ARG)	\
pthread_cleanup_push(ENSURE_ROUTINE, ARG)

#define seed_worker_try_ensure_close_imp()			\
pthread_cleanup_pop(1)

/* static initializers, flags, macro constants
 *─────────────────────────────────────────────────────────────────────────── */
#define SEED_MUTEX_INITIALIZER		PTHREAD_MUTEX_INITIALIZER
#define SEED_THREAD_COND_INITIALIZER	PTHREAD_COND_INITIALIZER

#define SEED_THREAD_ATTR_DETACHED	PTHREAD_CREATE_DETACHED
#define SEED_THREAD_ATTR_JOINABLE	PTHREAD_CREATE_JOINABLE

#ifdef PTHREAD_THREADS_MAX
#	define SEED_THREADS_MAX PTHREAD_THREADS_MAX
#	define SEED_THREADS_MAX_STRING EXPAND_STRINGIFY(PTHREAD_THREADS_MAX)
#endif	/* ifdef PTHREADS_THREADS_MAX */

#ifdef PTHREAD_KEYS_MAX
#	define SEED_THREAD_KEYS_MAX PTHREAD_KEYS_MAX
#	define SEED_THREAD_KEYS_MAX_STRING EXPAND_STRINGIFY(PTHREAD_KEYS_MAX)
#endif	/* ifdef PTHREADS_THREADS_MAX */


/* helper macros
 *─────────────────────────────────────────────────────────────────────────── */
#define SEED_WORKER_LINK(WORKER, PREV, NEXT)		\
WORKER->prev = PREV;					\
WORKER->next = NEXT



/* SeedSupervisor operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
seed_supervisor_init(void)
{
	struct SeedWorker *const restrict worker0  = &supervisor.workers[0];
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

	supervisor.dead.head = worker0;
	supervisor.dead.last = worker15;
}

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
	switch (seed_thread_create_imp(thread,
				       routine,
				       arg)) {
	case 0:
		return true;

	case EAGAIN:
		*message_ptr = "\n\nseed_thread_create failure:\n"
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
		*message_ptr = "\n\nseed_thread_create failure:\n"
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
	switch (seed_thread_cancel_imp(thread)) {
	case 0:
		return true;

	case ESRCH:
		*message_ptr = "\n\nseed_thread_cancel failure:\n"
			       "\tNo thread could be found corresponding to that "
			       "specified by the given SeedThread 'thread'\n";
		return false;

	default:
		*message_ptr = "\n\nseed_thread_cancel failure:\n"
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
seed_thread_key_create(SeedThreadKey *const key,
		       SeedWorkerHandler *const handle,
		       const char *restrict *const restrict message_ptr)
{
	switch (seed_thread_key_create_imp(key,
					   handle)) {
	case 0:
		return true;

	case EAGAIN:
		*message_ptr = "\n\nseed_thread_key_create failure:\n"
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
		*message_ptr = "\n\nseed_thread_key_create failure:\n"
			       "\tInsufficient memory exists to create "
			       "SeedThreadKey, 'key'.\n";
		return false;

	default:
		*message_ptr = "\n\nseed_thread_key_create failure:\n"
			       "\tunknown\n";
		return false;
	}
}

inline void
seed_thread_key_handle_create(SeedThreadKey *const key,
			      SeedWorkerHandler *const handle)
{
	const char *restrict failure;

	if (!seed_thread_key_create(key,
				    handle,
				    &failure))
		seed_supervisor_exit(failure);
}

inline bool
seed_thread_key_delete(SeedThreadKey key,
		       const char *restrict *const restrict message_ptr)
{
	switch (seed_thread_key_delete_imp(key)) {
	case 0:
		return true;

	case EINVAL:
		*message_ptr = "\n\nseed_thread_key_delete failure:\n"
			       "\tthe value of SeedThread 'key' is invalid.\n";
		return false;

	default:
		*message_ptr = "\n\nseed_thread_key_delete failure:\n"
			       "\tunknown\n";
		return false;
	}
}

inline void
seed_thread_key_handle_delete(SeedThreadKey key)
{
	const char *restrict failure;

	if (!seed_thread_key_delete(key,
				    &failure))
		seed_supervisor_exit(failure);
}



/* SeedMutex operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
seed_mutex_init(SeedMutex *const restrict lock)
{
	seed_mutex_init_imp(lock);
}

inline void
seed_mutex_handle_init(SeedMutex *const restrict lock)
{
	seed_mutex_init_imp(lock);
}

inline bool
seed_mutex_lock(SeedMutex *const lock,
		const char *restrict *const restrict message_ptr)
{
	switch (seed_mutex_lock_imp(lock)) {
	case 0:
		return true;

	case EDEADLK:
		*message_ptr = "\n\nseed_mutex_lock failure:\n"
			       "\tA deadlock would occur if the thread blocked "
			       "waiting for SeedMutex 'lock'.";
		return false;

	case EINVAL:
		*message_ptr = "\n\nseed_mutex_lock failure:\n"
			       "\tThe value specified by SeedMutex 'lock' is "
			       "invalid.\n";
		return false;


	default:
		*message_ptr = "\n\nseed_mutex_lock failure:\n"
			       "\tunknown\n";
		return false;
	}
}

inline bool
seed_mutex_unlock(SeedMutex *const lock,
		  const char *restrict *const restrict message_ptr)
{
	switch (seed_mutex_unlock_imp(lock)) {
	case 0:
		return true;

	case EINVAL:
		*message_ptr = "\n\nseed_mutex_unlock failure:\n"
			       "\tThe value specified by SeedMutex 'lock' is "
			       "invalid.\n";
		return false;

	case EPERM:
		*message_ptr = "\n\nseed_mutex_unlock failure:\n"
			       "\tThe current thread does not hold a lock on "
			       "SeedMutex 'lock'.\n";
		return false;

	default:
		*message_ptr = "\n\nseed_mutex_unlock failure:\n"
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

/* SeedThreadAttr operations
 *─────────────────────────────────────────────────────────────────────────── */
inline bool
seed_thread_attr_init(SeedThreadAttr *const restrict attr,
		      const char *restrict *const restrict message_ptr)
{
	switch (seed_thread_attr_init_imp(attr)) {
	case 0:
		return true;

	case ENOMEM:
		*message_ptr = "\n\nseed_thread_attr_init failure:\n"
			       "\tout of memory.\n";
		return false;

	default:
		*message_ptr = "\n\nseed_thread_attr_init failure:\n"
			       "\tunknown\n";
		return false;
	}
}

inline void
seed_thread_attr_handle_init(SeedThreadAttr *const restrict attr)
{
	const char *restrict failure;

	if (!seed_thread_attr_init(attr,
				   &failure))
		seed_supervisor_exit(failure);
}


inline bool
seed_thread_attr_set_detach_state(SeedThreadAttr *const restrict attr,
				  const int state,
				  const char *restrict *const restrict message_ptr)
{
	switch (seed_thread_attr_set_detach_state_imp(attr,
						      state)) {
	case 0:
		return true;

	case EINVAL:
		*message_ptr = "\n\nseed_thread_attr_set_detach_state failure:\n"
			       "\tinvalid value for 'attr' or 'state'\n";
		return false;

	default:
		*message_ptr = "\n\nseed_thread_attr_set_detach_state failure:\n"
			       "\tunknown\n";
		return false;
	}
}

inline void
seed_thread_attr_handle_set_detach_state(SeedThreadAttr *const restrict attr,
					 const int state)
{
	const char *restrict failure;

	if (!seed_thread_attr_set_detach_state(attr,
					       state,
					       &failure))
		seed_supervisor_exit(failure);
}

inline bool
seed_thread_attr_destroy(SeedThreadAttr *const restrict attr,
			 const char *restrict *const restrict message_ptr)
{
	switch (seed_thread_attr_destroy_imp(attr)) {
	case 0:
		return true;

	case EINVAL:
		*message_ptr = "\n\nseed_thread_attr_destroy failure:\n"
			       "\tinvalid value for 'attr'\n";
		return false;

	default:
		*message_ptr = "\n\nseed_thread_attr_destroy failure:\n"
			       "\tunknown\n";
		return false;
	}
}

inline void
seed_thread_attr_handle_destroy(SeedThreadAttr *const restrict attr)
{
	const char *restrict failure;

	if (!seed_thread_attr_destroy(attr,
				      &failure))
		seed_supervisor_exit(failure);
}

/* SeedThreadCond operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
seed_thread_cond_init(SeedThreadCond *const restrict cond)
{
	seed_thread_cond_init_imp(cond);
}

inline void
seed_thread_cond_handle_init(SeedThreadCond *const restrict cond)
{
	seed_thread_cond_init_imp(cond);
}


inline bool
seed_thread_cond_signal(SeedThreadCond *const restrict cond,
		      const char *restrict *const restrict message_ptr)
{
	switch (seed_thread_cond_signal_imp(cond)) {
	case 0:
		return true;

	case EINVAL:
		*message_ptr = "\n\nseed_thread_cond_signal failure:\n"
			       "\tThe value specified by 'cond' is "
			       "invalid.\n";
		return false;

	default:
		*message_ptr = "\n\nseed_thread_cond_signal failure:\n"
			       "\tunknown\n";
		return false;
	}
}

inline void
seed_thread_cond_handle_signal(SeedThreadCond *const restrict cond)
{
	const char *restrict failure;

	if (!seed_thread_cond_signal(cond,
				   &failure))
		seed_supervisor_exit(failure);
}

inline bool
seed_thread_cond_broadcast(SeedThreadCond *const restrict cond,
			 const char *restrict *const restrict message_ptr)
{
	switch (seed_thread_cond_broadcast_imp(cond)) {
	case 0:
		return true;

	case EINVAL:
		*message_ptr = "\n\nseed_thread_cond_broadcast failure:\n"
			       "\tThe value specified by 'cond' is "
			       "invalid.\n";
		return false;

	default:
		*message_ptr = "\n\nseed_thread_cond_broadcast failure:\n"
			       "\tunknown\n";
		return false;
	}
}

inline void
seed_thread_cond_handle_broadcast(SeedThreadCond *const restrict cond)
{
	const char *restrict failure;

	if (!seed_thread_cond_broadcast(cond,
				      &failure))
		seed_supervisor_exit(failure);
}

inline bool
seed_thread_cond_await(SeedThreadCond *const restrict cond,
		     SeedMutex *const restrict lock,
		     const char *restrict *const restrict message_ptr)
{
	switch (seed_thread_cond_await_imp(cond,
					   lock)) {
	case 0:
		return true;

	case EINVAL:
		*message_ptr = "\n\nseed_thread_cond_await failure:\n"
			       "\tThe value specified by 'cond' or 'lock' "
			       "is invalid.\n";
		return false;

	default:
		*message_ptr = "\n\nseed_thread_cond_await failure:\n"
			       "\tunknown\n";
		return false;
	}
}

inline void
seed_thread_cond_handle_await(SeedThreadCond *const restrict cond,
			    SeedMutex *const restrict lock)
{
	const char *restrict failure;

	if (!seed_thread_cond_await(cond,
				  lock,
				  &failure))
		seed_supervisor_exit(failure);
}

inline bool
seed_thread_cond_await_limit(SeedThreadCond *const restrict cond,
			   SeedMutex *const restrict lock,
			   const struct timespec *const restrict limit,
			   const char *restrict *const restrict message_ptr)
{
	switch (seed_thread_cond_await_limit_imp(cond,
						 lock,
						 limit)) {
	case 0:
		return true;

	case EINVAL:
		*message_ptr = "\n\nseed_thread_cond_await_limit failure:\n"
			       "\tThe value specified by 'cond', 'lock', "
			       "or 'limit' is invalid.\n";
		return false;

	case ETIMEDOUT:
		*message_ptr = "\n\nseed_thread_cond_await_limit failure:\n"
			       "\tThe system time has reached or exceeded the "
			       "time specified in 'limit'.\n";
		return false;

	default:
		*message_ptr = "\n\nseed_thread_cond_await_limit failure:\n"
			       "\tunknown\n";
		return false;
	}
}

inline void
seed_thread_cond_handle_await_limit(SeedThreadCond *const restrict cond,
				  SeedMutex *const restrict lock,
				  const struct timespec *const restrict limit)
{
	const char *restrict failure;

	if (!seed_thread_cond_await_limit(cond,
					lock,
					limit,
					&failure))
		seed_supervisor_exit(failure);
}

inline bool
seed_thread_cond_await_span(SeedThreadCond *const restrict cond,
			  SeedMutex *const restrict lock,
			  const struct timespec *const restrict span,
			  const char *restrict *const restrict message_ptr)
{
	struct timespec limit;

	timespec_offset_now(&limit,
			    span);

	return seed_thread_cond_await_limit(cond,
					  lock,
					  &limit,
					  message_ptr);
}

inline void
seed_thread_cond_handle_await_span(SeedThreadCond *const restrict cond,
				 SeedMutex *const restrict lock,
				 const struct timespec *const restrict span)
{
	const char *restrict failure;

	if (!seed_thread_cond_await_span(cond,
				       lock,
				       span,
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
seed_worker_try_catch_open_imp(CATCH_ROUTINE, ARG)

#define seed_worker_try_catch_close()					\
seed_worker_try_catch_close_imp()

/* apply 'ARG' to 'ENSURE_ROUTINE' if exit in block or upon completing block */
#define seed_worker_try_ensure_open(ENSURE_ROUTINE, ARG)		\
seed_worker_try_ensure_open_imp(ENSURE_ROUTINE, ARG)

#define seed_worker_try_ensure_close()					\
seed_worker_try_ensure_close_imp()



inline void
seed_worker_exit_clean_up(void *arg)
{
	struct SeedWorker *const restrict
	worker = (struct SeedWorker *const restrict) arg;

	seed_thread_key_handle_delete(worker->key);

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

	worker->key	= (SeedThreadKey) worker;
	worker->routine = routine;
	worker->arg	= arg;

	seed_thread_handle_create(&worker->thread,
				  &seed_worker_start_routine,
				  worker);

	return id;
}





/* Constructors, Destructors
 *─────────────────────────────────────────────────────────────────────────── */

/* prototypes */

inline void
seed_thread_attr_prototype_init(void)
{
	seed_thread_attr_handle_init(&seed_thread_attr_prototype);

	seed_thread_attr_handle_set_detach_state(&seed_thread_attr_prototype,
						 SEED_THREAD_ATTR_DETACHED);
}

inline void
seed_thread_attr_prototype_destroy(void)
{
	seed_thread_attr_handle_destroy(&seed_thread_attr_prototype);
}
void
seed_parallel_start(void)
__attribute__((constructor));

void
seed_parallel_stop(void)
__attribute__((destructor));




#endif /* ifndef MYSQL_SEED_MYSQL_SEED_PARALLEL_H_ */
