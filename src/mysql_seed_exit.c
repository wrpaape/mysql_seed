#include "mysql_seed_exit.h"

extern inline void seed_exit_spec_set(struct SeedExitSpec *const restrict spec,
				      const int status,
				      const FILE *const restrict stream,
				      const char *const restrict format,
				      ...);


void seed_exit(const union SeedModeSpec *const restrict mode_spec)
{
	const struct SeedExitSpec *const restrict spec = &mode_spec->exit;

	vfprintf(spec->stream,
		 spec->format,
		 spec->ap);

	exit(spec->status);
}
