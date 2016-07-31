#include "time/time_utils.h"

/* constants
 * ────────────────────────────────────────────────────────────────────────── */

const unsigned int DAY_COUNT_MAP[DECEMBER + 1] = {
	[JANUARY]   = JANUARY_DAY_COUNT,
	[FEBRUARY]  = FEBRUARY_DAY_COUNT,
	[MARCH]     = MARCH_DAY_COUNT,
	[APRIL]     = APRIL_DAY_COUNT,
	[MAY]       = MAY_DAY_COUNT,
	[JUNE]      = JUNE_DAY_COUNT,
	[JULY]      = JULY_DAY_COUNT,
	[AUGUST]    = AUGUST_DAY_COUNT,
	[SEPTEMBER] = SEPTEMBER_DAY_COUNT,
	[OCTOBER]   = OCTOBER_DAY_COUNT,
	[NOVEMBER]  = NOVEMBER_DAY_COUNT,
	[DECEMBER]  = DECEMBER_DAY_COUNT
};

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

extern inline bool
is_leap_year(const unsigned int year);

/* Timestamp operations
 * ────────────────────────────────────────────────────────────────────────── */
extern inline void
timestamp_set_month_day(struct Timestamp *const restrict timestamp,
			unsigned int day_offset);

extern inline void
timestamp_init(struct Timestamp *const restrict timestamp,
	       const time_t time);

extern inline bool
timestamp_now_status(struct Timestamp *const restrict timestamp);
extern inline void
timestamp_now_muffle(struct Timestamp *const restrict timestamp);
extern inline bool
timestamp_now_report(struct Timestamp *const restrict timestamp,
		     const char *restrict *const restrict failure);
extern inline void
timestamp_now_handle(struct Timestamp *const restrict timestamp,
		     Handler *const handle,
		     void *arg);
extern inline void
timestamp_now_handle_cl(struct Timestamp *const restrict timestamp,
			const struct HandlerClosure *const restrict fail_cl);

/* timespec operations
 * ────────────────────────────────────────────────────────────────────────── */
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
