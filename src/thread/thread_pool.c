#include "thread/thread_pool.h"

/* Supervisor operations, ThreadPoolEvents
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
supervisor_oversee_completion(struct ThreadPool *const restrict pool);
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
	struct ThreadPool *const restrict pool =
	(struct ThreadPool *const restrict) arg;

	mutex_lock_try_catch_open(&pool->log.lock)

	mutex_lock_muffle(&pool->log.lock);

	thread_log_append_string(&pool->log,
				 failure);

	mutex_unlock_muffle(&pool->log.lock);

	mutex_lock_try_catch_close();

	thread_exit_detached();
	__builtin_unreachable();
}
extern inline void
supervisor_init(struct Supervisor *const restrict supervisor,
		struct ThreadPool *const restrict pool);
extern inline void
supervisor_listen(struct Supervisor *const restrict supervisor);
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

/* Task operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
task_init(struct Task *const restrict task,
	  struct ThreadQueueNode *const restrict node,
	  const struct ProcedureClosure *const restrict closure);

/* ThreadQueue operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
task_queues_vacant_init(struct ThreadQueue *const restrict vacant,
			struct ThreadQueueNode *restrict node,
			struct Task *restrict task);
extern inline void
task_queues_awaiting_init(struct ThreadQueue *const restrict awaiting,
			  struct ThreadQueueNode *restrict node,
			  struct Task *restrict task,
			  const struct ProcedureClosure *restrict task_cl);
extern inline void
worker_queue_init(struct ThreadQueue *const restrict worker_queue,
		  struct ThreadQueueNode *restrict node,
		  struct Worker *restrict worker,
		  struct ThreadPool *const restrict pool);

/* TaskQueues operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
task_queues_init(struct TaskQueues *const restrict task_queues,
		 struct ThreadQueueNode *const restrict vacant_task_nodes,
		 struct ThreadQueueNode *const restrict init_task_nodes,
		 struct Task *const restrict vacant_tasks,
		 struct Task *const restrict init_tasks,
		 const struct ProcedureClosure *const restrict task_cls);


/* ThreadPool operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
thread_pool_init(struct ThreadPool *const restrict pool,
		 const struct ProcedureClosure *const restrict task_cls,
		 const size_t count_workers,
		 const size_t count_init_tasks,
		 const size_t count_vacant_tasks);
extern inline struct ThreadPool *
thread_pool_create(const struct ProcedureClosure *const restrict task_cls,
		   const size_t count_workers,
		   const size_t count_init_tasks,
		   const size_t count_vacant_tasks,
		   const struct HandlerClosure *const restrict fail_cl);

extern inline void
thread_pool_start(struct ThreadPool *restrict pool,
		  const struct HandlerClosure *const restrict fail_cl);

extern inline void
thread_pool_process(struct ThreadPool *restrict pool,
		    const struct HandlerClosure *const restrict fail_cl);
extern inline void
thread_pool_destroy(struct ThreadPool *restrict pool);

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
