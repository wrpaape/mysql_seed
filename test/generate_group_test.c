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
	size_t groups[12];

	size_t *restrict group = &groups[0];
	const size_t *const restrict group_until
	= partition_groups_even(group,
				12,
				1000);

	TEST_ASSERT_EQUAL_INT(12,
			      group_until - group);

	do {
		printf("%zu\n", *group);
		++group;
	} while (group < group_until);
}

void test_generate_groups_linear(void)
{
	size_t groups[10];

	size_t *restrict group = &groups[0];
	const size_t *const restrict group_until
	= partition_groups_linear(group,
				  10,
				  100);

	TEST_ASSERT_EQUAL_INT(10,
			      group_until - group);

	do {
		printf("%zu\n", *group);
		++group;
	} while (group < group_until);
}
