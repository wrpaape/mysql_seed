#include "generate/counter.h"

/* global variables
 *─────────────────────────────────────────────────────────────────────────── */
const Mag0String mag_0_min_string = { "1" };
const Mag1String mag_1_min_string = { "10" };
const Mag2String mag_2_min_string = { "100" };
const Mag3String mag_3_min_string = { "1000" };
#ifdef LARGE_UPTO_MAX
const Mag4String mag_4_min_string = { "10000" };
const Mag5String mag_5_min_string = { "100000" };
const Mag6String mag_6_min_string = { "1000000" };
const Mag7String mag_7_min_string = { "10000000" };
#endif	/*  ifdef LARGE_UPTO_MAX */

extern inline void
counter_size_internals(struct Counter *const restrict counter);

extern inline void
count_buffer_increment(char *restrict digit);

extern inline void
counter_set_internals(struct Counter *const restrict counter);

extern inline void
counter_init_internals(struct Counter *const restrict counter);

extern inline void
counter_await(struct Counter *const restrict counter,
	      const struct HandlerClosure *const restrict fail_cl);

extern inline void
counter_free_internals(struct Counter *const restrict counter);

void
counter_do_init(void *arg)
{
	struct Counter *const restrict
	counter = (struct Counter *const restrict) arg;

	seed_mutex_handle_lock(&counter->processing);


	counter_init_internals(counter);

	counter->incomplete = false;

	seed_mutex_handle_unlock(&counter->processing);

	thread_cond_broadcast_handle_cl(&counter->done,
					&counter->fail_cl);
}

extern inline void
counter_init(struct Counter *const restrict counter,
	     const size_t upto);
