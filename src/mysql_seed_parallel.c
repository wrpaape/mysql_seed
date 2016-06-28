#include "mysql_seed_parallel.h"


const SeedMutex seed_mutex_prototype		= SEED_MUTEX_INITIALIZER;
const SeedThreadCond seed_thread_cond_prototype = SEED_THREAD_COND_INITIALIZER;
SeedThreadAttr seed_thread_attr_prototype;

struct SeedSupervisor supervisor = {
	.dead = { .lock = SEED_MUTEX_INITIALIZER, .head = NULL, .last = NULL },
	.live = { .lock = SEED_MUTEX_INITIALIZER, .head = NULL, .last = NULL },
	.workers = {
		[ 0u] = { .id  =  0u, .prev = NULL, .next = NULL },
		[ 1u] = { .id  =  1u, .prev = NULL, .next = NULL },
		[ 2u] = { .id  =  2u, .prev = NULL, .next = NULL },
		[ 3u] = { .id  =  3u, .prev = NULL, .next = NULL },
		[ 4u] = { .id  =  4u, .prev = NULL, .next = NULL },
		[ 5u] = { .id  =  5u, .prev = NULL, .next = NULL },
		[ 6u] = { .id  =  6u, .prev = NULL, .next = NULL },
		[ 7u] = { .id  =  7u, .prev = NULL, .next = NULL },
		[ 8u] = { .id  =  8u, .prev = NULL, .next = NULL },
		[ 9u] = { .id  =  9u, .prev = NULL, .next = NULL },
		[10u] = { .id  = 10u, .prev = NULL, .next = NULL },
		[11u] = { .id  = 11u, .prev = NULL, .next = NULL },
		[12u] = { .id  = 12u, .prev = NULL, .next = NULL },
		[13u] = { .id  = 13u, .prev = NULL, .next = NULL },
		[14u] = { .id  = 14u, .prev = NULL, .next = NULL },
		[15u] = { .id  = 15u, .prev = NULL, .next = NULL }
	}
};

