#include "unity.h"
#include "thread/thread_log.h"


void setUp(void)
{
}

void tearDown(void)
{
}


void handle_thread_log_failure(void *arg,
			       const char *restrict failure)
__attribute__((noreturn));

static const struct HandlerClosure handle_failure= {
	.handle = &handle_thread_log_failure,
	.arg	= NULL
};


void handle_thread_log_failure(void *arg,
			       const char *restrict failure)
{
	puts(failure);
	exit(EXIT_FAILURE);
	__builtin_unreachable();
}

void test_thread_log(void)
{
	struct ThreadLog log;

	thread_log_init(&log,
			"test log");

	thread_log_lock_handle_cl(&log,
				  &handle_failure);

	thread_log_append_string(&log,
				 "\nThis should appear in stdout.");

	thread_log_append_close(&log);

	thread_log_dump_handle_cl(&log,
				  STDOUT_FILENO,
				  &handle_failure);

	thread_log_unlock_handle_cl(&log,
				    &handle_failure);
}
