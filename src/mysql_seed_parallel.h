#ifndef MYSQL_SEED_MYSQL_SEED_PARALLEL_H_
#define MYSQL_SEED_MYSQL_SEED_PARALLEL_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <pthread.h>		/* threads API */
#include <errno.h>		/* error codes, errno */
#include <limits.h>		/* PTHREAD_THREADS_MAX */
#include <string.h>		/* memcpy */
#include <stdbool.h>		/* bool */


/* typedefs
 *─────────────────────────────────────────────────────────────────────────── */
typedef pthread_mutex_t SeedMutex;

typedef pthread_cond_t SeedThreadCond;

typedef pthread_t SeedThread;

typedef pthread_attr_t SeedThreadAttr;

typedef pthread_key_t SeedThreadKey;

typedef void *
SeedThreadRoutine(void *arg);

typedef void
SeedThreadHandler(void *arg,
		  const char *restrict failure);

struct SeedThreadRoutineClosure {
	SeedThreadRoutine *routine;
	void *arg;
};

struct SeedThreadHandlerClosure {
	SeedThreadHandler *handle;
	void *arg;
};


/* global variables
 *─────────────────────────────────────────────────────────────────────────── */
extern const SeedMutex seed_mutex_prototype;
extern const SeedThreadCond seed_thread_cond_prototype;
extern SeedThreadAttr seed_thread_attr_prototype;

/* low-level threads API access
 *─────────────────────────────────────────────────────────────────────────── */
#define seed_thread_create_imp(THREAD, ROUTINE, ARG)		\
pthread_create(THREAD, &seed_thread_attr_prototype, ROUTINE, ARG)

#define seed_thread_cancel_imp(THREAD)				\
pthread_cancel(THREAD)

#define seed_thread_exit_imp()					\
pthread_exit(NULL)

#define seed_thread_try_catch_open_imp(CATCH_ROUTINE, ARG)	\
pthread_cleanup_push(CATCH_ROUTINE, ARG)

#define seed_thread_try_catch_close_imp()			\
pthread_cleanup_pop(0)

#define seed_thread_try_ensure_open_imp(ENSURE_ROUTINE, ARG)	\
pthread_cleanup_push(ENSURE_ROUTINE, ARG)

#define seed_thread_try_ensure_close_imp()			\
pthread_cleanup_pop(1)

#define seed_thread_key_create_imp(KEY, WORKER_HANDLER)		\
pthread_key_create(KEY, WORKER_HANDLER)

#define seed_thread_key_delete_imp(KEY)				\
pthread_key_delete(KEY)

#define seed_mutex_lock_imp(MUTEX)				\
pthread_mutex_lock(MUTEX)

#define seed_mutex_unlock_imp(MUTEX)				\
pthread_mutex_unlock(MUTEX)

#define seed_mutex_try_lock_imp(MUTEX)				\
pthread_mutex_trylock(MUTEX)

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



/* SeedThread operations
 *─────────────────────────────────────────────────────────────────────────── */
/* seed_thread_create */
inline bool
seed_thread_create(SeedThread *const restrict thread,
		   SeedThreadRoutine *const routine,
		   void *arg)
{
	return seed_thread_create_imp(thread,
				      routine,
				      arg) == 0;
}

inline void
seed_thread_create_muffle(SeedThread *const restrict thread,
			  SeedThreadRoutine *const routine,
			  void *arg)
{
	(void) seed_thread_create_imp(thread,
				      routine,
				      arg);
}

inline bool
seed_thread_create_report(SeedThread *const restrict thread,
			  SeedThreadRoutine *const routine,
			  void *arg,
			  const char *restrict *const restrict failure)
{
	switch (seed_thread_create_imp(thread,
				       routine,
				       arg)) {
	case 0:
		return true;

	case EAGAIN:
		*failure = "\n\nseed_thread_create failure:\n"
			   "\tThe system lacked the necessary resources to "
			   "create another thread"
#ifdef SEED_THREADS_MAX
			   ", or the system-imposed limit on the total number "
			   "of threads in a process, ('SEED_THREADS_MAX' = "
			   SEED_THREADS_MAX_STRING "), would be exceeded"
#endif /* ifdef SEED_THREADS_MAX */
			       ".\n";
		return false;

	default:
		*failure = "\n\nseed_thread_create failure:\n"
			   "\tunknown\n";
		return false;
	}
}

inline void
seed_thread_create_handle(SeedThread *const restrict thread,
			  SeedThreadRoutine *const routine,
			  void *routine_arg,
			  SeedThreadHandler *const handle,
			  void *handler_arg)
{
	const char *restrict failure;

	if (!seed_thread_create_report(thread,
				       routine,
				       routine_arg,
				       &failure))
		handle(handler_arg,
		       failure);
}

extern inline void
seed_thread_create_handle_closure(SeedThread *const restrict thread,
				  SeedThreadRoutine *const routine,
				  void *routine_arg,
				  SeedThreadHandlerClosure *const handler_closure)
{
	seed_thread_create_handle(thread,
				  routine,
				  routine_arg)
}





