#include "thread/thread.h"

/* global variables
 *─────────────────────────────────────────────────────────────────────────── */
const Mutex mutex_prototype	       = MUTEX_INITIALIZER;
const ThreadCond thread_cond_prototype = THREAD_COND_INITIALIZER;
ThreadAttr thread_attr_prototype;

/* Thread operations
 *─────────────────────────────────────────────────────────────────────────── */
/* thread_create */
extern inline bool
thread_create(Thread *const restrict thread,
	      ThreadRoutine *const routine,
	      void *arg);

extern inline void
thread_create_muffle(Thread *const restrict thread,
		     ThreadRoutine *const routine,
		     void *arg);
extern inline bool
thread_create_report(Thread *const restrict thread,
		     ThreadRoutine *const routine,
		     void *arg,
		     const char *restrict *const restrict failure);
extern inline void
thread_create_handle(Thread *const restrict thread,
		     ThreadRoutine *const routine,
		     void *routine_arg,
		     ThreadHandler *const handle,
		     void *handler_arg);
extern inline void
thread_create_handle_cl(Thread *const restrict thread,
			ThreadRoutine *const routine,
			void *routine_arg,
			ThreadHandlerClosure *const restrict cl);

/* thread_create_cl */
extern inline bool
thread_create_cl(Thread *const restrict thread,
		 ThreadRoutineClosure *const restrict cl);
extern inline void
thread_create_cl_muffle(Thread *const restrict thread,
			ThreadRoutineClosure *const restrict cl);
extern inline bool
thread_create_cl_report(Thread *const restrict thread,
			ThreadRoutineClosure *const restrict cl,
			const char *restrict *const restrict failure);
extern inline void
thread_create_cl_handle(Thread *const restrict thread,
			ThreadRoutineClosure *const restrict cl,
			ThreadHandler *const handle,
			void *handler_arg);

extern inline void
thread_create_cl_handle_cl(Thread *const restrict thread,
			   ThreadRoutineClosure *const restrict routine_cl,
			   ThreadHandlerClosure *const restrict handler_cl);


/* thread_cancel */
extern inline bool
thread_cancel(Thread thread);

extern inline void
thread_cancel_muffle(Thread thread);

extern inline bool
thread_cancel_report(Thread thread,
		     const char *restrict *const restrict failure);

extern inline void
thread_cancel_handle(Thread thread,
		     ThreadHandler *const handle,
		     void *arg);

extern inline void
thread_cancel_handle_cl(Thread thread,
			ThreadHandlerClosure *const restrict cl);

/* thread_exit */
extern inline void
thread_exit_detached(void);

extern inline void
thread_exit_joinable(void *pointer);

/* ThreadKey operations
 *─────────────────────────────────────────────────────────────────────────── */
/* thread_key_create */
extern inline bool
thread_key_create(ThreadKey *const key,
		  ThreadProcedure *const restrict cleanup);
extern inline void
thread_key_create_muffle(ThreadKey *const key,
			 ThreadProcedure *const cleanup);
extern inline bool
thread_key_create_report(ThreadKey *const key,
			 ThreadProcedure *const restrict cleanup,
			 const char *restrict *const restrict failure);
extern inline void
thread_key_create_handle(ThreadKey *const key,
			 ThreadProcedure *const restrict cleanup,
			 ThreadHandler *const handle,
			 void *arg);
extern inline void
thread_key_create_handle_cl(ThreadKey *const key,
			    ThreadProcedure *const restrict cleanup,
			    ThreadHandlerClosure *const restrict cl);

/* thread_key_delete */
extern inline bool
thread_key_delete(ThreadKey key);
extern inline void
thread_key_delete_muffle(ThreadKey key);
extern inline bool
thread_key_delete_report(ThreadKey key,
			 const char *restrict *const restrict failure);
extern inline void
thread_key_delete_handle(ThreadKey key,
			 ThreadHandler *const handle,
			 void *arg);
extern inline void
thread_key_delete_handle_cl(ThreadKey key,
			    ThreadHandlerClosure *const restrict cl);


/* ThreadAttr operations
 *─────────────────────────────────────────────────────────────────────────── */
