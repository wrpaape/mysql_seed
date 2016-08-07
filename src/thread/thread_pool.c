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
worker_crew_init(struct WorkerCrew *const restrict worker_crew,
		  struct Worker *restrict worker,
		  const size_t count_workers,
		  struct ThreadPool *const restrict pool);
extern inline bool
worker_crew_start(struct WorkerCrew *const restrict worker_crew,
		  const char *restrict *const restrict failure);
extern inline void
worker_crew_cancel_failure(struct WorkerCrew *const restrict worker_crew);
extern inline void
worker_crew_cancel_success(struct WorkerCrew *const restrict worker_crew,
			   const struct HandlerClosure *const restrict fail_cl);


/* TaskBuffer operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
task_buffer_init(struct TaskBuffer *const restrict task_buffer,
		 const struct TaskStore *const restrict task_store);

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
extern inline bool
thread_pool_status_await_success(struct ThreadPoolStatus *const restrict status,
				 const char *restrict *const restrict failure);
extern inline enum ThreadFlag
thread_pool_status_check_busy(struct ThreadPoolStatus *const restrict status,
			      const char *restrict *const restrict failure);

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
extern inline bool
supervisor_start(struct Supervisor *const restrict supervisor,
		 const char *restrict *const restrict failure);
extern inline void
supervisor_init(struct Supervisor *const restrict supervisor,
		struct ThreadPool *const restrict pool);
extern inline void
supervisor_listen(struct Supervisor *const restrict supervisor);
extern inline void
supervisor_signal_muffle(struct Supervisor *const restrict supervisor,
			 SupervisorEvent *const event);
extern inline bool
supervisor_signal_report(struct Supervisor *const restrict supervisor,
			 SupervisorEvent *const event,
			 const char *restrict *const restrict failure);
extern inline void
supervisor_signal_handle_cl(struct Supervisor *const restrict supervisor,
			    SupervisorEvent *const event,
			    const struct HandlerClosure *const restrict fail_cl);


/* ThreadPool operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
thread_pool_init(struct ThreadPool *const restrict pool,
		 const struct TaskStore *const restrict task_store,
		 struct Worker *const restrict workers,
		 const size_t count_workers);
extern inline struct ThreadPool *
thread_pool_create(const struct ProcedureClosure *const restrict init_tasks,
		   const size_t count_init_tasks,
		   const size_t count_workers,
		   const char *restrict *const restrict failure);
extern inline bool
thread_pool_start(struct ThreadPool *const restrict pool,
		  const char *restrict *const restrict failure);
extern inline bool
thread_pool_await(struct ThreadPool *const restrict pool,
		  const char *restrict *const restrict failure);
extern inline enum ThreadFlag
thread_pool_alive(struct ThreadPool *const restrict pool,
		  const char *restrict *const restrict failure);
extern inline void
thread_pool_push_task(struct ThreadPool *const restrict pool,
		      const struct ProcedureClosure *const restrict task_cl,
		      const struct HandlerClosure *const restrict fail_cl);
extern inline void
thread_pool_cancel(struct ThreadPool *const restrict pool);
extern inline bool
thread_pool_stop(struct ThreadPool *const restrict pool,
		 const char *restrict *const restrict failure);
extern inline void
thread_pool_await_exit_failure(struct ThreadPool *const restrict pool);
extern inline bool
thread_pool_await_exit_success(struct ThreadPool *const restrict pool,
			       const char *restrict *const restrict failure);
/* extern inline int */
/* thread_pool_exit_status(struct ThreadPool *const restrict pool, */
/* 			const char *restrict *const restrict failure); */
extern inline void
thread_pool_exit_on_failure(struct ThreadPool *const restrict pool,
			    const char *restrict failure);
extern inline bool
thread_pool_reload(struct ThreadPool *const restrict pool,
		   struct TaskStore *const restrict store,
		   const char *restrict *const restrict failure);
extern inline void
thread_pool_retreive_cold(struct ThreadPool *const restrict pool,
			  struct TaskStore *const restrict store);
extern inline void
thread_pool_retreive_hot(struct ThreadPool *const restrict pool,
			 struct TaskStore *const restrict store,
			 const struct HandlerClosure *const restrict fail_cl);
extern inline void
thread_pool_destroy(struct ThreadPool *const restrict pool);
