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
	struct String db_name = {
		.bytes	= "foo_forum",
		.length = 9lu
	};

	const struct StringInterval db_names = {
		.from  = &db_name,
		.until = &db_name + 1l
	};

	const struct MysqlCredentials creds = {
		.password.bytes = MYSQL_DEFAULT_PASSWORD,
		.user		= "root"
	};




	int exit_status = EXIT_SUCCESS;

	mysql_seed_execute(&creds,
			   &db_names,
			   1u,
			   &exit_status);

	TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS,
			      exit_status);
}