/* SeedSupervisor operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
seed_supervisor_init(void);

void
seed_supervisor_exit(const char *restrict failure)
{
	struct SeedWorker *restrict worker;
	struct SeedExitSpec spec;

	(void) seed_mutex_lock_imp(&supervisor.live.lock);

	while (1) {
		worker = worker_queue_pop(&supervisor.live);

		if (worker == NULL)
			break;

		(void) seed_thread_cancel_imp(worker->thread);
	}

	seed_exit_spec_set_failure(&spec,
				   failure);

	seed_exit_spec_exit(&spec);
}


/* SeedThread operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline bool
seed_thread_create(SeedThread *const restrict thread,
		   SeedWorkerRoutine *const routine,
		   void *arg,
		   const char *restrict *const restrict message_ptr);

extern inline void
seed_thread_handle_create(SeedThread *const restrict thread,
			  SeedWorkerRoutine *const routine,
			  void *arg);

extern inline bool
seed_thread_cancel(SeedThread thread,
		   const char *restrict *const restrict message_ptr);

extern inline void
seed_thread_handle_cancel(SeedThread thread);


/* SeedThreadAttr operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline bool
seed_thread_attr_init(SeedThreadAttr *const restrict attr,
		      const char *restrict *const restrict message_ptr);

extern inline void
seed_thread_attr_handle_init(SeedThreadAttr *const restrict attr);

extern inline bool
seed_thread_attr_set_detach_state(SeedThreadAttr *const restrict attr,
				  const int state,
				  const char *restrict *const restrict message_ptr);

extern inline void
seed_thread_attr_handle_set_detach_state(SeedThreadAttr *const restrict attr,
					 const int state);

/* SeedThreadKey operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline bool
seed_thread_key_create(SeedThreadKey *const key,
		       SeedWorkerHandler *const handle,
		       const char *restrict *const restrict message_ptr);

extern inline void
seed_thread_key_handle_create(SeedThreadKey *const key,
			      SeedWorkerHandler *const handle);

extern inline bool
seed_thread_key_delete(SeedThreadKey key,
		       const char *restrict *const restrict message_ptr);

extern inline void
seed_thread_key_handle_delete(SeedThreadKey key);


/* SeedMutex operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
seed_mutex_init(SeedMutex *const restrict lock);

extern inline void
seed_mutex_handle_init(SeedMutex *const restrict lock);

extern inline bool
seed_mutex_lock(SeedMutex *const lock,
		const char *restrict *restrict message_ptr);

extern inline bool
seed_mutex_unlock(SeedMutex *const lock,
		  const char *restrict *const restrict message_ptr);

extern inline void
seed_mutex_handle_lock(SeedMutex *const restrict lock);

extern inline void
seed_mutex_handle_unlock(SeedMutex *const restrict lock);


/* SeedThreadCond operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
seed_thread_cond_init(SeedThreadCond *const restrict cond);

extern inline void
seed_thread_cond_handle_init(SeedThreadCond *const restrict cond);

extern inline bool
seed_thread_cond_signal(SeedThreadCond *const restrict cond,
		      const char *restrict *const restrict message_ptr);
extern inline void
seed_thread_cond_handle_signal(SeedThreadCond *const restrict cond);

extern inline bool
seed_thread_cond_broadcast(SeedThreadCond *const restrict cond,
			 const char *restrict *const restrict message_ptr);
extern inline void
seed_thread_cond_handle_broadcast(SeedThreadCond *const restrict cond);

extern inline bool
seed_thread_cond_await(SeedThreadCond *const restrict cond,
		     SeedMutex *const restrict lock,
		     const char *restrict *const restrict message_ptr);
extern inline void
seed_thread_cond_handle_await(SeedThreadCond *const restrict cond,
			    SeedMutex *const restrict lock);
extern inline bool
seed_thread_cond_await_limit(SeedThreadCond *const restrict cond,
			   SeedMutex *const restrict lock,
			   const struct timespec *const restrict limit,
			   const char *restrict *const restrict message_ptr);
extern inline void
seed_thread_cond_handle_await_limit(SeedThreadCond *const restrict cond,
				  SeedMutex *const restrict lock,
				  const struct timespec *const restrict limit);
extern inline bool
seed_thread_cond_await_span(SeedThreadCond *const restrict cond,
			  SeedMutex *const restrict lock,
			  const struct timespec *const restrict span,
			  const char *restrict *const restrict message_ptr);
extern inline void
seed_thread_cond_handle_await_span(SeedThreadCond *const restrict cond,
				   SeedMutex *const restrict lock,
				   const struct timespec *const restrict span);

/* SeedWorkerQueue operations
 *─────────────────────────────────────────────────────────────────────────── */
/* LIFO push */
extern inline void
worker_queue_push(struct SeedWorkerQueue *const restrict queue,
		  struct SeedWorker *const restrict worker);

extern inline void
worker_queue_handle_push(struct SeedWorkerQueue *const restrict queue,
			 struct SeedWorker *const restrict worker);

/* LIFO pop */
extern inline struct SeedWorker *
worker_queue_pop(struct SeedWorkerQueue *const restrict queue);

extern inline struct SeedWorker *
worker_queue_handle_pop(struct SeedWorkerQueue *const restrict queue);

/* random access delete */
extern inline void
worker_queue_remove(struct SeedWorkerQueue *const restrict queue,
		    struct SeedWorker *const restrict worker);

extern inline void
worker_queue_handle_remove(struct SeedWorkerQueue *const restrict queue,
			   struct SeedWorker *const restrict worker);

/* SeedWorker operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline struct SeedWorker *
seed_worker_fetch(const SeedWorkerID id);


extern inline void
seed_worker_exit_clean_up(void *arg);


void *
seed_worker_start_routine(void *arg)
{
	struct SeedWorker *const restrict
	worker = (struct SeedWorker *const restrict) arg;

	seed_thread_key_handle_create(&worker->key,
				      &seed_worker_exit_clean_up);

	return worker->routine(worker->arg);
}

extern inline SeedWorkerID
seed_worker_start(SeedWorkerRoutine *const routine,
		  void *arg);



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

