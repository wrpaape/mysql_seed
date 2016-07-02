#ifndef MYSQL_SEED_THREAD_THREAD_UTILS_H_
#define MYSQL_SEED_THREAD_THREAD_UTILS_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <pthread.h>			/* threads API */
#include <limits.h>			/* PTHREAD_THREADS_MAX */
#include <string.h>			/* memcpy */
#include "time/time_utils.h"		/* time utils */
#include "utils/fail_switch_open.h"	/* bool, errno, error report macros */

/* typedefs
 *─────────────────────────────────────────────────────────────────────────── */
typedef pthread_mutex_t Mutex;

typedef pthread_cond_t ThreadCond;

typedef pthread_t Thread;

typedef pthread_attr_t ThreadAttr;

typedef pthread_key_t ThreadKey;

typedef void *
ThreadRoutine(void *arg);

typedef void
ThreadProcedure(void *arg);

typedef void
ThreadHandler(void *arg,
	      const char *restrict failure)
__attribute__((noreturn));


struct ThreadRoutineClosure {
	ThreadRoutine *routine;
	void *arg;
};

struct ThreadHandlerClosure {
	ThreadHandler *handle;
	void *arg;
};

enum ThreadFlag {
	THREAD_ERROR = -1,
	THREAD_FALSE = false,
	THREAD_TRUE  = true
};


/* global variables
 *─────────────────────────────────────────────────────────────────────────── */
extern const Mutex mutex_prototype;
extern const ThreadCond thread_cond_prototype;
extern ThreadAttr thread_attr_prototype;

/* low-level threads API access
 *─────────────────────────────────────────────────────────────────────────── */
#define thread_create_imp(THREAD, ROUTINE, ARG)				\
pthread_create(THREAD, &thread_attr_prototype, ROUTINE, ARG)

#define thread_self_imp()						\
pthread_self()

#define threads_equal_imp(THREAD1, THREAD2)				\
pthread_equal(THREAD1, THREAD2)

#define thread_cancel_imp(THREAD)					\
pthread_cancel(THREAD)

#define thread_exit_detached_imp()					\
pthread_exit(NULL)

#define thread_exit_joinable_imp(pointer)				\
pthread_exit(pointer)

#define thread_try_catch_open_imp(CATCH_ROUTINE, ARG)			\
pthread_cleanup_push(CATCH_ROUTINE, ARG)

#define thread_try_catch_close_imp()					\
pthread_cleanup_pop(0)

#define thread_try_ensure_open_imp(ENSURE_ROUTINE, ARG)			\
pthread_cleanup_push(ENSURE_ROUTINE, ARG)

#define thread_try_ensure_close_imp()					\
pthread_cleanup_pop(1)

#define thread_key_create_imp(KEY, CLEANUP)				\
pthread_key_create(KEY, CLEANUP)

#define thread_key_delete_imp(KEY)					\
pthread_key_delete(KEY)

#define mutex_lock_imp(MUTEX)						\
pthread_mutex_lock(MUTEX)

#define mutex_unlock_imp(MUTEX)						\
pthread_mutex_unlock(MUTEX)

#define mutex_try_lock_imp(MUTEX)					\
pthread_mutex_trylock(MUTEX)

#define mutex_init_imp(MUTEX)						\
(void) memcpy(MUTEX, &mutex_prototype, sizeof(mutex_prototype))

#define thread_attr_init_imp(ATTR)					\
pthread_attr_init(ATTR)

#define thread_attr_set_detach_state_imp(ATTR, STATE)			\
pthread_attr_setdetachstate(ATTR, STATE)

#define thread_attr_destroy_imp(ATTR)					\
pthread_attr_destroy(ATTR)

#define thread_cond_init_imp(COND)					\
(void) memcpy(COND, &thread_cond_prototype, sizeof(thread_cond_prototype))

#define thread_cond_signal_imp(COND)					\
pthread_cond_signal(COND)

#define thread_cond_broadcast_imp(COND)					\
pthread_cond_broadcast(COND)

