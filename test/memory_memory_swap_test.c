#include "unity.h"
#include "memory/memory_swap.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_VAR_SWAP(void)
{
	char *this = "this";
	char *that = "that";

	VAR_SWAP(this, that);

	TEST_ASSERT_EQUAL_STRING("this", that);
	TEST_ASSERT_EQUAL_STRING("that", this);

	VAR_SWAP(this, that);

	TEST_ASSERT_EQUAL_STRING("this", this);
	TEST_ASSERT_EQUAL_STRING("that", that);
}

void test_EL_SWAP_char(void)
{
	char array[] = "ooga";

	EL_SWAP(array, 1, 2);

	TEST_ASSERT_EQUAL_STRING("ogoa", &array[0]);

	EL_SWAP(array, 1, 2);

	TEST_ASSERT_EQUAL_STRING("ooga", &array[0]);
}

void test_EL_SWAP_int64(void)
{
	int64_t array[] = { 0, 1, 2, 3, 4, 5 };

	EL_SWAP(array, 0, 5);

	TEST_ASSERT_EQUAL_INT64(array[0], 5);
	TEST_ASSERT_EQUAL_INT64(array[5], 0);

	EL_SWAP(array, 0, 5);

	TEST_ASSERT_EQUAL_INT64(array[0], 0);
	TEST_ASSERT_EQUAL_INT64(array[5], 5);
}

void test_memory_swap_width_basic_primitive_types(void)
{
	char x = 'x';
	char y = 'y';

	memory_swap_width(&x, &y, sizeof(char));

	TEST_ASSERT_EQUAL(x, 'y');
	TEST_ASSERT_EQUAL(y, 'x');

	int threes = 333;
	int sevens = 777;

	memory_swap_width(&threes, &sevens, sizeof(int));

	TEST_ASSERT_EQUAL_INT(333, sevens);
	TEST_ASSERT_EQUAL_INT(777, threes);

	double pi = 3.141;
	double e  = 2.718;

	memory_swap_width(&pi, &e, sizeof(double));

	TEST_ASSERT_EQUAL_DOUBLE(2.718, pi);
	TEST_ASSERT_EQUAL_DOUBLE(3.141, e);
}


void test_memory_swap_string(void)
{
	char this[] = "_this_ is 'this'";
	char that[] = "_this_ is 'that'";

	memory_swap_width(&this[0], &that[0], sizeof(this));

	TEST_ASSERT_EQUAL_STRING("_this_ is 'that'", &this[0]);
	TEST_ASSERT_EQUAL_STRING("_this_ is 'this'", &that[0]);
}

void test_memory_swap_pointers(void)
{
	MemorySwap *this[3] = { &memory_swap1, &memory_swap2, &memory_swap3 };
	MemorySwap *that[3] = { &memory_swap3, &memory_swap2, &memory_swap1 };

	MemorySwap *this_copy[3];
	MemorySwap *that_copy[3];

	memcpy(&this_copy[0], &this[0], sizeof(MemorySwap *) * 3ul);
	memcpy(&that_copy[0], &that[0], sizeof(MemorySwap *) * 3ul);

	TEST_ASSERT_EQUAL_PTR_ARRAY_MESSAGE(&this[0], &this_copy[0], 3,
					    "bad memcpy");
	TEST_ASSERT_EQUAL_PTR_ARRAY_MESSAGE(&that[0], &that_copy[0], 3,
					    "bad memcpy");

	memory_swap_width(&this[0], &that[0], sizeof(MemorySwap *) * 3ul);

	TEST_ASSERT_EQUAL_PTR_ARRAY(&this_copy[0], &that[0], 3);
	TEST_ASSERT_EQUAL_PTR_ARRAY(&that_copy[0], &this[0], 3);
}


void test_assign_memory_swap(void)
{
	TEST_ASSERT_EQUAL_PTR(&memory_swap0,
			      assign_memory_swap(0lu));

	TEST_ASSERT_EQUAL_PTR(&memory_swap1,
			      assign_memory_swap(sizeof(Width1)));

	TEST_ASSERT_EQUAL_PTR(&memory_swap2,
			      assign_memory_swap(sizeof(Width2)));

	TEST_ASSERT_EQUAL_PTR(&memory_swap3,
			      assign_memory_swap(sizeof(Width3)));

	TEST_ASSERT_EQUAL_PTR(&memory_swap4,
			      assign_memory_swap(sizeof(Width4)));

	TEST_ASSERT_EQUAL_PTR(&memory_swap5,
			      assign_memory_swap(sizeof(Width5)));

	TEST_ASSERT_EQUAL_PTR(&memory_swap6,
			      assign_memory_swap(sizeof(Width6)));

	TEST_ASSERT_EQUAL_PTR(&memory_swap7,
			      assign_memory_swap(sizeof(Width7)));

	TEST_ASSERT_EQUAL_PTR(&memory_swap8,
			      assign_memory_swap(sizeof(Width8)));

	TEST_ASSERT_EQUAL_PTR(&memory_swap9,
			      assign_memory_swap(sizeof(Width9)));

	TEST_ASSERT_EQUAL_PTR(&memory_swap10,
			      assign_memory_swap(sizeof(Width10)));

	TEST_ASSERT_EQUAL_PTR(&memory_swap11,
			      assign_memory_swap(sizeof(Width11)));

	TEST_ASSERT_EQUAL_PTR(&memory_swap12,
			      assign_memory_swap(sizeof(Width12)));

	TEST_ASSERT_EQUAL_PTR(&memory_swap13,
			      assign_memory_swap(sizeof(Width13)));

	TEST_ASSERT_EQUAL_PTR(&memory_swap14,
			      assign_memory_swap(sizeof(Width14)));

	TEST_ASSERT_EQUAL_PTR(&memory_swap15,
			      assign_memory_swap(sizeof(Width15)));

	TEST_ASSERT_EQUAL_PTR(&memory_swap16,
			      assign_memory_swap(sizeof(Width16)));

	TEST_ASSERT_NULL(assign_memory_swap(WIDTH_MAX_SIZE + 1ul));
}

void test_assign_memory_swap_then_swap(void)
{
	MemorySwap *swap;

	char x = 'x';
	char y = 'y';

	swap = assign_memory_swap(sizeof(char));

	TEST_ASSERT_NOT_NULL(swap);

	(*swap)(&x, &y);

	TEST_ASSERT_EQUAL(x, 'y');
	TEST_ASSERT_EQUAL(y, 'x');

	short int a = 0xA;
	short int b = 0xB;

	swap = assign_memory_swap(sizeof(short int));

	TEST_ASSERT_NOT_NULL(swap);

	(*swap)(&a, &b);

	TEST_ASSERT_EQUAL_INT(a, 0xB);
	TEST_ASSERT_EQUAL_INT(b, 0xA);

	long double pi = 3.141592653589793l;
	long double e  = 2.718281828459045l;

	swap = assign_memory_swap(sizeof(long double));

	TEST_ASSERT_NOT_NULL(swap);

	(*swap)(&pi, &e);

	TEST_ASSERT_EQUAL_DOUBLE(2.718281828459045l, pi);
	TEST_ASSERT_EQUAL_DOUBLE(3.141592653589793l, e);
}
