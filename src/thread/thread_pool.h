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
struct Supervisor;

typedef void
SupervisorEvent(struct Supervisor *const restrict supervisor)
__attribute__((noreturn));

struct Supervisor {
	Thread thread;
	ThreadKey key;
	SupervisorEvent *event;
	ThreadCond trigger;
	Mutex listening;
	struct HandlerClosure fail_cl;
	struct ThreadPool *pool;
};

struct Worker {
	Thread thread;
	struct HandlerClosure fail_cl;
	struct ThreadPool *pool;
};

struct TaskQueue {
	struct ThreadQueue backlog;
	struct ThreadQueue active;
	struct ThreadQueue complete;
	struct ThreadQueue vacant;
};

struct WorkerCrew {
	const struct Worker *until_ptr;
	struct Worker *workers;
};

struct ThreadPoolStatus {
	Mutex processing;
	ThreadCond done;
	bool busy;
	int exit;
};

struct ThreadPool {
	struct ThreadPoolStatus status;
	struct ThreadLog log;
	struct TaskQueue task_queue;
	struct Supervisor supervisor;
	struct WorkerCrew worker_crew;
};

struct ThreadPoolGrid {
	const struct ThreadPool *until_ptr;
	struct ThreadPool *pools;
};




/* Worker operations
 *─────────────────────────────────────────────────────────────────────────── */
void
worker_exit_on_failure(void *arg,
		       const char *restrict failure)
__attribute__((noreturn));

inline void
worker_init(struct Worker *const restrict worker,
	    struct ThreadPool *const restrict pool)
{
	handler_closure_init(&worker->fail_cl,
			     &worker_exit_on_failure,
			     worker);

	worker->pool = pool;
}

inline void
worker_process_tasks(struct Worker *const restrict worker)
{
	struct TaskQueue *const restrict
	task_queue = &worker->pool->task_queue;

	struct ThreadQueueNode *restrict node;
	struct ProcedureClosure *restrict task_cl;

	while (1) {
		/* pop next assigned task, blocking if there are none,
		 * then push into active queue */
		thread_queue_pop_push_handle_cl(&task_queue->backlog,
						&task_queue->active,
						&node,
						&worker->fail_cl);

		/* do task */
		task_cl = (struct ProcedureClosure *restrict) node->payload;

		task_cl->fun(task_cl->arg);

		thread_queue_remove_handle_cl(&task_queue->active,
					      node,
					      &worker->fail_cl);

		/* push completed task */
		thread_queue_push_handle_cl(&task_queue->complete,
					    node,
					    &worker->fail_cl);
	}
	__builtin_unreachable();
}

void *
worker_spawn(void *arg)
__attribute__((noreturn));


