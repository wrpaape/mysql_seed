#include "mysql_seed.h"

int main(int argc, char *argv[])
{
	struct SeedMode mode;

	cli_parse_input(&mode, argc, &argv[0]);

	(*mode.handle)(&mode.spec);

	return EXIT_SUCCESS;
}

void cli_parse_input(struct SeedMode *const restrict mode,
		     const int argc,
		     char *const restrict *const restrict argv)
{
	mode->handle = &seed_exit;

	seed_exit_spec_set(&mode->spec.exit,
			   EXIT_SUCCESS,
			   stdout,
			   HELP_USAGE_MESSAGE);
}
