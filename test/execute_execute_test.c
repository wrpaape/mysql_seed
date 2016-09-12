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

	int exit_status;

	mysql_seed_execute(&db_name,
			   "root",
			   MYSQL_DEFAULT_PASSWORD,
			   &exit_status);
}
