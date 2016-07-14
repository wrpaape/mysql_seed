#ifndef MYSQL_SEED_GENERATE_NAMES_H_
#define MYSQL_SEED_GENERATE_NAMES_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <stdint.h>			/* SIZE_MAX, UINT32_MAX */
#include "random/random.h"		/* urint_t, random_uint_upto */
#include "generate/generator.h"		/* string/parallelization utils */

#define FIRST_NAMES_COUNT 200lu
#define LAST_NAMES_COUNT  200lu
#define FIRST_NAMES_MAP_I_LAST 199l
#define LAST_NAMES_MAP_I_LAST  199l

#define FIRST_NAME_SIZE_MAX 12lu	/* 11 chars + '\0' */
#define LAST_NAME_SIZE_MAX  11lu	/* 10 chars + '\0' */
#define FULL_NAME_SIZE_MAX  (((FIRST_NAME_SIZE_MAX) * 2lu)	\
			     + LAST_NAME_SIZE_MAX		\
			     + 2lu)	/* 2 spaces */

#if (SIZE_MAX < UINT32_MAX)
#	define FIRST_NAMES_COUNT_MAX SIZE_MAX
#	define LAST_NAMES_COUNT_MAX  SIZE_MAX
#	define FULL_NAMES_COUNT_MAX  SIZE_MAX
#else
#	define FIRST_NAMES_COUNT_MAX 450000lu
#	define LAST_NAMES_COUNT_MAX  450000lu
#	define FULL_NAMES_COUNT_MAX  150000lu
#endif /* if (SIZE_MAX < UINT32_MAX) */


/* failure messages
 *─────────────────────────────────────────────────────────────────────────── */
#define FIRST_NCM_EXCEEDED_FAIL_MSG					\
FAILURE_REASON("last_names_column",					\
	       "'FIRST_NAMES_COUNT_MAX' ("				\
	       EXPAND_STRINGIFY(FIRST_NAMES_COUNT_MAX) ") exceeded\n")

#define LAST_NCM_EXCEEDED_FAIL_MSG					\
FAILURE_REASON("last_names_column",					\
	       "'LAST_NAMES_COUNT_MAX' ("				\
	       EXPAND_STRINGIFY(LAST_NAMES_COUNT_MAX) ") exceeded\n")

#define FULL_NCM_EXCEEDED_FAIL_MSG					\
FAILURE_REASON("full_names_column",					\
	       "'FULL_NAMES_COUNT_MAX' ("				\
	       EXPAND_STRINGIFY(FULL_NAMES_COUNT_MAX) ") exceeded\n")


/* enum, struct declarations
 *─────────────────────────────────────────────────────────────────────────── */
struct NameMap {
	const struct Label *names;
	const urint_t i_last;
};

/* global variables
 *─────────────────────────────────────────────────────────────────────────── */
extern const struct Label first_names[FIRST_NAMES_COUNT];
extern const struct Label last_names[LAST_NAMES_COUNT];

extern const struct NameMap first_name_map;
extern const struct NameMap last_name_map;

inline char *
put_random_initial(char *const restrict string)
{
	*string = (char) random_int_in_range((rint_t) 'A',
					     (rint_t) 'Z');
	return string + 1l;
}

inline const struct Label *
name_map_sample(const struct NameMap *const restrict map)
{
	return &map->names[ random_uint_upto(map->i_last) ];
}

inline size_t
single_names_init(char *restrict *const name_ptrs_base,
		  const struct NameMap *const restrict map,
		  size_t count)
{
	/* start 'names' after NULL terminator */
	char *const restrict *name_ptrs_end = name_ptrs_base + count;
	char *restrict *name_ptrs = name_ptrs_base;
	char *restrict names	  = (char *restrict) (name_ptrs_end + 1l);

	while (1) {
		*name_ptrs = names;

		names = put_label(names,
				  name_map_sample(map));
		*names = '\0';

		++name_ptrs;

		if (((void *) name_ptrs) == ((void *) name_ptrs_end)) {
			*name_ptrs = NULL;
			return ((void *) names) - ((void *) name_ptrs_base);
		}

		++names;
	}
}

inline size_t
full_names_init(char *restrict *const name_ptrs_base,
		size_t count)
{
	/* start 'names' after NULL terminator */
	char *const restrict *name_ptrs_end = name_ptrs_base + count;
	char *restrict *name_ptrs = name_ptrs_base;
	char *restrict names	  = (char *restrict) (name_ptrs_end + 1l);

	while (1) {
		*name_ptrs = names;

		names = put_label(names,
				  name_map_sample(&first_name_map));

		PUT_CHAR(names, ' ');

		if (coin_flip()) {
			names = coin_flip()
			      ? put_random_initial(names)
			      : put_label(names,
					  name_map_sample(&first_name_map));

			PUT_CHAR(names, ' ');
		}

		names = put_label(names,
				  name_map_sample(&last_name_map));

		*names = '\0';

		++name_ptrs;

		if (((void *) name_ptrs) == ((void *) name_ptrs_end)) {
			*name_ptrs = NULL;
			return ((void *) names) - ((void *) name_ptrs_base);
		}

		++names;
	}
}


inline char **
gen_first_names(const size_t count)
{
	if (count > FIRST_NAMES_COUNT_MAX) {
		gen_strings_log_alloc_failure(count,
					      0lu,
					      FIRST_NCM_EXCEEDED_FAIL_MSG);
		return NULL;
	}

	/* 'count' + 1 (NULL terminated) pointers + (max * count) chars */
	const size_t size_est  = (sizeof(char *) * (count + 1lu))
			       + (FIRST_NAMES_COUNT_MAX * count);

	char **const name_ptrs_base = malloc(size_est);

	if (name_ptrs_base == NULL) {
		gen_strings_log_alloc_failure(count,
					      size_est,
					      MALLOC_FAILURE_MESSAGE);
		return NULL;
	}

	const size_t size_act = single_names_init(name_ptrs_base,
						  &first_name_map,
						  count);

	char **const realloc_size_act = realloc(name_ptrs_base,
						size_act);

	if (realloc_size_act == NULL) {
		gen_strings_log_realloc_failure(count,
						size_est,
						size_act);
		return name_ptrs_base;
	}

	return realloc_size_act;
}


inline char **
gen_last_names(const size_t count)
{
	if (count > LAST_NAMES_COUNT_MAX) {
		gen_strings_log_alloc_failure(count,
					      0lu,
					      LAST_NCM_EXCEEDED_FAIL_MSG);
		return NULL;
	}

	/* 'count' + 1 (NULL terminated) pointers + (max * count) chars */
	const size_t size_est  = (sizeof(char *) * (count + 1lu))
			       + (LAST_NAMES_COUNT_MAX * count);

	char **const name_ptrs_base = malloc(size_est);

	if (name_ptrs_base == NULL) {
		gen_strings_log_alloc_failure(count,
					      size_est,
					      MALLOC_FAILURE_MESSAGE);
		return NULL;
	}

	const size_t size_act = single_names_init(name_ptrs_base,
						  &last_name_map,
						  count);

	char **const realloc_size_act = realloc(name_ptrs_base,
						size_act);

	if (realloc_size_act == NULL) {
		gen_strings_log_realloc_failure(count,
						size_est,
						size_act);
		return name_ptrs_base;
	}

	return realloc_size_act;
}


void
full_names_column(void *arg);


#endif	/* ifndef MYSQL_SEED_GENERATE_NAMES_H_ */