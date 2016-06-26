#ifndef MYSQL_SEED_MYSQL_SEED_COUNT_STRING_H_
#define MYSQL_SEED_MYSQL_SEED_COUNT_STRING_H_

#define DEFAULT_USER_COUNT 25000

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <stdlib.h>		/* malloc, free */
#include "mysql_seed_log.h"	/* seed_log, string utils */

#if (SIZE_MAX < UINT32_MAX)
#	define UPTO_MAX 9999lu
#	define UPTO_MAX_DIGIT_COUNT 4u
#	define MAG_NULL_PAD
#else
#	define UPTO_MAX 99999999lu
#	define UPTO_MAX_DIGIT_COUNT 8u
#	define MAG_NULL_PAD "\0\0\0\0"
#endif /* if (SIZE_MAX < UINT32_MAX) */

#define MAG_0_MIN		1lu
#define MAG_1_MIN		10lu
#define MAG_2_MIN		100lu
#define MAG_3_MIN		1000lu
#define MAG_0_MAX		9lu
#define MAG_1_MAX		99lu
#define MAG_2_MAX		999lu
#define MAG_3_MAX		9999lu
#define MAG_0_MIN_STR		"1\0\0\0"	MAG_NULL_PAD
#define MAG_1_MIN_STR		"10\0\0"	MAG_NULL_PAD
#define MAG_2_MIN_STR		"100\0"		MAG_NULL_PAD
#define MAG_3_MIN_STR		"1000"		MAG_NULL_PAD
#define SIZE_MAG_0_0		0lu	   /* empty */
#define SIZE_MAG_0_1		18lu	   /* (1 digit  + '\0') * 9 */
#define SIZE_MAG_1_2		270lu	   /* (2 digits + '\0') * 90 */
#define SIZE_MAG_2_3		3600lu	   /* (3 digits + '\0') * 900 */
#define SIZE_MAG_0_2		(SIZE_MAG_0_1	+ SIZE_MAG_1_2)
#define SIZE_MAG_0_3		(SIZE_MAG_0_2	+ SIZE_MAG_2_3)

#if (UPTO_MAX == 99999999lu)
#	define MAG_4_MIN	10000lu
#	define MAG_5_MIN	100000lu
#	define MAG_6_MIN	1000000lu
#	define MAG_7_MIN	10000000lu
#	define MAG_4_MAX	99999lu
#	define MAG_5_MAX	999999lu
#	define MAG_6_MAX	9999999lu
#	define MAG_7_MAX	99999999lu
#	define MAG_4_MIN_STR	"10000\0\0\0"
#	define MAG_5_MIN_STR	"100000\0\0"
#	define MAG_6_MIN_STR	"1000000\0"
#	define MAG_7_MIN_STR	"10000000"
#	define SIZE_MAG_3_4	45000lu	   /* (3 digits + '\0') * 9000 */
#	define SIZE_MAG_4_5	540000lu   /* (4 digits + '\0') * 90000 */
#	define SIZE_MAG_5_6	6300000lu  /* (5 digits + '\0') * 900000 */
#	define SIZE_MAG_6_7	72000000lu /* (6 digits + '\0') * 9000000 */
#	define SIZE_MAG_0_4	(SIZE_MAG_0_3	+ SIZE_MAG_3_4)
#	define SIZE_MAG_0_5	(SIZE_MAG_0_4	+ SIZE_MAG_4_5)
#	define SIZE_MAG_0_6	(SIZE_MAG_0_5	+ SIZE_MAG_5_6)
#	define SIZE_MAG_0_7	(SIZE_MAG_0_6	+ SIZE_MAG_6_7)
#endif	/*  if (UPTO_MAX >= 9999999lu) */



#define UPTO_MAX_EXCEEDED_FAILURE_MESSAGE "'UPTO_MAX' exceeded\n"
#define MALLOC_FAILURE_MESSAGE		  "malloc failure (out of memory)\n"

#define CS_ALLOC_FAILURE_MESSAGE_BEGIN				\
"failed to allocate count string memory for 'upto' of "

#define CS_ALLOC_FAILURE_MESSAGE_MIDDLE				\
" ('UPTO_MAX' = " EXPAND_STRINGIFY(UPTO_MAX) ")\nreason:\n\t"

/* struct declarations, typedefs
 *─────────────────────────────────────────────────────────────────────────── */
union DigitsBuffer {
	char string[UPTO_MAX_DIGIT_COUNT + 1u];
#if (UPTO_MAX_DIGIT_COUNT == 8u)
	CharBuff9 mag_7;
	CharBuff8 mag_6;
	CharBuff7 mag_5;
	CharBuff6 mag_4;
#endif /* if (UPTO_MAX_DIGIT_COUNT == 8u) */
	CharBuff5 mag_3;
	CharBuff4 mag_2;
	CharBuff3 mag_1;
	CharBuff2 mag_0;
};

union DigitsPointer {
	char *restrict string;
#if (UPTO_MAX_DIGIT_COUNT == 8u)
	CharBuff9 *restrict mag_7;
	CharBuff8 *restrict mag_6;
	CharBuff7 *restrict mag_5;
	CharBuff6 *restrict mag_4;
#endif /* if (UPTO_MAX_DIGIT_COUNT == 8u) */
	CharBuff5 *restrict mag_3;
	CharBuff4 *restrict mag_2;
	CharBuff3 *restrict mag_1;
	CharBuff2 *restrict mag_0;
};

struct CountStringSpec {
	unsigned int mag_upto;	/* ⌊ log₁₀(upto) ⌋ */
	size_t size_1_upto;	/* sizeof("1", "2", ... "upto") */
};




/* misc helper functions
 *─────────────────────────────────────────────────────────────────────────── */
