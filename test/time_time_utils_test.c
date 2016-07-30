#include "unity.h"
#include "time/time_utils.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_time_stamp_now(void)
{
	struct TimeStamp now;

	time_stamp_now_muffle(&now);

	printf("year:    %u\n"
	       "month:   %u\n"
	       "day:     %u\n"
	       "hours:   %u\n"
	       "minutes: %u\n"
	       "seconds: %u\n",
	       now.year,
	       now.month,
	       now.day,
	       now.hours,
	       now.minutes,
	       now.seconds);
}
