#include "mysql_seed_exit.h"

/* 'SeedModeHandler' dispatch function
 *─────────────────────────────────────────────────────────────────────────── */
void
seed_exit(const union SeedModeSpec *const restrict mode_spec)
{
	seed_exit_spec_exit(&mode_spec->exit);
}

void
seed_exit_spec_exit(const struct SeedExitSpec *const restrict spec)
{
	fputs(spec->message,
	      spec->stream);

	exit(spec->status);
}

/* extern inline function declarations
 *─────────────────────────────────────────────────────────────────────────── */

extern inline void
seed_exit_spec_set(struct SeedExitSpec *const restrict spec,
		   const int status,
		   FILE *const restrict stream,
		   const char *const restrict message);

extern inline void
seed_exit_spec_set_failure(struct SeedExitSpec *const restrict spec,
			   const char *const restrict reason);

extern inline void
seed_exit_spec_set_help(struct SeedExitSpec *const restrict spec,
			const char *const restrict message);
extern inline void
seed_exit_spec_set_help_usage(struct SeedExitSpec *const restrict spec);

extern inline void
seed_exit_spec_set_help_create(struct SeedExitSpec *const restrict spec);

extern inline void
seed_exit_spec_set_help_run(struct SeedExitSpec *const restrict spec);
