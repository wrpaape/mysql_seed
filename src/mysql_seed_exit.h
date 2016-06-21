#ifndef MYSQL_SEED_MYSQL_SEED_EXIT_H_
#define MYSQL_SEED_MYSQL_SEED_EXIT_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <stdlib.h>		/* exit */
#include <stdarg.h>		/* va_list */
#include "mysql_seed_mode.h"	/* SeedExitSpec, SeedModeSpec, <stdio.h> */


/* 'SeedModeHandler' dispatch function
 *─────────────────────────────────────────────────────────────────────────── */
void seed_exit(const union SeedModeSpec *const restrict mode_spec);


/* misc helper functions
 *─────────────────────────────────────────────────────────────────────────── */
inline void seed_exit_spec_set(struct SeedExitSpec *const restrict spec,
			       const int status,
			       const File *const restrict stream,
			       const char *const restrict format,
			       ...)
{
	va_list params;

	spec->status = status;
	spec->stream = stream;
	spec->format = format;

	va_start(params, format);
	va_copy(spec->ap, params);
	va_end(params);
}

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_EXIT_H_ */
