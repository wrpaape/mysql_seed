#include "unity.h"
#include "memory/memory_put_array.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_assign_memory_put_array(void)
{
	TEST_ASSERT_EQUAL_PTR(&memory_put_array0,
			      assign_memory_put_array(0lu));

	TEST_ASSERT_EQUAL_PTR(&memory_put_array1,
			      assign_memory_put_array(sizeof(Width1)));

	TEST_ASSERT_EQUAL_PTR(&memory_put_array2,
			      assign_memory_put_array(sizeof(Width2)));

	TEST_ASSERT_EQUAL_PTR(&memory_put_array3,
			      assign_memory_put_array(sizeof(Width3)));

	TEST_ASSERT_EQUAL_PTR(&memory_put_array4,
			      assign_memory_put_array(sizeof(Width4)));

	TEST_ASSERT_EQUAL_PTR(&memory_put_array5,
			      assign_memory_put_array(sizeof(Width5)));

	TEST_ASSERT_EQUAL_PTR(&memory_put_array6,
			      assign_memory_put_array(sizeof(Width6)));

	TEST_ASSERT_EQUAL_PTR(&memory_put_array7,
			      assign_memory_put_array(sizeof(Width7)));

	TEST_ASSERT_EQUAL_PTR(&memory_put_array8,
			      assign_memory_put_array(sizeof(Width8)));

	TEST_ASSERT_EQUAL_PTR(&memory_put_array9,
			      assign_memory_put_array(sizeof(Width9)));

	TEST_ASSERT_EQUAL_PTR(&memory_put_array10,
			      assign_memory_put_array(sizeof(Width10)));

	TEST_ASSERT_EQUAL_PTR(&memory_put_array11,
			      assign_memory_put_array(sizeof(Width11)));

	TEST_ASSERT_EQUAL_PTR(&memory_put_array12,
			      assign_memory_put_array(sizeof(Width12)));

	TEST_ASSERT_EQUAL_PTR(&memory_put_array13,
			      assign_memory_put_array(sizeof(Width13)));

	TEST_ASSERT_EQUAL_PTR(&memory_put_array14,
			      assign_memory_put_array(sizeof(Width14)));

	TEST_ASSERT_EQUAL_PTR(&memory_put_array15,
			      assign_memory_put_array(sizeof(Width15)));

	TEST_ASSERT_EQUAL_PTR(&memory_put_array16,
			      assign_memory_put_array(sizeof(Width16)));

	TEST_ASSERT_NULL(assign_memory_put_array(WIDTH_MAX_SIZE + 1ul));
}


void test_assign_memory_put_array_then_put_array(void)
{
	MemoryPutArray *put_array;
	void *end_ptr;

	char x_string[1000] = { [0 ... 999] = '\0' };
	char y_string[1000] = { [0 ... 998] = 'y', [999] = '\0' };

	put_array = assign_memory_put_array(sizeof(char));

	TEST_ASSERT_NOT_NULL(put_array);

	end_ptr = (*put_array)(&x_string[0], &y_string[0], 1000lu);

	TEST_ASSERT_EQUAL_STRING(&y_string[0], &x_string[0]);

	TEST_ASSERT_EQUAL_PTR(&x_string[1000], end_ptr);


	double zros[4] = {0.00l, 0.00l, 0.00l, 0.00l };
	double nums[4] = {-1e6l, 2e-7l, -3e8l, 4e-9l };

	put_array = assign_memory_put_array(sizeof(double));

	TEST_ASSERT_NOT_NULL(put_array);

	end_ptr = (*put_array)(&zros[0], &nums[0], 4lu);

	TEST_ASSERT_EQUAL_DOUBLE_ARRAY(&nums[0], &zros[0], 4lu);

	TEST_ASSERT_EQUAL_PTR(&zros[4], end_ptr);
}

void test_memory_put(void)
{
	char buffer[128];

	char *ptr;

	ptr = memory_put(&buffer[0],
			 "test",
			 sizeof("test"));

	TEST_ASSERT_EQUAL_STRING("test", &buffer[0]);

	--ptr;

	TEST_ASSERT_EQUAL('\0', *ptr);

	ptr = memory_put(&buffer[0],
			 "OOGA BOOGA",
			 sizeof("OOGA BOOGA"));

	TEST_ASSERT_EQUAL_STRING("OOGA BOOGA", &buffer[0]);

	--ptr;

	TEST_ASSERT_EQUAL('\0', *ptr);
}
