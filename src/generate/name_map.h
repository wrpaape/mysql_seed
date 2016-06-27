#ifndef MYSQL_SEED_NAME_MAP_H_
#define MYSQL_SEED_NAME_MAP_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <stdint.h>		/* SIZE_MAX, UINT32_MAX */
#include "random/random.h"	/* urint_t, random_uint_upto */

#define FIRST_NAMES_COUNT 200lu
#define LAST_NAMES_COUNT  200lu
#define FIRST_NAMES_MAP_I_LAST 199l
#define LAST_NAMES_MAP_I_LAST  199l

#define SIZE_FIRST_NAME_MAX 12lu	/* 11 chars + '\0' */
#define SIZE_LAST_NAME_MAX 11lu		/* 10 chars + '\0' */
#define SIZE_FULL_NAME_MAX (((SIZE_FIRST_NAME_MAX) * 2lu)	\
			    + SIZE_LAST_NAME_MAX		\
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

/* struct definitions
 *─────────────────────────────────────────────────────────────────────────── */
struct NameMap {
	const char *const restrict *restrict names;
	const urint_t i_last;
};

/* global variables
 *─────────────────────────────────────────────────────────────────────────── */
extern const char *const first_names[FIRST_NAMES_COUNT];
extern const char *const last_names[LAST_NAMES_COUNT];

extern const struct NameMap first_name_map;
extern const struct NameMap last_name_map;


inline char *
name_map_sample(const struct NameMap *const restrict map)
{
	return map->names[ random_uint_upto(map->i_last) ];
}




#endif	/* MYSQL_SEED_NAME_MAP_H_