/* WorkerCrew operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
worker_crew_init(struct WorkerCrew *const restrict worker_crew,
		 struct Worker *restrict worker,
		 const size_t count_workers,
		 struct ThreadPool *const restrict pool)
{
	const struct Worker *const restrict until_ptr = worker + count_workers;

	worker_crew->until_ptr = until_ptr;
	worker_crew->workers   = worker;

	do {
		worker_init(worker,
			    pool);
		++worker;
	} while(worker < until_ptr);
}

inline void
worker_crew_start(struct WorkerCrew *const restrict worker_crew,
		  const struct HandlerClosure *const restrict fail_cl)
{
	const struct Worker *const restrict until_ptr = worker_crew->until_ptr;
	struct Worker *restrict worker		      = worker_crew->workers;

	do {
		thread_create_handle_cl(&worker->thread,
					&worker_spawn,
					worker,
					fail_cl);
		++worker;
	} while (worker < until_ptr);
}

inline void
worker_crew_cancel_failure(struct WorkerCrew *const restrict worker_crew)
{
	const struct Worker *const restrict until_ptr = worker_crew->until_ptr;
	struct Worker *restrict worker		      = worker_crew->workers;

	do {
		thread_cancel_muffle(worker->thread);
		++worker;
	} while (worker < until_ptr);
}

inline void
worker_crew_cancel_success(struct WorkerCrew *const restrict worker_crew,
			   const struct HandlerClosure *const restrict fail_cl)
{
	const struct Worker *const restrict until_ptr = worker_crew->until_ptr;
	struct Worker *restrict worker		      = worker_crew->workers;

	do {
		thread_cancel_handle_cl(worker->thread,
					fail_cl);
		++worker;
	} while (worker < until_ptr);
}


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


/* ThreadPoolStatus operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
thread_pool_status_init(struct ThreadPoolStatus *const restrict status)
{
	mutex_init(&status->processing);
	thread_cond_init(&status->done);
	status->busy = true;
}

inline void
thread_pool_status_set_failure(struct ThreadPoolStatus *const restrict status)
{
	mutex_lock_try_catch_open(&status->processing);

	mutex_lock_muffle(&status->processing);

	status->exit = EXIT_FAILURE;

	status->busy = false;

	thread_cond_signal_muffle(&status->done);

	mutex_unlock_muffle(&status->processing);

	mutex_lock_try_catch_close();
}

inline void
thread_pool_status_set_success(struct ThreadPoolStatus *const restrict status,
			       const struct HandlerClosure *const restrict fail_cl)
{
	mutex_lock_try_catch_open(&status->processing);

	mutex_lock_handle_cl(&status->processing,
			     fail_cl);

	status->exit = EXIT_SUCCESS;

	status->busy = false;

	thread_cond_signal_handle_cl(&status->done,
				     fail_cl);

	mutex_unlock_handle_cl(&status->processing,
			       fail_cl);

	mutex_lock_try_catch_close();
}

inline void
thread_pool_status_await_failure(struct ThreadPoolStatus *const restrict status)
{
	mutex_lock_try_catch_open(&status->processing);

	mutex_lock_muffle(&status->processing);

	while (status->busy)
		thread_cond_await_muffle(&status->done,
					 &status->processing);

	mutex_unlock_muffle(&status->processing);

	mutex_lock_try_catch_close();
}

inline void
thread_pool_status_await_success(struct ThreadPoolStatus *const restrict status,
				 const struct HandlerClosure *const restrict fail_cl)
{
	mutex_lock_try_catch_open(&status->processing);

	mutex_lock_handle_cl(&status->processing,
			     fail_cl);

	while (status->busy)
		thread_cond_await_handle_cl(&status->done,
					    &status->processing,
					    fail_cl);

	mutex_unlock_handle_cl(&status->processing,
			       fail_cl);

	mutex_lock_try_catch_close();
}


/* Supervisor operations, SupervisorEvents
 *─────────────────────────────────────────────────────────────────────────── */
/* should only be called from supervisor thread */
inline void
supervisor_do_exit_failure(struct Supervisor *const restrict supervisor)
{
	/* ensure destructor function not called recursively */
	thread_key_delete_muffle(supervisor->key);

	struct ThreadPool *const restrict pool = supervisor->pool;

	/* cancel all living workers */
	worker_crew_cancel_failure(&pool->worker_crew);

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
	thread_queue_clear_muffle(&pool->task_queue.active);

	/* signal pool is done */
	thread_pool_status_set_failure(&pool->status);
}

inline void
supervisor_do_exit_success(struct Supervisor *const restrict supervisor)
{
	/* ensure destructor function not called recursively */
	thread_key_delete_handle_cl(supervisor->key,
				    &supervisor->fail_cl);

	struct ThreadPool *const restrict pool = supervisor->pool;

	/* cancel all living workers */
	worker_crew_cancel_success(&pool->worker_crew,
				   &supervisor->fail_cl);

	/* close the log with a success message and dump to stdout */
	mutex_lock_try_catch_open(&pool->log.lock);

	mutex_lock_handle_cl(&pool->log.lock,
			     &supervisor->fail_cl);

	thread_log_append_string(&pool->log,
				 THREAD_POOL_EXIT_SUCCESS_MESSAGE);

	thread_log_append_close(&pool->log);

	thread_log_dump_handle_cl(&pool->log,
				  STDOUT_FILENO,
				  &supervisor->fail_cl);

	mutex_unlock_handle_cl(&pool->log.lock,
			       &supervisor->fail_cl);

	mutex_lock_try_catch_close();

	/* signal pool is done */
	thread_pool_status_set_success(&pool->status,
				       &supervisor->fail_cl);
}
void
supervisor_exit_failure(struct Supervisor *const restrict supervisor)
__attribute__((noreturn));

void
supervisor_exit_success(struct Supervisor *const restrict supervisor)
__attribute__((noreturn));

/* should only be called from supervisor thread */
void
supervisor_exit_cleanup(void *arg);

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

	handler_closure_init(&supervisor->fail_cl,
			     &supervisor_exit_on_failure,
			     supervisor);

	supervisor->pool = pool;
}

