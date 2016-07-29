#include "time/time_utils.h"

/* seconds since 00:00:00, January 1st, 1970 */
extern inline bool
time_status(time_t *const restrict now);
extern inline void
time_muffle(time_t *const restrict now);
extern inline bool
time_report(time_t *const restrict now,
	    const char *restrict *const restrict failure);
extern inline void
time_handle(time_t *const restrict now,
	    Handler *const handle,
	    void *arg);
extern inline void
time_handle_cl(time_t *const restrict now,
	       const struct HandlerClosure *const restrict fail_cl);

extern inline void
timespec_now(struct timespec *restrict time);
extern inline long
timespec_diff_nano(const struct timespec *const restrict time0,
		   const struct timespec *const restrict time1);
extern inline void
timespec_offset(struct timespec *const restrict time,
		const struct timespec *const restrict offset);
extern inline void
timespec_offset_now(struct timespec *restrict time,
		    const struct timespec *const restrict offset);
