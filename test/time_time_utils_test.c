#include "unity.h"
#include "time/time_utils.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_time_stamp_init(void)
{
	struct TimeStamp time_stamp;
	time_t now;

	TEST_ASSERT_TRUE(time_status(&now));

	time_stamp_init(&time_stamp,
			now);

	unsigned int days = time_stamp.day;

	switch (time_stamp.month) {
	case 12u:
		days += 31u;
	case 11u:
		days += 30u;
	case 10u:
		days += 31u;
	case  9u:
		days += 30u;
	case  8u:
		days += 31u;
	case  7u:
		days += 31u;
	case  6u:
		days += 30u;
	case  5u:
		days += 31u;
	case  4u:
		days += 30u;
	case  3u:
		days += 31u;
	case  2u:
		days += is_leap_year(time_stamp.year) ? 29u : 28u;
	case  1u:
		days -= 1u;
		break;
	default:
		TEST_FAIL_MESSAGE("invalid month");
	}

	const uint64_t sum = time_stamp.seconds
			   + (time_stamp.minutes * 60u)
			   + (time_stamp.hours * 3600u)
			   + (days * 86400u)
			   + ((time_stamp.year - 1970) * 31536000u)
			   + (((  ((time_stamp.year - 1969) * 100u)
			        - ((time_stamp.year - 1901) * 4u)
			        + ((time_stamp.year - 1601)))
			       * 86400u) / 400u);

	TEST_ASSERT_EQUAL_UINT(now, sum);
}

void test_time_stamp_now(void)
{
	struct TimeStamp time_stamp;

	TEST_ASSERT_TRUE(time_stamp_now_status(&time_stamp));

	printf("year:    %u\n"
	       "month:   %u\n"
	       "day:     %u\n"
	       "hours:   %u\n"
	       "minutes: %u\n"
	       "seconds: %u\n",
	       time_stamp.year,
	       time_stamp.month,
	       time_stamp.day,
	       time_stamp.hours,
	       time_stamp.minutes,
	       time_stamp.seconds);
}
