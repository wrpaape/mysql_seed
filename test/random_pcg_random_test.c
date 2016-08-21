#include "unity.h"
#include "random/pcg_random.h"
#include <time.h>

#define RAND_TRIALS 10000u

void setUp(void)
{
}

void tearDown(void)
{
}

void test_random_pcg32_random_r(void)
{
	pcg32_random_t rng;

	time_t now;

	TEST_ASSERT_NOT_EQUAL((time_t) -1,
			      time(&now));

	const uint64_t seed = (uintptr_t) &now;

	pcg32_srandom_r(&rng,
			&seed);

	uint32_t random;

	unsigned int count_q0 = 0u;
	unsigned int count_q1 = 0u;
	unsigned int count_q2 = 0u;
	unsigned int count_q3 = 0u;

	for (unsigned int i = 0u; i < RAND_TRIALS; ++i) {

		random = pcg32_random_r(&rng);

		if (random < (UINT32_MAX / 2llu)) {
			if (random < (UINT32_MAX / 4llu))
				++count_q0;
			else
				++count_q1;
		} else {
			if (random < ((UINT32_MAX / 4llu) * 3llu))
				++count_q2;
			else
				++count_q3;
		}
	}

	printf("pcg32_random_r results:\n"
	       "\tq0: %u\n"
	       "\tq1: %u\n"
	       "\tq2: %u\n"
	       "\tq3: %u\n",
	       count_q0,
	       count_q1,
	       count_q2,
	       count_q3);
}


void test_random_pcg64_random_r(void)
{
	pcg64_random_t rng;

	time_t now;

	TEST_ASSERT_NOT_EQUAL((time_t) -1,
			      time(&now));

	const uint128_t seed = UINT128_INITIALIZER(now,
						   (uintptr_t) &now);

	pcg64_srandom_r(&rng,
			&seed);

	uint64_t random;

	unsigned int count_q0 = 0u;
	unsigned int count_q1 = 0u;
	unsigned int count_q2 = 0u;
	unsigned int count_q3 = 0u;

	for (unsigned int i = 0u; i < RAND_TRIALS; ++i) {

		random = pcg64_random_r(&rng);

		if (random < (UINT64_MAX / 2llu)) {
			if (random < (UINT64_MAX / 4llu))
				++count_q0;
			else
				++count_q1;
		} else {
			if (random < ((UINT64_MAX / 4llu) * 3llu))
				++count_q2;
			else
				++count_q3;
		}
	}

	printf("pcg64_random_r results:\n"
	       "\tq0: %u\n"
	       "\tq1: %u\n"
	       "\tq2: %u\n"
	       "\tq3: %u\n",
	       count_q0,
	       count_q1,
	       count_q2,
	       count_q3);
}
