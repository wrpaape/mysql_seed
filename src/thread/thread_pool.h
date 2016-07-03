#ifndef MYSQL_SEED_THREAD_THREAD_POOL_H_
#define MYSQL_SEED_THREAD_THREAD_POOL_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "thread/thread_utils.h"	/* threads API */
#include "thread/thread_queue.h"	/* ThreadQueue */
#include "thread/thread_log.h"		/* ThreadLog */

#define WORKERS_MAX 16lu

/* failure messages
 *─────────────────────────────────────────────────────────────────────────── */
#define WORKER_SPAWN_FAILURE_MESSAGE					\
"\n\nfailed to spawn new worker\nreason:\n"				\
"\t'WORKERS_MAX' (" EXPAND_STRINGIFY(SEED_WORKERS_MAX) ") "		\
"exceeded\n"

#define THREAD_POOL_EXIT_ON_FAILURE_MESSAGE ANSI_BRIGHT ANSI_RED_BG	\
ANSI_YELLOW "\nTHREAD POOL EXITING ON FAILURE\n" ANSI_RESET

#define THREAD_POOL_EXIT_ON_SUCCESS_MESSAGE ANSI_BRIGHT ANSI_WHITE_BG	\
ANSI_GREEN "\nTHREAD POOL EXITING ON SUCCESS\n" ANSI_RESET


/* typedefs
 *─────────────────────────────────────────────────────────────────────────── */
union TaskFun {
	ThreadRoutine *awaitable;
	ThreadProcedure *independent;
};

struct Task {
	struct ThreadHandlerClosure *handle_fail;
	union TaskFun fun;
	void *arg;
	void *result;
	bool busy;
	ThreadCond done;
	Mutex processing;
};

struct Worker {
	struct Task *task;
	ThreadKey key;
	Thread thread;
};

struct Supervisor {
	Thread thread;
	ThreadKey key;
	ThreadProcedure *event;
	ThreadCond trigger;
	Mutex listening;
};

struct TaskQueues {
	struct ThreadQueue vacant;
	struct ThreadQueue awaitable;
	struct ThreadQueue independent;
	struct ThreadQueue finished;
};

struct ThreadPool {
	bool busy;
	ThreadCond done;
	Mutex processing;
	struct Supervisor supervisor;
	struct ThreadQueue workers;
	struct TaskQueues tasks;
	struct ThreadLog log;
	struct ThreadHandlerClosure handle_fail;
};




/* ThreadPool operations
 *─────────────────────────────────────────────────────────────────────────── */

/* should only be called from supervisor thread */
inline void
thread_pool_cancel_workers(struct ThreadPool *const restrict pool)
{
	struct ThreadQueueNode *restrict node;
	struct Worker *restrict worker;

	thread_queue_lock_muffle(&pool->workers);

	thread_queue_peek(&pool->workers,
			  &node);

	while (node != NULL) {
		worker = (struct Worker *restrict) node->payload;

		thread_cancel_muffle(worker->thread);

		node = node->next;
	}

	thread_queue_unlock_muffle(&pool->workers);
}

inline void
thread_pool_exit_on_failure(void *arg,
			    const char *restrict failure)
{
	struct ThreadPool *const restrict pool =
	(struct ThreadPool *const restrict) arg;

	thread_log_lock_muffle(&pool->log);

	thread_log_append_string(&pool->log,
				 THREAD_POOL_EXIT_ON_FAILURE_MESSAGE);

	thread_log_append_close(&pool->log);



}

inline void
thread_pool_init(struct ThreadPool *restrict pool,
		 size_t count_workers)
{

}


/* void */
/* supervisor_exit(const char *restrict failure) */
/* __attribute__((noreturn)); */




/* Worker operations
 *─────────────────────────────────────────────────────────────────────────── */


/* apply 'ARG' to 'CATCH_ROUTINE' if exit in block */
#define worker_try_catch_open(CATCH_ROUTINE, ARG)			\
thread_try_catch_open_imp(CATCH_ROUTINE, ARG)

#define worker_try_catch_close()					\
thread_try_catch_close_imp()

/* apply 'ARG' to 'ENSURE_ROUTINE' if exit in block or upon completing block */
#define worker_try_ensure_open(ENSURE_ROUTINE, ARG)			\
thread_try_ensure_open_imp(ENSURE_ROUTINE, ARG)

#define worker_try_ensure_close()					\
thread_try_ensure_close_imp()



