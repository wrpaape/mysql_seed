#include "unity.h"
#include "generate/group.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_generate_groups_even(void)
{
	size_t groups[10];

	size_t *restrict group = &groups[0];
	const size_t *const restrict group_until
	= partition_groups_even(group,
				10,
				100);

	TEST_ASSERT_EQUAL_INT(10, group_until - group);

	size_t total = 0lu;

	do {
		printf("%zu\n", *group);
		total += *group;
		++group;
	} while (group < group_until);

	TEST_ASSERT_EQUAL_UINT(100lu, total);
}

void test_generate_groups_linear(void)
{
	size_t groups[10];

	size_t *restrict group = &groups[0];
	const size_t *const restrict group_until
	= partition_groups_linear(group,
				  10,
				  100);

	TEST_ASSERT_EQUAL_INT(10, group_until - group);

	size_t total = 0lu;

	do {
		printf("%zu\n", *group);
		total += *group;
		++group;
	} while (group < group_until);

	TEST_ASSERT_EQUAL_UINT(100lu, total);
}
