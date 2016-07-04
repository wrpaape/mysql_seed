#include "thread/thread_utils.h"

/* global variables
 *─────────────────────────────────────────────────────────────────────────── */
const Mutex mutex_prototype	       = MUTEX_INITIALIZER;
const ThreadCond thread_cond_prototype = THREAD_COND_INITIALIZER;
ThreadAttr thread_attr_prototype;

/* Thread operations
 *─────────────────────────────────────────────────────────────────────────── */
/* thread_create */
extern inline bool
thread_create_status(Thread *const restrict thread,
		     Routine *const routine,
		     void *arg);

extern inline void
thread_create_muffle(Thread *const restrict thread,
		     Routine *const routine,
		     void *arg);
extern inline bool
thread_create_report(Thread *const restrict thread,
		     Routine *const routine,
		     void *arg,
		     const char *restrict *const restrict failure);
extern inline void
thread_create_handle(Thread *const restrict thread,
		     Routine *const routine,
		     void *r_arg,
		     Handler *const handle,
		     void *h_arg);
extern inline void
thread_create_handle_cl(Thread *const restrict thread,
			Routine *const routine,
			void *r_arg,
			const struct HandlerClosure *const restrict cl);

/* thread_create_cl */
extern inline bool
thread_create_cl_status(Thread *const restrict thread,
			const struct RoutineClosure *const restrict cl);
extern inline void
thread_create_cl_muffle(Thread *const restrict thread,
			const struct RoutineClosure *const restrict cl);
extern inline bool
thread_create_cl_report(Thread *const restrict thread,
			const struct RoutineClosure *const restrict cl,
			const char *restrict *const restrict failure);
extern inline void
thread_create_cl_handle(Thread *const restrict thread,
			const struct RoutineClosure *const restrict cl,
			Handler *const handle,
			void *h_arg);
extern inline void
thread_create_cl_handle_cl(Thread *const restrict thread,
			   const struct RoutineClosure *const restrict r_cl,
			   const struct HandlerClosure *const restrict h_cl);

/* thread_cancel */
extern inline bool
thread_cancel_status(Thread thread);
extern inline void
thread_cancel_muffle(Thread thread);
extern inline bool
thread_cancel_report(Thread thread,
		     const char *restrict *const restrict failure);
extern inline void
thread_cancel_handle(Thread thread,
		     Handler *const handle,
		     void *arg);
extern inline void
thread_cancel_handle_cl(Thread thread,
			const struct HandlerClosure *const restrict cl);

/* thread_exit */
extern inline void
thread_exit_detached(void);

extern inline void
thread_exit_joinable(void *pointer);

/* thread_self */
extern inline Thread
thread_self(void);

/* threads_equal */
extern inline bool
threads_equal(const Thread thread1,
	      const Thread thread2);


/* ThreadKey operations
 *─────────────────────────────────────────────────────────────────────────── */
/* thread_key_create */
extern inline bool
thread_key_create_status(ThreadKey *const key,
			 Procedure *const cleanup);
extern inline void
thread_key_create_muffle(ThreadKey *const key,
			 Procedure *const cleanup);
extern inline bool
thread_key_create_report(ThreadKey *const key,
			 Procedure *const cleanup,
			 const char *restrict *const restrict failure);
extern inline void
thread_key_create_handle(ThreadKey *const key,
			 Procedure *const cleanup,
			 Handler *const handle,
			 void *arg);
extern inline void
thread_key_create_handle_cl(ThreadKey *const key,
			    Procedure *const cleanup,
			    const struct HandlerClosure *const restrict cl);

/* thread_key_delete */
extern inline bool
thread_key_delete_status(ThreadKey key);
extern inline void
thread_key_delete_muffle(ThreadKey key);
extern inline bool
thread_key_delete_report(ThreadKey key,
			 const char *restrict *const restrict failure);
extern inline void
thread_key_delete_handle(ThreadKey key,
			 Handler *const handle,
			 void *arg);
extern inline void
thread_key_delete_handle_cl(ThreadKey key,
			    const struct HandlerClosure *const restrict cl);


/* ThreadAttr operations
 *─────────────────────────────────────────────────────────────────────────── */
/* thread_attr_init */
extern inline bool
thread_attr_init_status(ThreadAttr *const restrict attr);
extern inline void
thread_attr_init_muffle(ThreadAttr *const restrict attr);
extern inline bool
thread_attr_init_report(ThreadAttr *const restrict attr,
			const char *restrict *const restrict failure);
extern inline void
thread_attr_init_handle(ThreadAttr *const restrict attr,
			Handler *const handle,
			void *arg);
extern inline void
thread_attr_init_handle_cl(ThreadAttr *const restrict attr,
			   const struct HandlerClosure *const restrict cl);

/* thread_attr_set_detach_state */
extern inline bool
thread_attr_set_detach_state_status(ThreadAttr *const restrict attr,
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
				    Handler *const handle,
				    void *arg);
extern inline void
thread_attr_set_detach_state_handle_cl(ThreadAttr *const restrict attr,
				       const int state,
				       const struct HandlerClosure *const restrict cl);

/* thread_attr_destroy */
extern inline bool
thread_attr_destroy_status(ThreadAttr *const restrict attr);

extern inline void
thread_attr_destroy_muffle(ThreadAttr *const restrict attr);

extern inline bool
thread_attr_destroy_report(ThreadAttr *const restrict attr,
			   const char *restrict *const restrict failure);
extern inline void
thread_attr_destroy_handle(ThreadAttr *const restrict attr,
			   Handler *const handle,
			   void *arg);