/* inline void */
/* worker_exit_cleanup(void *arg) */
/* { */
/* 	struct Worker *const restrict */
/* 	worker = (struct Worker *const restrict) arg; */

/* 	thread_key_delete_handle(worker->key); */

/* 	worker_queue_handle_remove(&supervisor.busy, */
/* 				   worker); */

/* 	worker_queue_handle_push(&supervisor.idle, */
/* 				 worker); */
/* } */

/* void * */
/* worker_do_awaitable(void *arg); */


/* inline WorkerID */
/* worker_spawn_awaitable(ThreadRoutine *const routine, */
/* 			    void *arg) */
/* { */
/* 	struct Worker *const restrict */
/* 	worker = worker_queue_handle_pop(&supervisor.idle); */

/* 	if (worker == NULL) */
/* 		supervisor_exit(SEED_WORKER_SPAWN_FAILURE_MESSAGE); */

/* 	worker->busy		  = true; */
/* 	worker->key		  = (ThreadKey) worker; */
/* 	worker->routine.awaitable = routine; */
/* 	worker->arg		  = arg; */

/* 	thread_handle_create(&worker->thread, */
/* 				  &worker_do_awaitable, */
/* 				  worker); */

/* 	worker_queue_handle_push(&supervisor.busy, */
/* 				 worker); */

/* 	return worker->id; */
/* } */

/* void * */
/* worker_do_independent(void *arg); */

/* inline void */
/* worker_spawn_independent(ThreadProcedure *const routine, */
/* 			      void *arg) */
/* { */
/* 	struct Worker *const restrict */
/* 	worker = worker_queue_handle_pop(&supervisor.idle); */

/* 	if (worker == NULL) */
/* 		supervisor_exit(SEED_WORKER_SPAWN_FAILURE_MESSAGE); */

/* 	worker->key		    = (ThreadKey) worker; */
/* 	worker->routine.independent = routine; */
/* 	worker->arg		    = arg; */

/* 	thread_handle_create(&worker->thread, */
/* 				  &worker_do_independent, */
/* 				  worker); */

/* 	worker_queue_handle_push(&supervisor.busy, */
/* 				 worker); */
/* } */



/* inline void * */
/* worker_await(const WorkerID id) */
/* { */


/* 	struct Worker *const restrict worker = worker_fetch(id); */

/* 	mutex_handle_lock(&worker->processing); */

/* 	while (worker->busy) */
/* 		thread_cond_handle_await(&worker->done, */
/* 					      &worker->processing); */

/* 	void *const restrict result = worker->result; */

/* 	mutex_handle_unlock(&worker->processing); */

/* 	worker_queue_handle_remove(&supervisor.done, */
/* 				   worker); */

/* 	worker_queue_handle_push(&supervisor.idle, */
/* 				 worker); */

/* 	return result; */
/* } */

/* inline void * */
/* worker_await_limit(const WorkerID id, */
/* 			const struct timespec *const restrict limit) */
/* { */


/* 	struct Worker *const restrict worker = worker_fetch(id); */

/* 	mutex_handle_lock(&worker->processing); */

/* 	while (worker->busy) */
/* 		thread_cond_handle_await_limit(&worker->done, */
/* 						    &worker->processing, */
/* 						    limit); */

/* 	void *const restrict result = worker->result; */

/* 	mutex_handle_unlock(&worker->processing); */

/* 	worker_queue_handle_remove(&supervisor.done, */
/* 				   worker); */

/* 	worker_queue_handle_push(&supervisor.idle, */
/* 				 worker); */

/* 	return result; */
/* } */

/* inline void * */
/* worker_await_span(const WorkerID id, */
/* 		       const struct timespec *const restrict span) */
/* { */
/* 	struct Worker *const restrict worker = worker_fetch(id); */

/* 	mutex_handle_lock(&worker->processing); */

/* 	while (worker->busy) */
/* 		thread_cond_handle_await_span(&worker->done, */
/* 						   &worker->processing, */
/* 						   span); */

/* 	void *const restrict result = worker->result; */

/* 	mutex_handle_unlock(&worker->processing); */

/* 	worker_queue_handle_remove(&supervisor.done, */
/* 				   worker); */

/* 	worker_queue_handle_push(&supervisor.idle, */
/* 				 worker); */

/* 	return result; */
/* } */

#endif /* ifndef MYSQL_SEED_THREAD_THREAD_POOL_H_ */
