#include "unity.h"
#include "thread/thread_pool.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void thread_pool_handle_failure(void *arg,
				const char *restrict failure)
__attribute__((noreturn));

void thread_pool_handle_failure(void *arg,
				const char *restrict failure)
{
	printf("test_thread_pool failure on %s:\n%s",
	       (const char *const restrict) arg,
	       failure);

	TEST_FAIL();
	__builtin_unreachable();
}

void set_integer(void *arg)
{
	int *const restrict integer = (int *const restrict) arg;

	*integer = 123;
}

void set_double(void *arg)
{
	double *const restrict dbl = (double *const restrict) arg;

	*dbl = 3.141;
}

void set_string(void *arg)
{
	const char *restrict *const restrict
	string = (const char *restrict *const restrict) arg;

	*string = "tastyham";
}

void divide_by_zero(void *arg)
{
	const intptr_t zero = (const intptr_t) arg;

	printf("2 / %zd = %zd\n", zero, 2 / zero);
}

void test_thread_pool(void)
{
	int one_two_three;
	double qtpi;
	const char *restrict tastyham;

	const struct ProcedureClosure tasks[4] = {
		{ .fun = &set_integer,	   .arg = (void *) &one_two_three },
		{ .fun = &set_double,	   .arg = (void *) &qtpi },
		{ .fun = &set_string,	   .arg = (void *) &tastyham },
		{ .fun = &divide_by_zero,  .arg = (void *) 0 },
	};

	struct HandlerClosure fail_cl = {
		.handle = &thread_pool_handle_failure,
		.arg	= "first test - creation"
	};

	struct ThreadPool *const restrict pool = thread_pool_create(&tasks[0],
								    3lu,
								    0lu,
								    3lu,
								    &fail_cl);

	fail_cl.arg = "first test - start up";

	thread_pool_start(pool,
			  &fail_cl);

	fail_cl.arg = "first test - awaiting tasks";

	thread_pool_await(pool,
			  &fail_cl);

	fail_cl.arg = "first test - shutdown";

	thread_pool_stop(pool,
			 &fail_cl);

	thread_pool_destroy(pool);

	TEST_ASSERT_EQUAL_INT(123,	  one_two_three);

	TEST_ASSERT_EQUAL_INT(3.141,	  qtpi);

	TEST_ASSERT_EQUAL_INT("tastyham", tastyham);
}
