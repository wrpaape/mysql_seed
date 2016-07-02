#include "unity.h"
#include "string/string_utils.h"
#include <math.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_string_length(void)
{
	TEST_ASSERT_EQUAL_UINT(0lu, string_length(""));
	TEST_ASSERT_EQUAL_UINT(4lu, string_length("ooga"));

	TEST_ASSERT_EQUAL_INT(0l,   string_length_limit("", 0l));
	TEST_ASSERT_EQUAL_INT(0l,   string_length_limit("", 1l));
	TEST_ASSERT_EQUAL_INT(4l,   string_length_limit("ooga", 10l));

	TEST_ASSERT_TRUE(string_length_limit("",     -1l) < 0l);
	TEST_ASSERT_TRUE(string_length_limit("ooga", -1l) < 0l);
	TEST_ASSERT_TRUE(string_length_limit("ooga", -123l) < 0l);
}

void test_put_string(void)
{
	char buffer[10];
	char *ptr;

	ptr = put_string(&buffer[0],
			 "test");
	*ptr = '\0';

	TEST_ASSERT_EQUAL_STRING("test", &buffer[0]);


	ptr = put_string(&buffer[0], "one");
	ptr = put_string(ptr,	     " ");
	ptr = put_string(ptr,	     "two");

	*ptr = '\0';

	TEST_ASSERT_EQUAL_STRING("one two", &buffer[0]);


	ptr = put_string_length(&buffer[0],
				"123",
				5);
	*ptr = '\0';

	TEST_ASSERT_EQUAL_STRING("123", &buffer[0]);


	ptr = put_string_length(&buffer[0],
				"12345678910112",
				5);
	*ptr = '\0';

	TEST_ASSERT_EQUAL_STRING("12345", &buffer[0]);


	ptr = put_string_until(&buffer[0],
			       "12345",
			       &buffer[9]);
	*ptr = '\0';

	TEST_ASSERT_EQUAL_STRING("12345", &buffer[0]);

	TEST_ASSERT_EQUAL_PTR(&buffer[5], ptr);



	ptr = put_string_until(&buffer[0],
			       "12345678910112",
			       &buffer[9]);
	*ptr = '\0';

	TEST_ASSERT_EQUAL_STRING("123456789", &buffer[0]);

	TEST_ASSERT_EQUAL_PTR(&buffer[9], ptr);
}


#ifdef DIGIT_COUNT_MAX
void test_ten_pow_map(void)
{
	for (unsigned int i = 0u; i < DIGIT_COUNT_MAX; ++i)
		TEST_ASSERT_EQUAL_UINT((size_t) pow(10.0,
						    (double) i),
				       ten_pow_map[i]);
}

void test_digit_count(void)
{
	for (unsigned int i = 0u; i < DIGIT_COUNT_MAX; ++i)
		TEST_ASSERT_EQUAL_UINT(i + 1u,
				       digit_count(ten_pow_map[i]));
}
#endif	/* ifdef (DIGIT_COUNT_MAX) */

void test_put_number(void)
{
	char buffer[8];
	char *ptr;

	ptr = put_number(&buffer[0],
			 -1234);
	*ptr = '\0';

	TEST_ASSERT_EQUAL_STRING("-1234",
				 &buffer[0]);

	ptr = put_number(&buffer[0],
			 0);
	*ptr = '\0';

	TEST_ASSERT_EQUAL_STRING("0",
				 &buffer[0]);

	ptr = put_number(&buffer[0],
			 666);
	*ptr = '\0';

	TEST_ASSERT_EQUAL_STRING("666",
				 &buffer[0]);

	ptr = put_number_length(&buffer[0],
				12345,
				3);
	*ptr = '\0';

	TEST_ASSERT_EQUAL_STRING("123",
				 &buffer[0]);

	ptr = put_number_until(&buffer[0],
				-1234,
				&buffer[4]);
	*ptr = '\0';

	TEST_ASSERT_EQUAL_STRING("-123",
				 &buffer[0]);
}
