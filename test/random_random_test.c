#include "unity.h"
#include "random/random.h"
#include <string.h>

__typeof__(glob_rng32) unset_glob_rng32;

void setUp(void)
{
}

void tearDown(void)
{
}

void test_glob_rng_ctor(void)
{
	TEST_ASSERT_NOT_EQUAL(0,
			      memcmp(&glob_rng32,
				     &unset_glob_rng32,
				     sizeof(glob_rng32)));
}