inline void
supervisor_listen(struct Supervisor *const restrict supervisor)
{
	mutex_lock_try_catch_open(&supervisor->listening);

	mutex_lock_handle_cl(&supervisor->listening,
			     &supervisor->fail_cl);

	/* listen for event */
	while (supervisor->event == NULL)
		thread_cond_await_handle_cl(&supervisor->trigger,
					    &supervisor->listening,
					    &supervisor->fail_cl);

	mutex_unlock_handle_cl(&supervisor->listening,
			       &supervisor->fail_cl);

	mutex_lock_try_catch_close();

	/* process event and exit */
	supervisor->event(supervisor);
	__builtin_unreachable();
}

inline void
supervisor_signal_muffle(struct Supervisor *const restrict supervisor,
			 SupervisorEvent *const event)
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
			    SupervisorEvent *const event,
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




/* ThreadPool operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
thread_pool_init(struct ThreadPool *const restrict pool,
		 const struct ProcedureClosure *const restrict init_tasks,
		 struct ThreadQueueNode *const restrict task_nodes,
		 struct Worker *const restrict workers,
		 const size_t count_init_tasks,
		 const size_t length_task_queue,
		 const size_t count_workers)
{
	/* initialize thread pool status */
	thread_pool_status_init(&pool->status);

	/* initialize thread log */
	thread_log_init(&pool->log,
			"thread pool");

	/* initialize task queues */
	task_queue_init(&pool->task_queue,
			task_nodes,
			init_tasks,
			length_task_queue,
			count_init_tasks);

	/* initialize supervisor */
	supervisor_init(&pool->supervisor,
			pool);


	/* initialize worker crew */
	worker_crew_init(&pool->worker_crew,
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
	 *	length_task_queue	ThreadQueueNode (for task queue) */

	struct ThreadPool *const restrict pool
	= malloc(sizeof(struct ThreadPool)
		 + (sizeof(struct Worker)	   * count_workers)
		 + (sizeof(struct ThreadQueueNode) * length_task_queue));

	if (pool != NULL) {
		/* divvy up memory for task queue nodes */
		struct ThreadQueueNode *const restrict task_nodes
		= (struct ThreadQueueNode *const restrict) (pool + 1l);

		/* divvy up memory for workers */
		struct Worker *const restrict workers
		= (struct Worker *const restrict) (task_nodes
						   + length_task_queue);

		/* initialize internal fields, but do not start */
		thread_pool_init(pool,
				 init_tasks,
				 task_nodes,
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
	worker_crew_start(&pool->worker_crew,
			  fail_cl);

	supervisor_start(&pool->supervisor,
			 fail_cl);
}


inline void
thread_pool_await(struct ThreadPool *restrict pool,
		  const struct HandlerClosure *const restrict fail_cl)
{
	/* wait for backlog tasks to be completed */
	thread_queue_await_empty_handle_cl(&pool->task_queue.backlog,
					   fail_cl);

	/* wait for active tasks to be completed */
	thread_queue_await_empty_handle_cl(&pool->task_queue.active,
					   fail_cl);
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
				    &supervisor_exit_success,
				    fail_cl);
}

inline void
thread_pool_await_exit_success(struct ThreadPool *restrict pool,
			       const struct HandlerClosure *const restrict fail_cl)
{
	thread_pool_status_await_success(&pool->status,
					 fail_cl);
}

inline void
thread_pool_await_exit_failure(struct ThreadPool *restrict pool)
{
	thread_pool_status_await_failure(&pool->status);
}

inline int
thread_pool_exit_status(struct ThreadPool *restrict pool,
			const struct HandlerClosure *const restrict fail_cl)
{
	thread_pool_status_await_success(&pool->status,
					 fail_cl);

	return pool->status.exit;
}

inline void
thread_pool_exit_on_failure(struct ThreadPool *restrict pool,
			    const char *restrict failure)
{
	mutex_lock_try_catch_open(&pool->log.lock)

	mutex_lock_muffle(&pool->log.lock);

	thread_log_append_string(&pool->log,
				 failure);

	mutex_unlock_muffle(&pool->log.lock);

	mutex_lock_try_catch_close();

	supervisor_signal_muffle(&pool->supervisor,
				 &supervisor_exit_failure);
}

inline void
thread_pool_destroy(struct ThreadPool *restrict pool)
{
	free(pool);
}

#endif /* ifndef MYSQL_SEED_THREAD_THREAD_POOL_H_ */
