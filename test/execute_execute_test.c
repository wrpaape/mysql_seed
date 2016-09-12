#include "unity.h"
#include "execute/execute.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_execute_execute(void)
{
	/* run only if foo_forum has been generated */

	const struct String db_name = {
		.bytes	= "foo_forum",
		.length = 9lu
	};

	TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS,
			      mysql_seed_execute("root",
						 MYSQL_DEFAULT_PASSWORD,
						 &db_name));
}
