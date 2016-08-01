#include "generate/counter.h"

/* global variables
 *─────────────────────────────────────────────────────────────────────────── */
const Mag0String mag_0_min_string = { "1" };
const Mag1String mag_1_min_string = { "10" };
const Mag2String mag_2_min_string = { "100" };
const Mag3String mag_3_min_string = { "1000" };
#if LARGE_UPTO_MAX
const Mag4String mag_4_min_string = { "10000" };
const Mag5String mag_5_min_string = { "100000" };
const Mag6String mag_6_min_string = { "1000000" };
const Mag7String mag_7_min_string = { "10000000" };
#endif	/*  if LARGE_UPTO_MAX */

extern inline void
counter_size_internals(struct Counter *const restrict counter);

extern inline size_t
counter_size_upto(const size_t upto);

extern inline void
count_buffer_increment_2(char *restrict digit);

extern inline void
count_buffer_increment(char *restrict digit);

extern inline void
counter_set_internals(struct Counter *const restrict counter);

extern inline void
counter_init_internals(struct Counter *const restrict counter);

void
counter_exit_on_failure(void *arg,
			const char *restrict failure)
{
	struct Counter *const restrict counter
	= (struct Counter *const restrict) arg;

	struct Generator *const restrict generator
	= counter->parent;

	struct ThreadLog *const restrict generator_log
	= &generator->log;

	mutex_lock_try_catch_open(&generator_log->lock);

	mutex_lock_muffle(&generator_log->lock);

	thread_log_append_string_size(generator_log,
				      COUNTER_FAILURE_MESSAGE,
				      sizeof(COUNTER_FAILURE_MESSAGE) - 1lu);

	thread_log_append_string(generator_log,
				 failure);

	mutex_unlock_muffle(&generator_log->lock);

	mutex_lock_try_catch_close();

	handler_closure_call(&generator->fail_cl,
			     failure);
	__builtin_unreachable();
}


/* top-level functions
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
counter_init(struct Counter *const restrict counter,
	     struct Generator *const restrict parent,
	     const size_t upto);

extern inline void
counter_free_internals(struct Counter *const restrict counter);

void
build_counter(void *arg)
{
	struct Counter *const restrict
	counter = (struct Counter *const restrict) arg;

	mutex_lock_try_catch_open(&counter->processing);

	mutex_lock_handle_cl(&counter->processing,
			     &counter->fail_cl);

	counter_init_internals(counter);

	counter->ready = true;

	thread_cond_broadcast_handle_cl(&counter->done,
					&counter->fail_cl);

	mutex_unlock_handle_cl(&counter->processing,
			       &counter->fail_cl);

	mutex_lock_try_catch_close();
}

extern inline void
counter_await(struct Counter *const restrict counter,
	      const struct HandlerClosure *const restrict fail_cl);
