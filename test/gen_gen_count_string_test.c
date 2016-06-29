#include "unity.h"
#include "gen/gen_count_string.h"

void setUp(void)
{
}

void tearDown(void)
{
}

inline void
test_assert_size_fields_equal(struct CountString *const restrict string,
			      const unsigned int mag_upto_expected,
			      const size_t size_digits_expected)
{
	TEST_ASSERT_EQUAL_UINT_MESSAGE(mag_upto_expected,
				       string->mag_upto,
				       "string->mag_upto != mag_upto_expected");


	TEST_ASSERT_EQUAL_UINT_MESSAGE(size_digits_expected,
				       string->size_digits,
				       "string->size_digits != size_digits_expected");
}

void test_count_string_size_internals(void)
{
	struct CountString string;

	string.upto = 3lu;

	count_string_size_internals(&string);

	test_assert_size_fields_equal(&string,
				      0u,
				      sizeof("1") + sizeof("2") + sizeof("3"));
	string.upto = 25000lu;

	count_string_size_internals(&string);

	test_assert_size_fields_equal(&string,
				      4u,
				      SIZE_MAG_0_4_STR + (15001lu * 6lu));
}

void test_count_string_alloc_failure(void)
{
	char failure[128];

	struct CountString string;

	string.upto = UPTO_MAX + 1lu;

	count_string_init_internals(&string);

	TEST_ASSERT_NULL(string.pointers);

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

void test_count_string_increment_buffer(void)
{
	char digits[5] = "8998";

	count_buffer_increment(&digits[3]);

	TEST_ASSERT_EQUAL_STRING("8999",
				 &digits[0]);

	count_buffer_increment(&digits[3]);

	TEST_ASSERT_EQUAL_STRING("9000",
				 &digits[0]);
}

void test_count_string_set_internals(void)
{
	char *buffer[64];
	struct CountString string;

	string.upto	= 3lu;
	string.mag_upto	= 0u;
	string.pointers = &buffer[0];

	count_string_set_internals(&string);

	TEST_ASSERT_EQUAL_STRING("1", string.pointers[0]);

	TEST_ASSERT_EQUAL_STRING("2", string.pointers[1]);

	TEST_ASSERT_EQUAL_STRING("3", string.pointers[2]);
}

void test_assert_count_string_pointers(char **const restrict pointers,
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

void test_count_string_init(void)
{
	struct CountString string;

	count_string_init(&string,
			  150000lu);

	TEST_ASSERT_TRUE(string.incomplete);

	TEST_ASSERT_EQUAL_UINT(150000lu, string.upto);

	count_string_await(&string);

	TEST_ASSERT_FALSE(string.incomplete);

	test_assert_count_string_pointers(string.pointers,
					  string.upto);

	count_string_free_internals(&string);
}
