#include "unity.h"
#include "system/stdio_utils.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_stdio_utils(void)
{
	char buffer[20];
	const char *restrict failure;

	TEST_ASSERT_TRUE_MESSAGE(read_password(&buffer[0],
					       sizeof(buffer),
					       &failure),
				 failure);

	printf("read upto 20 characters: %s\n",
	       &buffer[0]);
}
