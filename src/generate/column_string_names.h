#ifndef MYSQL_SEED_GENERATE_COLUMN_STRING_NAMES_H_
#define MYSQL_SEED_GENERATE_COLUMN_STRING_NAMES_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <stdint.h>			/* SIZE_MAX, UINT32_MAX */
#include "random/random.h"		/* urint_t, random_uint_upto */
#include "generate/generator.h"		/* string/parallelization utils */

/* macro constants
 *─────────────────────────────────────────────────────────────────────────── */
#define FIRST_NAMES_COUNT 200lu
#define LAST_NAMES_COUNT  200lu
#define FIRST_NAMES_MAP_I_LAST 199l
#define LAST_NAMES_MAP_I_LAST  199l

#define FIRST_NAME_SIZE_MAX	12lu	/* 11 chars + '\0' */
#define NAMES_FIRST_TYPE_STRING	"VARCHAR(12)"
#define NAMES_FIRST_TYPE_PUT	put_string_width11
#define NAMES_FIRST_TYPE_WIDTH	12
#define SET_NAMES_FIRST_TYPE(PTR)					\
SET_STRING_WIDTH(PTR, NAMES_FIRST_TYPE_STRING, NAMES_FIRST_TYPE_WIDTH)

#define LAST_NAME_SIZE_MAX     11lu	/* 10 chars + '\0' */
#define NAMES_LAST_TYPE_STRING "VARCHAR(11)"
#define NAMES_LAST_TYPE_PUT    put_string_width11
#define NAMES_LAST_TYPE_WIDTH  12
#define SET_NAMES_LAST_TYPE(PTR)					\
SET_STRING_WIDTH(PTR, NAMES_LAST_TYPE_STRING, NAMES_LAST_TYPE_WIDTH)

#define FULL_NAME_SIZE_MAX     37lu	/* 2 * 1st_max + last_max + 2 spaces */
#define NAMES_FULL_TYPE_STRING "VARCHAR(37)"
#define NAMES_FULL_TYPE_PUT    put_string_width11
#define NAMES_FULL_TYPE_WIDTH  12
#define SET_NAMES_FULL_TYPE(PTR)					\
SET_STRING_WIDTH(PTR, NAMES_FULL_TYPE_STRING, NAMES_FULL_TYPE_WIDTH)


/* failure messages
 *─────────────────────────────────────────────────────────────────────────── */
#define BCSN_FIRST_MALLOC_FAILURE					\
MALLOC_FAILURE_MESSAGE("build_column_string_names_first")
#define BCSN_FIRST_GROUP_MALLOC_FAILURE					\
MALLOC_FAILURE_MESSAGE("build_column_string_names_first_group")

#define BCSN_LAST_MALLOC_FAILURE					\
MALLOC_FAILURE_MESSAGE("build_column_string_names_last")
#define BCSN_LAST_GROUP_MALLOC_FAILURE					\
MALLOC_FAILURE_MESSAGE("build_column_string_names_last_group")

#define BCSN_FULL_MALLOC_FAILURE					\
MALLOC_FAILURE_MESSAGE("build_column_string_names_full")
#define BCSN_FULL_GROUP_MALLOC_FAILURE					\
MALLOC_FAILURE_MESSAGE("build_column_string_names_full_group")


/* enum, struct declarations
 *─────────────────────────────────────────────────────────────────────────── */
struct NameMap {
	const struct Stub *names;
	const urint_t i_last;
};

/* global variables
 *─────────────────────────────────────────────────────────────────────────── */
extern const struct Stub first_names[FIRST_NAMES_COUNT];
extern const struct Stub last_names[LAST_NAMES_COUNT];

extern const struct NameMap first_name_map;
extern const struct NameMap last_name_map;

inline char *
put_random_initial(char *const restrict string)
{
	*string = (char) random_int_in_range((rint_t) 'A',
					     (rint_t) 'Z');
	return string + 1l;
}

inline const struct Stub *
name_map_sample(const struct NameMap *const restrict map)
{
	return &map->names[ random_uint_upto(map->i_last) ];
}

inline char *
put_single_names(char *restrict ptr,
		 const struct NameMap *const restrict map,
		 size_t count)
{
	do {
		ptr = put_stub_stop(ptr,
				    name_map_sample(map));

		--count;
	} while (count > 0lu);

	return ptr;
}

inline char *
put_full_name(char *restrict ptr)
{
	ptr = put_stub(ptr,
		       name_map_sample(&first_name_map));

	*ptr = ' ';
	++ptr;

	if (coin_flip()) {
		ptr = coin_flip()
		      ? put_random_initial(ptr)
		      : put_stub(ptr,
				 name_map_sample(&first_name_map));

		*ptr = ' ';
		++ptr;
	}

	return put_stub_stop(ptr,
			     name_map_sample(&last_name_map));
}

inline char *
put_full_names(char *restrict ptr,
	       size_t count)
{
	do {
		ptr = put_full_name(ptr);

		--count;
	} while (count > 0lu);

	return ptr;
}


/* worker thread entry points */
void
build_column_string_names_first(void *arg);
void
build_column_string_names_first_group(void *arg);
void
build_column_string_names_last(void *arg);
void
build_column_string_names_last_group(void *arg);
void
build_column_string_names_full(void *arg);
void
build_column_string_names_full_group(void *arg);


#endif	/* ifndef MYSQL_SEED_GENERATE_COLUMN_STRING_NAMES_H_ */
