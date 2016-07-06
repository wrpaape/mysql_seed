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
#define THREAD_POOL_EXIT_FAILURE_MESSAGE ANSI_BRIGHT ANSI_RED_BG	\
ANSI_WHITE "\n\nTHREAD POOL EXITING ON FAILURE\n" ANSI_RESET

#define THREAD_POOL_EXIT_SUCCESS_MESSAGE ANSI_BRIGHT ANSI_WHITE_BG	\
ANSI_GREEN "\n\nTHREAD POOL EXITING ON SUCCESS\n" ANSI_RESET


/* typedefs
 *─────────────────────────────────────────────────────────────────────────── */
struct ThreadPool;

typedef void
ThreadPoolEvent(struct ThreadPool *const restrict pool);

struct Worker {
	ThreadKey key;
	Thread thread;
	struct ThreadQueueNode *node;
	struct ThreadPool *pool;
	struct HandlerClosure fail_cl;
};

struct Supervisor {
	Thread thread;
	ThreadKey key;
	ThreadPoolEvent *event;
	ThreadCond trigger;
	Mutex listening;
	struct ThreadPool *pool;
	struct HandlerClosure fail_cl;
};

struct TaskQueue {
	struct ThreadQueue backlog;
	struct ThreadQueue active;
	struct ThreadQueue complete;
	struct ThreadQueue vacant;
};


struct ThreadPool {
	struct ThreadLog log;
	struct Supervisor supervisor;
	struct ThreadQueue worker_queue;
	struct TaskQueue task_queue;
};

/* Supervisor operations, ThreadPoolEvents
 *─────────────────────────────────────────────────────────────────────────── */
/* should only be called from supervisor thread */
inline void
supervisor_cancel_workers_failure(struct ThreadPool *const restrict pool)
{
	struct ThreadQueueNode *restrict node;
	struct Worker *restrict worker;

	mutex_lock_try_catch_open(&pool->worker_queue.lock)

	mutex_lock_muffle(&pool->worker_queue.lock);

	thread_queue_peek(&pool->worker_queue,
			  &node);

	while (node != NULL) {
		worker = (struct Worker *restrict) node->payload;

		thread_cancel_muffle(worker->thread);

		node = node->next;
	}

	mutex_unlock_muffle(&pool->worker_queue.lock);

	mutex_lock_try_catch_close();
}

inline void
supervisor_cancel_workers_success(struct ThreadPool *const restrict pool)
{
	struct ThreadQueueNode *restrict node;
	struct Worker *restrict worker;

	mutex_lock_try_catch_open(&pool->worker_queue.lock)

	mutex_lock_handle_cl(&pool->worker_queue.lock,
			     &pool->supervisor.fail_cl);

	thread_queue_peek(&pool->worker_queue,
			  &node);

	while (node != NULL) {
		worker = (struct Worker *restrict) node->payload;

		thread_cancel_handle_cl(worker->thread,
					&pool->supervisor.fail_cl);

		node = node->next;
	}

	mutex_unlock_handle_cl(&pool->worker_queue.lock,
			       &pool->supervisor.fail_cl);

	mutex_lock_try_catch_close();
}

/* should only be called from supervisor thread */
void
supervisor_exit_cleanup(void *arg);
/* should only be called from supervisor thread */
inline void
supervisor_do_exit_failure(struct ThreadPool *const restrict pool)
{
	/* cancel all living workers */
	supervisor_cancel_workers_failure(pool);

	/* close the log with a failure message and dump to stderr */
	mutex_lock_try_catch_open(&pool->log.lock);

	mutex_lock_muffle(&pool->log.lock);

	thread_log_append_string(&pool->log,
				 THREAD_POOL_EXIT_FAILURE_MESSAGE);

	thread_log_append_close(&pool->log);

	thread_log_dump_muffle(&pool->log,
			       STDERR_FILENO);

	mutex_unlock_muffle(&pool->log.lock);

	mutex_lock_try_catch_close();

	/* if there's a thread waiting in thread_pool_await, ensure that it's
	 * awoken */
	thread_queue_clear_muffle(&pool->task_queue.backlog);
}

inline void
supervisor_do_exit_success(struct ThreadPool *const restrict pool)
{
	/* cancel all living workers */
	supervisor_cancel_workers_success(pool);

	/* close the log with a success message and dump to stdout */
	mutex_lock_try_catch_open(&pool->log.lock);

	mutex_lock_handle_cl(&pool->log.lock,
			     &pool->supervisor.fail_cl);

	thread_log_append_string(&pool->log,
				 THREAD_POOL_EXIT_SUCCESS_MESSAGE);

	thread_log_append_close(&pool->log);

	thread_log_dump_handle_cl(&pool->log,
				  STDOUT_FILENO,
				  &pool->supervisor.fail_cl);

	mutex_unlock_handle_cl(&pool->log.lock,
			       &pool->supervisor.fail_cl);

	mutex_lock_try_catch_close();

	/* ensure failure destructor functions aren't called on exit */
	thread_key_delete_handle_cl(pool->supervisor.key,
				    &pool->supervisor.fail_cl);

	/* exit */
	thread_exit_detached();
	__builtin_unreachable();
}

