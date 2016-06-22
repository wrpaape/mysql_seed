#include "mysql_seed.h"

int main(int argc, char *argv[])
{

	struct SeedMode mode;

	parse_input(&mode, argc, &argv[0]);

	(*mode.handle)(&mode.spec);

	return EXIT_SUCCESS;
}


void
parse_input(struct SeedMode *const restrict mode,
	    const int argc,
	    char *const restrict *const restrict argv)
{
	if (argc == 1) {
		seed_mode_set_exit_failure(mode,
					    ERROR_NO_INPUT_MESSAGE);
		return;
	}

	const char *const restrict option = argv[1];

	if (option[0] != '-')
		goto EXIT_INVALID_OPTION;


	switch (option[1]) {
	case '-':
		break;
	case 'c':
		if (option[2] == '\0') {
			/* TODO: dispatch 'create' mode */
			return;
		}

		goto EXIT_INVALID_OPTION;


	case 'h':
		if (option[2] == '\0') {
			seed_mode_set_exit_help(mode,
						argc,
						argv);
			return;
		}

		goto EXIT_INVALID_OPTION;


	case 'r':
		if (option[2] == '\0') {
			/* TODO: dispatch 'run' mode */
			return;
		}

		/* fall through */

	default:
		goto EXIT_INVALID_OPTION;
	}


	/* parse long option */
	switch (option[2]) {
	case 'c':
		if (strings_equal("reate",
				  &option[3])) {
			/* TODO: dispatch 'create' mode */
			return;
		}

		goto EXIT_INVALID_OPTION;


	case 'h':
		if (strings_equal("elp",
				  &option[3])) {

			seed_mode_set_exit_help(mode,
						argc,
						argv);
			return;
		}

		goto EXIT_INVALID_OPTION;


	case 'r':
		if (strings_equal("un",
				  &option[3])) {
			/* TODO: dispatch 'run' mode */
			return;
		}

		/* fall through */
	}

EXIT_INVALID_OPTION:
	seed_mode_set_exit_invalid_option(mode,
					  &log_buffer[0],
					  option);
}

inline void
seed_mode_set_exit_failure(struct SeedMode *const restrict mode,
			   const char *const restrict reason)
{
	mode->handle = &seed_exit;
	seed_exit_spec_set_failure(&mode->spec.exit,
				   reason);
}

inline void
seed_mode_set_exit_help(struct SeedMode *const restrict mode,
			const int argc,
			char *const restrict *const restrict argv)
{
	mode->handle = &seed_exit;

	if (argc == 2)
		goto HELP_USAGE;

	const char *const restrict help_option = argv[2];

	switch (help_option[1]) {
	case '-':
		break;

	case 'c':
		if (help_option[2] == '\0') {
			seed_exit_spec_set_help_create(&mode->spec.exit);
			return;
		}

		goto HELP_USAGE;

	case 'r':
		if (help_option[2] == '\0') {
			seed_exit_spec_set_help_run(&mode->spec.exit);
			return;
		}

		/* fall through */

	default:
		goto HELP_USAGE;
	}



	/* parse long option */
	switch (help_option[2]) {
	case 'c':
		if (strings_equal("reate",
				  &help_option[3])) {

			seed_exit_spec_set_help_create(&mode->spec.exit);
			return;
		}

		goto HELP_USAGE;

	case 'r':
		if (strings_equal("un",
				  &help_option[3])) {

			seed_exit_spec_set_help_run(&mode->spec.exit);
			return;
		}

		/* fall through */
	}

HELP_USAGE:
	seed_exit_spec_set_help_usage(&mode->spec.exit);
}

inline void
seed_mode_set_exit_invalid_option(struct SeedMode *const restrict mode,
				  char *const restrict buffer,
				  const char *const restrict option)
{
	mode->handle = &seed_exit;
	seed_exit_spec_set_invalid_option(&mode->spec.exit,
					  buffer,
					  option);
}
