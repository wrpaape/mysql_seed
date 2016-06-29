#include "mysql_seed_parallel.h"

/* global variables
 *─────────────────────────────────────────────────────────────────────────── */
#define SEED_SUPERVISOR_WORKER_STATIC_INITIALIZER(ID)	\
[ID] = {						\
	.id  =  ID,					\
	.done = SEED_THREAD_COND_INITIALIZER,		\
	.processing = SEED_MUTEX_INITIALIZER,		\
	.prev = NULL,					\
	.next = NULL					\
}

#define SEED_SUPERVISOR_WORKER_QUEUE_STATIC_INITIALIZER		\
{ .lock = SEED_MUTEX_INITIALIZER, .head = NULL, .last = NULL }

const SeedMutex seed_mutex_prototype		= SEED_MUTEX_INITIALIZER;
const SeedThreadCond seed_thread_cond_prototype = SEED_THREAD_COND_INITIALIZER;
SeedThreadAttr seed_thread_attr_prototype;

struct SeedSupervisor supervisor = {
	.dead	 = SEED_SUPERVISOR_WORKER_QUEUE_STATIC_INITIALIZER,
	.busy	 = SEED_SUPERVISOR_WORKER_QUEUE_STATIC_INITIALIZER,
	.done	 = SEED_SUPERVISOR_WORKER_QUEUE_STATIC_INITIALIZER,
	.workers = {
		SEED_SUPERVISOR_WORKER_STATIC_INITIALIZER( 0u),
		SEED_SUPERVISOR_WORKER_STATIC_INITIALIZER( 1u),
		SEED_SUPERVISOR_WORKER_STATIC_INITIALIZER( 2u),
		SEED_SUPERVISOR_WORKER_STATIC_INITIALIZER( 3u),
		SEED_SUPERVISOR_WORKER_STATIC_INITIALIZER( 4u),
		SEED_SUPERVISOR_WORKER_STATIC_INITIALIZER( 5u),
		SEED_SUPERVISOR_WORKER_STATIC_INITIALIZER( 6u),
		SEED_SUPERVISOR_WORKER_STATIC_INITIALIZER( 7u),
		SEED_SUPERVISOR_WORKER_STATIC_INITIALIZER( 8u),
		SEED_SUPERVISOR_WORKER_STATIC_INITIALIZER( 9u),
		SEED_SUPERVISOR_WORKER_STATIC_INITIALIZER(10u),
		SEED_SUPERVISOR_WORKER_STATIC_INITIALIZER(11u),
		SEED_SUPERVISOR_WORKER_STATIC_INITIALIZER(12u),
		SEED_SUPERVISOR_WORKER_STATIC_INITIALIZER(13u),
		SEED_SUPERVISOR_WORKER_STATIC_INITIALIZER(14u),
		SEED_SUPERVISOR_WORKER_STATIC_INITIALIZER(15u)
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

	(void) seed_mutex_lock_imp(&supervisor.done.lock);
	(void) seed_mutex_lock_imp(&supervisor.dead.lock);
	(void) seed_mutex_lock_imp(&supervisor.busy.lock);

	while (1) {
		worker = worker_queue_pop(&supervisor.busy);

		if (worker == NULL)
			break;

		(void) seed_thread_cancel_imp(worker->thread);
	}

	(void) seed_mutex_unlock_imp(&supervisor.busy.lock);
	(void) seed_mutex_unlock_imp(&supervisor.dead.lock);
	(void) seed_mutex_unlock_imp(&supervisor.done.lock);

	seed_exit_spec_set_failure(&spec,
				   failure);

	seed_exit_spec_exit(&spec);
}


/* SeedThread operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline bool
seed_thread_create(SeedThread *const restrict thread,
		   AwaitableRoutine *const routine,
		   void *arg,
		   const char *restrict *const restrict message_ptr);

extern inline void
seed_thread_handle_create(SeedThread *const restrict thread,
			  AwaitableRoutine *const routine,
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
		       IndependentRoutine *const handle,
		       const char *restrict *const restrict message_ptr);

extern inline void
seed_thread_key_handle_create(SeedThreadKey *const key,
			      IndependentRoutine *const handle);

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
seed_worker_exit_cleanup(void *arg);


void *
seed_worker_do_awaitable(void *arg)
{
	struct SeedWorker *const restrict
	worker = (struct SeedWorker *const restrict) arg;

	seed_mutex_handle_lock(&worker->processing);

	seed_thread_key_handle_create(&worker->key,
				      &seed_worker_exit_cleanup);

	worker->result = worker->routine.awaitable(worker->arg);

	seed_thread_key_handle_delete(worker->key);

	worker_queue_handle_remove(&supervisor.busy,
				   worker);

	worker_queue_handle_push(&supervisor.done,
				 worker);

	seed_thread_cond_handle_signal(&worker->done);

	seed_mutex_handle_unlock(&worker->processing);

	return NULL;
}

extern inline SeedWorkerID
seed_worker_spawn_awaitable(AwaitableRoutine *const routine,
			    void *arg);

void *
seed_worker_do_independent(void *arg)
{
	struct SeedWorker *const restrict
	worker = (struct SeedWorker *const restrict) arg;

	seed_thread_key_handle_create(&worker->key,
				      &seed_worker_exit_cleanup);

	worker->routine.independent(worker->arg);

	seed_thread_key_handle_delete(worker->key);

	worker_queue_handle_remove(&supervisor.busy,
				   worker);

	worker_queue_handle_push(&supervisor.dead,
				 worker);

	return NULL;
}

extern inline void
seed_worker_spawn_independent(IndependentRoutine *const routine,
			      void *arg);

inline void *
seed_worker_await(const SeedWorkerID id);

inline void *
seed_worker_await_limit(const SeedWorkerID id,
			const struct timespec *const restrict limit);

inline void *
seed_worker_await_span(const SeedWorkerID id,
		       const struct timespec *const restrict span);


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

