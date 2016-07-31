#include "unity.h"
#include "generate/column_timestamp.h"

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

	timestamp_string_init(&timestamp,
			      &string[0]);

	puts(&string[0]);
}
