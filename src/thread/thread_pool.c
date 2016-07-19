#include "thread/thread_pool.h"


/* Worker operations
 *─────────────────────────────────────────────────────────────────────────── */
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

	supervisor_signal_muffle(&pool->supervisor,
				 &supervisor_exit_failure);
	thread_exit();
	__builtin_unreachable();
}
extern inline void
worker_init(struct Worker *const restrict worker,
	    struct ThreadPool *const restrict pool);
extern inline void
worker_process_tasks(struct Worker *const restrict worker);
void *
worker_spawn(void *arg)
{
	worker_process_tasks((struct Worker *const restrict) arg);
	__builtin_unreachable();
}

/* WorkerCrew operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
worker_crew_init(struct WorkerCrew *const restrict workers,
		  struct Worker *restrict worker,
		  const size_t count_workers,
		  struct ThreadPool *const restrict pool);
extern inline void
worker_crew_start(struct WorkerCrew *const restrict workers,
		  const struct HandlerClosure *const restrict fail_cl);
extern inline void
worker_crew_cancel_failure(struct WorkerCrew *const restrict workers);
extern inline void
worker_crew_cancel_success(struct WorkerCrew *const restrict workers,
			   const struct HandlerClosure *const restrict fail_cl);


/* TaskBuffer operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
task_buffer_init(struct TaskBuffer *const restrict tasks,
		 struct TaskQueueNode *const restrict task_nodes,
		 const struct ProcedureClosure *const restrict init_tasks,
		 const size_t count_init_tasks);

/* ThreadPoolStatus operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
thread_pool_status_init(struct ThreadPoolStatus *const restrict status);
extern inline void
thread_pool_status_set_failure(struct ThreadPoolStatus *const restrict status);
extern inline void
thread_pool_status_set_success(struct ThreadPoolStatus *const restrict status,
			       const struct HandlerClosure *const restrict fail_cl);
extern inline void
thread_pool_status_await_failure(struct ThreadPoolStatus *const restrict status);
extern inline void
thread_pool_status_await_success(struct ThreadPoolStatus *const restrict status,
				 const struct HandlerClosure *const restrict fail_cl);

/* Supervisor operations, SupervisorEvents
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
supervisor_do_exit_failure(struct Supervisor *const restrict supervisor);
extern inline void
supervisor_do_exit_success(struct Supervisor *const restrict supervisor);
void
supervisor_exit_failure(struct Supervisor *const restrict supervisor)
{
	supervisor_do_exit_failure(supervisor);

	thread_exit();
	__builtin_unreachable();
}
void
supervisor_exit_success(struct Supervisor *const restrict supervisor)
{
	supervisor_do_exit_success(supervisor);

	thread_exit();
	__builtin_unreachable();
}
void
supervisor_exit_cleanup(void *arg)
{
	supervisor_do_exit_failure((struct Supervisor *const restrict) arg);
}
void
supervisor_exit_on_failure(void *arg,
			   const char *restrict failure)
{
	struct Supervisor *const restrict
	supervisor = (struct Supervisor *const restrict) arg;

	struct ThreadPool *const restrict pool = supervisor->pool;

	mutex_lock_try_catch_open(&pool->log.lock)

	mutex_lock_muffle(&pool->log.lock);

	thread_log_append_string(&pool->log,
				 failure);

	mutex_unlock_muffle(&pool->log.lock);

	mutex_lock_try_catch_close();

	supervisor_do_exit_failure(supervisor);

	thread_exit();
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

	thread_key_set_handle_cl(supervisor->key,
				 supervisor,
				 &supervisor->fail_cl);

	/* listen for event */
	supervisor_listen(supervisor);
	__builtin_unreachable();
}
extern inline void
supervisor_start(struct Supervisor *const restrict supervisor,
		 const struct HandlerClosure *const restrict fail_cl);
extern inline void
supervisor_init(struct Supervisor *const restrict supervisor,
		struct ThreadPool *const restrict pool);
extern inline void
supervisor_listen(struct Supervisor *const restrict supervisor);
extern inline void
supervisor_signal_muffle(struct Supervisor *const restrict supervisor,
			 SupervisorEvent *const event);
extern inline void
supervisor_signal_handle_cl(struct Supervisor *const restrict supervisor,
			    SupervisorEvent *const event,
			    const struct HandlerClosure *const restrict fail_cl);


/* ThreadPool operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
thread_pool_init(struct ThreadPool *const restrict pool,
		 const struct ProcedureClosure *const restrict init_tasks,
		 struct TaskQueueNode *const restrict task_nodes,
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
/* extern inline void */
/* thread_pool_clear_completed(struct ThreadPool *restrict pool, */
/* 			    const struct HandlerClosure *const restrict fail_cl); */
extern inline void
thread_pool_stop(struct ThreadPool *restrict pool,
		 const struct HandlerClosure *const restrict fail_cl);
extern inline void
thread_pool_await_exit_failure(struct ThreadPool *restrict pool);
extern inline void
thread_pool_await_exit_success(struct ThreadPool *restrict pool,
			       const struct HandlerClosure *const restrict fail_cl);
extern inline int
thread_pool_exit_status(struct ThreadPool *restrict pool,
			const struct HandlerClosure *const restrict fail_cl);
extern inline void
thread_pool_exit_on_failure(struct ThreadPool *restrict pool,
			    const char *restrict failure);
extern inline void
thread_pool_destroy(struct ThreadPool *restrict pool);
