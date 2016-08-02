#include "unity.h"
#include "memory/memory_zero.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_memory_zero(void)
{
	char one[1] = { 1 };
	char two[2] = { 1, 1 };
	char fourty_two[42] = { [0 ... 41] = 1};


	memory_zero(&one[0],
		    sizeof(one));

	TEST_ASSERT_EQUAL_INT(0, one[0]);

	memory_zero(&two[0],
		    sizeof(two));

	TEST_ASSERT_EQUAL_INT(0, two[0]);
	TEST_ASSERT_EQUAL_INT(0, two[1]);

	memory_zero(&fourty_two[0],
		    sizeof(fourty_two));

	for (int i = 0; i < 42; ++i)
		TEST_ASSERT_EQUAL_INT(0, fourty_two[i]);
}
