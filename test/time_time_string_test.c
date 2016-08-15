#include "unity.h"
#include "time/time_string.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_timestamp_string_init(void)
{
	char string[SIZE_TIMESTAMP_STRING];

	struct Timestamp timestamp;

	TEST_ASSERT_TRUE(timestamp_now_status(&timestamp));

	timestamp_string_init(&string[0],
			      &timestamp);

	puts(&string[0]);
}

void test_timestamp_string_increment(void)
{
	char string[SIZE_TIMESTAMP_STRING] = "2000-01-01 00:00:00";

	char *const restrict ptr = &string[SIZE_TIMESTAMP_STRING - 2];

	timestamp_string_increment(ptr);

	TEST_ASSERT_EQUAL_STRING("2000-01-01 00:00:01", &string[0]);

	SET_STRING_WIDTH(&string[11], "23:59:59", 8);

	TEST_ASSERT_EQUAL_STRING("2000-01-01 23:59:59", &string[0]);

	timestamp_string_increment(ptr);

	TEST_ASSERT_EQUAL_STRING("2000-01-02 00:00:00", &string[0]);

	SET_STRING_WIDTH(&string[6], "2-28 23:59:59", 13);

	TEST_ASSERT_EQUAL_STRING("2000-02-28 23:59:59", &string[0]);

	/* 2000 is a leap year */
	timestamp_string_increment(ptr);

	TEST_ASSERT_EQUAL_STRING("2000-02-29 00:00:00", &string[0]);

	SET_STRING_WIDTH(&string[3], "1-02-28 23:59:59", 16);

	TEST_ASSERT_EQUAL_STRING("2001-02-28 23:59:59", &string[0]);

	/* 2001 is a common year */
	timestamp_string_increment(ptr);

	TEST_ASSERT_EQUAL_STRING("2001-03-01 00:00:00", &string[0]);
}
