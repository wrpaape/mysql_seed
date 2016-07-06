#include "thread/thread_pool.h"

/* Supervisor operations, ThreadPoolEvents
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
supervisor_cancel_workers_failure(struct ThreadPool *const restrict pool);
extern inline void
supervisor_cancel_workers_success(struct ThreadPool *const restrict pool);
extern inline void
supervisor_do_exit_failure(struct ThreadPool *const restrict pool);
extern inline void
supervisor_do_exit_success(struct ThreadPool *const restrict pool);
void
supervisor_exit_cleanup(void *arg)
{
	struct Supervisor *const restrict
	supervisor = (struct Supervisor *const restrict) arg;

	thread_key_delete_muffle(supervisor->key);

	supervisor_do_exit_failure(supervisor->pool);
}
void
supervisor_exit_on_failure(void *arg,
			   const char *restrict failure)
{
	struct ThreadPool *const restrict
	pool = (struct ThreadPool *const restrict) arg;

	mutex_lock_try_catch_open(&pool->log.lock)

	mutex_lock_muffle(&pool->log.lock);

	thread_log_append_string(&pool->log,
				 failure);

	mutex_unlock_muffle(&pool->log.lock);

	mutex_lock_try_catch_close();

	thread_exit_detached();
	__builtin_unreachable();
}
void *
supervisor_spawn(void *arg)
{
	struct Supervisor *const restrict
	supervisor = (struct Supervisor *const restrict) arg;

	/* push destructor method to be executed on thread exit */
	thread_key_create_handle_cl(&supervisor->key,
				    &supervisor_exit_cleanup,
				    &supervisor->fail_cl);

	/* listen for events */
	supervisor_process_events(supervisor);
	__builtin_unreachable();
}
extern inline void
supervisor_start(struct Supervisor *const restrict supervisor,
		 const struct HandlerClosure *const restrict fail_cl);
extern inline void
supervisor_init(struct Supervisor *const restrict supervisor,
		struct ThreadPool *const restrict pool);
extern inline void
supervisor_process_events(struct Supervisor *const restrict supervisor);
extern inline void
supervisor_signal_muffle(struct Supervisor *const restrict supervisor,
			 ThreadPoolEvent *const event);
extern inline void
supervisor_signal_handle_cl(struct Supervisor *const restrict supervisor,
			    ThreadPoolEvent *const event,
			    const struct HandlerClosure *const restrict fail_cl);

/* Worker operations
 *─────────────────────────────────────────────────────────────────────────── */
void
worker_exit_cleanup(void *arg)
{
	struct Worker *const restrict
	worker = (struct Worker *const restrict) arg;

	thread_key_delete_muffle(worker->key);
}

void
worker_exit_on_failure(void *arg,
		       const char *restrict failure)
{
	struct Worker *const restrict worker =
	(struct Worker *const restrict) arg;

	struct ThreadPool *const restrict pool = worker->pool;

	mutex_lock_try_catch_open(&pool->log.lock);

	mutex_lock_muffle(&pool->log.lock);

	thread_log_append_string(&pool->log,
				 failure);

	mutex_unlock_muffle(&pool->log.lock);

	mutex_lock_try_catch_close();

	thread_queue_remove_muffle(&pool->worker_queue,
				   worker->node);

	supervisor_signal_muffle(&pool->supervisor,
				 &supervisor_do_exit_failure);
	thread_exit_detached();
	__builtin_unreachable();
}
extern inline void
worker_init(struct Worker *const restrict worker,
	    struct ThreadQueueNode *const restrict node,
	    struct ThreadPool *const restrict pool);
extern inline void
worker_process_tasks(struct Worker *const restrict worker);
void *
worker_spawn(void *arg)
{
	struct Worker *const restrict worker =
	(struct Worker *const restrict) arg;

	/* push destructor method to be executed on thread exit */
	thread_key_create_handle_cl(&worker->key,
				    &worker_exit_cleanup,
				    &worker->fail_cl);

	/* begin work */
	worker_process_tasks(worker);
	__builtin_unreachable();
}


/* ThreadQueue operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
task_queue_backlog_init(struct ThreadQueue *const restrict backlog,
			struct ThreadQueueNode *restrict node,
			const struct ProcedureClosure *restrict init_task,
			const size_t count_init_tasks);
extern inline void
task_queue_vacant_init(struct ThreadQueue *const restrict vacant,
		       struct ThreadQueueNode *restrict node,
		       const size_t count_vacant_tasks);
extern inline void
worker_queue_init(struct ThreadQueue *const restrict worker_queue,
		  struct ThreadQueueNode *restrict node,
		  struct Worker *restrict worker,
		  const size_t count_workers,
		  struct ThreadPool *const restrict pool);
extern inline void
worker_queue_start(struct ThreadQueue *const restrict worker_queue,
		   const struct HandlerClosure *const restrict fail_cl);

/* TaskQueue operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
task_queue_init(struct TaskQueue *const restrict task_queue,
		struct ThreadQueueNode *const restrict task_nodes,
		const struct ProcedureClosure *const restrict init_tasks,
		const size_t length_task_queue,
		const size_t count_init_tasks);


/* ThreadPool operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
thread_pool_init(struct ThreadPool *const restrict pool,
		 const struct ProcedureClosure *const restrict init_tasks,
		 struct ThreadQueueNode *const restrict task_nodes,
		 struct ThreadQueueNode *const restrict worker_nodes,
		 struct Worker *const restrict workers,
		 const size_t count_init_tasks,
		 const size_t length_task_queue,
		 const size_t count_workers);
extern inline struct ThreadPool *
thread_pool_create(const struct ProcedureClosure *const restrict init_tasks,
		   const size_t count_init_tasks,
		   const size_t length_task_queue,
		   const size_t count_workers,
		   const struct HandlerClosure *const restrict fail_cl);

extern inline void
thread_pool_start(struct ThreadPool *restrict pool,
		  const struct HandlerClosure *const restrict fail_cl);

extern inline void
thread_pool_await(struct ThreadPool *restrict pool,
		  const struct HandlerClosure *const restrict fail_cl);
extern inline void
thread_pool_push_task(struct ThreadPool *restrict pool,
		      const struct ProcedureClosure *const restrict task_cl,
		      const struct HandlerClosure *const restrict fail_cl);
extern inline void
thread_pool_clear_completed(struct ThreadPool *restrict pool,
			    const struct HandlerClosure *const restrict fail_cl);
extern inline void
thread_pool_stop(struct ThreadPool *restrict pool,
		 const struct HandlerClosure *const restrict fail_cl);
extern inline void
thread_pool_destroy(struct ThreadPool *restrict pool);