extern inline void
thread_attr_destroy_handle_cl(ThreadAttr *const restrict attr,
			      const struct HandlerClosure *const restrict cl);


/* Mutex operations
 *─────────────────────────────────────────────────────────────────────────── */
/* mutex_init */
extern inline void
mutex_init(Mutex *const restrict lock);

/* mutex_lock */
extern inline bool
mutex_lock_status(Mutex *const restrict lock);
extern inline void
mutex_lock_muffle(Mutex *const restrict lock);
extern inline bool
mutex_lock_report(Mutex *const restrict lock,
		  const char *restrict *restrict failure);
extern inline void
mutex_lock_handle(Mutex *const restrict lock,
		  Handler *const handle,
		  void *arg);
extern inline void
mutex_lock_handle_cl(Mutex *const restrict lock,
		     const struct HandlerClosure *const restrict cl);

/* mutex_try_lock */
extern inline enum ThreadFlag
mutex_try_lock_status(Mutex *const restrict lock);
extern inline bool
mutex_try_lock_muffle(Mutex *const restrict lock);
extern inline enum ThreadFlag
mutex_try_lock_report(Mutex *const restrict lock,
		      const char *restrict *const restrict failure);
extern inline bool
mutex_try_lock_handle(Mutex *const restrict lock,
		      Handler *const handle,
		      void *arg);
extern inline bool
mutex_try_lock_handle_cl(Mutex *const restrict lock,
			 const struct HandlerClosure *const restrict cl);

/* mutex_unlock */
extern inline bool
mutex_unlock_status(Mutex *const restrict lock);
extern inline void
mutex_unlock_muffle(Mutex *const restrict lock);
extern inline bool
mutex_unlock_report(Mutex *const restrict lock,
		    const char *restrict *const restrict failure);
extern inline void
mutex_unlock_handle(Mutex *const restrict lock,
		    Handler *const handle,
		    void *arg);
extern inline void
mutex_unlock_handle_cl(Mutex *const restrict lock,
		       const struct HandlerClosure *const restrict cl);

/* mutex_ensure_unlocked */
extern inline bool
mutex_ensure_unlocked_status(Mutex *const restrict lock);
extern inline void
mutex_ensure_unlocked_muffle(Mutex *const restrict lock);
extern inline bool
mutex_ensure_unlocked_report(Mutex *const restrict lock,
			     const char *restrict *const restrict failure);
extern inline void
mutex_ensure_unlocked_handle(Mutex *const restrict lock,
			     Handler *const handle,
			     void *arg);
extern inline void
mutex_ensure_unlocked_handle_cl(Mutex *const restrict lock,
				const struct HandlerClosure *const restrict cl);

/* mutex_lock_cleanup */
void
mutex_lock_cleanup(void *arg)
{
	Mutex *const restrict lock = (Mutex *const restrict) arg;

	if (mutex_try_lock_muffle(lock))
		mutex_unlock_muffle(lock);
}

/* ThreadCond operations
 *─────────────────────────────────────────────────────────────────────────── */
/* thread_cond_init */
extern inline void
thread_cond_init(ThreadCond *const restrict cond);

/* thread_cond_signal */
extern inline bool
thread_cond_signal_status(ThreadCond *const restrict cond);
extern inline void
thread_cond_signal_muffle(ThreadCond *const restrict cond);
extern inline bool
thread_cond_signal_report(ThreadCond *const restrict cond,
			  const char *restrict *const restrict failure);
extern inline void
thread_cond_signal_handle(ThreadCond *const restrict cond,
			  Handler *const handle,
			  void *arg);
extern inline void
thread_cond_signal_handle_cl(ThreadCond *const restrict cond,
			     const struct HandlerClosure *const restrict cl);


/* thread_cond_broadcast */
extern inline bool
thread_cond_broadcast_status(ThreadCond *const restrict cond);
extern inline void
thread_cond_broadcast_muffle(ThreadCond *const restrict cond);
extern inline bool
thread_cond_broadcast_report(ThreadCond *const restrict cond,
			     const char *restrict *const restrict failure);
extern inline void
thread_cond_broadcast_handle(ThreadCond *const restrict cond,
			     Handler *const handle,
			     void *arg);
extern inline void
thread_cond_broadcast_handle_cl(ThreadCond *const restrict cond,
				const struct HandlerClosure *const restrict cl);

/* thread_cond_await */
extern inline bool
thread_cond_await_status(ThreadCond *const restrict cond,
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
			 Handler *const handle,
			 void *arg);
extern inline void
thread_cond_await_handle_cl(ThreadCond *const restrict cond,
			    Mutex *const restrict lock,
			    const struct HandlerClosure *const restrict cl);

/* thread_cond_await_limit */
extern inline bool
thread_cond_await_limit_status(ThreadCond *const restrict cond,
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
			       Handler *const handle,
			       void *arg);
extern inline void
thread_cond_await_limit_handle_cl(ThreadCond *const restrict cond,
				  Mutex *const restrict lock,
				  const struct timespec *const restrict limit,
				  const struct HandlerClosure *const restrict cl);

/* thread_cond_await_span */
extern inline bool
thread_cond_await_span_status(ThreadCond *const restrict cond,
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
			      Handler *const handle,
			      void *arg);
extern inline void
thread_cond_await_span_handle_cl(ThreadCond *const restrict cond,
				 Mutex *const restrict lock,
				 const struct timespec *const restrict span,
				 const struct HandlerClosure *const restrict cl);


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
