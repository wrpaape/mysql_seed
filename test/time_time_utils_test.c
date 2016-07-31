#include "unity.h"
#include "time/time_utils.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_timestamp_init(void)
{
	struct Timestamp timestamp;
	time_t now;

	TEST_ASSERT_TRUE(time_status(&now));

	timestamp_init(&timestamp,
		       now);

	unsigned int days = timestamp.day;

	switch (timestamp.month) {
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
		days += is_leap_year(timestamp.year) ? 29u : 28u;
	case  1u:
		days -= 1u;
		break;
	default:
		TEST_FAIL_MESSAGE("invalid month");
	}

	const uint64_t sum = timestamp.seconds
			   + (timestamp.minutes * 60u)
			   + (timestamp.hours * 3600u)
			   + (days * 86400u)
			   + ((timestamp.year - 1970) * 31536000u)
			   + (((  ((timestamp.year - 1969) * 100u)
			        - ((timestamp.year - 1901) * 4u)
			        + ((timestamp.year - 1601)))
			       * 86400u) / 400u);

	TEST_ASSERT_EQUAL_UINT(now, sum);
}

void test_timestamp_now(void)
{
	struct Timestamp timestamp;

	TEST_ASSERT_TRUE(timestamp_now_status(&timestamp));

	printf("year:    %u\n"
	       "month:   %u\n"
	       "day:     %u\n"
	       "hours:   %u\n"
	       "minutes: %u\n"
	       "seconds: %u\n",
	       timestamp.year,
	       timestamp.month,
	       timestamp.day,
	       timestamp.hours,
	       timestamp.minutes,
	       timestamp.seconds);
}