#define thread_cond_await_imp(COND, MUTEX)				\
pthread_cond_wait(COND, MUTEX)

#define thread_cond_await_limit_imp(COND, MUTEX, LIMIT)			\
pthread_cond_timedwait(COND, MUTEX, LIMIT)


/* static initializers, flags, macro constants
 *─────────────────────────────────────────────────────────────────────────── */
#define STRINGIFY(X)	    #X
#define EXPAND_STRINGIFY(X) STRINGIFY(X)

#define MUTEX_INITIALIZER	PTHREAD_MUTEX_INITIALIZER
#define THREAD_COND_INITIALIZER	PTHREAD_COND_INITIALIZER

#define THREAD_ATTR_DETACHED	PTHREAD_CREATE_DETACHED
#define THREAD_ATTR_JOINABLE	PTHREAD_CREATE_JOINABLE

#ifdef PTHREAD_THREADS_MAX
#	define THREADS_MAX PTHREAD_THREADS_MAX
#	define THREADS_MAX_STRING EXPAND_STRINGIFY(PTHREAD_THREADS_MAX)
#endif	/* ifdef PTHREADS_THREADS_MAX */

#ifdef PTHREAD_KEYS_MAX
#	define THREAD_KEYS_MAX PTHREAD_KEYS_MAX
#	define THREAD_KEYS_MAX_STRING EXPAND_STRINGIFY(PTHREAD_KEYS_MAX)
#endif	/* ifdef PTHREADS_THREADS_MAX */



/* Thread operations
 *─────────────────────────────────────────────────────────────────────────── */
/* thread_create */
inline bool
thread_create(Thread *const restrict thread,
		   ThreadRoutine *const routine,
		   void *arg)
{
	return thread_create_imp(thread,
				 routine,
				 arg) == 0;
}

inline void
thread_create_muffle(Thread *const restrict thread,
			  ThreadRoutine *const routine,
			  void *arg)
{
	(void) thread_create_imp(thread,
				 routine,
				 arg);
}

#define FAIL_SWITCH_STATUS_SUCCESS 0		/* same for all routines */
#define FAIL_SWITCH_FAILURE_POINTER failure	/* same for all routines */

#define FAIL_SWITCH_ROUTINE thread_create_imp
inline bool
thread_create_report(Thread *const restrict thread,
		     ThreadRoutine *const routine,
		     void *arg,
		     const char *restrict *const restrict failure)
{
	FAIL_SWITCH_STATUS_OPEN(thread, routine, arg)
	FAIL_SWITCH_STATUS_CASE_1(EAGAIN,
				  "The system lacked the necessary resources to"
				  " create another thread"
#ifdef THREADS_MAX
				  ", or the system-imposed limit on the total "
				  "number of threads in a process, ('"
				  "THREADS_MAX' = " THREADS_MAX_STRING "), "
				  "would be exceeded"
#endif /* ifdef THREADS_MAX */
				  ".")
	FAIL_SWITCH_STATUS_CLOSE()
}

inline void
thread_create_handle(Thread *const restrict thread,
		     ThreadRoutine *const routine,
		     void *routine_arg,
		     ThreadHandler *const handle,
		     void *handler_arg)
{
	const char *restrict failure;

	if (thread_create_report(thread,
				 routine,
				 routine_arg,
				 &failure))
		return;

	handle(handler_arg,
	       failure);
	__builtin_unreachable();
}

inline void
thread_create_handle_cl(Thread *const restrict thread,
			ThreadRoutine *const routine,
			void *routine_arg,
			ThreadHandlerClosure *const restrict cl)
{
	const char *restrict failure;

	if (thread_create_report(thread,
				 routine,
				 routine_arg,
				 &failure))
		return;

	cl->handle(cl->arg,
		   failure);
	__builtin_unreachable();
}

/* thread_create_cl */
inline bool
thread_create_cl(Thread *const restrict thread,
		      ThreadRoutineClosure *const restrict cl)
{
	return thread_create(thread,
			     cl->routine,
			     cl->arg);
}