/* should only be called from supervisor thread */
void
supervisor_exit_on_failure(void *arg,
			   const char *restrict failure)
__attribute__((noreturn));

void *
supervisor_spawn(void *arg)
__attribute__((noreturn));

inline void
supervisor_start(struct Supervisor *const restrict supervisor,
		 const struct HandlerClosure *const restrict fail_cl)
{
	thread_create_handle_cl(&supervisor->thread,
				&supervisor_spawn,
				supervisor,
				fail_cl);
}


inline void
supervisor_init(struct Supervisor *const restrict supervisor,
		struct ThreadPool *const restrict pool)
{
	supervisor->event = NULL;

	thread_cond_init(&supervisor->trigger);
	mutex_init(&supervisor->listening);

	supervisor->fail_cl.handle = &supervisor_exit_on_failure;
	supervisor->fail_cl.arg	   = pool;

	supervisor->pool = pool;
}

inline void
supervisor_process_events(struct Supervisor *const restrict supervisor)
{
	mutex_lock_try_catch_open(&supervisor->listening);

	while (1) {
		mutex_lock_handle_cl(&supervisor->listening,
				     &supervisor->fail_cl);

		while (supervisor->event == NULL)
			thread_cond_await_handle_cl(&supervisor->trigger,
						    &supervisor->listening,
						    &supervisor->fail_cl);

		/* process event */
		supervisor->event(supervisor->pool);

		/* reset listening condition */
		supervisor->event = NULL;

		mutex_unlock_handle_cl(&supervisor->listening,
				       &supervisor->fail_cl);
	}

	mutex_lock_try_catch_close();
	__builtin_unreachable();
}

inline void
supervisor_signal_muffle(struct Supervisor *const restrict supervisor,
			 ThreadPoolEvent *const event)
{
	mutex_lock_try_catch_open(&supervisor->listening);

	mutex_lock_muffle(&supervisor->listening);

	supervisor->event = event;

	thread_cond_signal_muffle(&supervisor->trigger);

	mutex_unlock_muffle(&supervisor->listening);

	mutex_lock_try_catch_close();
}

inline void
supervisor_signal_handle_cl(struct Supervisor *const restrict supervisor,
			    ThreadPoolEvent *const event,
			    const struct HandlerClosure *const restrict fail_cl)
{
	mutex_lock_try_catch_open(&supervisor->listening);

	mutex_lock_handle_cl(&supervisor->listening,
			     fail_cl);

	supervisor->event = event;

	thread_cond_signal_handle_cl(&supervisor->trigger,
				     fail_cl);

	mutex_unlock_handle_cl(&supervisor->listening,
			       fail_cl);

	mutex_lock_try_catch_close();
}


/* Worker operations
 *─────────────────────────────────────────────────────────────────────────── */
void
worker_exit_cleanup(void *arg);

void
worker_exit_on_failure(void *arg,
		       const char *restrict failure)
__attribute__((noreturn));

inline void
worker_init(struct Worker *const restrict worker,
	    struct ThreadQueueNode *const restrict node,
	    struct ThreadPool *const restrict pool)
{
	worker->fail_cl.handle = &worker_exit_on_failure;
	worker->fail_cl.arg    = worker;
	worker->pool	       = pool;
	worker->node	       = node;
}

inline void
worker_process_tasks(struct Worker *const restrict worker)
{
	struct TaskQueue *const restrict
	task_queue = &worker->pool->task_queue;

	struct ThreadQueueNode *restrict node;
	struct ProcedureClosure *restrict task_cl;

	while (1) {
		printf("thread %p waiting for task\n", worker->thread);
		/* pop next assigned task, blocking if there are none,
		 * then push into active queue */
		thread_queue_pop_push_handle_cl(&task_queue->backlog,
						&task_queue->active,
						&node,
						&worker->fail_cl);

		/* do task */
		task_cl = (struct ProcedureClosure *restrict) node->payload;

		printf("thread %p got task: %p\n", worker->thread, task_cl);

		task_cl->fun(task_cl->arg);

		printf("thread %p finished task: %p\n", worker->thread, task_cl);

		thread_queue_remove_handle_cl(&task_queue->active,
					      node,
					      &worker->fail_cl);

		printf("thread %p removed task: %p\n", worker->thread, task_cl);

		/* push completed task */
		thread_queue_push_handle_cl(&task_queue->complete,
					    node,
					    &worker->fail_cl);

		printf("thread %p pushed task: %p\n", worker->thread, task_cl);
	}
	__builtin_unreachable();
}

