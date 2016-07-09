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

	*integer = 123;
}

void set_four_five_six(void *arg)
{
	int *const restrict integer = (int *const restrict) arg;

	*integer = 456;
}

void set_pi(void *arg)
{
	double *const restrict dbl = (double *const restrict) arg;

	*dbl = 3.141;
}

void set_three_fifty(void *arg)
{
	double *const restrict dbl = (double *const restrict) arg;

	*dbl = 3.50;
}

void set_ooga_booga(void *arg)
{
	const char *restrict *const restrict
	string = (const char *restrict *const restrict) arg;

	*string = "ooga_booga";
}

void set_tastyham(void *arg)
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

	struct HandlerClosure fail_cl = {
		.handle = &thread_pool_handle_failure,
		.arg	= "first test - creation"
	};

	struct ThreadPool *const restrict pool = thread_pool_create(task_ptr,
								    3lu,
								    5lu,
								    12lu,
								    &fail_cl);

	fail_cl.arg = "first test - start up";

	thread_pool_start(pool,
			  &fail_cl);

	fail_cl.arg = "first test - pushing 4th task";

	task_ptr += 3lu;

	thread_pool_push_task(pool,
			      task_ptr,
			      &fail_cl);

	fail_cl.arg = "first test - awaiting first 4 tasks";


	thread_pool_await(pool,
			  &fail_cl);

	TEST_ASSERT_EQUAL_INT(123,	       one_two_three);
	TEST_ASSERT_EQUAL_DOUBLE(3.141,	       qtpi);
	TEST_ASSERT_EQUAL_STRING("ooga_booga", ooga_booga);
	TEST_ASSERT_EQUAL_INT(456,	       four_five_six);


	fail_cl.arg = "first test - pushing 5th task, task queue is saturated";

	++task_ptr;
	thread_pool_push_task(pool,
			      task_ptr,
			      &fail_cl);

	fail_cl.arg = "first test - awaiting 5th task";

	thread_pool_await(pool,
			  &fail_cl);

	TEST_ASSERT_EQUAL_DOUBLE(3.50,         tree_fitty);

	fail_cl.arg = "first test - reset task queue to make room last task";

	thread_pool_clear_completed(pool,
				    &fail_cl);

	fail_cl.arg = "first test - pushing 6th task";

	++task_ptr;
	thread_pool_push_task(pool,
			      task_ptr,
			      &fail_cl);

	fail_cl.arg = "first test - awaiting 6th task";

	thread_pool_await(pool,
			  &fail_cl);

	TEST_ASSERT_EQUAL_STRING("tastyham",   tastyham);


	fail_cl.arg = "first test - shutdown";

	thread_pool_stop(pool,
			 &fail_cl);

	TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS,
			      thread_pool_exit_status(pool,
						      &fail_cl));

	/* fail_cl.arg = "first test - exit on failure"; */

	/* thread_pool_exit_on_failure(pool, */
	/* 			    "OOGA BOOGA"); */

	/* TEST_ASSERT_EQUAL_INT(EXIT_FAILURE, */
	/* 		      thread_pool_exit_status(pool, */
						      /* &fail_cl)); */

	thread_pool_destroy(pool);
}
