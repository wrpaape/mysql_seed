#include "time/time_utils.h"

extern inline void timespec_now(struct timespec *restrict time);

extern inline long
timespec_diff_nano(const struct timespec *const restrict time0,
		   const struct timespec *const restrict time1);

extern inline void
timespec_offset(struct timespec *const restrict time,
		const struct timespec *const restrict offset);

extern inline void
timespec_offset_now(struct timespec *restrict time,
		    const struct timespec *const restrict offset);
