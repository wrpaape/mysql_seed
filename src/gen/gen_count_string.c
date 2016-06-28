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

struct CountString count_string = {
	.upto	    = 0lu,
	.incomplete = true,
	.pointers   = NULL,
	.done	    = SEED_THREAD_COND_INITIALIZER,
	.processing = SEED_MUTEX_INITIALIZER
};

/* 100 ms */
const struct timespec count_string_await_span = {
	.tv_sec  = 0,
	.tv_nsec = 100000000ll
};

extern inline void
count_string_spec_init(struct CountStringSpec *const restrict spec,
		       const size_t upto);

extern inline void
count_string_log_alloc_failure(const size_t upto,
			       const char *const restrict failure);

extern inline void
count_buffer_increment(char *restrict digit);


extern inline void
count_string_pointers_init(char *restrict *const string_ptrs,
			   const unsigned int mag_upto,
			   const size_t upto);

extern inline char **
count_string_pointers_create(const size_t upto);

void
count_string_do_init(void *arg)
{
	seed_worker_try_catch_open(&free,
				   count_string.pointers);

	count_string.pointers = count_string_pointers_create(count_string.upto);

	count_string.incomplete = false;

	seed_thread_cond_handle_broadcast(&count_string.done);

	seed_mutex_handle_unlock(&count_string.processing);

	seed_worker_try_catch_close();
}

extern inline void
count_string_init(const size_t upto);