inline void
thread_create_cl_muffle(Thread *const restrict thread,
			     ThreadRoutineClosure *const restrict cl)
{
	thread_create_muffle(thread,
			     cl->routine,
			     cl->arg);
}

inline bool
thread_create_cl_report(Thread *const restrict thread,
			     ThreadRoutineClosure *const restrict cl,
			     const char *restrict *const restrict failure)
{
	return thread_create_report(thread,
				    cl->routine,
				    cl->arg,
				    failure);
}

inline void
thread_create_cl_handle(Thread *const restrict thread,
			     ThreadRoutineClosure *const restrict cl,
			     ThreadHandler *const handle,
			     void *handler_arg)
{
	thread_create_handle(thread,
			     cl->routine,
			     cl->arg,
			     handle,
			     handler_arg);
}

inline void
thread_create_cl_handle_cl(Thread *const restrict thread,
			   ThreadRoutineClosure *const restrict routine_cl,
			   ThreadHandlerClosure *const restrict handler_cl)
{
	thread_create_handle_cl(thread,
				routine_cl->routine,
				routine_cl->arg,
				handler_cl);
}


/* thread_cancel */
inline bool
thread_cancel(Thread thread)
{
	return thread_cancel_imp(thread) == 0;
}

inline void
thread_cancel_muffle(Thread thread)
{
	(void) thread_cancel_imp(thread);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE thread_cancel_imp
inline bool
thread_cancel_report(Thread thread,
		     const char *restrict *const restrict failure);
{
	FAIL_SWITCH_STATUS_OPEN(thread)
	FAIL_SWITCH_STATUS_CASE_1(ESRCH,
				  "No thread could be found corresponding to "
				  "that specified by the given Thread '"
				  "thread'.")
	FAIL_SWITCH_STATUS_CLOSE()
}

inline void
thread_cancel_handle(Thread thread,
		     ThreadHandler *const handle,
		     void *arg)
{
	const char *restrict failure;

	if (thread_cancel_report(thread,
				 &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
thread_cancel_handle_cl(Thread thread,
			ThreadHandlerClosure *const restrict cl)
{
	const char *restrict failure;

	if (thread_cancel_report(thread,
				 &failure))
		return;

	cl->handle(cl->arg,
		   failure);
	__builtin_unreachable();
}


/* thread_exit */
inline void
thread_exit_detached(void)
{
	thread_exit_detached_imp();
}

inline void
thread_exit_joinable(void *pointer)
{
	thread_exit_joinable_imp(pointer);
}


/* thread_self */
inline Thread
thread_self(void)
{
	return thread_self_imp();
}


/* threads_equal */
inline bool
threads_equal(const Thread thread1,
	      const Thread thread2)
{
	return threads_equal_imp(thread1,
				 thread2) == 0;
}



/* ThreadKey operations
 *─────────────────────────────────────────────────────────────────────────── */
/* thread_key_create */
inline bool
thread_key_create(ThreadKey *const key,
		  ThreadProcedure *const restrict cleanup)
{
	return thread_key_create_imp(key,
				     cleanup);
}

inline void
thread_key_create_muffle(ThreadKey *const key,
			 ThreadProcedure *const restrict cleanup)
{
	(void) thread_key_create_imp(key,
				     cleanup);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE thread_key_create_imp
inline bool
thread_key_create_report(ThreadKey *const key,
			 ThreadProcedure *const restrict cleanup,
			 const char *restrict *const restrict failure)
{
	FAIL_SWITCH_STATUS_OPEN(key,
				cleanup)
	FAIL_SWITCH_STATUS_CASE_1(EAGAIN,
				  "The system lacked the necessary resources to"
				  " create another thread-specific data key"
#ifdef THREAD_KEYS_MAX
				  ", or the system-imposed limit on the total "
				  "number of keys per process, ('"
				  "THREAD_KEYS_MAX' = " THREAD_KEYS_MAX_STRING
				  "), would be exceeded"
#endif /* ifdef THREAD_KEYS_MAX */
			          ".")
	FAIL_SWITCH_STATUS_CASE_1(ENOMEM,
				  "Insufficient memory exists to create "
				  "ThreadKey, 'key'.")
	FAIL_SWITCH_STATUS_CLOSE()
}

inline void
thread_key_create_handle(ThreadKey *const key,
			 ThreadProcedure *const restrict cleanup,
			 ThreadHandler *const handle,
			 void *arg)
{
	const char *restrict failure;

	if (thread_key_create_report(key,
				     cleanup,
				     &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
thread_key_create_handle_cl(ThreadKey *const key,
			    ThreadProcedure *const restrict cleanup,
			    ThreadHandlerClosure *const restrict cl)
{
	const char *restrict failure;

	if (thread_key_create_report(key,
				     cleanup,
				     &failure))
		return;

	cl->handle(cl->arg,
		   failure);
	__builtin_unreachable();
}


/* thread_key_delete */
inline bool
thread_key_delete(ThreadKey key)
{
	return thread_key_delete_imp(key) == 0;
}

inline void
thread_key_delete_muffle(ThreadKey key)
{
	(void) thread_key_delete_imp(key);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE thread_key_delete_imp
inline bool
thread_key_delete_report(ThreadKey key,
			 const char *restrict *const restrict failure)
{
	FAIL_SWITCH_STATUS_OPEN(key)
	FAIL_SWITCH_STATUS_CASE_1(EINVAL,
				  "the value of Thread 'key' is invalid.")
	FAIL_SWITCH_STATUS_CLOSE()
}

inline void
thread_key_delete_handle(ThreadKey key,
			 ThreadHandler *const handle,
			 void *arg)
{
	const char *restrict failure;

	if (thread_key_delete_report(key,
				     &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
thread_key_delete_handle_cl(ThreadKey key,
			    ThreadHandlerClosure *const restrict cl)
{
	const char *restrict failure;

	if (thread_key_delete_report(key,
				     &failure))
		return;

	cl->handle(cl->arg,
		   failure);
	__builtin_unreachable();
}

/* ThreadAttr operations
 *─────────────────────────────────────────────────────────────────────────── */
/* thread_attr_init */
inline bool
thread_attr_init(ThreadAttr *const restrict attr)
{
	return thread_attr_init_imp(attr) == 0;
}

inline void
thread_attr_init_muffle(ThreadAttr *const restrict attr)
{
	(void) thread_attr_init_imp(attr);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE thread_attr_init_imp
inline bool
thread_attr_init_report(ThreadAttr *const restrict attr,
			const char *restrict *const restrict failure)
{
	FAIL_SWITCH_STATUS_OPEN(attr)
	FAIL_SWITCH_STATUS_CASE_1(ENOMEM,
				  "out of memory")
	FAIL_SWITCH_STATUS_CLOSE()
}

inline void
thread_attr_init_handle(ThreadAttr *const restrict attr,
			ThreadHandler *const handle,
			void *arg)
{
	const char *restrict failure;

	if (thread_attr_init_report(attr,
				    &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
thread_attr_init_handle_cl(ThreadAttr *const restrict attr,
			   ThreadHandlerClosure *const restrict cl)
{
	const char *restrict failure;

	if (thread_attr_init_report(attr,
				    &failure))
		return;

	cl->handle(cl->arg,
		   failure);
	__builtin_unreachable();
}


/* thread_attr_set_detach_state */
inline bool
thread_attr_set_detach_state(ThreadAttr *const restrict attr,
			     const int state)
{
	return thread_attr_set_detach_state_imp(attr,
						state) == 0;
}
inline bool
thread_attr_set_detach_state_muffle(ThreadAttr *const restrict attr,
				    const int state)
{
	void thread_attr_set_detach_state_imp(attr,
					      state);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE thread_attr_set_detach_state_imp
inline bool
thread_attr_set_detach_state_report(ThreadAttr *const restrict attr,
				    const int state,
				    const char *restrict *const restrict failure)
{
	FAIL_SWITCH_STATUS_OPEN(attr,
				state)
	FAIL_SWITCH_STATUS_CASE_1(EINVAL,
				  "invalid value for 'attr' or 'state'")
	FAIL_SWITCH_STATUS_CLOSE()
}

inline void
thread_attr_set_detach_state_handle(ThreadAttr *const restrict attr,
				    const int state,
				    ThreadHandler *const handle,
				    void *arg)
{
	const char *restrict failure;

	if(thread_attr_set_detach_state_report(attr,
					       state,
					       &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
thread_attr_set_detach_state_handle_cl(ThreadAttr *const restrict attr,
				       const int state,
				       ThreadHandlerClosure *const restrict cl)
{
	const char *restrict failure;

	if(thread_attr_set_detach_state_report(attr,
					       state,
					       &failure))
		return;

	cl->handle(cl->arg,
		   failure);
	__builtin_unreachable();
}


/* thread_attr_destroy */
inline bool
thread_attr_destroy(ThreadAttr *const restrict attr)
{
	return thread_attr_destroy_imp(attr) == 0;
}

inline void
thread_attr_destroy_muffle(ThreadAttr *const restrict attr)
{
	(void) thread_attr_destroy_imp(attr);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE thread_attr_destroy_imp
inline bool
thread_attr_destroy_report(ThreadAttr *const restrict attr,
			   const char *restrict *const restrict failure)
{
	FAIL_SWITCH_STATUS_OPEN(attr)
	FAIL_SWITCH_STATUS_CASE_1(EINVAL,
				  "invalid value for 'attr'")
	FAIL_SWITCH_STATUS_CLOSE()
}

inline void
thread_attr_destroy_handle(ThreadAttr *const restrict attr,
			   ThreadHandler *const handle,
			   void *arg)
{
	const char *restrict failure;

	if (!thread_attr_destroy_report(attr,
					&failure)) {
		handle(arg,
		       failure);

		__builtin_unreachable();
	}
}

inline void
thread_attr_destroy_handle_cl(ThreadAttr *const restrict attr,
			      ThreadHandlerClosure *const restrict cl)
{
	const char *restrict failure;

	if (!thread_attr_destroy_report(attr,
					&failure)) {
		cl->handle(cl->arg,
			   failure);

		__builtin_unreachable();
	}
}



/* Mutex operations
 *─────────────────────────────────────────────────────────────────────────── */
/* mutex_init */
inline void
mutex_init(Mutex *const restrict lock)
{
	mutex_init_imp(lock);
}

/* mutex_lock */
inline bool
mutex_lock(Mutex *const lock)
{
	mutex_lock_imp(lock);
}

inline bool
mutex_lock_muffle(Mutex *const lock)
{
	(void) mutex_lock_imp(lock);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE mutex_lock_imp
inline bool
mutex_lock_report(Mutex *const lock,
		  const char *restrict *const restrict failure)
{
	FAIL_SWITCH_STATUS_OPEN(lock)
	FAIL_SWITCH_STATUS_CASE_1(EDEADLK,
				  "A deadlock would occur if the thread blocked"
				  " waiting for Mutex 'lock'.")
	FAIL_SWITCH_STATUS_CASE_1(EINVAL,
				  "The value specified by Mutex 'lock' is "
				  "invalid.")
	FAIL_SWITCH_STATUS_CLOSE()
}

inline void
mutex_lock_handle(Mutex *const lock,
		  ThreadHandler *const handle,
		  void *arg);
{
	const char *restrict failure;

	if (!mutex_lock_report(lock,
			       &failure)) {
		handle(arg,
		       failure);

		__builtin_unreachable();
	}
}

inline void
mutex_lock_handle_cl(Mutex *const lock,
		     ThreadHandlerClosure *const restrict cl)
{
	const char *restrict failure;

	if (!mutex_lock_report(lock,
			       &failure)) {
		cl->handle(cl->arg,
			   failure);

		__builtin_unreachable();
	}
}

/* mutex_try_lock */
inline bool
mutex_try_lock(Mutex *const lock)
{
	return mutex_try_lock_imp(lock) == 0;
}

inline void
mutex_try_lock_muffle(Mutex *const lock)
{
	(void) mutex_try_lock_imp(lock);
}

/* since 3-value flag instead of bool is returned, can't use fail switch */
inline enum ThreadFlag
mutex_try_lock_report(Mutex *const lock,
		      const char *restrict *const restrict failure)
{
	switch (mutex_try_lock_imp(lock)) {
	case 0:
		return THREAD_TRUE;

	case EBUSY:
		return THREAD_FALSE;

	case EINVAL:
		*failure = FAILURE_REASONS_1("mutex_try_lock_imp",
					     "The value specified by Mutex "
					     "'lock' is invalid.");
		return THREAD_ERROR;

	default:
		*failure = FAILURE_REASONS_1("mutex_try_lock_imp",
					     "unknown");
		return THREAD_ERROR;
	}
}

inline bool
mutex_try_lock_handle(Mutex *const lock,
		      ThreadHandler *const handle,
		      void *arg)
{
	const char *restrict failure;

	const enum ThreadFlag acquired = mutex_try_lock_report(lock,
							       &failure);

	if (acquired != THREAD_ERROR)
		return (bool) aquired;

	handle(arg,
	       failure);

	__builtin_unreachable();
}

inline bool
mutex_try_lock_handle_cl(Mutex *const lock,
			 ThreadHandlerClosure *const restrict cl)
{
	const char *restrict failure;

	const enum ThreadFlag acquired = mutex_try_lock_report(lock,
							       &failure);

	if (acquired != THREAD_ERROR)
		return (bool) aquired;

	cl->handle(cl->arg,
		   failure);

	__builtin_unreachable();
}


inline bool
mutex_unlock(Mutex *const lock)
{
	return mutex_lock_imp(lock) == 0;
}

inline void
mutex_unlock_muffle(Mutex *const lock)
{
	(void) mutex_lock_imp(lock);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE mutex_unlock_imp
inline bool
mutex_unlock_report(Mutex *const lock,
		    const char *restrict *const restrict failure)
{
	FAIL_SWITCH_STATUS_OPEN(lock)
	FAIL_SWITCH_STATUS_CASE_1(EINVAL,
				  "The value specified by Mutex 'lock' is "
				  "invalid.")
	FAIL_SWITCH_STATUS_CASE_1(EINVAL,
				  "The current thread does not hold a lock on "
				  "Mutex 'lock'")
				  )
	FAIL_SWITCH_STATUS_CLOSE()
}

inline void
mutex_unlock_handle(Mutex *const lock,
		    ThreadHandler *const handle,
		    void *arg)
{
	const char *restrict failure;

	if (mutex_unlock_report(lock,
				&failure))
		return;

	handle(arg,
	       failure);

	__builtin_unreachable();
}

inline void
mutex_unlock_handle_cl(Mutex *const lock,
		       ThreadHandlerClosure *const restrict cl)
{
	const char *restrict failure;

	if (mutex_unlock_report(lock,
				&failure))
		return;

	cl->handle(cl->arg,
		   failure);

	__builtin_unreachable();
}


/* ThreadCond operations
 *─────────────────────────────────────────────────────────────────────────── */
/* thread_cond_init */
inline void
thread_cond_init(ThreadCond *const restrict cond)
{
	thread_cond_init_imp(cond);
}


/* thread_cond_signal */
inline bool
thread_cond_signal(ThreadCond *const restrict cond)
{
	return thread_cond_signal_imp(cond) == 0;
}

inline void
thread_cond_signal_muffle(ThreadCond *const restrict cond)
{
	(void) thread_cond_signal_imp(cond);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE thread_cond_signal_imp
inline bool
thread_cond_signal_report(ThreadCond *const restrict cond,
			  const char *restrict *const restrict failure)
{
	FAIL_SWITCH_STATUS_OPEN(cond)
	FAIL_SWITCH_STATUS_CASE_1(EINVAL,
				  "The value specified by 'cond' is invalid.")
	FAIL_SWITCH_STATUS_CLOSE()
}

inline void
thread_cond_signal_handle(ThreadCond *const restrict cond,
			  ThreadHandler *const handle,
			  void *arg)
{
	const char *restrict failure;

	if (thread_cond_signal_report(cond,
				      &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
thread_cond_signal_handle_cl(ThreadCond *const restrict cond,
			     ThreadHandlerClosure *const restrict cl)
{
	const char *restrict failure;

	if (thread_cond_signal_report(cond,
				      &failure))
		return;

	cl->handle(cl->arg,
		   failure);
	__builtin_unreachable();
}


/* thread_cond_broadcast */
inline bool
thread_cond_broadcast(ThreadCond *const restrict cond)
{
	return thread_cond_broadcast_imp(cond) == 0;
}

inline void
thread_cond_broadcast_muffle(ThreadCond *const restrict cond)
{
	(void) thread_cond_broadcast_imp(cond);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE thread_cond_broadcast_imp
inline bool
thread_cond_broadcast_report(ThreadCond *const restrict cond,
			     const char *restrict *const restrict failure)
{
	FAIL_SWITCH_STATUS_OPEN(cond)
	FAIL_SWITCH_STATUS_CASE_1(EINVAL,
				  "The value specified by 'cond' is invalid.")
	FAIL_SWITCH_STATUS_CLOSE()
}

inline void
thread_cond_broadcast_handle(ThreadCond *const restrict cond,
			     ThreadHandler *const handle,
			     void *arg)
{
	const char *restrict failure;

	if (thread_cond_broadcast_report(cond,
					 &failure))
		return;


	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
thread_cond_broadcast_handle_cl(ThreadCond *const restrict cond,
				ThreadHandlerClosure *const restrict cl)
{
	const char *restrict failure;

	if (thread_cond_broadcast_report(cond,
					 &failure))
		return;


	cl->handle(cl->arg,
		   failure);
	__builtin_unreachable();
}


/* thread_cond_await */
inline bool
thread_cond_await(ThreadCond *const restrict cond,
		  Mutex *const restrict lock)
{
	return thread_cond_await_imp(cond,
				     lock) == 0;
}

inline void
thread_cond_await_muffle(ThreadCond *const restrict cond,
			 Mutex *const restrict lock)
{
	void thread_cond_await_imp(cond,
				   lock);
}

#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE thread_cond_await_imp
inline bool
thread_cond_await_report(ThreadCond *const restrict cond,
			 Mutex *const restrict lock,
			 const char *restrict *const restrict failure)
{
	FAIL_SWITCH_STATUS_OPEN(cond,
				lock)
	FAIL_SWITCH_STATUS_CASE_1(EINVAL,
				  "The value specified by 'cond' or 'lock' is "
				  "invalid.")
	FAIL_SWITCH_STATUS_CLOSE()
}

inline void
thread_cond_await_handle(ThreadCond *const restrict cond,
			 Mutex *const restrict lock,
			 ThreadHandler *const handle,
			 void *arg)
{
	const char *restrict failure;

	if (thread_cond_await_report(cond,
				     lock,
				     &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
thread_cond_await_handle_cl(ThreadCond *const restrict cond,
			    Mutex *const restrict lock,
			    ThreadHandlerClosure *const restrict cl)
{
	const char *restrict failure;

	if (thread_cond_await_report(cond,
				     lock,
				     &failure))
		return;

	cl->handle(cl->arg,
		   failure);
	__builtin_unreachable();
}


/* thread_cond_await_limit */
inline bool
thread_cond_await_limit(ThreadCond *const restrict cond,
			Mutex *const restrict lock,
			const struct timespec *const restrict limit)
{
	return thread_cond_await_limit_imp(cond,
					   lock,
					   limit) == 0;
}

inline void
thread_cond_await_limit_muffle(ThreadCond *const restrict cond,
			       Mutex *const restrict lock,
			       const struct timespec *const restrict limit)
{
	(void) thread_cond_await_limit_imp(cond,
					   lock,
					   limit);
}


#undef  FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE thread_cond_await_limit_imp
inline bool
thread_cond_await_limit_report(ThreadCond *const restrict cond,
			       Mutex *const restrict lock,
			       const struct timespec *const restrict limit,
			       const char *restrict *const restrict failure)
{
	FAIL_SWITCH_STATUS_OPEN(cond,
				lock,
				limit)
	FAIL_SWITCH_STATUS_CASE_1(EINVAL,
				  "The value specified by 'cond', 'lock', or "
				  " 'limit' is invalid.")
	FAIL_SWITCH_STATUS_CASE_1(ETIMEDOUT,
				  "The system time has reached or exceeded the "
				  "time specified in 'limit'.")
	FAIL_SWITCH_STATUS_CLOSE()
}

inline void
thread_cond_await_limit_handle(ThreadCond *const restrict cond,
			       Mutex *const restrict lock,
			       const struct timespec *const restrict limit,
			       ThreadHandler *const handle,
			       void *arg)
{
	const char *restrict failure;

	if (thread_cond_await_limit_report(cond,
					   lock,
					   limit,
					   &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
thread_cond_await_limit_handle_cl(ThreadCond *const restrict cond,
				  Mutex *const restrict lock,
				  const struct timespec *const restrict limit,
				  ThreadHandlerClosure *const restrict cl)
{
	const char *restrict failure;

	if (thread_cond_await_limit_report(cond,
					   lock,
					   limit,
					   &failure))
		return;

	cl->handle(cl->arg,
		   failure);
	__builtin_unreachable();
}


/* thread_cond_await_span */
inline bool
thread_cond_await_span(ThreadCond *const restrict cond,
		       Mutex *const restrict lock,
		       const struct timespec *const restrict span)
{
	struct timespec limit;

	timespec_offset_now(&limit,
			    span);

	return thread_cond_await_limit(cond,
				       lock,
				       &limit);
}

inline void
thread_cond_await_span_muffle(ThreadCond *const restrict cond,
			      Mutex *const restrict lock,
			      const struct timespec *const restrict span)
{
	struct timespec limit;

	timespec_offset_now(&limit,
			    span);

	thread_cond_await_limit_muffle(cond,
				       lock,
				       &limit);
}

inline bool
thread_cond_await_span_report(ThreadCond *const restrict cond,
			      Mutex *const restrict lock,
			      const struct timespec *const restrict span,
			      const char *restrict *const restrict failure)
{
	struct timespec limit;

	timespec_offset_now(&limit,
			    span);

	return thread_cond_await_limit_report(cond,
					      lock,
					      &limit,
					      failure);
}

inline void
thread_cond_await_span_handle(ThreadCond *const restrict cond,
			      Mutex *const restrict lock,
			      const struct timespec *const restrict span,
			      ThreadHandler *const handle,
			      void *arg)
{
	const char *restrict failure;

	if (thread_cond_await_span_report(cond,
					  lock,
					  span,
					  &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
thread_cond_await_span_handle_cl(ThreadCond *const restrict cond,
				 Mutex *const restrict lock,
				 const struct timespec *const restrict span,
				 ThreadHandlerClosure *const restrict cl)
{
	const char *restrict failure;

	if (thread_cond_await_span_report(cond,
					  lock,
					  span,
					  &failure))
		return;

	cl->handle(cl->arg,
		   failure);
	__builtin_unreachable();
}



/* Prototypes
 *─────────────────────────────────────────────────────────────────────────── */
inline void
thread_attr_prototype_init(void)
{
	thread_attr_init_muffle(&thread_attr_prototype);

	thread_attr_set_detach_state_muffle(&thread_attr_prototype,
					    THREAD_ATTR_DETACHED);
}

inline void
thread_attr_prototype_destroy(void)
{
	thread_attr_destroy_muffle(&thread_attr_prototype);
}



/* Constructors, Destructors
 *─────────────────────────────────────────────────────────────────────────── */
void
parallel_start(void)
__attribute__((constructor));

void
parallel_stop(void)
__attribute__((destructor));

#endif /* ifndef MYSQL_SEED_THREAD_THREAD_UTILS_H_ */
