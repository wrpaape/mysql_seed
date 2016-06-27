#ifndef MYSQL_SEED_GENERATE_GENERATE_STRING_H_
#define MYSQL_SEED_GENERATE_GENERATE_STRING_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "generate/name_map.h"		/* NameMap, random/random */
#include "mysql_seed_count_string.h"	/* count string, utils, log */


/* failure messages
 *─────────────────────────────────────────────────────────────────────────── */
#define FIRST_NCM_EXCEEDED_FAIL_MSG			\
"'FIRST_NAMES_COUNT_MAX' (" EXPAND_STRINGIFY(FIRST_NAMES_COUNT_MAX)	\
") exceeded\n"

#define LAST_NCM_EXCEEDED_FAIL_MSG			\
"'LAST_NAMES_COUNT_MAX' (" EXPAND_STRINGIFY(LAST_NAMES_COUNT_MAX)	\
") exceeded\n"

#define FULL_NCM_EXCEEDED_FAIL_MSG			\
"'FULL_NAMES_COUNT_MAX' (" EXPAND_STRINGIFY(FULL_NAMES_COUNT_MAX)	\
") exceeded\n"

#define GS_ALLOC_FAILURE_MESSAGE_BEGIN					\
"failed to allocate string memory for 'count' of "

#define GS_ALLOC_FAILURE_MESSAGE_MIDDLE_1				\
" and an estimated size of "

#define GS_ALLOC_FAILURE_MESSAGE_MIDDLE_2				\
" bytes\nreason:\n\t"

#define GS_REALLOC_FAILURE_MESSAGE_BEGIN				\
"failed to reallocate string memory for 'count' of "

#define GS_REALLOC_FAILURE_MESSAGE_MIDDLE_1				\
" from an estimated size of "

#define GS_REALLOC_FAILURE_MESSAGE_MIDDLE_2				\
" bytes to an actual size of "

#define GS_REALLOC_FAILURE_MESSAGE_END					\
" bytes"





inline void
generate_string_log_alloc_failure(const size_t count,
				  const size_t size_est,
				  const char *const restrict failure)
{
	seed_log_handle_lock();

	seed_log_append_string(GS_ALLOC_FAILURE_MESSAGE_BEGIN);

	seed_log_append_digits(count);

	seed_log_append_string(GS_ALLOC_FAILURE_MESSAGE_MIDDLE_1);

	seed_log_append_digits(size_est);

	seed_log_append_string(GS_ALLOC_FAILURE_MESSAGE_MIDDLE_2);

	seed_log_append_string(failure);

	seed_log_handle_unlock();
}

inline void
generate_string_log_realloc_failure(const size_t count,
				    const size_t size_est,
				    const size_t size_act)
{
	seed_log_handle_lock();

	seed_log_append_string(GS_REALLOC_FAILURE_MESSAGE_BEGIN);

	seed_log_append_digits(count);

	seed_log_append_string(GS_REALLOC_FAILURE_MESSAGE_MIDDLE_1);

	seed_log_append_digits(size_est);

	seed_log_append_string(GS_REALLOC_FAILURE_MESSAGE_MIDDLE_2);

	seed_log_append_digits(size_act);

	seed_log_append_string(GS_REALLOC_FAILURE_MESSAGE_END);

	seed_log_handle_unlock();
}

inline size_t
single_names_init(char *restrict *const name_ptrs_base,
		  const struct NameMap *const restrict map,
		  size_t count)
{
	/* start 'names' after NULL terminator */
	char *const restrict names_base = (char *restrict) (name_ptrs_base
							    + count);
	char *restrict *name_ptrs = name_ptrs_base;
	char *restrict names	  = names_base;

	while (1) {
		*name_ptrs = names;

		names = put_string(names,
				   name_map_sample(map));
		*names = '\0';

		++name_ptrs;

		if (((void *) name_ptrs) == ((void *) names_base)) {
			*name_ptrs = NULL;
			return ((void *) names) - ((void *) name_ptrs_base);
		}

		++names;
	}
}


inline char **
generate_first_names(const size_t count)
{
	if (count > FIRST_NAMES_COUNT_MAX) {
		generate_string_log_alloc_failure(count,
						  0lu
						  FIRST_NCM_EXCEEDED_FAIL_MSG);
		return NULL;
	}

	/* 'count' + 1 (NULL terminated) pointers + (max * count) chars */
	const size_t size_est  = (sizeof(char *) * (count + 1lu))
			       + (FIRST_NAMES_COUNT_MAX * count);

	char **const name_ptrs_base = malloc(size_est);

	if (name_ptrs_base == NULL) {
		generate_string_log_alloc_failure(count,
						  size_est,
						  MALLOC_FAILURE_MESSAGE);
		return NULL;
	}

	const size_t size_act = single_names_init(name_ptrs_base,
						  &first_name_map[0],
						  FIRST_NAMES_COUNT

						 count);

	const **const realloc_size_act = realloc(&name_ptrs_base,
						 size_act);

	if (realloc_size_act == NULL) {
		generate_string_log_realloc_failure(count,
						    size_est,
						    size_act);
		return name_ptrs_base;
	}

	return realloc_size_act;

}

#endif	/* MYSQL_SEED_GENERATE_GENERATE_STRING_H_
