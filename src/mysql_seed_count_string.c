#include "mysql_seed_count_string.h"

extern inline void
count_string_spec_init(struct CountStringSpec *const restrict spec,
		       const size_t upto);

extern inline void
count_string_log_alloc_failure(const size_t upto,
			       const char *const restrict failure);

extern inline void
count_string_init(char *const restrict string,
		  const struct CountStringSpec *const restrict spec,
		  size_t upto);

extern inline char *
count_string_create(const size_t upto);