/* thread_attr_init */
extern inline bool
thread_attr_init(ThreadAttr *const restrict attr);
extern inline void
thread_attr_init_muffle(ThreadAttr *const restrict attr);
extern inline bool
thread_attr_init_report(ThreadAttr *const restrict attr,
			const char *restrict *const restrict failure);
extern inline void
thread_attr_init_handle(ThreadAttr *const restrict attr,
			ThreadHandler *const handle,
			void *arg);
extern inline void
thread_attr_init_handle_cl(ThreadAttr *const restrict attr,
			   ThreadHandlerClosure *const restrict cl);

/* thread_attr_set_detach_state */
extern inline bool
thread_attr_set_detach_state(ThreadAttr *const restrict attr,
			     const int state);
extern inline void
thread_attr_set_detach_state_muffle(ThreadAttr *const restrict attr,
				    const int state);
extern inline bool
thread_attr_set_detach_state_report(ThreadAttr *const restrict attr,
				    const int state,
				    const char *restrict *const restrict failure);
extern inline void
thread_attr_set_detach_state_handle(ThreadAttr *const restrict attr,
				    const int state,
				    ThreadHandler *const handle,
				    void *arg);
extern inline void
thread_attr_set_detach_state_handle_cl(ThreadAttr *const restrict attr,
				       const int state,
				       ThreadHandlerClosure *const restrict cl);

/* thread_attr_destroy */
extern inline bool
thread_attr_destroy(ThreadAttr *const restrict attr);

extern inline void
thread_attr_destroy_muffle(ThreadAttr *const restrict attr);

extern inline bool
thread_attr_destroy_report(ThreadAttr *const restrict attr,
			   const char *restrict *const restrict failure);
extern inline void
thread_attr_destroy_handle(ThreadAttr *const restrict attr,
			   ThreadHandler *const handle,
			   void *arg);
extern inline void
thread_attr_destroy_handle_cl(ThreadAttr *const restrict attr,
			      ThreadHandlerClosure *const restrict cl);


/* Mutex operations
 *─────────────────────────────────────────────────────────────────────────── */
/* mutex_init */
extern inline void
mutex_init(Mutex *const restrict lock);

/* mutex_lock */
extern inline bool
mutex_lock(Mutex *const lock);
extern inline void
mutex_lock_muffle(Mutex *const lock);
extern inline bool
mutex_lock_report(Mutex *const lock,
		  const char *restrict *restrict failure);
extern inline void
mutex_lock_handle(Mutex *const lock,
		  ThreadHandler *const handle,
		  void *arg);
extern inline void
mutex_lock_handle_cl(Mutex *const lock,
		     ThreadHandlerClosure *const restrict cl);

/* mutex_try_lock */
extern inline bool
mutex_try_lock(Mutex *const lock);
extern inline void
mutex_try_lock_muffle(Mutex *const lock);
extern inline enum ThreadFlag
mutex_try_lock_report(Mutex *const lock,
		      const char *restrict *const restrict failure);
extern inline bool
mutex_try_lock_handle(Mutex *const lock,
		      ThreadHandler *const handle,
		      void *arg);
extern inline bool
mutex_try_lock_handle_cl(Mutex *const lock,
			 ThreadHandlerClosure *const restrict cl);

/* mutex_unlock */
extern inline bool
mutex_unlock(Mutex *const lock);
extern inline void
mutex_unlock_muffle(Mutex *const lock);
extern inline bool
mutex_unlock_report(Mutex *const lock,
		    const char *restrict *const restrict failure);
extern inline void
mutex_unlock_handle(Mutex *const lock,
		    ThreadHandler *const handle,
		    void *arg);
extern inline void
mutex_unlock_handle_cl(Mutex *const lock,
		       ThreadHandlerClosure *const restrict cl);


/* ThreadCond operations
 *─────────────────────────────────────────────────────────────────────────── */
/* thread_cond_init */
extern inline void
thread_cond_init(ThreadCond *const restrict cond);

/* thread_cond_signal */
extern inline bool
thread_cond_signal(ThreadCond *const restrict cond);
extern inline bool
thread_cond_signal_muffle(ThreadCond *const restrict cond);
extern inline bool
thread_cond_signal_report(ThreadCond *const restrict cond,
			  const char *restrict *const restrict failure);
