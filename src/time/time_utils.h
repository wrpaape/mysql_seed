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

	extern mach_port_t clock_port;
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


/* UNIX time to timestamp:
 *
 * tm_sec + tm_min*60 + tm_hour*3600 + tm_yday*86400 +
 * (tm_year-70)*31536000 + ((tm_year-69)/4)*86400 -
 * ((tm_year-1)/100)*86400 + ((tm_year+299)/400)*86400
 *
 * simplifies to:
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
#define TIME_SECONDS_OFFSET	62167208832u /* add 55080 (15 hours, 18 minutes)
						for current UTC */

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
#define FAIL_SWITCH_ERRNO_FAILURE -1
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
timespec_now_muffle(struct timespec *const restrict time)
{
#ifdef __MACH__ /* OS X does not have clock_gettime, use clock_get_time */
/* taken from stackoverflow user 'jbenet''s answer to
 * https://stackoverflow.com/questions/5167269/clock-gettime-alternative-in-mac-os-x
 * https://gist.github.com/jbenet/1087739A (source) */
	mach_timespec_t mach_time;

	if (clock_get_time(clock_port,
			   &mach_time) != KERN_SUCCESS)
		return;

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
	(void) clock_gettime(CLOCK_REALTIME,
			     time);
#endif
}


inline bool
timespec_now_status(struct timespec *const restrict time)
{
#ifdef __MACH__
	mach_timespec_t mach_time;

	if (clock_get_time(clock_port,
			   &mach_time) != KERN_SUCCESS)
		return false;

	time->tv_sec  = mach_time.tv_sec;
	time->tv_nsec = mach_time.tv_nsec;

	return true;

#elif defined(WIN32)
	__int64 wintime;

	GetSystemTimeAsFileTime((FILETIME *) &wintime);

	wintime -= w2ux;

	time->tv_sec  = wintime / exp7;
	time->tv_nsec = (wintime % exp7) * 100;

	return true;
#else
	return clock_gettime(CLOCK_REALTIME,
			     time) == 0;
#endif
}

