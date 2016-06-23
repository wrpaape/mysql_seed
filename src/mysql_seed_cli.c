#include "mysql_seed_cli.h"

/* misc helper functions
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
seed_mode_set_exit_failure(struct SeedMode *const restrict mode,
			   const char *const restrict reason);

extern inline void
seed_mode_set_exit_help(struct SeedMode *const restrict mode,
			const int argc,
			char *const restrict *const restrict argv);

extern inline void
seed_mode_set_exit_invalid_option(struct SeedMode *const restrict mode,

				  const char *const restrict option);

/* parse stdin args
 *─────────────────────────────────────────────────────────────────────────── */
void
seed_cli_parse_input(struct SeedMode *const restrict mode,
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
					  option);
}
