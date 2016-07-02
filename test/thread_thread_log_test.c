#include "unity.h"
#include "thread/thread_log.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_thread_log(void)
{
	struct ThreadLog log;

	thread_log_init(&log,
			"supervisor");

	puts(&log.buffer[0]);
}
