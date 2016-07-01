#ifndef MYSQL_SEED_THREAD_THREAD_POOL_H_
#define MYSQL_SEED_THREAD_THREAD_POOL_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "thread/thread_utils.h"	/* threads API */
#include "thread/thread_log.h"		/* logger */

#define SEED_WORKERS_MAX 16lu

/* failure messages
 *─────────────────────────────────────────────────────────────────────────── */
#define SEED_WORKER_SPAWN_FAILURE_MESSAGE				\
"\n\nfailed to spawn new seed worker\nreason:\n"			\
"\t'SEED_WORKERS_MAX' (" EXPAND_STRINGIFY(SEED_WORKERS_MAX) ") "	\
"exceeded\n"

/* typedefs
 *─────────────────────────────────────────────────────────────────────────── */

union TaskFun {
	ThreadRoutine *awaitable;
	ThreadProcedure *independent;
};

struct Task {
	struct Task *prev;
	struct Task *next;
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


struct WorkerQueue {
	Mutex lock;
	struct Worker *restrict head;
	struct Worker *restrict last;
};


struct Supervisor {
	struct Worker *workers;
	struct WorkerQueue idle;
	struct WorkerQueue busy;
	struct WorkerQueue done;
	struct ThreadLog log;
};




/* Supervisor operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
supervisor_init(void)
{
}

void
supervisor_exit(const char *restrict failure)
__attribute__((noreturn));




/* WorkerQueue operations
 *─────────────────────────────────────────────────────────────────────────── */
/* LIFO push */
inline void
worker_queue_push(struct WorkerQueue *const restrict queue,
		  struct Worker *const restrict worker)
{
	worker->next = NULL;

	if (queue->last == NULL) {
		queue->head  = worker;
		worker->prev = NULL;
	} else {
		worker->prev	  = queue->last;
		queue->last->next = worker;
	}

	queue->last = worker;
}

inline void
worker_queue_handle_push(struct WorkerQueue *const restrict queue,
			 struct Worker *const restrict worker)
{
	mutex_handle_lock(&queue->lock);	/* exit on lock failure */

	worker_queue_push(queue,
			  worker);

	mutex_handle_unlock(&queue->lock);	/* exit on unlock failure */
}


/* LIFO pop */
inline struct Worker *
worker_queue_pop(struct WorkerQueue *const restrict queue)
{
	struct Worker *const restrict worker = queue->head;

	if (worker == NULL)
		return NULL;

	queue->head = worker->next;

	if (queue->head == NULL)
		queue->last = NULL;
	else
		queue->head->prev = NULL;

	return worker;
}

inline struct Worker *
worker_queue_handle_pop(struct WorkerQueue *const restrict queue)
{
	mutex_handle_lock(&queue->lock);	/* exit on lock failure */

	struct Worker *const restrict worker = worker_queue_pop(queue);

	mutex_handle_unlock(&queue->lock);	/* exit on unlock failure */

	return worker;
}

/* random access delete */
inline void
worker_queue_remove(struct WorkerQueue *const restrict queue,
		    struct Worker *const restrict worker)
{
	if (worker->prev == NULL) {
		if (worker->next == NULL) {
			queue->head = NULL;
			queue->last = NULL;
		} else {
			worker->next->prev = NULL;
			queue->head	   = worker->next;
		}
	} else {
		worker->prev->next = worker->next;

		if (worker->next == NULL)
			queue->last	   = worker->prev;
		else
			worker->next->prev = worker->prev;
	}
}

inline void
worker_queue_handle_remove(struct WorkerQueue *const restrict queue,
			   struct Worker *const restrict worker)
{
	mutex_handle_lock(&queue->lock);	/* exit on lock failure */

	worker_queue_remove(queue,
			    worker);

	mutex_handle_unlock(&queue->lock);	/* exit on unlock failure */
}

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



inline void
worker_exit_cleanup(void *arg)
{
	struct Worker *const restrict
	worker = (struct Worker *const restrict) arg;

	thread_key_handle_delete(worker->key);

	worker_queue_handle_remove(&supervisor.busy,
				   worker);

	worker_queue_handle_push(&supervisor.idle,
				 worker);
}

void *
worker_do_awaitable(void *arg);


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

void *
worker_do_independent(void *arg);

inline void
worker_spawn_independent(ThreadProcedure *const routine,
			      void *arg)
{
	struct Worker *const restrict
	worker = worker_queue_handle_pop(&supervisor.idle);

	if (worker == NULL)
		supervisor_exit(SEED_WORKER_SPAWN_FAILURE_MESSAGE);

	worker->key		    = (ThreadKey) worker;
	worker->routine.independent = routine;
	worker->arg		    = arg;

	thread_handle_create(&worker->thread,
				  &worker_do_independent,
				  worker);

	worker_queue_handle_push(&supervisor.busy,
				 worker);
}



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
