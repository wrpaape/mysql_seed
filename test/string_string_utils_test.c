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


#if HAVE_INT_STRING_ATTRS
void test_ten_pow_map(void)
{
	for (unsigned int i = 0u; i < DIGIT_COUNT_UINTMAX_MAX; ++i)
		TEST_ASSERT_EQUAL_UINT((uintmax_t) pow(10.0,
						       (double) i),
				       ten_pow_map[i]);
}

void test_uint_digit_count(void)
{
	for (unsigned int i = 0u; i < DIGIT_COUNT_UINTMAX_MAX; ++i)
		TEST_ASSERT_EQUAL_UINT(i + 1u,
				       uint_digit_count(ten_pow_map[i]));
}
#endif	/* if HAVE_INT_STRING_ATTRS */

void test_put_int(void)
{
	char buffer[8];
	char *ptr;

	ptr = put_int(&buffer[0],
		      -1234);
	*ptr = '\0';

	TEST_ASSERT_EQUAL_STRING("-1234",
				 &buffer[0]);

	ptr = put_int(&buffer[0],
		      0);
	*ptr = '\0';

	TEST_ASSERT_EQUAL_STRING("0",
				 &buffer[0]);

	ptr = put_int(&buffer[0],
		      666);
	*ptr = '\0';

	TEST_ASSERT_EQUAL_STRING("666",
				 &buffer[0]);

	ptr = put_int_length(&buffer[0],
			     12345,
			     3);
	*ptr = '\0';

	TEST_ASSERT_EQUAL_STRING("123",
				 &buffer[0]);

	ptr = put_int_until(&buffer[0],
			    -1234,
			    &buffer[4]);
	*ptr = '\0';

	TEST_ASSERT_EQUAL_STRING("-123",
				 &buffer[0]);
}


void test_put_pointer_id(void)
{
	char buffer[32];

	char *ptr = put_pointer_id(&buffer[0],
				   &buffer);

	*ptr = '\0';

	TEST_ASSERT_TRUE(is_printable_ascii_string(&buffer[0]));


}

void test_parse_uint(void)
{
	uintmax_t n;

	TEST_ASSERT_NULL(parse_uint(&n, ""));

	TEST_ASSERT_NULL(parse_uint(&n, "12oogabooga34"));

	TEST_ASSERT_NOT_NULL(parse_uint(&n, "12345"));

	TEST_ASSERT_EQUAL_UINT(12345llu, n);

	TEST_ASSERT_NOT_NULL(parse_uint(&n, "00012"));

	TEST_ASSERT_EQUAL_UINT(12llu, n);

#if HAVE_INT_STRING_ATTRS

	TEST_ASSERT_NOT_NULL(parse_uint(&n, DIGIT_STRING_UINTMAX_MAX));

	TEST_ASSERT_EQUAL_UINT(UINTMAX_MAX, n);

	TEST_ASSERT_NULL(parse_uint(&n, DIGIT_STRING_UINTMAX_MAX "1"));

#endif /* if HAVE_INT_STRING_ATTRS */
}


void test_parse_int(void)
{
	intmax_t n;

	TEST_ASSERT_NULL(parse_int(&n, ""));

	TEST_ASSERT_NULL(parse_int(&n, "12oogabooga34"));

	TEST_ASSERT_NOT_NULL(parse_int(&n, "12345"));

	TEST_ASSERT_EQUAL_INT(12345ll, n);

	TEST_ASSERT_NOT_NULL(parse_int(&n, "-12345"));

	TEST_ASSERT_EQUAL_INT(-12345ll, n);

	TEST_ASSERT_NOT_NULL(parse_int(&n, "-00012"));

	TEST_ASSERT_EQUAL_INT(-12ll, n);

#if HAVE_INT_STRING_ATTRS

	TEST_ASSERT_NOT_NULL(parse_int(&n, DIGIT_STRING_INTMAX_MAX));

	TEST_ASSERT_EQUAL_INT(INTMAX_MAX, n);

	TEST_ASSERT_NULL(parse_int(&n, DIGIT_STRING_INTMAX_MIN));

	TEST_ASSERT_NOT_NULL(parse_int(&n, "-" DIGIT_STRING_INTMAX_MIN));

	TEST_ASSERT_EQUAL_INT(INTMAX_MIN, n);

#endif /* if HAVE_INT_STRING_ATTRS */
}

void
test_parse_uint_stop(void)
{

	uintmax_t n;

	char buffer[] = "123!:45";

	TEST_ASSERT_NULL(parse_uint_stop(&n, &buffer[0], ':'));

	char *ptr = parse_uint_stop(&n, &buffer[0], '!');

	TEST_ASSERT_NOT_NULL(ptr);

	TEST_ASSERT_EQUAL_UINT(123llu, n);

	TEST_ASSERT_EQUAL_PTR(ptr, &buffer[3]);
}

void
test_parse_int_stop(void)
{

	intmax_t n;

	char buffer[] = "-123!:45";

	TEST_ASSERT_NULL(parse_int_stop(&n, &buffer[0], ':'));

	char *ptr = parse_int_stop(&n, &buffer[0], '!');

	TEST_ASSERT_NOT_NULL(ptr);

	TEST_ASSERT_EQUAL_INT(-123ll, n);

	TEST_ASSERT_EQUAL_PTR(ptr, &buffer[4]);
}
