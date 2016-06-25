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
#else
#	define UPTO_MAX 99999999lu
#	define UPTO_MAX_DIGIT_COUNT 8u
#endif /* if (SIZE_MAX < UINT32_MAX) */

#define SIZE_1_9		18lu	   /* (1 digit  + '\0') * 9 */
#define SIZE_10_99		270lu	   /* (2 digits + '\0') * 90 */
#define SIZE_100_999		3600lu	   /* (3 digits + '\0') * 900 */
#define SIZE_1_99		(SIZE_1_9	+ SIZE_10_99)
#define SIZE_1_999		(SIZE_1_99	+ SIZE_100_999)

#if (UPTO_MAX == 99999999lu)
#define SIZE_1000_9999		45000lu	   /* (3 digits + '\0') * 9000 */
#define SIZE_10000_99999	540000lu   /* (4 digits + '\0') * 90000 */
#define SIZE_100000_999999	6300000lu  /* (5 digits + '\0') * 900000 */
#define SIZE_1000000_9999999	72000000lu /* (6 digits + '\0') * 9000000 */
#define SIZE_1_9999		(SIZE_1_999	+ SIZE_1000_9999)
#define SIZE_1_99999		(SIZE_1_9999	+ SIZE_10000_99999)
#define SIZE_1_999999		(SIZE_1_99999	+ SIZE_100000_999999)
#define SIZE_1_9999999		(SIZE_1_999999	+ SIZE_1000000_9999999)
#endif	/*  if (UPTO_MAX >= 9999999lu) */





/* misc helper functions
 *─────────────────────────────────────────────────────────────────────────── */
/* count of decimal digits of 'n' when '0 <= n <= UPTO_MAX' */
inline unsigned int
count_string_digit_count(const size_t n)
{
#if (UPTO_MAX == 99999999lu)
	if (n < 10000lu) {
#endif	/*  if (UPTO_MAX == 9999999lu) */
		if (n < 100lu) {
			return (n < 10lu)	? 1u : 2u;
		} else {
			return (n < 1000lu)	? 3u : 4u;
		}
#if (UPTO_MAX == 99999999lu)
	} else {
		if (n < 1000000lu) {
			return (n < 100000lu)   ? 5u : 6u;
		} else {
			return (n < 10000000lu) ? 7u : 8u;
		}
	}
#endif	/*  if (UPTO_MAX == 9999999lu) */
}

/* count of chars required for "1", "2", ... "upto" null-terminated ascii
 * strings plus a final '\0' character to indicate end */
inline size_t
count_string_char_count(const size_t upto)
{
#if (UPTO_MAX == 99999999lu)
	if (upto < 10000lu) {
#endif	/*  if (UPTO_MAX == 9999999lu) */
		if (upto < 100lu) {
			return (upto < 10lu)
			     ? (upto * 2lu) + 1lu
			     : (upto * 3lu) + 1lu + SIZE_1_9;
		} else {
			return (upto < 1000lu)
			     ? (upto * 4lu) + 1lu + SIZE_1_99
			     : (upto * 5lu) + 1lu + SIZE_1_999;
		}
#if (UPTO_MAX == 99999999lu)
	} else {
		if (upto < 1000000lu) {
			return (upto < 100000lu)
			     ? (upto * 6lu) + 1lu + SIZE_1_9999
			     : (upto * 7lu) + 1lu + SIZE_1_99999;
		} else {
			return (upto < 10000000lu)
			     ? (upto * 8lu) + 1lu + SIZE_1_999999
			     : (upto * 9lu) + 1lu + SIZE_1_9999999;
		}
	}
#endif	/*  if (UPTO_MAX == 9999999lu) */
}



/* allocates space for ascending string of strings of ascii numbers, 'string' */
inline enum CountStringAllocStatus
count_string_alloc(char *restrict *const restrict string,
		      const size_t upto)
{
	if (upto > UPTO_MAX)
		return CSA_FAILURE_UPTO_MAX_EXCEEDED;


	return ((*string) == NULL)
	     ? CSA_FAILURE_OUT_OF_MEMORY
	     : CSA_SUCCESS;
}

inline void
count_string_log_alloc_failure(const size_t upto,
			       const char *const restrict failure)
{

	seed_log_handle_lock();

	seed_log_append_string("failed to allocate count string memory for "
			       "'upto' of ");

	seed_log_append_digits(upto);

	seed_log_append_string(" ('UPTO_MAX' = " EXPAND_STRINGIFY(UPTO_MAX)
			       ")\n"
			       "reason:\n\t");

	seed_log_append_string(failure);

	seed_log_handle_unlock();
}

inline char *
count_string_put_digits(char *restrict ptr,
			size_t upto);
{
	*ptr = '\0';
	--ptr;

	switch (count_string_digit_count(upto)) {
#if (UPTO_MAX_DIGIT_COUNT == 8u)
	case 8u:
	case 7u:
	case 6u:
	case 5u:
#endif /* if (UPTO_MAX_DIGIT_COUNT == 8u) */
	case 4u:
	case 3u:
	case 2u:
	case 1u:
	default:
	}
}


/* top-level functions
 *─────────────────────────────────────────────────────────────────────────── */
inline char *
count_string_create(const size_t upto)
{
	if (upto > UPTO_MAX) {
		count_string_log_alloc_failure("'UPTO_MAX' exceeded\n")
		return NULL;
	}

	char *const restrict string = malloc(sizeof(char)
					     * count_string_char_count(upto));


	if (string == NULL) {
		count_string_log_alloc_failure("malloc failure (out of memory)\n")
		return NULL;
	}

	const enum CountStringAllocStatus status = count_string_alloc(&string,
								      upto);
	if (csa_status != CSA_SUCCESS) {
		log_csa_failure(status,
				upto);
		return NULL;
	}

	return count_string_put_digits(string,
				       upto);
}


#endif	/* MYSQL_SEED_MYSQL_SEED_COUNT_STRING_H_ */
