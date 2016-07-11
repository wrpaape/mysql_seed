#include "unity.h"
#include "mysql_seed_file.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void file_handle_unexpected_fail(void *arg,
				 const char *const restrict failure)
__attribute__((noreturn));

void file_handle_unexpected_fail(void *arg,
				 const char *const restrict failure)
{
	fputs(failure,
	      stderr);
	TEST_FAIL();
	__builtin_unreachable();
}

void file_handle_expected_fail(void *arg,
			       const char *const restrict failure)
__attribute__((noreturn));

void file_handle_expected_fail(void *arg,
			       const char *const restrict failure)
{
	TEST_PASS();
	__builtin_unreachable();
}

static struct FileHandle file = {
	.contents = {
		.bytes  = "hello new file",
		.length = sizeof("hello new file") - 1lu
	},
	.path = {
		.buffer = {
			"test_file.txt"
		},
		.length = sizeof("test_file.txt") - 1lu
	}
};

static const struct HandlerClosure unexpected_fail_cl = {
	.handle = &file_handle_unexpected_fail,
	.arg	= NULL
};

static const struct HandlerClosure expected_fail_cl = {
	.handle = &file_handle_expected_fail,
	.arg	= NULL
};

void test_file_handle_proccess_success(void)
{

	file_handle_process(&file,
			    &unexpected_fail_cl);

	char buffer[sizeof("hello new file")];

	FILE *test_file = fopen("test_file.txt",
				"r");

	TEST_ASSERT_NOT_NULL(test_file);

	fgets(&buffer[0],
	      sizeof(buffer),
	      test_file);

	fclose(test_file);

	TEST_ASSERT_EQUAL_STRING("hello new file",
				 &buffer[0]);
}


void test_file_handle_proccess_failure(void)
{
	/* should fail because 'test_file' exits */
	file_handle_process(&file,
			    &expected_fail_cl);
}

void test_unlink_test_file(void)
{
	file_handle_unlink_handle_cl(&file,
				     &unexpected_fail_cl);
}

void test_flag_match(void)
{
	TEST_ASSERT_TRUE(flag_match("-h",
				    'h',
				    "help"));

	TEST_ASSERT_FALSE(flag_match("-h ",
				     'h',
				     "help"));

	TEST_ASSERT_TRUE(flag_match("--help",
				    'h',
				    "help"));

	TEST_ASSERT_FALSE(flag_match("--help ",
				     'h',
				     "help"));
}

void test_flag_count_until(void)
{
	char *test_input[10] = {
		"ooga",		/* bad */
		"-h",		/* good */
		"-h ",		/* bad  */
		"booga",	/* bad  */
		"--help",	/* good */
		"--help ",	/* bad */
		"-h",		/* good */
		"booga",	/* bad */
		"--help",	/* good */
		"-h"		/* good */
	};

	TEST_ASSERT_EQUAL_UINT(5lu,
			       flag_count_until(&test_input[0],
						&test_input[0] + 10l,
						'h',
						"help"));
}
