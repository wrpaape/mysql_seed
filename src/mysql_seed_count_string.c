#include "mysql_seed_count_string.h"


extern inline unsigned int
count_string_digit_count(const size_t n);

inline size_t
count_string_char_count(const size_t upto);

char *
count_string_alloc(char *restrict *const restrict string,
		   const size_t upto);

extern inline void
log_csa_failure(const enum CountStringAllocStatus status,
		const size_t upto);
inline void
count_string_log_alloc_failure(const size_t upto,
			       const char *const restrict failure);

extern inline char *
count_string_put_digits(char *restrict ptr,
			size_t upto);

extern inline char *
count_string_create(const size_t upto);
