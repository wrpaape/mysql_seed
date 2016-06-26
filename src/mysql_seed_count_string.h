#ifndef MYSQL_SEED_MYSQL_SEED_COUNT_STRING_H_
#define MYSQL_SEED_MYSQL_SEED_COUNT_STRING_H_

#define DEFAULT_USER_COUNT 25000

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <stdlib.h>		/* malloc, free */
#include "mysql_seed_log.h"	/* seed_log, string utils */

#if (SIZE_MAX < UINT32_MAX)
#	define UPTO_MAX 9999lu
#	define MAG_UPTO_MAX 3u
#	define SIZE_UPTO_MAX_STR 5u
#	undef  LARGE_UPTO_MAX
#else
#	define UPTO_MAX 99999999lu
#	define MAG_UPTO_MAX 7u
#	define SIZE_UPTO_MAX_STR 9u
#	define LARGE_UPTO_MAX
#endif /* if (SIZE_MAX < UINT32_MAX) */



#define UPTO_MAX_EXCEEDED_FAILURE_MESSAGE "'UPTO_MAX' exceeded\n"
#define MALLOC_FAILURE_MESSAGE		  "malloc failure (out of memory)\n"

#define CS_ALLOC_FAILURE_MESSAGE_BEGIN				\
"failed to allocate count string memory for 'upto' of "

#define CS_ALLOC_FAILURE_MESSAGE_MIDDLE				\
" ('UPTO_MAX' = " EXPAND_STRINGIFY(UPTO_MAX) ")\nreason:\n\t"

/* struct declarations, typedefs
 *─────────────────────────────────────────────────────────────────────────── */

#ifdef LARGE_UPTO_MAX
typedef CharBuffer9 Mag7String;
typedef CharBuffer8 Mag6String;
typedef CharBuffer7 Mag5String;
typedef CharBuffer6 Mag4String;
#endif /* ifdef LARGE_UPTO_MAX */
typedef CharBuffer5 Mag3String;
typedef CharBuffer4 Mag2String;
typedef CharBuffer3 Mag1String;
typedef CharBuffer2 Mag0String;

union DigitsBuffer {
	char string[SIZE_UPTO_MAX_STR];
#ifdef LARGE_UPTO_MAX
	Mag7String mag_7;
	Mag6String mag_6;
	Mag5String mag_5;
	Mag4String mag_4;
#endif /* ifdef LARGE_UPTO_MAX */
	Mag3String mag_3;
	Mag2String mag_2;
	Mag1String mag_1;
	Mag0String mag_0;
};

union DigitsPointer {
	char *restrict string;
#ifdef LARGE_UPTO_MAX
	Mag7String *restrict mag_7;
	Mag6String *restrict mag_6;
	Mag5String *restrict mag_5;
	Mag4String *restrict mag_4;
#endif /* ifdef LARGE_UPTO_MAX */
	Mag3String *restrict mag_3;
	Mag2String *restrict mag_2;
	Mag1String *restrict mag_1;
	Mag0String *restrict mag_0;
};

struct CountStringSpec {
	unsigned int mag_upto;	/* ⌊ log₁₀(upto) ⌋ */
	size_t size_1_upto;	/* sizeof("1", "2", ... "upto") */
};

/* macro constants
 *─────────────────────────────────────────────────────────────────────────── */
