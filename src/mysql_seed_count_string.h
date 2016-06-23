#ifndef MYSQL_SEED_MYSQL_SEED_COUNT_STRING_H_
#define MYSQL_SEED_MYSQL_SEED_COUNT_STRING_H_

#define DEFAULT_USER_COUNT 25000

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "mysql_seed_log.h"	/* seed_log, string utils */

/* error flags
 *─────────────────────────────────────────────────────────────────────────── */
enum CountStringAllocateFlag {
	CSA_SUCCESS,
	CSA_FAILURE_UPTO_MAX_EXCEEDED,
	CSA_FAILURE_OUT_OF_MEMORY
};


/* top-level functions
 *─────────────────────────────────────────────────────────────────────────── */
char **
count_string_create(const size_t upto);

inline void
count_string_destroy(char *restrict *string)
{
	free(string);
}


/* misc helper functions
 *─────────────────────────────────────────────────────────────────────────── */
void
log_csa_failure(const enum CountStringAllocateFlag status,
		const size_t upto);

enum CountStringAllocateFlag
count_string_allocate(char *const *restrict *string_pointers,
		      char *const *restrict digits,
		      const size_t upto);

#endif	/* MYSQL_SEED_MYSQL_SEED_COUNT_STRING_H_ */
