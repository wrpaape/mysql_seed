#include "time/time_string.h"

extern inline void
timestamp_string_init(char *restrict string,
		      const struct Timestamp *const restrict timestamp);

extern inline void
timestamp_string_increment_overflow(char *const restrict last);

extern inline void
timestamp_string_increment(char *restrict ptr);

extern inline void
datetime_string_increment(char *restrict ptr);