/* count of chars required for "1", "2", ... "upto" null-terminated ascii
 * strings plus a final '\0' character to indicate end */
inline void
count_string_spec_init(struct CountStringSpec *const restrict spec,
		       const size_t upto)
{
#if (UPTO_MAX == 99999999lu)
	if (upto < MAG_4_MIN) {
#endif	/*  if (UPTO_MAX == 9999999lu) */
		if (upto < MAG_2_MIN) {
			if (upto < MAG_1_MIN) {
				spec->mag_upto	      = 0u;
				spec->base_mag	      = MAG_0_MIN;
				spec->size_until_base = SIZE_MAG_0_0;
				spec->size_1_upto  = upto * 2lu;
				spec->base_string     = (const union
							 DigitsBuffer *restrict)
						        MAG_0_MIN_STR;
			} else {
				spec->mag_upto	      = 1u;
				spec->base_mag	      = MAG_1_MIN;
				spec->size_until_base = SIZE_MAG_0_1;
				spec->size_1_upto  = SIZE_MAG_0_1
						      + ((upto - MAG_0_MAX)
							 * 3lu);
				spec->base_string     = (const union
							 DigitsBuffer *restrict)
						        MAG_1_MIN_STR;
			}
		} else {
			if (upto < MAG_3_MIN) {
				spec->mag_upto	      = 2u;
				spec->base_mag	      = MAG_2_MIN;
				spec->size_until_base = SIZE_MAG_0_2;
				spec->size_1_upto  = SIZE_MAG_0_2
						      + ((upto - MAG_1_MAX)
							 * 4lu);
						      + (4lu
							 * (upto - 99lu));
				spec->base_string     = (const union
							 DigitsBuffer *restrict)
						        MAG_2_MIN_STR;
			} else {
				spec->mag_upto	      = 3u;
				spec->base_mag	      = MAG_3_MIN;
				spec->size_until_base = SIZE_MAG_0_3;
				spec->size_1_upto  = SIZE_MAG_0_3
						      + (5lu
							 * (upto - MAG_2_MAX));
				spec->base_string     = (const union
							 DigitsBuffer *restrict)
						        MAG_3_MIN_STR;
			}
		}
#if (UPTO_MAX == 99999999lu)
	} else {
		if (upto < MAG_6_MIN) {
			if (upto < MAG_5_MIN) {
				spec->mag_upto	      = 4u;
				spec->base_mag	      = MAG_4_MIN;
				spec->size_until_base = SIZE_MAG_0_4;
				spec->size_1_upto  = SIZE_MAG_0_4
						      + (6lu
							 * (upto - 9999lu));
				spec->base_string     = (const union
							 DigitsBuffer *restrict)
						        MAG_4_MIN_STR;
			} else {
				spec->mag_upto	      = 5u;
				spec->base_mag	      = MAG_5_MIN;
				spec->size_until_base = SIZE_MAG_0_5;
				spec->size_1_upto  = SIZE_MAG_0_5
						      + (7lu
							 * (upto - 99999lu));
				spec->base_string     = (const union
							 DigitsBuffer *restrict)
						        MAG_5_MIN_STR;
			}
		} else {
			if (upto < MAG_7_MIN) {
				spec->mag_upto	      = 6u;
				spec->base_mag	      = MAG_6_MIN;
				spec->size_until_base = SIZE_MAG_0_6;
				spec->size_1_upto  = SIZE_MAG_0_6
						      + (8lu
							 * (upto - 999999lu));
				spec->base_string     = (const union
							 DigitsBuffer *restrict)
						        MAG_6_MIN_STR;
			} else {
				spec->mag_upto	      = 7u;
				spec->base_mag	      = MAG_7_MIN;
				spec->size_until_base = SIZE_MAG_0_7;
				spec->size_1_upto  = SIZE_MAG_0_7
						      + (9lu
							 * (upto - 9999999lu));
				spec->base_string     = (const union
							 DigitsBuffer *restrict)
						        MAG_7_MIN_STR;
			}
		}
	}
#endif	/*  if (UPTO_MAX == 9999999lu) */
}



inline void
count_string_log_alloc_failure(const size_t upto,
			       const char *const restrict failure)
{

	seed_log_handle_lock();

	seed_log_append_string(CS_ALLOC_FAILURE_MESSAGE_BEGIN);

	seed_log_append_digits(upto);

	seed_log_append_string(CS_ALLOC_FAILURE_MESSAGE_MIDDLE);

	seed_log_append_string(failure);

	seed_log_handle_unlock();
}

inline void
count_string_update_buffer(char *restrict digit)
{
	while (1) {
		++(*digit);

		if ((*digit) < ':') /* digit is in '0' ... '9' */
			return;

		*digit = '0';

		--digit;
	}
}

void
count_string_init(char *const restrict string,
		  const struct CountStringSpec *const restrict spec,
		  size_t upto);


/* top-level functions
 *─────────────────────────────────────────────────────────────────────────── */
inline char *
count_string_create(const size_t upto)
{
	if (upto > UPTO_MAX) {
		count_string_log_alloc_failure(upto,
					       UPTO_MAX_EXCEEDED_FAILURE_MESSAGE);
		return NULL;
	}

	struct CountStringSpec spec;

	count_string_spec_init(&spec,
			       upto);

	/* + 1 for final null byte */
	char *const restrict string = malloc(spec.size_1_upto + 1lu);


	if (string == NULL) {
		count_string_log_alloc_failure(upto,
					       MALLOC_FAILURE_MESSAGE);
		return NULL;
	}

	count_string_init(string,
			  &spec,
			  upto);

	return string;
}


#endif	/* MYSQL_SEED_MYSQL_SEED_COUNT_STRING_H_ */