void *
worker_spawn(void *arg)
__attribute__((noreturn));


/* ThreadQueue operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
task_queue_backlog_init(struct ThreadQueue *const restrict backlog,
			struct ThreadQueueNode *restrict node,
			const struct ProcedureClosure *restrict init_task,
			const size_t count_init_tasks)
{
	if (count_init_tasks == 0lu) {
		thread_queue_init_empty(backlog);
		return;
	}

	thread_queue_init(backlog);

	struct ThreadQueueNode *const restrict last = node
						    + (count_init_tasks - 1l);
	struct ThreadQueueNode *restrict next;

	last->next    = NULL;
	backlog->last = last;

	node->prev    = NULL;
	backlog->head = node;

	while (1) {
		node->payload = (void *) init_task;

		if (node == last)
			return;

		next = node + 1l;

		node->next = next;
		next->prev = node;

		node = next;
		++init_task;
	}
}

inline void
task_queue_vacant_init(struct ThreadQueue *const restrict vacant,
		       struct ThreadQueueNode *restrict node,
		       const size_t count_vacant_tasks)
{
	if (count_vacant_tasks == 0lu) {
		thread_queue_init_empty(vacant);
		return;
	}

	thread_queue_init(vacant);

	struct ThreadQueueNode *const restrict last = node
						    + (count_vacant_tasks - 1l);
	struct ThreadQueueNode *restrict next;

	last->next   = NULL;
	vacant->last = last;

	node->prev   = NULL;
	vacant->head = node;

	while (1) {
		/* no payloads, just hook up links */
		if (node == last)
			return;

		next = node + 1l;

		node->next = next;
		next->prev = node;

		node = next;
	}
}

inline void
worker_queue_init(struct ThreadQueue *const restrict worker_queue,
		  struct ThreadQueueNode *restrict node,
		  struct Worker *restrict worker,
		  const size_t count_workers,
		  struct ThreadPool *const restrict pool)
{
	thread_queue_init(worker_queue);

	struct ThreadQueueNode *const restrict last = node
						    + (count_workers - 1l);
	struct ThreadQueueNode *restrict next;

	last->next	   = NULL;
	worker_queue->last = last;

	node->prev	   = NULL;
	worker_queue->head = node;

	while (1) {
		/* load workers, provide with pointer to their queue location */
		worker_init(worker,
			    node,
			    pool);

		node->payload = (void *) worker;

		if (node == last)
			return;

		next = node + 1l;

		node->next = next;
		next->prev = node;

		node = next;
		++worker;
	}
}

inline void
worker_queue_start(struct ThreadQueue *const restrict worker_queue,
		   const struct HandlerClosure *const restrict fail_cl)
{
	struct ThreadQueueNode *restrict node;
	struct Worker *restrict worker;

	mutex_lock_try_catch_open(&worker_queue->lock);

	mutex_lock_handle_cl(&worker_queue->lock,
			     fail_cl);

	thread_queue_peek(worker_queue,
			  &node);

	do {
		worker = (struct Worker *restrict) node->payload;

		thread_create_handle_cl(&worker->thread,
					&worker_spawn,
					worker,
					fail_cl);

		node = node->next;

	} while (node != NULL);



	mutex_unlock_handle_cl(&worker_queue->lock,
			       fail_cl);

	mutex_lock_try_catch_close();
}


/* TaskQueue operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
task_queue_init(struct TaskQueue *const restrict task_queue,
		struct ThreadQueueNode *const restrict task_nodes,
		const struct ProcedureClosure *const restrict init_tasks,
		const size_t length_task_queue,
		const size_t count_init_tasks)
{
	task_queue_backlog_init(&task_queue->backlog,
				task_nodes,
				init_tasks,
				count_init_tasks);

	thread_queue_init_empty(&task_queue->active);

	thread_queue_init_empty(&task_queue->complete);

	task_queue_vacant_init(&task_queue->vacant,
			       task_nodes + count_init_tasks,
			       length_task_queue - count_init_tasks);
}


/* ThreadPool operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
thread_pool_init(struct ThreadPool *const restrict pool,
		 const struct ProcedureClosure *const restrict init_tasks,
		 struct ThreadQueueNode *const restrict task_nodes,
		 struct ThreadQueueNode *const restrict worker_nodes,
		 struct Worker *const restrict workers,
		 const size_t count_init_tasks,
		 const size_t length_task_queue,
		 const size_t count_workers)
{
	/* initialize thread log */
	thread_log_init(&pool->log,
			"thread pool");

	/* initialize supervisor */
	supervisor_init(&pool->supervisor,
			pool);

	/* initialize task queues */
	task_queue_init(&pool->task_queue,
			task_nodes,
			init_tasks,
			length_task_queue,
			count_init_tasks);

	/* initialize worker queue */
	worker_queue_init(&pool->worker_queue,
			  worker_nodes,
			  workers,
			  count_workers,
			  pool);
}

