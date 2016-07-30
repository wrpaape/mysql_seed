#ifndef MYSQL_SEED_TIME_TIME_UTILS_H_
#define MYSQL_SEED_TIME_TIME_UTILS_H_


/* EXTERNAL DEPENDENCIES
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include <time.h>		/* time */
#include <sys/time.h>		/* timespec */
#include "utils/fail_switch.h"	/* bool, error macros */
#include "utils/closure.h"	/* Handler, HandlerClosure */

#ifdef __MACH__
#	include <mach/clock.h>
#	include <mach/mach.h>
#endif /* ifdef __MACH__ */

#ifdef WIN32
#	include <windows.h>
#	define exp7           10000000i64     /* 1E+7 */
#	define exp9         1000000000i64     /* 1E+9 */
#	define w2ux 116444736000000000i64     /* 1.jan1601 to 1.jan1970 */

struct timespec {
	long tv_sec;
	long tv_nsec;
};
#endif /* ifdef WIN32 */

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * EXTERNAL DEPENDENCIES
 *
 *
 * TYPEDEFS, ENUM AND STRUCT DEFINITIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

struct TimeStamp {
	uint16_t years;
	uint8_t months;
	uint8_t days;
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;
};

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * TYPEDEFS, ENUM AND STRUCT DEFINITIONS
 *
 *
 * CONSTANTS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#define TIME_ERROR ((time_t) -1)
#define ONE_BILLION 1000000000l

#define SECONDS_PER_YEAR	((time_t) 3153600)	/* no leap seconds */
#define SECONDS_PER_DAY		((time_t) 86400)
#define SECONDS_PER_HOUR	((time_t) 3600)
#define SECONDS_PER_MINUTE	((time_t) 60)

/* error messages
 * ────────────────────────────────────────────────────────────────────────── */
#define TIME_FAILURE_MESSAGE						\
FAILURE_REASON("time", "unknown")

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * CONSTANTS
 *
 *
 * FUNCTION-LIKE MACROS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * FUNCTION-LIKE MACROS
 *
 *
 * TOP-LEVEL FUNCTIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

/* seconds since 00:00:00, January 1st, 1970 */
inline bool
time_status(time_t *const restrict now)
{
	return time(now) >= 0;
}

inline void
time_muffle(time_t *const restrict now)
{
	(void) time(now);
}

#define FAIL_SWITCH_ROUTINE time
#define FAIL_SWITCH_FAILURE_POINTER failure

inline bool
time_report(time_t *const restrict now,
	    const char *restrict *const restrict failure)
{
	if (time(now) >= 0)
		return true;

	switch (errno) {
	FAIL_SWITCH_ERRNO_CASE_1(ENOSYS,
				 "function not implemented")
	FAIL_SWITCH_ERRNO_CASE_1(EFAULT,
				 "An argument address referenced invalid memory"
					 ".")
	FAIL_SWITCH_ERRNO_DEFAULT_CASE()
	}
}

inline void
time_handle(time_t *const restrict now,
	    Handler *const handle,
	    void *arg)
{
	const char *restrict failure;

	if (time_report(now,
			&failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
time_handle_cl(time_t *const restrict now,
	       const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (time_report(now,
			&failure))
		return;

	handler_closure_call(fail_cl,
			     failure);
	__builtin_unreachable();
}

/* tm_sec + tm_min*60 + tm_hour*3600 + tm_yday*86400 + */
/* (tm_year-70)*31536000 + ((tm_year-69)/4)*86400 - */
/* ((tm_year-1)/100)*86400 + ((tm_year+299)/400)*86400 */

/* simplifies to:
 *
 *	  seconds
 *	+ minutes * 60
 *	+ hours	  * 3600
 *	+ days	  * 86400
 *	+ year	  * 31556952
 *	- 62167153752
 */

inline void
time_stamp_init(struct TimeStamp *const restrict time_stamp,
		time_t time)
{
	  (tm_year -  69) * 100 / 400
	- (tm_year -   1) *   4 / 400
	+ (tm_year + 299) *   1 / 400;

	time_stamp->years = 1970 + (time / SECONDS_PER_YEAR);
	time %= SECONDS_PER_YEAR;
}

inline void
timespec_now(struct timespec *restrict time)
{
#ifdef __MACH__ /* OS X does not have clock_gettime, use clock_get_time */
/* taken from stackoverflow user 'jbenet''s answer to
 * https://stackoverflow.com/questions/5167269/clock-gettime-alternative-in-mac-os-x
 * https://gist.github.com/jbenet/1087739A (source) */
	clock_serv_t calendar_clock;
	mach_timespec_t mach_time;

	host_get_clock_service(mach_host_self(),
			       CALENDAR_CLOCK,
			       &calendar_clock);

	clock_get_time(calendar_clock,
		       &mach_time);

	mach_port_deallocate(mach_task_self(),
			     calendar_clock);

	time->tv_sec  = mach_time.tv_sec;
	time->tv_nsec = mach_time.tv_nsec;

#elif defined(WIN32)
/* taken from stackoverflow user 'Asain Kujovic''s answer to
 * http://stackoverflow.com/questions/5404277/porting-clock-gettime-to-windows */
	__int64 wintime;

	GetSystemTimeAsFileTime((FILETIME *) &wintime);

	wintime -= w2ux;

	time->tv_sec  = wintime / exp7;
	time->tv_nsec = (wintime % exp7) * 100;
#else
	clock_gettime(CLOCK_REALTIME,
		      time);
#endif
}

inline long
timespec_diff_nano(const struct timespec *const restrict time0,
		   const struct timespec *const restrict time1)
{
	return ((time1->tv_sec  - time0->tv_sec) * ONE_BILLION)
	     +  (time1->tv_nsec - time0->tv_nsec);
}

inline void
timespec_offset(struct timespec *const restrict time,
		const struct timespec *const restrict offset)
{
	time->tv_sec  += offset->tv_sec;
	time->tv_nsec += offset->tv_nsec;
}

inline void
timespec_offset_now(struct timespec *restrict time,
		    const struct timespec *const restrict offset)
{
	timespec_now(time);
	timespec_offset(time, offset);
}

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * TOP-LEVEL FUNCTIONS
 *
 *
 * HELPER FUNCTIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * HELPER FUNCTIONS */


#undef FAIL_SWITCH_ROUTINE
#undef FAIL_SWITCH_FAILURE_POINTER

#endif /* ifndef MYSQL_SEED_TIME_TIME_UTILS_H_ */