inline bool
timespec_now_report(struct timespec *const restrict time,
		    const char *restrict *const restrict failure)
{
#ifdef __MACH__
	mach_timespec_t mach_time;

#undef	FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE clock_get_time
	switch (clock_get_time(clock_port,
			       &mach_time)) {
	case KERN_SUCCESS:
		time->tv_sec  = mach_time.tv_sec;
		time->tv_nsec = mach_time.tv_nsec;
		return true;

	FAIL_SWITCH_STATUS_CASE_1(KERN_INVALID_ADDRESS,
				  "The specified address is not currently "
				  "valid.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_PROTECTION_FAILURE,
				  "The specified memory is valid, but does not "
				  "permit the required forms of access.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_NO_SPACE,
				  "The address range specified is already in "
				  "use, or no address range of the size "
				  "specified could be found.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_INVALID_ARGUMENT,
				  "The function requested was not applicable to"
				  " this type of argument, or an argument is "
				  "invalid.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_FAILURE,
				  "The function could not be performed.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_RESOURCE_SHORTAGE,
				  "A system resource could not be allocated to "
				  "fulfill this request.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_NOT_RECEIVER,
				  "The task in question does not hold receive "
				  "rights for the port argument.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_NO_ACCESS,
				  "bogus access restriction")
	FAIL_SWITCH_STATUS_CASE_1(KERN_MEMORY_FAILURE,
				  "During a page fault, the target address "
				  "refers to a memory object that has been "
				  "destroyed.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_MEMORY_ERROR,
				  "During a page fault, the memory object "
				  "indicated that the data could not be "
				  "returned.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_ALREADY_IN_SET,
				  "The receive right is already a member of the"
				  " portset.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_NOT_IN_SET,
				  "The receive right is not a member of a port "
				  "set.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_NAME_EXISTS,
				  "The name already denotes a right in the task"
				  ".")
	FAIL_SWITCH_STATUS_CASE_1(KERN_ABORTED,
				  "The operation was aborted.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_INVALID_NAME,
				  "The name doesn't denote a right in the task"
				  ".")
	FAIL_SWITCH_STATUS_CASE_1(KERN_INVALID_TASK,
				  "target task isn't an active task.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_INVALID_RIGHT,
				  "The name denotes a right, but not an "
				  "appropriate right.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_INVALID_VALUE,
				  "blatant range error")
	FAIL_SWITCH_STATUS_CASE_1(KERN_UREFS_OVERFLOW,
				  "Operation would overflow limit on "
				  "user-references.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_INVALID_CAPABILITY,
				  "The supplied (port) capability is improper.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_RIGHT_EXISTS,
				  "The task already has send or receive rights "
				  "for the port under another name.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_INVALID_HOST,
				  "target host isn't actually a host.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_MEMORY_PRESENT,
				  "An attempt was made to supply \"precious\" "
				  "data for memory that is already present in a"
				  " memory object.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_INVALID_PROCESSOR_SET,
				  "An argument applied to assert processor set "
				  "privilege was not a processor set control "
				  "port.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_POLICY_LIMIT,
				  "The specified scheduling attributes exceed "
				  "the thread's limits.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_INVALID_POLICY,
				  "The specified scheduling policy is not "
				  "currently enabled for the processor set.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_INVALID_OBJECT,
				  "The external memory manager failed to "
				  "initialize the memory object.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_ALREADY_WAITING,
				  "A thread is attempting to wait for an event "
				  "for which there is already a waiting thread"
				  ".")
	FAIL_SWITCH_STATUS_CASE_1(KERN_DEFAULT_SET,
				  "An attempt was made to destroy the default "
				  "processor set.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_EXCEPTION_PROTECTED,
				  "An attempt was made to fetch an exception "
				  "port that is protected, or to abort a thread"
				  " while processing a protected exception.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_INVALID_LEDGER,
				  "A ledger was required but not supplied.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_INVALID_MEMORY_CONTROL,
				  "The port was not a memory cache control port"
				  ".")
	FAIL_SWITCH_STATUS_CASE_1(KERN_INVALID_SECURITY,
				  "An argument supplied to assert security "
				  "privilege was not a host security port.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_NOT_DEPRESSED,
				  "thread_depress_abort was called on a thread "
				  "which was not currently depressed.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_TERMINATED,
				  "object has been terminated and is no longer "
				  "available")
	FAIL_SWITCH_STATUS_CASE_1(KERN_LOCK_SET_DESTROYED,
				  "The lock set has been destroyed and is no "
				  "longer available.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_LOCK_UNSTABLE,
				  "The thread holding the lock terminated "
				  "before releasing the lock.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_LOCK_OWNED,
				  "The lock is already owned by another thread"
				  ".")
	FAIL_SWITCH_STATUS_CASE_1(KERN_LOCK_OWNED_SELF,
				  "The lock is already owned by the calling "
				  "thread.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_SEMAPHORE_DESTROYED,
				  "semaphore has been destroyed and is no "
				  "longer available.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_RPC_SERVER_TERMINATED,
				  "return from RPC indicating the target server"
				  " was terminated before it successfully "
				  "replied.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_RPC_TERMINATE_ORPHAN,
				  "terminated an orphaned activation.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_RPC_CONTINUE_ORPHAN,
				  "Allow an orphaned activation to continue "
				  "executing.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_NOT_SUPPORTED,
				  "Empty thread activation (No thread linked to"
				  " it)")
	FAIL_SWITCH_STATUS_CASE_1(KERN_NODE_DOWN,
				  "remote node down or inaccessible.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_NOT_WAITING,
				  "A signalled thread was not actually waiting"
				  ".")
	FAIL_SWITCH_STATUS_CASE_1(KERN_OPERATION_TIMED_OUT,
				  "Some thread-oriented operation "
				  "(semaphore_wait) timed out")
	FAIL_SWITCH_STATUS_CASE_1(KERN_CODESIGN_ERROR,
				  "During a page fault, indicates that the page"
				  " was rejectedas a result of a signature "
				  "check.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_POLICY_STATIC,
				  "The requested property cannot be changed at "
				  "this time.")
	FAIL_SWITCH_STATUS_CASE_1(KERN_INSUFFICIENT_BUFFER_SIZE,
				  "The provided buffer is of insufficient size "
				  "for the requested data.")
	FAIL_SWITCH_STATUS_DEFAULT_CASE()
	}

#elif defined(WIN32)
	__int64 wintime;

	GetSystemTimeAsFileTime((FILETIME *) &wintime);

	wintime -= w2ux;

	time->tv_sec  = wintime / exp7;
	time->tv_nsec = (wintime % exp7) * 100;

	return true;
#else
#undef	FAIL_SWITCH_ROUTINE
#define FAIL_SWITCH_ROUTINE clock_gettime

	FAIL_SWITCH_ERRNO_OPEN(CLOCK_REALTIME,
			       time)
	FAIL_SWITCH_ERRNO_CASE_1(EFAULT,
				 "'time' points outside the accessible address space.")
	FAIL_SWITCH_ERRNO_CASE_1(EINVAL,
				 "'CLOCK_REALTIME' is not supported on this system.")
	FAIL_SWITCH_ERRNO_CLOSE()
#endif
}

inline void
timespec_now_handle(struct timespec *const restrict time,
		    Handler *const handle,
		    void *arg)
{
	const char *restrict failure;

	if (timespec_now_report(time,
				&failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
timespec_now_handle_cl(struct timespec *const restrict time,
		       const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (timespec_now_report(time,
				&failure))
		return;

	handler_closure_call(fail_cl,
			     failure);
	__builtin_unreachable();
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


inline bool
timespec_offset_now_status(struct timespec *restrict time,
			   const struct timespec *const restrict offset)
{
	const bool success = timespec_now_status(time);

	if (success)
		timespec_offset(time,
				offset);
	return success;
}

inline void
timespec_offset_now_muffle(struct timespec *restrict time,
			   const struct timespec *const restrict offset)
{
	timespec_now_muffle(time);
	timespec_offset(time,
			offset);
}

inline bool
timespec_offset_now_report(struct timespec *restrict time,
			   const struct timespec *const restrict offset,
			   const char *restrict *const restrict failure)
{
	const bool success = timespec_now_report(time,
						 failure);
	if (success)
		timespec_offset(time,
				offset);
	return success;
}

inline void
timespec_offset_now_handle(struct timespec *restrict time,
			   const struct timespec *const restrict offset,
			   Handler *const handle,
			   void *arg)
{
	timespec_now_handle(time,
			    handle,
			    arg);
	timespec_offset(time,
			offset);
}

inline void
timespec_offset_now_handle_cl(struct timespec *restrict time,
			      const struct timespec *const restrict offset,
			      const struct HandlerClosure *const restrict fail_cl)
{
	timespec_now_handle_cl(time,
			       fail_cl);
	timespec_offset(time,
			offset);
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
