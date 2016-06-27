#include "generate_string.h"

extern inline void
generate_string_log_alloc_failure(const size_t count,
				  const size_t size_est,
				  const char *const restrict failure);

extern inline void
generate_string_log_realloc_failure(const size_t count,
				    const size_t size_est,
				    const size_t size_act);

extern inline size_t
single_names_init(char *restrict *const name_ptrs_base,
		  const struct NameMap *const restrict map,
		  size_t count);

extern inline char **
generate_first_names(const size_t count);
