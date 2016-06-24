#ifndef MYSQL_SEED_MYSQL_SEED_COUNT_STRING_H_
#define MYSQL_SEED_MYSQL_SEED_COUNT_STRING_H_

#define DEFAULT_USER_COUNT 25000

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <stdlib.h>		/* malloc, free */
#include "mysql_seed_log.h"	/* seed_log, string utils */

#if (SIZE_MAX >= 99999999llu)
#	define UPTO_MAX 99999999lu
#else
#	define UPTO_MAX SIZE_MAX
#endif /* if (SIZE_MAX >= 99999999llu) */

#define SIZE_1_9		18lu		/* (1 digit  + '\0') * 9 */
#define SIZE_10_99		270lu		/* (2 digits + '\0') * 90 */
#define SIZE_100_999		3600lu		/* (3 digits + '\0') * 900 */
#define SIZE_1000_9999		45000lu		/* (3 digits + '\0') * 9000 */
#define SIZE_1_99	(SIZE_1_9	+ SIZE_10_99)
#define SIZE_1_999	(SIZE_1_99	+ SIZE_100_999)
#define SIZE_1_9999	(SIZE_1_999	+ SIZE_1000_9999)

#if (UPTO_MAX >= 99999999lu)
#define SIZE_10000_99999	540000lu	/* (4 digits + '\0') * 90000 */
#define SIZE_100000_999999	6300000lu	/* (5 digits + '\0') * 900000 */
#define SIZE_1000000_9999999	72000000lu	/* (6 digits + '\0') * 9000000 */
#define SIZE_1_99999	(SIZE_1_9999	+ SIZE_10000_99999)
#define SIZE_1_999999	(SIZE_1_99999	+ SIZE_100000_999999)
#define SIZE_1_9999999	(SIZE_1_999999	+ SIZE_1000000_9999999)
#endif	/*  if (UPTO_MAX >= 9999999lu) */



/* declarations
 *─────────────────────────────────────────────────────────────────────────── */
enum CountStringAllocateFlag {
	CSA_SUCCESS,
	CSA_FAILURE_UPTO_MAX_EXCEEDED,
	CSA_FAILURE_OUT_OF_MEMORY
};

struct CountString {
	char *restrict digits;
	size_t size_digits;
	size_t upto;
};


/* misc helper functions
 *─────────────────────────────────────────────────────────────────────────── */
inline size_t
count_string_char_count(const size_t upto)
{
	if (upto < 10000lu) {
		if (upto < 100lu) {
			count_chars = (upto < 10lu)
				    ? (upto * 2lu)
				    : (upto * 3lu) + SIZE_1_9;
		} else {
			count_chars = (upto < 1000lu)
				    ? (upto * 4lu) + SIZE_1_99
				    : (upto * 5lu) + SIZE_1_999;
		}
	} else {
		if (upto < 1000000lu) {
			count_chars = (upto < 100000lu)
				    ? (upto * 6lu) + SIZE_1_9999
				    : (upto * 7lu) + SIZE_1_99999;
		} else {
			count_chars = (upto < 10000000lu)
				    ? (upto * 8lu) + SIZE_1_999999
				    : (upto * 9lu) + SIZE_1_9999999;
		}
	}
}


void
log_csa_failure(const enum CountStringAllocateFlag status,
		const size_t upto);

enum CountStringAllocateFlag
count_string_allocate(struct CountString *const *restrict string,
		      const size_t upto);



/* top-level functions
 *─────────────────────────────────────────────────────────────────────────── */
struct CountString *
count_string_create(const size_t upto);

inline void
count_string_destroy(struct CountString *restrict string)
{
	free(string);
}


#endif	/* MYSQL_SEED_MYSQL_SEED_COUNT_STRING_H_ */
