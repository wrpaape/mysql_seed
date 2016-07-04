#include "thread/thread_pool.h"

/* global variables
 *─────────────────────────────────────────────────────────────────────────── */

/* ThreadPool operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
thread_pool_cancel_workers(struct ThreadPool *const restrict pool);

void
thread_pool_exit_on_failure(void *arg,
			    const char *restrict failure);
{
	struct ThreadPool *const restrict pool =
	(struct ThreadPool *const restrict) arg;

	thread_log_lock_muffle(&pool->log);

	thread_log_append_string(&pool->log,
				 failure);

	thread_log_append_string(&pool->log,
				 THREAD_POOL_EXIT_ON_FAILURE_MESSAGE);

	thread_log_append_close(&pool->log);


	thread_log_dump_muffle(&pool->log,
			       STDERR_FILENO);

	/* signal to supervisor to cancel workers */

	thread_log_unlock_muffle(&pool->log);

	thread_exit_detached();

	__builtin_unreachable();
}

extern inline void
thread_pool_init(struct ThreadPool *restrict pool,
		 size_t count_workers,
		 const struct HandlerClosure *const restrict handle_init_fail);

/* void */
/* supervisor_exit(const char *restrict failure) */
/* { */
/* 	struct Worker *restrict worker; */
/* 	struct ExitSpec spec; */

/* 	(void) mutex_lock_imp(&supervisor.done.lock); */
/* 	(void) mutex_lock_imp(&supervisor.idle.lock); */
/* 	(void) mutex_lock_imp(&supervisor.busy.lock); */

/* 	while (1) { */
/* 		worker = worker_queue_pop(&supervisor.busy); */

/* 		if (worker == NULL) */
/* 			break; */

/* 		(void) thread_cancel_imp(worker->thread); */
/* 	} */

/* 	(void) mutex_unlock_imp(&supervisor.busy.lock); */
/* 	(void) mutex_unlock_imp(&supervisor.idle.lock); */
/* 	(void) mutex_unlock_imp(&supervisor.done.lock); */

/* 	exit_spec_set_failure(&spec, */
/* 				   failure); */

/* 	exit_spec_exit(&spec); */
/* } */

/* WorkerQueue operations
 *─────────────────────────────────────────────────────────────────────────── */

/* Worker operations
 *─────────────────────────────────────────────────────────────────────────── */

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