#define MAG_0_MIN		1lu
#define MAG_1_MIN		10lu
#define MAG_2_MIN		100lu
#define MAG_3_MIN		1000lu
#define MAG_0_MAX		9lu
#define MAG_1_MAX		99lu
#define MAG_2_MAX		999lu
#define MAG_3_MAX		9999lu
#define OFF_LO_MAG_0		0l
#define OFF_LO_MAG_1		1l
#define OFF_LO_MAG_2		2l
#define OFF_LO_MAG_3		3l
#define SIZE_MAG_0_STR		2lu
#define SIZE_MAG_1_STR		3lu
#define SIZE_MAG_2_STR		4lu
#define SIZE_MAG_3_STR		5lu
#define MAG_0_MIN_STR		((Mag0String *restrict) "1")
#define MAG_1_MIN_STR		((Mag1String *restrict) "10")
#define MAG_2_MIN_STR		((Mag2String *restrict) "100")
#define MAG_3_MIN_STR		((Mag3String *restrict) "1000")
#define SIZE_MAG_0_0_STR	0lu	   /* empty */
#define SIZE_MAG_0_1_STR	18lu	   /* (1 digit  + '\0') * 9 */
#define SIZE_MAG_1_2_STR	270lu	   /* (2 digits + '\0') * 90 */
#define SIZE_MAG_2_3_STR	3600lu	   /* (3 digits + '\0') * 900 */
#define SIZE_MAG_0_2_STR	(SIZE_MAG_0_1_STR + SIZE_MAG_1_2_STR)
#define SIZE_MAG_0_3_STR	(SIZE_MAG_0_2_STR + SIZE_MAG_2_3_STR)
#ifdef LARGE_UPTO_MAX
#	define MAG_4_MIN	10000lu
#	define MAG_5_MIN	100000lu
#	define MAG_6_MIN	1000000lu
#	define MAG_7_MIN	10000000lu
#	define MAG_4_MAX	99999lu
#	define MAG_5_MAX	999999lu
#	define MAG_6_MAX	9999999lu
#	define MAG_7_MAX	99999999lu
#	define OFF_LO_MAG_4	4l
#	define OFF_LO_MAG_5	5l
#	define OFF_LO_MAG_6	6l
#	define OFF_LO_MAG_7	7l
#	define SIZE_MAG_4_STR	6lu
#	define SIZE_MAG_5_STR	7lu
#	define SIZE_MAG_6_STR	8lu
#	define SIZE_MAG_7_STR	9lu
#	define MAG_4_MIN_STR	((Mag4String *restrict) "10000")
#	define MAG_5_MIN_STR	((Mag5String *restrict) "100000")
#	define MAG_6_MIN_STR	((Mag6String *restrict) "1000000")
#	define MAG_7_MIN_STR	((Mag7String *restrict) "10000000")
#	define SIZE_MAG_3_4_STR	45000lu	   /* (3 digits + '\0') * 9000 */
#	define SIZE_MAG_4_5_STR	540000lu   /* (4 digits + '\0') * 90000 */
#	define SIZE_MAG_5_6_STR	6300000lu  /* (5 digits + '\0') * 900000 */
#	define SIZE_MAG_6_7_STR	72000000lu /* (6 digits + '\0') * 9000000 */
#	define SIZE_MAG_0_4_STR	(SIZE_MAG_0_3_STR + SIZE_MAG_3_4_STR)
#	define SIZE_MAG_0_5_STR	(SIZE_MAG_0_4_STR + SIZE_MAG_4_5_STR)
#	define SIZE_MAG_0_6_STR	(SIZE_MAG_0_5_STR + SIZE_MAG_5_6_STR)
#	define SIZE_MAG_0_7_STR	(SIZE_MAG_0_6_STR + SIZE_MAG_6_7_STR)
#endif	/*  ifdef LARGE_UPTO_MAX */


/* global variables
 *─────────────────────────────────────────────────────────────────────────── */
extern const Mag0String *const restrict mag_0_min_string;
extern const Mag1String *const restrict mag_1_min_string;
extern const Mag2String *const restrict mag_2_min_string;
extern const Mag3String *const restrict mag_3_min_string;
#ifdef LARGE_UPTO_MAX
extern const Mag4String *const restrict mag_4_min_string;
extern const Mag5String *const restrict mag_5_min_string;
extern const Mag6String *const restrict mag_6_min_string;
extern const Mag7String *const restrict mag_7_min_string;
#endif	/*  ifdef LARGE_UPTO_MAX */




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
				spec->mag_upto	  = 0u;
				spec->size_1_upto = SIZE_MAG_0_STR * upto;
			} else {
				spec->mag_upto	  = 1u;
				spec->size_1_upto = SIZE_MAG_0_1_STR
						  + (SIZE_MAG_1_STR
						     * (upto - MAG_0_MAX));
			}
		} else {
			if (upto < MAG_3_MIN) {
				spec->mag_upto	  = 2u;
				spec->size_1_upto = SIZE_MAG_0_2_STR
						  + (SIZE_MAG_2_STR
						     * (upto - MAG_1_MAX));
			} else {
				spec->mag_upto	  = 3u;
				spec->size_1_upto = SIZE_MAG_0_3_STR
						  + (SIZE_MAG_3_STR
						     * (upto - MAG_2_MAX));
			}
		}
#if (UPTO_MAX == 99999999lu)
	} else {
		if (upto < MAG_6_MIN) {
			if (upto < MAG_5_MIN) {
				spec->mag_upto	  = 4u;
				spec->size_1_upto = SIZE_MAG_0_4_STR
						  + (SIZE_MAG_4_STR
						     * (upto - MAG_3_MAX));
			} else {
				spec->mag_upto	  = 5u;
				spec->size_1_upto = SIZE_MAG_0_5_STR
						  + (SIZE_MAG_5_STR
						     * (upto - MAG_4_MAX));
			}
		} else {
			if (upto < MAG_7_MIN) {
				spec->mag_upto	  = 6u;
				spec->size_1_upto = SIZE_MAG_0_6_STR
						  + (SIZE_MAG_6_STR
						     * (upto - MAG_5_MAX));
			} else {
				spec->mag_upto	  = 7u;
				spec->size_1_upto = SIZE_MAG_0_7_STR
						  + (SIZE_MAG_7_STR
						     * (upto - MAG_6_MAX));
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
count_string_increment_buffer(char *restrict digit)
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
		  const unsigned int mag_upto,
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
			  spec.mag_upto,
			  upto);

	string[spec.size_1_upto] = '\0';

	return string;
}


#endif	/* MYSQL_SEED_MYSQL_SEED_COUNT_STRING_H_ */
