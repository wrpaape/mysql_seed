#include "unity.h"
#include "gen/gen_names.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_gen_first_names(void)
{
	for (char **names = gen_full_names(10lu); (*names) != NULL; ++names)
		puts(*names);
}
