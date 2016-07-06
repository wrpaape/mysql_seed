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

void set_one_two_three(void *arg)
{
	int *const restrict integer = (int *const restrict) arg;

	printf("in set_one_two_three (%p)\n", (void *) thread_self());

	*integer = 123;

	printf("integer = %d\n", *integer);
}

void set_four_five_six(void *arg)
{
	int *const restrict integer = (int *const restrict) arg;

	printf("in set_four_five_six (%p)\n", (void *) thread_self());
	*integer = 456;
}

void set_pi(void *arg)
{
	double *const restrict dbl = (double *const restrict) arg;

	printf("in set_pi (%p)\n", (void *) thread_self());

	*dbl = 3.141;
}
void set_three_fifty(void *arg)
{
	double *const restrict dbl = (double *const restrict) arg;

	printf("in set_three_fifty (%p)\n", (void *) thread_self());
	*dbl = 3.50;
}

void set_ooga_booga(void *arg)
{
	const char *restrict *const restrict
	string = (const char *restrict *const restrict) arg;

	printf("in set_ooga_booga (%p)\n", (void *) thread_self());

	*string = "ooga_booga";
}

void set_tastyham(void *arg)
{
	const char *restrict *const restrict
	string = (const char *restrict *const restrict) arg;

	printf("in set_tastyham (%p)\n", (void *) thread_self());

	*string = "tastyham";
}


void divide_by_zero(void *arg)
{
	const intptr_t zero = (const intptr_t) arg;

	printf("2 / %zd = %zd\n", zero, 2 / zero);
}

void test_thread_pool(void)
{
	int one_two_three, four_five_six;
	double qtpi, tree_fitty;
	const char *restrict tastyham;
	const char *restrict ooga_booga;

	const struct ProcedureClosure tasks[] = {
		{ .fun = &set_one_two_three, .arg = (void *) &one_two_three },
		{ .fun = &set_pi,	     .arg = (void *) &qtpi },
		{ .fun = &set_ooga_booga,    .arg = (void *) &ooga_booga },
		{ .fun = &set_four_five_six, .arg = (void *) &four_five_six },
		{ .fun = &set_three_fifty,   .arg = (void *) &tree_fitty },
		{ .fun = &set_tastyham,	     .arg = (void *) &tastyham }
	};

	const struct ProcedureClosure *restrict task_ptr       = &tasks[0];
	const struct ProcedureClosure *const restrict last_ptr = &tasks[5];

	struct HandlerClosure fail_cl = {
		.handle = &thread_pool_handle_failure,
		.arg	= "first test - creation"
	};

	struct ThreadPool *const restrict pool = thread_pool_create(NULL,
								    0lu,
								    6lu,
								    4lu,
								    &fail_cl);

	fail_cl.arg = "first test - start up";

	thread_pool_start(pool,
			  &fail_cl);

	fail_cl.arg = "first test - pushing first task";

	thread_pool_push_task(pool,
			      task_ptr,
			      &fail_cl);

	fail_cl.arg = "first test - awaiting first task";


	thread_pool_await(pool,
			  &fail_cl);

	TEST_ASSERT_EQUAL_INT(123, one_two_three);


	fail_cl.arg = "first test - pushing remaining tasks";

	do {
		++task_ptr;
		thread_pool_push_task(pool,
				      task_ptr,
				      &fail_cl);

	} while (task_ptr < last_ptr);


	fail_cl.arg = "first test - awaiting remaining tasks";

	thread_pool_await(pool,
			  &fail_cl);

	TEST_ASSERT_EQUAL_DOUBLE(3.141,	       qtpi);
	TEST_ASSERT_EQUAL_STRING("ooga_booga", ooga_booga);
	TEST_ASSERT_EQUAL_INT(456,	       four_five_six);
	TEST_ASSERT_EQUAL_DOUBLE(3.50,         tree_fitty);
	TEST_ASSERT_EQUAL_STRING("tastyham",   tastyham);


	fail_cl.arg = "first test - shutdown";

	thread_pool_stop(pool,
			 &fail_cl);

	thread_pool_destroy(pool);

	/* thread_pool_reset_task_queue(pool, */
	/* 			     &fail_cl); */
}