inline void
seed_thread_cancel(SeedThread thread)
{
	(void) seed_thread_cancel_imp(thread);
}


inline bool
seed_thread_cancel_report(SeedThread thread,
			  const char *restrict *const restrict failure);
{
	switch (seed_thread_cancel_imp(thread)) {
	case 0:
		return true;

	case ESRCH:
		*failure = "\n\nseed_thread_cancel failure:\n"
			   "\tNo thread could be found corresponding to that "
			   "specified by the given SeedThread 'thread'\n";
		return false;

	default:
		*failure = "\n\nseed_thread_cancel failure:\n"
			   "\tunknown\n";
		return false;
	}
}

inline void
seed_thread_exit(void)
{
	seed_thread_exit_imp();
}

/* SeedThreadKey operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
seed_thread_key_create(SeedThreadKey *const key,
		       IndependentRoutine *const handle)
{
	(void) seed_thread_key_create_imp(key,
					  handle);
}

inline bool
seed_thread_key_create_report(SeedThreadKey *const key,
			      IndependentRoutine *const handle,
			      const char *restrict *const restrict failure)
{
	switch (seed_thread_key_create_imp(key,
					   handle)) {
	case 0:
		return true;

	case EAGAIN:
		*failure = "\n\nseed_thread_key_create failure:\n"
			   "\tThe system lacked the necessary resources to "
			   "create another thread-specific data key"
#ifdef SEED_THREAD_KEYS_MAX
			   ", or the system-imposed limit on the total number "
			   "of keys per process, ('SEED_THREAD_KEYS_MAX' = "
			   SEED_THREAD_KEYS_MAX_STRING "), would be exceeded"
#endif /* ifdef SEED_THREAD_KEYS_MAX */
			       ".\n";
		return false;

	case ENOMEM:
		*failure = "\n\nseed_thread_key_create failure:\n"
			   "\tInsufficient memory exists to create "
			   "SeedThreadKey, 'key'.\n";
		return false;

	default:
		*failure = "\n\nseed_thread_key_create failure:\n"
			   "\tunknown\n";
		return false;
	}
}

inline void
seed_thread_key_delete(SeedThreadKey key)
{
	(void) seed_thread_key_delete_imp(key);
}

inline bool
seed_thread_key_delete_report(SeedThreadKey key,
			      const char *restrict *const restrict failure)
{
	switch (seed_thread_key_delete_imp(key)) {
	case 0:
		return true;

	case EINVAL:
		*failure = "\n\nseed_thread_key_delete failure:\n"
			   "\tthe value of SeedThread 'key' is invalid.\n";
		return false;

	default:
		*failure = "\n\nseed_thread_key_delete failure:\n"
			   "\tunknown\n";
		return false;
	}
}




/* SeedMutex operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
seed_mutex_init(SeedMutex *const restrict lock)
{
	seed_mutex_init_imp(lock);
}

inline bool
seed_mutex_lock(SeedMutex *const lock,
		const char *restrict *const restrict failure)
{
	switch (seed_mutex_lock_imp(lock)) {
	case 0:
		return true;

	case EDEADLK:
		*failure = "\n\nseed_mutex_lock failure:\n"
			   "\tA deadlock would occur if the thread blocked "
			   "waiting for SeedMutex 'lock'.";
		return false;

	case EINVAL:
		*failure = "\n\nseed_mutex_lock failure:\n"
			   "\tThe value specified by SeedMutex 'lock' is "
			   "invalid.\n";
		return false;


	default:
		*failure = "\n\nseed_mutex_lock failure:\n"
			   "\tunknown\n";
		return false;
	}
}

inline void
seed_mutex_lock_ignore(SeedMutex *const lock)
{
	(void) seed_mutex_lock_imp(lock);
}

inline bool
seed_mutex_try_lock(SeedMutex *const lock,
		    const char *restrict *const restrict failure)
{
	switch (seed_mutex_try_lock_imp(lock)) {

	case 0:
		return true;

	case EBUSY:
		*failure = NULL;
		return false;

	case EINVAL:
		*failure = "\n\nseed_mutex_try_lock failure:\n"
			   "\tThe value specified by SeedMutex 'lock' is "
			   "invalid.\n";
		return false;

	default:
		*failure = "\n\nseed_mutex_unlock failure:\n"
			   "\tunknown\n";
		return false;
	}
}

inline void
seed_mutex_try_lock_ignore(SeedMutex *const lock)
{
	(void) seed_mutex_try_lock_imp(lock);
}

inline bool
seed_mutex_unlock(SeedMutex *const lock,
		  const char *restrict *const restrict failure)
{
	switch (seed_mutex_unlock_imp(lock)) {
	case 0:
		return true;

	case EINVAL:
		*failure = "\n\nseed_mutex_unlock failure:\n"
			   "\tThe value specified by SeedMutex 'lock' is "
			   "invalid.\n";
		return false;

	case EPERM:
		*failure = "\n\nseed_mutex_unlock failure:\n"
			   "\tThe current thread does not hold a lock on "
			   "SeedMutex 'lock'.\n";
		return false;

	default:
		*failure = "\n\nseed_mutex_unlock failure:\n"
			   "\tunknown\n";
		return false;
	}
}

inline void
seed_mutex_unlock_ignore(SeedMutex *const lock)
{
	(void) seed_mutex_unlock_imp(lock);
}

/* SeedThreadAttr operations
 *─────────────────────────────────────────────────────────────────────────── */