extern inline void
thread_cond_signal_handle(ThreadCond *const restrict cond,
			  ThreadHandler *const handle,
			  void *arg);
extern inline void
thread_cond_signal_handle_cl(ThreadCond *const restrict cond,
			     ThreadHandlerClosure *const restrict cl);


/* thread_cond_broadcast */
extern inline bool
thread_cond_broadcast(ThreadCond *const restrict cond);
extern inline void
thread_cond_broadcast_muffle(ThreadCond *const restrict cond);
extern inline bool
thread_cond_broadcast_report(ThreadCond *const restrict cond,
			     const char *restrict *const restrict failure);
extern inline void
thread_cond_broadcast_handle(ThreadCond *const restrict cond,
			     ThreadHandler *const handle,
			     void *arg);
extern inline void
thread_cond_broadcast_handle_cl(ThreadCond *const restrict cond,
				ThreadHandlerClosure *const restrict cl);

/* thread_cond_await */
extern inline bool
thread_cond_await(ThreadCond *const restrict cond,
		  Mutex *const restrict lock);
extern inline void
thread_cond_await_muffle(ThreadCond *const restrict cond,
			 Mutex *const restrict lock);
extern inline bool
thread_cond_await_report(ThreadCond *const restrict cond,
			 Mutex *const restrict lock,
			 const char *restrict *const restrict failure);
extern inline void
thread_cond_await_handle(ThreadCond *const restrict cond,
			 Mutex *const restrict lock,
			 ThreadHandler *const handle,
			 void *arg);
extern inline void
thread_cond_await_handle_cl(ThreadCond *const restrict cond,
			    Mutex *const restrict lock,
			    ThreadHandlerClosure *const restrict cl);

/* thread_cond_await_limit */
extern inline bool
thread_cond_await_limit(ThreadCond *const restrict cond,
			Mutex *const restrict lock,
			const struct timespec *const restrict limit);
extern inline void
thread_cond_await_limit_muffle(ThreadCond *const restrict cond,
			       Mutex *const restrict lock,
			       const struct timespec *const restrict limit);
extern inline bool
thread_cond_await_limit_report(ThreadCond *const restrict cond,
			       Mutex *const restrict lock,
			       const struct timespec *const restrict limit,
			       const char *restrict *const restrict failure);
extern inline void
thread_cond_await_limit_handle(ThreadCond *const restrict cond,
			       Mutex *const restrict lock,
			       const struct timespec *const restrict limit,
			       ThreadHandler *const handle,
			       void *arg);
extern inline void
thread_cond_await_limit_handle_cl(ThreadCond *const restrict cond,
				  Mutex *const restrict lock,
				  const struct timespec *const restrict limit,
				  ThreadHandlerClosure *const restrict cl);

/* thread_cond_await_span */
extern inline bool
thread_cond_await_span(ThreadCond *const restrict cond,
		       Mutex *const restrict lock,
		       const struct timespec *const restrict span);
extern inline void
thread_cond_await_span_muffle(ThreadCond *const restrict cond,
			      Mutex *const restrict lock,
			      const struct timespec *const restrict span);
extern inline bool
thread_cond_await_span_report(ThreadCond *const restrict cond,
			      Mutex *const restrict lock,
			      const struct timespec *const restrict span,
			      const char *restrict *const restrict failure);
extern inline void
thread_cond_await_span_handle(ThreadCond *const restrict cond,
			      Mutex *const restrict lock,
			      const struct timespec *const restrict span,
			      ThreadHandler *const handle,
			      void *arg);
extern inline void
thread_cond_await_span_handle_cl(ThreadCond *const restrict cond,
				 Mutex *const restrict lock,
				 const struct timespec *const restrict span,
				 ThreadHandlerClosure *const restrict cl);


/* Prototypes
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
thread_attr_prototype_init(void);

inline void
thread_attr_prototype_destroy(void);


/* Constructors, Destructors
 *─────────────────────────────────────────────────────────────────────────── */
void
parallel_start(void)
{
	thread_attr_prototype_init();
}

void
parallel_stop(void)
{
	thread_attr_prototype_destroy();
}
