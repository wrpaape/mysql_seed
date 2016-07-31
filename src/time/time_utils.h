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

struct Timestamp {
	uint16_t year;		/* 0000 - 9999 */
	uint8_t leap_year;	/* 0	-    1 */
	uint8_t month;		/* 01	-   12 */
	uint8_t day;		/* 01	-   31 */
	uint8_t hour;		/* 00	-   23 */
	uint8_t minute;		/* 00	-   59 */
	uint8_t second;		/* 00	-   59 */
};

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * TYPEDEFS, ENUM AND STRUCT DEFINITIONS
 *
 *
 * CONSTANTS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#define TIME_ERROR ((time_t) -1)

#define ONE_BILLION 1000000000l

#define JANUARY	   1u
#define FEBRUARY   2u
#define MARCH	   3u
#define APRIL	   4u
#define MAY	   5u
#define JUNE	   6u
#define JULY	   7u
#define AUGUST	   8u
#define SEPTEMBER  9u
#define OCTOBER	  10u
#define NOVEMBER  11u
#define DECEMBER  12u

/* common year values */
#define JANUARY_DAY_COUNT   31u
#define FEBRUARY_DAY_COUNT  28u
#define MARCH_DAY_COUNT	    31u
#define APRIL_DAY_COUNT	    30u
#define MAY_DAY_COUNT	    31u
#define JUNE_DAY_COUNT	    30u
#define JULY_DAY_COUNT	    31u
#define AUGUST_DAY_COUNT    31u
#define SEPTEMBER_DAY_COUNT 30u
#define OCTOBER_DAY_COUNT   31u
#define NOVEMBER_DAY_COUNT  30u
#define DECEMBER_DAY_COUNT  31u

/* offset from january 1st */
#define JANUARY_DAY_OFFSET_MIN    0u
#define JANUARY_DAY_OFFSET_MAX   30u
#define FEBRUARY_DAY_OFFSET_MIN  31u
#define FEBRUARY_DAY_OFFSET_MAX  58u
#define MARCH_DAY_OFFSET_MIN     59u
#define MARCH_DAY_OFFSET_MAX     89u
#define APRIL_DAY_OFFSET_MIN     90u
#define APRIL_DAY_OFFSET_MAX     120u
#define MAY_DAY_OFFSET_MIN	 121u
#define MAY_DAY_OFFSET_MAX	 150u
#define JUNE_DAY_OFFSET_MIN	 151u
#define JUNE_DAY_OFFSET_MAX	 181u
#define JULY_DAY_OFFSET_MIN	 182u
#define JULY_DAY_OFFSET_MAX	 212u
#define AUGUST_DAY_OFFSET_MIN    213u
#define AUGUST_DAY_OFFSET_MAX    242u
#define SEPTEMBER_DAY_OFFSET_MIN 243u
#define SEPTEMBER_DAY_OFFSET_MAX 272u
#define OCTOBER_DAY_OFFSET_MIN   273u
#define OCTOBER_DAY_OFFSET_MAX   302u
#define NOVEMBER_DAY_OFFSET_MIN  303u
#define NOVEMBER_DAY_OFFSET_MAX  333u
#define DECEMBER_DAY_OFFSET_MIN  334u
#define DECEMBER_DAY_OFFSET_MAX  365u

extern const unsigned int DAY_COUNT_MAP[DECEMBER + 1];

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
 *	+ years	  * 31556952
 *	- 62167153752
 */

#define TIME_SECONDS_PER_MINUTE	60u
#define TIME_SECONDS_PER_HOUR	3600u
#define TIME_SECONDS_PER_DAY	86400u
#define TIME_SECONDS_PER_YEAR	31556952u
/* #define TIME_SECONDS_OFFSET	62167153752u */
#define TIME_SECONDS_OFFSET	62167208832u


inline bool
is_leap_year(const unsigned int year)
{
	if ((year % 4u) != 0u)
		return false;

	if ((year % 100u) != 0u)
		return true;

	return (year % 400u) == 0u;
}

/* Timestamp operations
 * ────────────────────────────────────────────────────────────────────────── */
