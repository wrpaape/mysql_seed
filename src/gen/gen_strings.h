#ifndef MYSQL_SEED_GEN_GEN_STRINGS_H_
#define MYSQL_SEED_GEN_GEN_STRINGS_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <stdlib.h>		/* malloc, free */
#include "mysql_seed_log.h"	/* seed_log, seed_parallel, string utils */


/* failure messages
 *─────────────────────────────────────────────────────────────────────────── */
#define MALLOC_FAILURE_MESSAGE						\
"malloc failure (out of memory)\n"

#define GS_ALLOC_FAILURE_MESSAGE_1					\
"\n\nfailed to allocate string memory for 'count' of "

#define GS_ALLOC_FAILURE_MESSAGE_2					\
" and an estimated size of "

#define GS_ALLOC_FAILURE_MESSAGE_3					\
" bytes\nreason:\n\t"

#define GS_REALLOC_FAILURE_MESSAGE_1					\
"failed to reallocate string memory for 'count' of "

#define GS_REALLOC_FAILURE_MESSAGE_2					\
" from an estimated size of "

#define GS_REALLOC_FAILURE_MESSAGE_3					\
" bytes to an actual size of "

#define GS_REALLOC_FAILURE_MESSAGE_4					\
" bytes\n"


inline void
gen_strings_log_alloc_failure(const size_t count,
			      const size_t size_est,
			      const char *const restrict failure)
{
	seed_log_handle_lock();

	seed_log_append_string(GS_ALLOC_FAILURE_MESSAGE_1);

	seed_log_append_digits(count);

	seed_log_append_string(GS_ALLOC_FAILURE_MESSAGE_2);

	seed_log_append_digits(size_est);

	seed_log_append_string(GS_ALLOC_FAILURE_MESSAGE_3);

	seed_log_append_string(failure);

	seed_log_handle_unlock();
}

inline void
gen_strings_log_realloc_failure(const size_t count,
				const size_t size_est,
				const size_t size_act)
{
	seed_log_handle_lock();

	seed_log_append_string(GS_REALLOC_FAILURE_MESSAGE_1);

	seed_log_append_digits(count);

	seed_log_append_string(GS_REALLOC_FAILURE_MESSAGE_2);

	seed_log_append_digits(size_est);

	seed_log_append_string(GS_REALLOC_FAILURE_MESSAGE_3);

	seed_log_append_digits(size_act);

	seed_log_append_string(GS_REALLOC_FAILURE_MESSAGE_4);

	seed_log_handle_unlock();
}

#endif	/* ifndef MYSQL_SEED_GEN_GEN_STRINGS_H_ */
