#include "unity.h"
#include "memory/memory_utils.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_pointer_offset(void)
{
	void *pointer;

	uint8_t string[] = "01234567";
	pointer = (void *) &string[0];

	TEST_ASSERT_EQUAL_INT8('0', *((uint8_t *) memory_offset(pointer, 0l)));
	TEST_ASSERT_EQUAL_INT8('1', *((uint8_t *) memory_offset(pointer, 1l)));
	TEST_ASSERT_EQUAL_INT8('5', *((uint8_t *) memory_offset(pointer, 5l)));
	TEST_ASSERT_EQUAL_INT8('7', *((uint8_t *) memory_offset(pointer, 7l)));


	double doubles[] = { 0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7 };
	pointer = (void *) &doubles[0];

	TEST_ASSERT_EQUAL_DOUBLE(0.0,
				 *((double *) memory_offset(pointer,
							    sizeof(double)
							    * 0l)));
	TEST_ASSERT_EQUAL_DOUBLE(1.1,
				 *((double *) memory_offset(pointer,
							    sizeof(double)
							    * 1l)));
	TEST_ASSERT_EQUAL_DOUBLE(5.5,
				 *((double *) memory_offset(pointer,
							    sizeof(double)
							    * 5l)));
	TEST_ASSERT_EQUAL_DOUBLE(7.7,
				 *((double *) memory_offset(pointer,
							    sizeof(double)
							    * 7l)));


	uint64_t hex = 0x7766554433221100;
	pointer = (void *) &hex;

	TEST_ASSERT_EQUAL_HEX8(0x00, *((uint8_t *) memory_offset(pointer, 0l)));
	TEST_ASSERT_EQUAL_HEX8(0x11, *((uint8_t *) memory_offset(pointer, 1l)));
	TEST_ASSERT_EQUAL_HEX8(0x55, *((uint8_t *) memory_offset(pointer, 5l)));
	TEST_ASSERT_EQUAL_HEX8(0x77, *((uint8_t *) memory_offset(pointer, 7l)));
}