inline void
timestamp_set_month_day(struct Timestamp *const restrict timestamp,
			unsigned int day_offset)
{
	if (day_offset < FEBRUARY_DAY_OFFSET_MIN) {
		timestamp->month = JANUARY;
		timestamp->day	 = 1u + day_offset;
		return;
	}

	day_offset -= timestamp->leap_year;

	if (day_offset < JULY_DAY_OFFSET_MIN) {
		if (day_offset < MAY_DAY_OFFSET_MIN) {
			if (day_offset < APRIL_DAY_OFFSET_MIN) {
				if (day_offset < MARCH_DAY_OFFSET_MIN) {
					timestamp->month = FEBRUARY;
					timestamp->day	 = day_offset
							 + timestamp->leap_year
							 - JANUARY_DAY_OFFSET_MAX;
				} else {
					timestamp->month = MARCH;
					timestamp->day	 = day_offset
							 + timestamp->leap_year
							 - FEBRUARY_DAY_OFFSET_MAX;
				}
			} else {
				timestamp->month = APRIL;
				timestamp->day	 = day_offset
						 + timestamp->leap_year
						 - MARCH_DAY_OFFSET_MAX;
			}
		} else {
			if (day_offset < JUNE_DAY_OFFSET_MIN) {
				timestamp->month = MAY;
				timestamp->day	 = day_offset
						 + timestamp->leap_year
						 - APRIL_DAY_OFFSET_MAX;
			} else {
				timestamp->month = JUNE;
				timestamp->day	 = day_offset
						 + timestamp->leap_year
						 - MAY_DAY_OFFSET_MAX;
			}
		}
	} else {
		if (day_offset < OCTOBER_DAY_OFFSET_MIN) {
			if (day_offset < SEPTEMBER_DAY_OFFSET_MIN) {
				if (day_offset < AUGUST_DAY_OFFSET_MIN) {
					timestamp->month = JULY;
					timestamp->day	 = day_offset
							 + timestamp->leap_year
							 - JUNE_DAY_OFFSET_MAX;
				} else {
					timestamp->month = AUGUST;
					timestamp->day	 = day_offset
							 + timestamp->leap_year
							 - JULY_DAY_OFFSET_MAX;
				}
			} else {
				timestamp->month = SEPTEMBER;
				timestamp->day	 = day_offset
						 + timestamp->leap_year
						 - AUGUST_DAY_OFFSET_MAX;
			}
		} else {
			if (day_offset < DECEMBER_DAY_OFFSET_MIN) {
				if (day_offset < NOVEMBER_DAY_OFFSET_MIN) {
					timestamp->month = OCTOBER;
					timestamp->day	 = day_offset
							 + timestamp->leap_year
							 - SEPTEMBER_DAY_OFFSET_MAX;
				} else {
					timestamp->month = NOVEMBER;
					timestamp->day	 = day_offset
							 + timestamp->leap_year
							 - OCTOBER_DAY_OFFSET_MAX;
				}
			} else {
				timestamp->month = DECEMBER;
				timestamp->day	 = day_offset
						 + timestamp->leap_year
						 - NOVEMBER_DAY_OFFSET_MAX;
			}
		}
	}
}

inline void
timestamp_init(struct Timestamp *const restrict timestamp,
		const time_t time)
{
	uint64_t rem_seconds = time + TIME_SECONDS_OFFSET;

	timestamp->year = rem_seconds / TIME_SECONDS_PER_YEAR;

	rem_seconds %= TIME_SECONDS_PER_YEAR;

	timestamp->leap_year = is_leap_year(timestamp->year);

	timestamp_set_month_day(timestamp,
				rem_seconds / TIME_SECONDS_PER_DAY);

	rem_seconds %= TIME_SECONDS_PER_DAY;

	timestamp->hour = rem_seconds / TIME_SECONDS_PER_HOUR;

	rem_seconds %= TIME_SECONDS_PER_HOUR;

	timestamp->minute = rem_seconds / TIME_SECONDS_PER_MINUTE;

	timestamp->second = rem_seconds % TIME_SECONDS_PER_MINUTE;
}

inline bool
timestamp_now_status(struct Timestamp *const restrict timestamp)
{
	time_t now;

	if (time_status(&now)) {
		timestamp_init(timestamp,
				now);
		return true;
	}

	return false;
}

inline void
timestamp_now_muffle(struct Timestamp *const restrict timestamp)
{
	time_t now;

	time_muffle(&now);

	timestamp_init(timestamp,
		       now);
}

inline bool
timestamp_now_report(struct Timestamp *const restrict timestamp,
		     const char *restrict *const restrict failure)
{
	time_t now;

	if (time_report(&now,
			failure)) {
		timestamp_init(timestamp,
				now);
		return true;
	}

	return false;
}

inline void
timestamp_now_handle(struct Timestamp *const restrict timestamp,
		     Handler *const handle,
		     void *arg)
{
	const char *restrict failure;

	if (timestamp_now_report(timestamp,
				  &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
timestamp_now_handle_cl(struct Timestamp *const restrict timestamp,
			const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (timestamp_now_report(timestamp,
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
