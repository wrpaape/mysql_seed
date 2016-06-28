#include "gen_strings.h"

extern inline void
gen_strings_log_alloc_failure(const size_t count,
			      const size_t size_est,
			      const char *const restrict failure);

extern inline void
gen_strings_log_realloc_failure(const size_t count,
				const size_t size_est,
				const size_t size_act);
