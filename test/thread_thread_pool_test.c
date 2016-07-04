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
	printf("failure in %s:\n%s",
	       (const char *const restrict) arg,
	       failure);

	TEST_FAIL();

/* 	exit(EXIT_FAILURE); */

	__builtin_unreachable();
}

void test_thread_pool_init(void)
{
	const struct HandlerClosure fail_cl = {
		.handle = &thread_pool_handle_failure,
		.arg	= "test_thread_pool_init"
	};

	struct ThreadPool *const restrict pool = thread_pool_create(25lu,
								    &fail_cl);

	thread_pool_destroy(pool);
}
