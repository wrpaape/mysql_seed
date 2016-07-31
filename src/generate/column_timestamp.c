#include "generate/column_timestamp.h"

/* "YYYY-MM-DD HH:MM:SS" */


extern inline void
timestamp_string_init(const struct Timestamp *const restrict timestamp,
		      char *restrict string);

extern inline void
timestamp_string_increment(char *restrict ptr);

void
build_column_timestamp_fixed(void *arg)
{
}
