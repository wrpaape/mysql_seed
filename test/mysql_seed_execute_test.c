#include "unity.h"
#include "mysql_seed_execute.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_read_mysql_password(void)
{
	struct MysqlPassword password;

	const char *restrict failure;

	TEST_ASSERT_TRUE_MESSAGE(read_mysql_password(&password),
				 failure);

	printf("read upto %zu characters: %s\n",
	       MYSQL_PASSWORD_SIZE_MAX,
	       password.bytes);
}
