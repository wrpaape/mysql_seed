#include "unity.h"
#include <math.h>
#include "utils/utils.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_next_pow_two_ib(void)
{
	TEST_ASSERT_EQUAL_UINT(2lu,      next_pow_two_ib(1lu));
	TEST_ASSERT_EQUAL_UINT(4lu,      next_pow_two_ib(2lu));
	TEST_ASSERT_EQUAL_UINT(1024lu,   next_pow_two_ib(512lu));
	TEST_ASSERT_EQUAL_UINT(1024lu,   next_pow_two_ib(513lu));
}

void test_next_pow_two_lb(void)
{
	TEST_ASSERT_EQUAL_UINT(2lu,      next_pow_two_ib(1lu));
	TEST_ASSERT_EQUAL_UINT(1lu,      next_pow_two_lb(0lu));
}

void test_next_pow_two_ub(void)
{
	TEST_ASSERT_EQUAL_UINT(2lu,      next_pow_two_ib(1lu));
	TEST_ASSERT_EQUAL_UINT(SIZE_MAX, next_pow_two_ub(SIZE_MAX));
}

void test_next_pow_two(void)
{
	TEST_ASSERT_EQUAL_UINT(2lu,      next_pow_two(1lu));
	TEST_ASSERT_EQUAL_UINT(1lu,      next_pow_two(0lu));
	TEST_ASSERT_EQUAL_UINT(SIZE_MAX, next_pow_two(SIZE_MAX));
}




void test_round_pow_two_ib(void)
{
	TEST_ASSERT_EQUAL_UINT(2lu,      round_pow_two_ib(2lu));
	TEST_ASSERT_EQUAL_UINT(512lu,    round_pow_two_ib(512lu));
	TEST_ASSERT_EQUAL_UINT(1024lu,   round_pow_two_ib(513lu));
}

void test_round_pow_two_lb(void)
{
	TEST_ASSERT_EQUAL_UINT(2lu,      round_pow_two_lb(2lu));
	TEST_ASSERT_EQUAL_UINT(1lu,      round_pow_two_lb(0lu));
	TEST_ASSERT_EQUAL_UINT(1lu,      round_pow_two_lb(1lu));
}

void test_round_pow_two_ub(void)
{
	TEST_ASSERT_EQUAL_UINT(2lu,      round_pow_two_ub(2lu));
	TEST_ASSERT_EQUAL_UINT(SIZE_MAX, round_pow_two_ub(SIZE_MAX));
}

void test_round_pow_two(void)
{
	TEST_ASSERT_EQUAL_UINT(2lu,      round_pow_two(2lu));
	TEST_ASSERT_EQUAL_UINT(1lu,      round_pow_two(0lu));
	TEST_ASSERT_EQUAL_UINT(SIZE_MAX, round_pow_two(SIZE_MAX));
}

void test_log_base_two_p2(void)
{
	TEST_ASSERT_EQUAL_UINT(0lu,  log_base_two_p2(1lu));
	TEST_ASSERT_EQUAL_UINT(1lu,  log_base_two_p2(2lu));
	TEST_ASSERT_EQUAL_UINT(15lu, log_base_two_p2(1lu << 15));

	TEST_ASSERT_EQUAL_UINT((unsigned long) log2(1lu << 17),
				    log_base_two_p2(1lu << 17));
}


void test_log_base_two(void)
{
	TEST_ASSERT_EQUAL_UINT(0lu,  log_base_two(1lu));
	TEST_ASSERT_EQUAL_UINT(1lu,  log_base_two(2lu));
	TEST_ASSERT_EQUAL_UINT(15lu, log_base_two(1lu << 15));

	TEST_ASSERT_EQUAL_UINT((unsigned long) log2(1lu << 17),
				       log_base_two(1lu << 17));


	TEST_ASSERT_EQUAL_UINT(1lu,  log_base_two(3lu));
	TEST_ASSERT_EQUAL_UINT(15lu, log_base_two((1lu << 15) + 1lu));
}
