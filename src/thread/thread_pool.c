#include "thread/thread_pool.h"

/* global variables
 *─────────────────────────────────────────────────────────────────────────── */

/* Supervisor operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
supervisor_init(void);

void
supervisor_exit(const char *restrict failure)
{
	struct Worker *restrict worker;
	struct ExitSpec spec;

	(void) mutex_lock_imp(&supervisor.done.lock);
	(void) mutex_lock_imp(&supervisor.idle.lock);
	(void) mutex_lock_imp(&supervisor.busy.lock);

	while (1) {
		worker = worker_queue_pop(&supervisor.busy);

		if (worker == NULL)
			break;

		(void) thread_cancel_imp(worker->thread);
	}

	(void) mutex_unlock_imp(&supervisor.busy.lock);
	(void) mutex_unlock_imp(&supervisor.idle.lock);
	(void) mutex_unlock_imp(&supervisor.done.lock);

	exit_spec_set_failure(&spec,
				   failure);

	exit_spec_exit(&spec);
}

/* WorkerQueue operations
 *─────────────────────────────────────────────────────────────────────────── */
/* LIFO push */
extern inline void
worker_queue_push(struct WorkerQueue *const restrict queue,
		  struct Worker *const restrict worker);

extern inline void
worker_queue_handle_push(struct WorkerQueue *const restrict queue,
			 struct Worker *const restrict worker);

/* LIFO pop */
extern inline struct Worker *
worker_queue_pop(struct WorkerQueue *const restrict queue);

extern inline struct Worker *
worker_queue_handle_pop(struct WorkerQueue *const restrict queue);

/* random access delete */
extern inline void
worker_queue_remove(struct WorkerQueue *const restrict queue,
		    struct Worker *const restrict worker);

extern inline void
worker_queue_handle_remove(struct WorkerQueue *const restrict queue,
			   struct Worker *const restrict worker);

/* Worker operations
 *─────────────────────────────────────────────────────────────────────────── */
/* extern inline struct Worker * */
/* worker_fetch(const WorkerID id); */


extern inline void
worker_exit_cleanup(void *arg);


void *
worker_do_awaitable(void *arg)
{
	struct Worker *const restrict
	worker = (struct Worker *const restrict) arg;

	mutex_handle_lock(&worker->processing);

	thread_key_handle_create(&worker->key,
				      &worker_exit_cleanup);

	worker->result = worker->routine.awaitable(worker->arg);

	worker->busy = false;

	thread_key_handle_delete(worker->key);

	worker_queue_handle_remove(&supervisor.busy,
				   worker);

	worker_queue_handle_push(&supervisor.done,
				 worker);

	mutex_handle_unlock(&worker->processing);

	thread_cond_handle_signal(&worker->done);

	return NULL;
}

/* extern inline WorkerID */
/* worker_spawn_awaitable(AwaitableRoutine *const routine, */
/* 			    void *arg); */

void *
worker_do_independent(void *arg)
{
	struct Worker *const restrict
	worker = (struct Worker *const restrict) arg;

	thread_key_handle_create(&worker->key,
				      &worker_exit_cleanup);

	worker->routine.independent(worker->arg);

	thread_key_handle_delete(worker->key);

	worker_queue_handle_remove(&supervisor.busy,
				   worker);

	worker_queue_handle_push(&supervisor.idle,
				 worker);

	return NULL;
}

extern inline void
worker_spawn_independent(IndependentRoutine *const routine,
			      void *arg);

/* inline void * */
/* worker_await(const WorkerID id); */

/* inline void * */
/* worker_await_limit(const WorkerID id, */
/* 		   const struct timespec *const restrict limit); */

/* inline void * */
/* worker_await_span(const WorkerID id, */
/* 		       const struct timespec *const restrict span); */
