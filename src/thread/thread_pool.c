#include "thread/thread_pool.h"

/* Supervisor operations, ThreadPoolEvents
 *─────────────────────────────────────────────────────────────────────────── */
void
supervisor_exit_cleanup(void *arg)
{
	struct Supervisor *const restrict
	supervisor = (struct Supervisor *const restrict) arg;

	thread_key_delete_muffle(supervisor->key);

	struct ThreadPool *const restrict pool = supervisor->pool;

	mutex_lock_muffle(&pool->processing);

	pool->busy = false;

	thread_cond_signal_muffle(&pool->done);

	mutex_unlock_muffle(&pool->processing);

	/* release held mutexes? */
}
extern inline void
supervisor_cancel_workers(struct ThreadPool *const restrict pool);
extern inline void
supervisor_do_exit_failure(struct ThreadPool *const restrict pool);
void
supervisor_exit_on_failure(void *arg,
			   const char *restrict failure)
{
	struct ThreadPool *const restrict pool =
	(struct ThreadPool *const restrict) arg;

	thread_log_lock_muffle(&pool->log);

	thread_log_append_string(&pool->log,
				 failure);

	thread_log_unlock_muffle(&pool->log);

	supervisor_do_exit_failure(pool);
	__builtin_unreachable();
}
extern inline void
supervisor_init(struct Supervisor *const restrict supervisor,
		struct ThreadPool *const restrict pool);
extern inline void
supervisor_listen(struct Supervisor *const restrict supervisor);
extern inline void
supervisor_signal_event_muffle(struct Supervisor *const restrict supervisor,
			       ThreadPoolEvent *const event);

/* Worker operations
 *─────────────────────────────────────────────────────────────────────────── */
void
worker_exit_cleanup(void *arg)
{
	struct Worker *const restrict
	worker = (struct Worker *const restrict) arg;

	thread_key_delete_muffle(worker->key);

	/* release held mutexes? */
}
void
worker_exit_on_failure(void *arg,
		       const char *restrict failure)
{
	struct Worker *const restrict worker =
	(struct Worker *const restrict) arg;

	struct ThreadPool *const restrict pool = worker->pool;

	thread_log_lock_muffle(&pool->log);

	thread_log_append_string(&pool->log,
				 failure);

	thread_log_unlock_muffle(&pool->log);

	thread_queue_remove_muffle(&pool->workers,
				   worker->node);

	supervisor_signal_event_muffle(&pool->supervisor,
				       &supervisor_do_exit_failure);
	thread_exit_detached();

	__builtin_unreachable();
}

/* ThreadPool operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
thread_pool_init(struct ThreadPool *restrict pool,
		 size_t count_workers,
		 const struct HandlerClosure *const restrict init_fail_cl);




/* extern inline void */
/* worker_exit_cleanup(void *arg); */


/* void * */
/* worker_do_awaitable(void *arg) */
/* { */
/* 	struct Worker *const restrict */
/* 	worker = (struct Worker *const restrict) arg; */

/* 	mutex_handle_lock(&worker->processing); */

/* 	thread_key_handle_create(&worker->key, */
/* 				      &worker_exit_cleanup); */

/* 	worker->result = worker->routine.awaitable(worker->arg); */

/* 	worker->busy = false; */

/* 	thread_key_handle_delete(worker->key); */

/* 	worker_queue_handle_remove(&supervisor.busy, */
/* 				   worker); */

/* 	worker_queue_handle_push(&supervisor.done, */
/* 				 worker); */

/* 	mutex_handle_unlock(&worker->processing); */

/* 	thread_cond_handle_signal(&worker->done); */

/* 	return NULL; */
/* } */

/* /1* extern inline WorkerID *1/ */
/* /1* worker_spawn_awaitable(AwaitableRoutine *const routine, *1/ */
/* /1* 			    void *arg); *1/ */

/* void * */
/* worker_do_independent(void *arg) */
/* { */
/* 	struct Worker *const restrict */
/* 	worker = (struct Worker *const restrict) arg; */

/* 	thread_key_handle_create(&worker->key, */
/* 				      &worker_exit_cleanup); */

/* 	worker->routine.independent(worker->arg); */

/* 	thread_key_handle_delete(worker->key); */

/* 	worker_queue_handle_remove(&supervisor.busy, */
/* 				   worker); */

/* 	worker_queue_handle_push(&supervisor.idle, */
/* 				 worker); */

/* 	return NULL; */
/* } */

/* extern inline void */
/* worker_spawn_independent(IndependentRoutine *const routine, */
/* 			      void *arg); */

/* inline void * */
/* worker_await(const WorkerID id); */

/* inline void * */
/* worker_await_limit(const WorkerID id, */
/* 		   const struct timespec *const restrict limit); */

/* inline void * */
/* worker_await_span(const WorkerID id, */
/* 		       const struct timespec *const restrict span); */
