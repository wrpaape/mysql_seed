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
	.incomplete = true,
	.pointers   = NULL,
	.ready	    = SEED_THREAD_COND_INITIALIZER,
	.ready_lock = SEED_MUTEX_INITIALIZER
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
