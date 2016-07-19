#ifndef MYSQL_SEED_THREAD_THREAD_POOL_H_
#define MYSQL_SEED_THREAD_THREAD_POOL_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "thread/thread_utils.h"	/* threads API */
#include "thread/task_queue.h"		/* TaskQueue */
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

struct TaskBuffer {
	struct TaskQueue backlog;
	struct TaskQueue active;
	struct TaskQueue complete;
};

struct WorkerCrew {
	const struct Worker *until;
	struct Worker *from;
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
	struct TaskBuffer task_buffer;
	struct Supervisor supervisor;
	struct WorkerCrew worker_crew;
};

struct ThreadPoolGrid {
	const struct ThreadPool *until;
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
	struct TaskBuffer *const restrict
	task_buffer = &worker->pool->task_buffer;

	struct TaskNode *restrict node;

	while (1) {
		/* pop next assigned task, blocking if there are none,
		 * then push into active queue */
		task_queue_pop_push_handle_cl(&task_buffer->backlog,
					      &task_buffer->active,
					      &node,
					      &worker->fail_cl);

		/* do task */
		procedure_closure_call(node->task);

		task_queue_remove_handle_cl(&task_buffer->active,
					    node,
					    &worker->fail_cl);

		/* push completed task */
		task_queue_push_quiet_handle_cl(&task_buffer->complete,
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
	const struct Worker *const restrict until = worker + count_workers;

	worker_crew->until = until;
	worker_crew->from  = worker;

	do {
		worker_init(worker,
			    pool);
		++worker;
	} while(worker < until);
}

inline void
worker_crew_start(struct WorkerCrew *const restrict worker_crew,
		  const struct HandlerClosure *const restrict fail_cl)
{
	const struct Worker *const restrict until = worker_crew->until;
	struct Worker *restrict worker		  = worker_crew->from;

	do {
		thread_create_handle_cl(&worker->thread,
					&worker_spawn,
					worker,
					fail_cl);
		++worker;
	} while (worker < until);
}

inline void
worker_crew_cancel_failure(struct WorkerCrew *const restrict worker_crew)
{
	const struct Worker *const restrict until = worker_crew->until;
	struct Worker *restrict worker		  = worker_crew->from;

	do {
		thread_cancel_muffle(worker->thread);
		++worker;
	} while (worker < until);
}

inline void
worker_crew_cancel_success(struct WorkerCrew *const restrict worker_crew,
			   const struct HandlerClosure *const restrict fail_cl)
{
	const struct Worker *const restrict until = worker_crew->until;
	struct Worker *restrict worker		  = worker_crew->from;

	do {
		thread_cancel_handle_cl(worker->thread,
					fail_cl);
		++worker;
	} while (worker < until);
}



/* TaskBuffer operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
task_buffer_init(struct TaskBuffer *const restrict task_buffer,
		 const struct TaskStore *const restrict task_store)
{
	task_queue_init_from_store(&task_buffer->backlog,
				   task_store);

	task_queue_init_empty(&task_buffer->active);

	task_queue_init_empty(&task_buffer->complete);
}


/* ThreadPoolStatus operations
 *─────────────────────────────────────────────────────────────────────────── */
inline void
thread_pool_status_init(struct ThreadPoolStatus *const restrict status)
{
	mutex_init(&status->processing);

	thread_cond_init(&status->done);
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

inline bool
thread_pool_status_check_busy(struct ThreadPoolStatus *const restrict status,
			      const struct HandlerClosure *const restrict fail_cl)
{
	bool busy;

	mutex_lock_try_catch_open(&status->processing);

	mutex_lock_handle_cl(&status->processing,
			     fail_cl);

	busy = status->busy;

	mutex_unlock_handle_cl(&status->processing,
			       fail_cl);

	mutex_lock_try_catch_close();

	return busy;
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

	/* cancel all living from */
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
	task_queue_clear_muffle(&pool->task_buffer.backlog);

	task_queue_clear_muffle(&pool->task_buffer.active);

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

	/* cancel all living from */
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
		 const struct TaskStore *const restrict task_store,
		 struct Worker *const restrict workers,
		 const size_t count_workers)
{
	/* initialize thread pool status */
	thread_pool_status_init(&pool->status);

	/* initialize thread log */
	thread_log_init(&pool->log,
			"thread pool");

	/* initialize task queues */
	task_buffer_init(&pool->task_buffer,
			 task_store);

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
		   const size_t count_workers,
		   const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (count_workers == 0lu) {
		failure = FAILURE_REASON("thread_pool_create",
					 "no space allocated for pool from"
					 " (count_workers == 0)");
		goto HANDLE_FAILURE;
	}

	/* allocate space for:
	 *	1			ThreadPool
	 *	count_workers		Worker
	 *	count_init_tasks	TaskNode (for task queue) */

	struct ThreadPool *const restrict pool
	= malloc(sizeof(struct ThreadPool)
		 + (sizeof(struct Worker)   * count_workers)
		 + (sizeof(struct TaskNode) * count_init_tasks));

	if (pool != NULL) {
		struct TaskStore task_store;

		/* divvy up memory for task queue nodes */
		struct TaskNode *const restrict task_nodes
		= (struct TaskNode *const restrict) (pool + 1l);

		task_store_populate(&task_store,
				    task_nodes,
				    init_tasks,
				    count_init_tasks);

		/* divvy up memory for workers */
		struct Worker *const restrict workers
		= (struct Worker *const restrict) (task_nodes
						   + count_init_tasks);

		/* initialize internal fields, but do not start */
		thread_pool_init(pool,
				 &task_store,
				 workers,
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
thread_pool_start(struct ThreadPool *const restrict pool,
		  const struct HandlerClosure *const restrict fail_cl)
{
	pool->status.busy = true;

	worker_crew_start(&pool->worker_crew,
			  fail_cl);

	supervisor_start(&pool->supervisor,
			 fail_cl);
}


inline void
thread_pool_await(struct ThreadPool *const restrict pool,
		  const struct HandlerClosure *const restrict fail_cl)
{
	/* wait for backlog task_buffer to be completed */
	task_queue_await_empty_handle_cl(&pool->task_buffer.backlog,
					 fail_cl);

	/* wait for active task_buffer to be completed */
	task_queue_await_empty_handle_cl(&pool->task_buffer.active,
					 fail_cl);
}

inline bool
thread_pool_alive(struct ThreadPool *const restrict pool,
		  const struct HandlerClosure *const restrict fail_cl)
{
	return thread_pool_status_check_busy(&pool->status,
					     fail_cl);
}

inline void
thread_pool_push_task(struct ThreadPool *const restrict pool,
		      const struct ProcedureClosure *const restrict task_cl,
		      const struct HandlerClosure *const restrict fail_cl)
{
	struct TaskNode *restrict node;

	task_queue_pop_handle_cl(&pool->task_buffer.complete,
				 &node,
				 fail_cl);

	node->task = task_cl;

	task_queue_push_handle_cl(&pool->task_buffer.backlog,
				  node,
				  fail_cl);
}

inline void
thread_pool_stop(struct ThreadPool *const restrict pool,
		 const struct HandlerClosure *const restrict fail_cl)
{
	supervisor_signal_handle_cl(&pool->supervisor,
				    &supervisor_exit_success,
				    fail_cl);
}

inline void
thread_pool_await_exit_success(struct ThreadPool *const restrict pool,
			       const struct HandlerClosure *const restrict fail_cl)
{
	thread_pool_status_await_success(&pool->status,
					 fail_cl);
}

inline void
thread_pool_await_exit_failure(struct ThreadPool *const restrict pool)
{
	thread_pool_status_await_failure(&pool->status);
}

inline int
thread_pool_exit_status(struct ThreadPool *const restrict pool,
			const struct HandlerClosure *const restrict fail_cl)
{
	thread_pool_status_await_success(&pool->status,
					 fail_cl);

	return pool->status.exit;
}

inline void
thread_pool_exit_on_failure(struct ThreadPool *const restrict pool,
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
thread_pool_reload(struct ThreadPool *const restrict pool,
		   struct TaskStore *const restrict store,
		   const struct HandlerClosure *const restrict fail_cl)
{
	task_queue_reload_handle_cl(&pool->task_buffer.backlog,
				    store,
				    fail_cl);
}

inline void
thread_pool_retreive_cold(struct ThreadPool *const restrict pool,
			  struct TaskStore *const restrict store)
{
	task_queue_retreive_cold_quiet(&pool->task_buffer.complete,
				       store);
}

inline void
thread_pool_retreive_hot(struct ThreadPool *const restrict pool,
			 struct TaskStore *const restrict store,
			 const struct HandlerClosure *const restrict fail_cl)
{
	task_queue_retreive_hot_quiet_handle_cl(&pool->task_buffer.complete,
						store,
						fail_cl);
}

inline void
thread_pool_destroy(struct ThreadPool *const restrict pool)
{
	free(pool);
}

#endif /* ifndef MYSQL_SEED_THREAD_THREAD_POOL_H_ */
