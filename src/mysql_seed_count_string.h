#ifndef MYSQL_SEED_MYSQL_SEED_COUNT_STRING_H_
#define MYSQL_SEED_MYSQL_SEED_COUNT_STRING_H_

#define DEFAULT_USER_COUNT 25000

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <stdlib.h>	/* malloc */


/* error flags
 *─────────────────────────────────────────────────────────────────────────── */
enum CountStringInitFlag {
	CSI_SUCCESS,
	CSI_FAILURE_UPTO_MAX_EXCEEDED,
	CSI_FAILURE_OUT_OF_MEMORY
};


/* parse stdin args
 *─────────────────────────────────────────────────────────────────────────── */
char **
count_string_create(const size_t upto);


/* misc helper functions
 *─────────────────────────────────────────────────────────────────────────── */
enum CountStringInitFlag
count_string_init(char *const *restrict *string_pointers,
		  char *const *restrict buffer,
		  const size_t upto);

#endif	/* MYSQL_SEED_MYSQL_SEED_COUNT_STRING_H_ */
