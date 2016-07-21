#include "unity.h"
#include "memory/memory_copy_array.h"

void copyUp(void)
{
}

void tearDown(void)
{
}

void test_assign_memory_copy_array(void)
{
	TEST_ASSERT_EQUAL_PTR(&memory_copy_array0,
			      assign_memory_copy_array(0lu));

	TEST_ASSERT_EQUAL_PTR(&memory_copy_array1,
			      assign_memory_copy_array(sizeof(Width1)));

	TEST_ASSERT_EQUAL_PTR(&memory_copy_array2,
			      assign_memory_copy_array(sizeof(Width2)));

	TEST_ASSERT_EQUAL_PTR(&memory_copy_array3,
			      assign_memory_copy_array(sizeof(Width3)));

	TEST_ASSERT_EQUAL_PTR(&memory_copy_array4,
			      assign_memory_copy_array(sizeof(Width4)));

	TEST_ASSERT_EQUAL_PTR(&memory_copy_array5,
			      assign_memory_copy_array(sizeof(Width5)));

	TEST_ASSERT_EQUAL_PTR(&memory_copy_array6,
			      assign_memory_copy_array(sizeof(Width6)));

	TEST_ASSERT_EQUAL_PTR(&memory_copy_array7,
			      assign_memory_copy_array(sizeof(Width7)));

	TEST_ASSERT_EQUAL_PTR(&memory_copy_array8,
			      assign_memory_copy_array(sizeof(Width8)));

	TEST_ASSERT_EQUAL_PTR(&memory_copy_array9,
			      assign_memory_copy_array(sizeof(Width9)));

	TEST_ASSERT_EQUAL_PTR(&memory_copy_array10,
			      assign_memory_copy_array(sizeof(Width10)));

	TEST_ASSERT_EQUAL_PTR(&memory_copy_array11,
			      assign_memory_copy_array(sizeof(Width11)));

	TEST_ASSERT_EQUAL_PTR(&memory_copy_array12,
			      assign_memory_copy_array(sizeof(Width12)));

	TEST_ASSERT_EQUAL_PTR(&memory_copy_array13,
			      assign_memory_copy_array(sizeof(Width13)));

	TEST_ASSERT_EQUAL_PTR(&memory_copy_array14,
			      assign_memory_copy_array(sizeof(Width14)));

	TEST_ASSERT_EQUAL_PTR(&memory_copy_array15,
			      assign_memory_copy_array(sizeof(Width15)));

	TEST_ASSERT_EQUAL_PTR(&memory_copy_array16,
			      assign_memory_copy_array(sizeof(Width16)));

	TEST_ASSERT_NULL(assign_memory_copy_array(WIDTH_MAX_SIZE + 1ul));
}


void test_assign_memory_copy_array_then_copy_array(void)
{
	MemoryCopyArray *copy_array;

	char x_string[1000] = { [0 ... 999] = '\0' };
	char y_string[1000] = { [0 ... 998] = 'y', [999] = '\0' };

	copy_array = assign_memory_copy_array(sizeof(char));

	TEST_ASSERT_NOT_NULL(copy_array);

	(*copy_array)(&x_string[0], &y_string[0], 1000lu);

	TEST_ASSERT_EQUAL_STRING(&y_string[0], &x_string[0]);


	double zros[4] = {0.00l, 0.00l, 0.00l, 0.00l };
	double nums[4] = {-1e6l, 2e-7l, -3e8l, 4e-9l };

	copy_array = assign_memory_copy_array(sizeof(double));

	TEST_ASSERT_NOT_NULL(copy_array);

	(*copy_array)(&zros[0], &nums[0], 4lu);

	TEST_ASSERT_EQUAL_DOUBLE_ARRAY(&nums[0], &zros[0], 4lu);
}

void test_memory_copy(void)
{
	char buffer[128];
	memory_copy(&buffer[0],
		    "test",
		    sizeof("test"));

	TEST_ASSERT_EQUAL_STRING("test", &buffer[0]);

	memory_copy(&buffer[0],
		    "OOGA BOOGA",
		    sizeof("OOGA BOOGA"));

	TEST_ASSERT_EQUAL_STRING("OOGA BOOGA", &buffer[0]);
}