inline bool
seed_thread_attr_init(SeedThreadAttr *const restrict attr,
		      const char *restrict *const restrict failure)
{
	switch (seed_thread_attr_init_imp(attr)) {
	case 0:
		return true;

	case ENOMEM:
		*failure = "\n\nseed_thread_attr_init failure:\n"
			   "\tout of memory\n";
		return false;

	default:
		*failure = "\n\nseed_thread_attr_init failure:\n"
			   "\tunknown\n";
		return false;
	}
}


inline bool
seed_thread_attr_set_detach_state(SeedThreadAttr *const restrict attr,
				  const int state,
				  const char *restrict *const restrict failure)
{
	switch (seed_thread_attr_set_detach_state_imp(attr,
						      state)) {
	case 0:
		return true;

	case EINVAL:
		*failure = "\n\nseed_thread_attr_set_detach_state failure:\n"
			   "\tinvalid value for 'attr' or 'state'\n";
		return false;

	default:
		*failure = "\n\nseed_thread_attr_set_detach_state failure:\n"
			   "\tunknown\n";
		return false;
	}
}


inline bool
seed_thread_attr_destroy(SeedThreadAttr *const restrict attr,
			 const char *restrict *const restrict failure)
{
	switch (seed_thread_attr_destroy_imp(attr)) {
	case 0:
		return true;

	case EINVAL:
		*failure = "\n\nseed_thread_attr_destroy failure:\n"
			   "\tinvalid value for 'attr'\n";
		return false;

	default:
		*failure = "\n\nseed_thread_attr_destroy failure:\n"
			   "\tunknown\n";
		return false;
	}
}


/* SeedThreadCond operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
seed_thread_cond_init(SeedThreadCond *const restrict cond)
{
	seed_thread_cond_init_imp(cond);
}

inline bool
seed_thread_cond_signal(SeedThreadCond *const restrict cond,
		      const char *restrict *const restrict failure)
{
	switch (seed_thread_cond_signal_imp(cond)) {
	case 0:
		return true;

	case EINVAL:
		*failure = "\n\nseed_thread_cond_signal failure:\n"
			   "\tThe value specified by 'cond' is invalid.\n";
		return false;

	default:
		*failure = "\n\nseed_thread_cond_signal failure:\n"
			   "\tunknown\n";
		return false;
	}
}


inline bool
seed_thread_cond_broadcast(SeedThreadCond *const restrict cond,
			 const char *restrict *const restrict failure)
{
	switch (seed_thread_cond_broadcast_imp(cond)) {
	case 0:
		return true;

	case EINVAL:
		*failure = "\n\nseed_thread_cond_broadcast failure:\n"
			   "\tThe value specified by 'cond' is invalid.\n";
		return false;

	default:
		*failure = "\n\nseed_thread_cond_broadcast failure:\n"
			   "\tunknown\n";
		return false;
	}
}


inline bool
seed_thread_cond_await(SeedThreadCond *const restrict cond,
		       SeedMutex *const restrict lock,
		       const char *restrict *const restrict failure)
{
	switch (seed_thread_cond_await_imp(cond,
					   lock)) {
	case 0:
		return true;

	case EINVAL:
		*failure = "\n\nseed_thread_cond_await failure:\n"
			   "\tThe value specified by 'cond' or 'lock' is "
			   "invalid.\n";
		return false;

	default:
		*failure = "\n\nseed_thread_cond_await failure:\n"
			   "\tunknown\n";
		return false;
	}
}

inline bool
seed_thread_cond_await_limit(SeedThreadCond *const restrict cond,
			     SeedMutex *const restrict lock,
			     const struct timespec *const restrict limit,
			     const char *restrict *const restrict failure)
{
	switch (seed_thread_cond_await_limit_imp(cond,
						 lock,
						 limit)) {
	case 0:
		return true;

	case EINVAL:
		*failure = "\n\nseed_thread_cond_await_limit failure:\n"
			   "\tThe value specified by 'cond', 'lock', or 'limit'"
			   "is invalid.\n";
		return false;

	case ETIMEDOUT:
		*failure = "\n\nseed_thread_cond_await_limit failure:\n"
			   "\tThe system time has reached or exceeded the time "
			   "specified in 'limit'.\n";
		return false;

	default:
		*failure = "\n\nseed_thread_cond_await_limit failure:\n"
			   "\tunknown\n";
		return false;
	}
}


inline bool
seed_thread_cond_await_span(SeedThreadCond *const restrict cond,
			  SeedMutex *const restrict lock,
			  const struct timespec *const restrict span,
			  const char *restrict *const restrict failure)
{
	struct timespec limit;

	timespec_offset_now(&limit,
			    span);

	return seed_thread_cond_await_limit(cond,
					    lock,
					    &limit,
					    failure);
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
