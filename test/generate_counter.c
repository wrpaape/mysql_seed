#include "unity.h"
#include "generate/counter.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void
test_counter_exit_on_failure(void *arg,
			     const char *restrict failure)
{
	write_muffle(STDERR_FILENO,
		     failure,
		     string_length(failure));

	TEST_FAIL();
	__builtin_unreachable();
}

inline void
test_assert_size_fields_equal(struct Counter *const restrict counter,
			      const unsigned int mag_upto_expected,
			      const size_t size_digits_expected)
{
	TEST_ASSERT_EQUAL_UINT_MESSAGE(mag_upto_expected,
				       counter->mag_upto,
				       "counter->mag_upto != mag_upto_expected");


	TEST_ASSERT_EQUAL_UINT_MESSAGE(size_digits_expected,
				       counter->size_digits,
				       "counter->size_digits != size_digits_expected");
}

void
test_counter_size_internals(void)
{
	struct Counter counter;

	counter.upto = 3lu;

	counter_size_internals(&counter);

	test_assert_size_fields_equal(&counter,
				      0u,
				      sizeof("1") + sizeof("2") + sizeof("3"));
	counter.upto = 25000lu;

	counter_size_internals(&counter);

	test_assert_size_fields_equal(&counter,
				      4u,
				      SIZE_MAG_0_4_STR + (15001lu * 6lu));
}

void
test_counter_alloc_failure(void)
{
	char failure[128];

	struct Counter counter;

	counter.upto = UPTO_MAX + 1lu;

	counter_init_internals(&counter);

	TEST_ASSERT_NULL(counter.pointers);

	sprintf(&failure[0],
		GCS_ALLOC_FAILURE_MESSAGE_1
		"%zu"
		GCS_ALLOC_FAILURE_MESSAGE_2
		UPTO_MAX_EXCEEDED_FAILURE_MESSAGE,
		UPTO_MAX + 1lu);

	TEST_ASSERT_EQUAL_STRING(&failure[0],
				 seed_log_buffer_ptr());

	seed_log_reset();
}

void test_counter_increment_buffer(void)
{
	char digits[5] = "8998";

	count_buffer_increment(&digits[3]);

	TEST_ASSERT_EQUAL_STRING("8999",
				 &digits[0]);

	count_buffer_increment(&digits[3]);

	TEST_ASSERT_EQUAL_STRING("9000",
				 &digits[0]);
}

void test_counter_set_internals(void)
{
	char *buffer[64];
	struct Counter counter;

	counter.upto	= 3lu;
	counter.mag_upto	= 0u;
	counter.pointers = &buffer[0];

	counter_set_internals(&counter);

	TEST_ASSERT_EQUAL_STRING("1", counter.pointers[0]);

	TEST_ASSERT_EQUAL_STRING("2", counter.pointers[1]);

	TEST_ASSERT_EQUAL_STRING("3", counter.pointers[2]);
}

void test_assert_counter_pointers(char **const restrict pointers,
				       const size_t upto)
{
	char buffer[16];

	TEST_ASSERT_NOT_NULL(pointers);

	for (unsigned int i = 0u, j = 1u; j < upto; i = j, ++j) {
		TEST_ASSERT_NOT_NULL(pointers[i]);
		sprintf(&buffer[0], "%u", j);
		TEST_ASSERT_EQUAL_STRING(&buffer[0], pointers[i]);
	}
}

void test_counter_init(void)
{
	struct Counter counter;

	counter_init(&counter,
		     150000lu);

	TEST_ASSERT_TRUE(counter.incomplete);

	TEST_ASSERT_EQUAL_UINT(150000lu, counter.upto);

	counter_await(&counter);

	TEST_ASSERT_FALSE(counter.incomplete);

	test_assert_counter_pointers(counter.pointers,
					  counter.upto);

	counter_free_internals(&counter);
}
