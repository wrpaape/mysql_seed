#include "mysql_seed_count_string.h"

extern inline void
count_string_spec_init(struct CountStringSpec *const restrict spec,
		       const size_t upto);

extern inline void
count_string_log_alloc_failure(const size_t upto,
			       const char *const restrict failure);

extern inline void
count_string_update_buffer(char *restrict digit);

count_string_init(char *const restrict string,
		  const struct CountStringSpec *const restrict spec,
		  size_t upto)
{
	union DigitsBuffer buffer;
	union DigitsBuffer *const restrict buffer_ptr = &buffer;
	union DigitsPointer string_ptr;
	char *restrict active;
	size_t counter;

	buffer	       = *(spec->base_string);

	switch (spec->mag_upto) {
#if (UPTO_MAX_DIGIT_COUNT == 8u)
	case 7u:
		*(buffer_ptr.string) = MAG_7_MIN_STR
		string_ptr.string = string + SIZE_1_
		active	       = string_ptr.string + 7l;
		counter	       = MAG_7_MIN;

		while (1) {
			*(string_ptr.mag_7) = buffer.mag_7;

			++(string_ptr.mag_7);

			if (counter == upto)
				break;

			++counter;

			count_string_update_buffer(active);
		}

		counter = BASE_MAG_6;
		upto	= BASE_MAG_7 - 1lu;

	case 6u:
	case 5u:
	case 4u:
#endif /* if (UPTO_MAX_DIGIT_COUNT == 8u) */
	case 3u:
	case 2u:
	case 1u:
	default:
		/* string[spec->size_1_upto] = '\0'; */
		return;
	}
}

extern inline char *
count_string_create(const size_t upto);
