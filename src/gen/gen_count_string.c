#include "gen/gen_count_string.h"

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

/* 10 ms */
const struct timespec cs_await_span = {
	.tv_sec  = 0,
	.tv_nsec = 10000000l
};

extern inline void
count_string_size_internals(struct CountString *const restrict string);

extern inline void
count_string_log_alloc_failure(const size_t upto,
			       const char *const restrict failure);

extern inline void
count_buffer_increment(char *restrict digit);

extern inline void
count_string_set_internals(struct CountString *const restrict string);

extern inline void
count_string_init_internals(struct CountString *const restrict string);

extern inline void
count_string_await(struct CountString *const restrict string);

extern inline void
count_string_free_internals(struct CountString *const restrict string);

void
count_string_do_init(void *arg)
{
	struct CountString *const restrict
	string = (struct CountString *const restrict) arg;

	seed_mutex_handle_lock(&string->processing);


	count_string_init_internals(string);

	string->incomplete = false;

	seed_mutex_handle_unlock(&string->processing);

	seed_thread_cond_handle_broadcast(&string->done);
}

extern inline void
count_string_init(struct CountString *const restrict string,
		  const size_t upto);
