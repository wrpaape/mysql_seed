#include "mysql_seed_count_string.h"

extern inline void
count_string_spec_init(struct CountStringSpec *const restrict spec,
		       const size_t upto);

extern inline void
count_string_log_alloc_failure(const size_t upto,
			       const char *const restrict failure);

extern inline void
count_buffer_increment(char *restrict digit);

/* global variables
 *─────────────────────────────────────────────────────────────────────────── */
const Mag0String mag_0_min_string = { "1" };
const Mag1String mag_1_min_string = { "10" };
const Mag2String mag_2_min_string = { "100" };
const Mag3String mag_3_min_string = { "1000" };
#ifdef LARGE_UPTO_MAX
const Mag4String mag_4_min_string = { "10000" };
const Mag5String mag_5_min_string = { "100000" };
const Mag6String mag_6_min_string = { "1000000" };
const Mag7String mag_7_min_string = { "10000000" };
#endif	/*  ifdef LARGE_UPTO_MAX */

#define SET_RANGE_DIGITS_MAG_UPTO(MAG)					\
do {									\
	buffer.mag_ ## MAG = mag_ ## MAG ##_min_string;			\
	string_ptr.string  = string + SIZE_MAG_0_ ## MAG ## _STR;	\
	counter		   = MAG_ ## MAG ## _MIN;			\
	while (1) {							\
		*(string_ptr.mag_ ## MAG) = buffer.mag_ ## MAG;		\
		if (counter == upto)					\
			break;						\
		++counter;						\
		++(string_ptr.mag_ ## MAG);				\
		count_buffer_increment(active);				\
	}								\
} while (0)

void
count_string_init(char *const restrict string,
		  const unsigned int mag_upto,
		  size_t upto)
{
	union DigitsBuffer buffer;
	union DigitsPointer string_ptr;
	size_t counter;
	char *restrict active;

	active = &buffer.string[mag_upto]; /* point 'active' at one's digit */

	switch (mag_upto) {
#ifdef LARGE_UPTO_MAX
	case 7u:
		SET_RANGE_DIGITS_MAG_UPTO(7);
		--active;
		upto = MAG_6_MAX;
	case 6u:
		SET_RANGE_DIGITS_MAG_UPTO(6);
		--active;
		upto = MAG_5_MAX;
	case 5u:
		SET_RANGE_DIGITS_MAG_UPTO(5);
		--active;
		upto = MAG_4_MAX;
	case 4u:
		SET_RANGE_DIGITS_MAG_UPTO(4);
		--active;
		upto = MAG_3_MAX;
#endif /* ifdef LARGE_UPTO_MAX */
	case 3u:
		SET_RANGE_DIGITS_MAG_UPTO(3);
		--active;
		upto = MAG_2_MAX;
	case 2u:
		SET_RANGE_DIGITS_MAG_UPTO(2);
		--active;
		upto = MAG_1_MAX;
	case 1u:
		SET_RANGE_DIGITS_MAG_UPTO(1);
		--active;
		upto = MAG_0_MAX;
	default:
		SET_RANGE_DIGITS_MAG_UPTO(0);
	}
}

extern inline char *
count_string_create(const size_t upto);
