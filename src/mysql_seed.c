#include "mysql_seed.h"

void main(int argc, char *argv[])
{
	struct SeedMode mode;

	cli_parse_input(&mode, argc, argv);

	(*mode.handle)(&mode.spec);

	return EXIT_SUCCESS;
}

void cli_parse_input(struct SeedMode *const restrict mode,
		     const int argc,
		     const char *const restrict *argv)
{
	mode->handle = &seed_exit;

	struct SeedExitSpec *const restrict exit = &mode->spec.exit;

	seed_exit_spec_set(&mode->spec.exit,
			   EXIT_SUCCESS,
			   stdout,
			   HELP_USAGE_MESSAGE);
}
