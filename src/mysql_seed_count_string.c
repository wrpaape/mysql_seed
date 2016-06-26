#include "mysql_seed_count_string.h"

extern inline void
count_string_spec_init(struct CountStringSpec *const restrict spec,
		       const size_t upto);

extern inline void
count_string_log_alloc_failure(const size_t upto,
			       const char *const restrict failure);

extern inline void
count_string_increment_buffer(char *restrict digit);

/* global variables
 *─────────────────────────────────────────────────────────────────────────── */
const Mag0String *const restrict mag_0_min_string = (Mag0String *) "1";
const Mag1String *const restrict mag_1_min_string = (Mag1String *) "10";
const Mag2String *const restrict mag_2_min_string = (Mag2String *) "100";
const Mag3String *const restrict mag_3_min_string = (Mag3String *) "1000";
#ifdef LARGE_UPTO_MAX
const Mag4String *const restrict mag_4_min_string = (Mag4String *) "10000";
const Mag5String *const restrict mag_5_min_string = (Mag5String *) "100000";
const Mag6String *const restrict mag_6_min_string = (Mag6String *) "1000000";
const Mag7String *const restrict mag_7_min_string = (Mag7String *) "10000000";
#endif	/*  ifdef LARGE_UPTO_MAX */

#define SET_RANGE_DIGITS_MAG_UPTO(MAG_UPTO)				\
do {									\
	buffer.mag_ ## MAG_UPTO = *(mag_ ## MAG_UPTO ##_min_string);	\
	string_ptr.string = string					\
			  + SIZE_MAG_0_ ## MAG_UPTO ## _STR;		\
	active		  = string_ptr.string				\
			  + OFF_LO_MAG_ ## MAG_UPTO;			\
	counter		  = MAG_ ## MAG_UPTO ## _MIN;			\
	while (1) {							\
		*(string_ptr.mag_					\
		  ## MAG_UPTO) = buffer.mag_ ## MAG_UPTO;		\
		++(string_ptr.mag_ ## MAG_UPTO);			\
		if (counter == upto)					\
			break;						\
		++counter;						\
		count_string_increment_buffer(active);			\
	}								\
} while (0)

void
count_string_init(char *const restrict string,
		  const unsigned int mag_upto,
		  size_t upto)
{
	union DigitsBuffer buffer;
	union DigitsPointer string_ptr;
	char *restrict active;
	size_t counter;


	switch (mag_upto) {
#ifdef LARGE_UPTO_MAX
	case 7u:
		SET_RANGE_DIGITS_MAG_UPTO(7);
		upto = MAG_6_MAX;
	case 6u:
		SET_RANGE_DIGITS_MAG_UPTO(6);
		upto = MAG_5_MAX;
	case 5u:
		SET_RANGE_DIGITS_MAG_UPTO(5);
		upto = MAG_4_MAX;
	case 4u:
		SET_RANGE_DIGITS_MAG_UPTO(4);
		upto = MAG_3_MAX;
#endif /* ifdef LARGE_UPTO_MAX */
	case 3u:
		SET_RANGE_DIGITS_MAG_UPTO(3);
		upto = MAG_2_MAX;
	case 2u:
		SET_RANGE_DIGITS_MAG_UPTO(2);
		upto = MAG_1_MAX;
	case 1u:
		SET_RANGE_DIGITS_MAG_UPTO(1);
		upto = MAG_0_MAX;
	default:
		SET_RANGE_DIGITS_MAG_UPTO(0);
	}
}

extern inline char *
count_string_create(const size_t upto);