inline struct ThreadPool *
thread_pool_create(const struct ProcedureClosure *const restrict init_tasks,
		   const size_t count_init_tasks,
		   const size_t length_task_queue,
		   const size_t count_workers,
		   const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (count_workers == 0lu) {
		failure = FAILURE_REASON("thread_pool_create",
					 "no space allocated for pool workers"
					 " (count_workers == 0)");
		goto HANDLE_FAILURE;
	}

	if (count_init_tasks > length_task_queue) {
		failure = FAILURE_REASON("thread_pool_create",
					 "task queue too small to manage "
					 "initial tasks (count_init_tasks > "
					 "length_task_queue)");
		goto HANDLE_FAILURE;
	}

	/* allocate space for:
	 *	1			ThreadPool
	 *	count_workers		Worker
	 *	count_workers		ThreadQueueNode (for worker queue)
	 *	length_task_queue	ThreadQueueNode (for task queue) */

	struct ThreadPool *const restrict pool
	= malloc(sizeof(struct ThreadPool)
		 + (sizeof(struct Worker)	   * count_workers)
		 + (sizeof(struct ThreadQueueNode) * (count_workers
						      + length_task_queue)));
	if (pool != NULL) {
		/* divvy up memory for task queue nodes */
		struct ThreadQueueNode *const restrict task_nodes
		= (struct ThreadQueueNode *const restrict) (pool + 1l);

		/* struct ThreadQueueNode *const restrict vacant_task_nodes */
		/* = init_task_nodes + count_init_tasks; */

		/* divvy up memory for worker queue nodes, workers */
		struct ThreadQueueNode *const restrict worker_nodes
		= task_nodes + length_task_queue;

		struct Worker *const restrict workers
		= (struct Worker *const restrict) (worker_nodes
						   + count_workers);

		/* initialize internal fields, but do not start */
		thread_pool_init(pool,
				 init_tasks,
				 task_nodes,
				 worker_nodes,
				 workers,
				 count_init_tasks,
				 length_task_queue,
				 count_workers);
		return pool;
	}

	failure = MALLOC_FAILURE_MESSAGE("thread_pool_create");

HANDLE_FAILURE:
	fail_cl->handle(fail_cl->arg,
			failure);
	__builtin_unreachable();
}

inline void
thread_pool_start(struct ThreadPool *restrict pool,
		  const struct HandlerClosure *const restrict fail_cl)
{
	worker_queue_start(&pool->worker_queue,
			   fail_cl);

	supervisor_start(&pool->supervisor,
			 fail_cl);
}


inline void
thread_pool_await(struct ThreadPool *restrict pool,
		  const struct HandlerClosure *const restrict fail_cl)
{
	printf("waiting on tasks to finish\n");
	fflush(stdout);

	/* wait for tasks to be completed */
	thread_queue_await_empty_handle_cl(&pool->task_queue.backlog,
					   fail_cl);

	puts("backlog empty");
	fflush(stdout);

	thread_queue_await_empty_handle_cl(&pool->task_queue.active,
					   fail_cl);

	printf("tasks finished, returning\n");
	fflush(stdout);
}

inline void
thread_pool_push_task(struct ThreadPool *restrict pool,
		      const struct ProcedureClosure *const restrict task_cl,
		      const struct HandlerClosure *const restrict fail_cl)
{
	struct ThreadQueueNode *restrict node;

	thread_queue_pop_handle_cl(&pool->task_queue.vacant,
				   &node,
				   fail_cl);

	node->payload = (void *) task_cl;

	thread_queue_push_handle_cl(&pool->task_queue.backlog,
				    node,
				    fail_cl);
}

/* transfer all 'complete' tasks to the 'vacant' task queue, should call after
 * assured that results from all completed tasks have been gathered, processed
 * (perhaps following thread_pool_await) */
inline void
thread_pool_clear_completed(struct ThreadPool *restrict pool,
			    const struct HandlerClosure *const restrict fail_cl)
{
	thread_queue_transfer_all_handle_cl(&pool->task_queue.complete,
					    &pool->task_queue.vacant,
					    fail_cl);
}

inline void
thread_pool_stop(struct ThreadPool *restrict pool,
		 const struct HandlerClosure *const restrict fail_cl)
{
	supervisor_signal_handle_cl(&pool->supervisor,
				    &supervisor_do_exit_success,
				    fail_cl);
}


inline void
thread_pool_destroy(struct ThreadPool *restrict pool)
{
	free(pool);
}

#endif /* ifndef MYSQL_SEED_THREAD_THREAD_POOL_H_ */
