#include "mysql_seed_parallel.h"

/* global variables
 *─────────────────────────────────────────────────────────────────────────── */
const SeedMutex seed_mutex_prototype		= SEED_MUTEX_INITIALIZER;
const SeedThreadCond seed_thread_cond_prototype = SEED_THREAD_COND_INITIALIZER;
SeedThreadAttr seed_thread_attr_prototype;

/* SeedThread operations
 *─────────────────────────────────────────────────────────────────────────── */
/* seed_thread_create */
extern inline bool
seed_thread_create(SeedThread *const restrict thread,
		   SeedThreadRoutine *const routine,
		   void *arg);
extern inline void
seed_thread_create_muffle(SeedThread *const restrict thread,
			  SeedThreadRoutine *const routine,
			  void *arg);
extern inline bool
seed_thread_create_report(SeedThread *const restrict thread,
			  SeedThreadRoutine *const routine,
			  void *arg,
			  const char *restrict *const restrict failure);
extern inline void
seed_thread_create_handle(SeedThread *const restrict thread,
			  SeedThreadRoutine *const routine,
			  void *routine_arg,
			  SeedThreadHandler *const handle,
			  void *handler_arg);
extern inline void
seed_thread_create_handle_closure(SeedThread *const restrict thread,
				  SeedThreadRoutine *const routine,
				  void *routine_arg,
				  SeedThreadHandler *const handle,
				  void *handler_arg);

/* seed_thread_create_closure */
extern inline bool
seed_thread_create_closure(SeedThread *const restrict thread,
			   SeedThreadRoutine *const routine,
			   void *arg);
extern inline void
seed_thread_create_closure_muffle(SeedThread *const restrict thread,
				  SeedThreadRoutine *const routine,
				  void *arg);
extern inline bool
seed_thread_create_closure_report(SeedThread *const restrict thread,
				  SeedThreadRoutine *const routine,
				  void *arg,
				  const char *restrict *const restrict failure);

extern inline void
seed_thread_create_closure_handle_closure(SeedThread *const restrict thread,
					  SeedThreadRoutine *const routine,
					  void *routine_arg,
					  SeedThreadHandler *const handle,
					  void *handler_arg);


extern inline void
seed_thread_cancel(SeedThread thread);

extern inline bool
seed_thread_cancel_report(SeedThread thread,
			  const char *restrict *const restrict failure);



/* SeedThreadKey operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
seed_thread_key_create(SeedThreadKey *const key,
		       IndependentRoutine *const handle);

extern inline bool
seed_thread_key_create_report(SeedThreadKey *const key,
			      IndependentRoutine *const handle,
			      const char *restrict *const restrict failure);

extern inline void
seed_thread_key_delete(SeedThreadKey key);

extern inline bool
seed_thread_key_delete_report(SeedThreadKey key,
			      const char *restrict *const restrict failure);


/* SeedThreadAttr operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline bool
seed_thread_attr_init(SeedThreadAttr *const restrict attr,
		      const char *restrict *const restrict failure);

extern inline bool
seed_thread_attr_set_detach_state(SeedThreadAttr *const restrict attr,
				  const int state,
				  const char *restrict *const restrict failure);


/* SeedMutex operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
seed_mutex_init(SeedMutex *const restrict lock);

extern inline bool
seed_mutex_lock(SeedMutex *const lock,
		const char *restrict *restrict failure);

inline void
seed_mutex_lock_ignore(SeedMutex *const lock);

extern inline bool
seed_mutex_try_lock(SeedMutex *const lock,
		    const char *restrict *const restrict failure);

extern inline void
seed_mutex_try_lock_ignore(SeedMutex *const lock);

extern inline bool
seed_mutex_unlock(SeedMutex *const lock,
		  const char *restrict *const restrict failure);

inline void
seed_mutex_unlock_ignore(SeedMutex *const lock);


/* SeedThreadCond operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
seed_thread_cond_init(SeedThreadCond *const restrict cond);

extern inline bool
seed_thread_cond_signal(SeedThreadCond *const restrict cond,
		      const char *restrict *const restrict failure);

extern inline bool
seed_thread_cond_broadcast(SeedThreadCond *const restrict cond,
			   const char *restrict *const restrict failure);

extern inline bool
seed_thread_cond_await(SeedThreadCond *const restrict cond,
		       SeedMutex *const restrict lock,
		       const char *restrict *const restrict failure);

extern inline bool
seed_thread_cond_await_limit(SeedThreadCond *const restrict cond,
			     SeedMutex *const restrict lock,
			     const struct timespec *const restrict limit,
			     const char *restrict *const restrict failure);

extern inline bool
seed_thread_cond_await_span(SeedThreadCond *const restrict cond,
			    SeedMutex *const restrict lock,
			    const struct timespec *const restrict span,
			    const char *restrict *const restrict failure);

/* Constructors, Destructors
 *─────────────────────────────────────────────────────────────────────────── */
void
seed_parallel_start(void)
{
	seed_supervisor_init();
	seed_thread_attr_prototype_init();
}

void
seed_parallel_stop(void)
{
	seed_thread_attr_prototype_destroy();
}
