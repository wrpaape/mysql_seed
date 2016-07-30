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
	uint16_t year;
	uint8_t month;
	uint8_t day;
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

#define TIME_SECONDS_PER_MINUTE	60u
#define TIME_SECONDS_PER_HOUR	3600u
#define TIME_SECONDS_PER_DAY	86400u
/* #define TIME_SECONDS_PER_YEAR	31556952u */
/* #define TIME_SECONDS_OFFSET	62167153752u */
#define TIME_SECONDS_PER_YEAR	31558680u
#define TIME_SECONDS_OFFSET	62170438680u

inline bool
is_leap_year(const unsigned int year)
{
	if ((year % 4u) != 0u)
		return false;

	if ((year % 100u) != 0u)
		return true;

	return (year % 400u) == 0u;
}

/* TimeStamp operations
 * ────────────────────────────────────────────────────────────────────────── */
inline void
time_stamp_set_month_day(struct TimeStamp *const restrict time_stamp,
			 unsigned int days_since_jan1)
{
	/* jan	31 */

	/* feb	28 / 29	 31 */
	/* mar	31	 59 / 60 */
	/* apr	30	 90 / 91 */

	/* may	31	121 / 122 */
	/* jun	30	151 / 152 */

	/* jul	31	182 / 183 */
	/* aug	31	213 / 214 */
	/* sep	30	243 / 244 */

	/* oct	31	273 / 274 */
	/* nov	30	303 / 304 */
	/* dec	31	334 / 335 */


	if (days_since_jan1 < 31) {
		time_stamp->month = 1u;
		time_stamp->day	  = 1u + days_since_jan1;
		return;
	}

	const unsigned int leap_day = is_leap_year(time_stamp->year);

	days_since_jan1 -= leap_day;

	if (days_since_jan1 < 182) {
		if (days_since_jan1 < 121) {
			if (days_since_jan1 < 90) {
				if (days_since_jan1 < 59) {
					time_stamp->month = 2u;
					time_stamp->day	  = days_since_jan1
							  + leap_day
							  - 30u;
				} else {
					time_stamp->month = 3u;
					time_stamp->day	  = days_since_jan1
							  + leap_day
							  - 58u;
				}
			} else {
				time_stamp->month = 4u;
				time_stamp->day	  = days_since_jan1
						  + leap_day
						  - 89u;
			}
		} else {
			if (days_since_jan1 < 151) {
				time_stamp->month = 5u;
				time_stamp->day	  = days_since_jan1
						  + leap_day
						  - 120u;
			} else {
				time_stamp->month = 6u;
				time_stamp->day	  = days_since_jan1
						  + leap_day
						  - 150u;
			}
		}
	} else {
		if (days_since_jan1 < 273) {
			if (days_since_jan1 < 243) {
				if (days_since_jan1 < 213) {
					time_stamp->month = 7u;
					time_stamp->day	  = days_since_jan1
							  + leap_day
							  - 181u;
				} else {
					time_stamp->month = 8u;
					time_stamp->day	  = days_since_jan1
							  + leap_day
							  - 212u;
				}
			} else {
				time_stamp->month = 9u;
				time_stamp->day	  = days_since_jan1
						  + leap_day
						  - 242u;
			}
		} else {
			if (days_since_jan1 < 334) {
				if (days_since_jan1 < 303) {
					time_stamp->month = 10u;
					time_stamp->day	  = days_since_jan1
							  + leap_day
							  - 272u;
				} else {
					time_stamp->month = 11u;
					time_stamp->day	  = days_since_jan1
							  + leap_day
							  - 302u;
				}
			} else {
				time_stamp->month = 12u;
				time_stamp->day	  = days_since_jan1
						  + leap_day
						  - 333u;
			}
		}
	}
}

inline void
time_stamp_init(struct TimeStamp *const restrict time_stamp,
		const time_t time)
{
	uint64_t rem_seconds = time + TIME_SECONDS_OFFSET;

	time_stamp->year = rem_seconds / TIME_SECONDS_PER_YEAR;

	rem_seconds %= TIME_SECONDS_PER_YEAR;

	const unsigned int days_since_jan1 = rem_seconds / TIME_SECONDS_PER_DAY;

	rem_seconds %= TIME_SECONDS_PER_DAY;

	time_stamp_set_month_day(time_stamp,
				 days_since_jan1);

	time_stamp->hours = rem_seconds / TIME_SECONDS_PER_HOUR;

	rem_seconds %= TIME_SECONDS_PER_HOUR;

	time_stamp->minutes = rem_seconds / TIME_SECONDS_PER_MINUTE;

	time_stamp->seconds = rem_seconds % TIME_SECONDS_PER_MINUTE;
}

inline bool
time_stamp_now_status(struct TimeStamp *const restrict time_stamp)
{
	time_t now;

	if (time_status(&now)) {
		time_stamp_init(time_stamp,
				now);
		return true;
	}

	return false;
}

inline void
time_stamp_now_muffle(struct TimeStamp *const restrict time_stamp)
{
	time_t now;

	time_muffle(&now);

	time_stamp_init(time_stamp,
			now);
}

inline bool
time_stamp_now_report(struct TimeStamp *const restrict time_stamp,
		      const char *restrict *const restrict failure)
{
	time_t now;

	if (time_report(&now,
			failure)) {
		time_stamp_init(time_stamp,
				now);
		return true;
	}

	return false;
}

inline void
time_stamp_now_handle(struct TimeStamp *const restrict time_stamp,
		      Handler *const handle,
		      void *arg)
{
	const char *restrict failure;

	if (time_stamp_now_report(time_stamp,
				  &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
time_stamp_now_handle_cl(struct TimeStamp *const restrict time_stamp,
			 const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (time_stamp_now_report(time_stamp,
				  &failure))
		return;

	handler_closure_call(fail_cl,
			     failure);
	__builtin_unreachable();
}

/* timespec operations
 * ────────────────────────────────────────────────────────────────────────── */

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
