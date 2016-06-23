#ifndef MYSQL_SEED_MYSQL_SEED_CLI_H_
#define MYSQL_SEED_MYSQL_SEED_CLI_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "mysql_seed_create.h"	/* CreateSpec */
#include "mysql_seed_run.h"	/* RunSpec */
#include "mysql_seed_exit.h"	/* ExitSpec, seed_exit_spec_set_<X> */



/* cap reads on input strings
 *─────────────────────────────────────────────────────────────────────────── */
#define OPTION_MAX_LENGTH 128lu

/* #define DEFAULT_USER_COUNT 25000 */

inline void
seed_mode_set_exit_invalid_option(struct SeedMode *const restrict mode,
				  const char *const restrict option)
{
	mode->handle = &seed_exit;
	seed_exit_spec_set_invalid_option(&mode->spec.exit,
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

/* parse stdin args
 *─────────────────────────────────────────────────────────────────────────── */
void
seed_cli_parse_input(struct SeedMode *const restrict mode,
		     const int argc,
		     char *const restrict *const restrict argv);


#endif	/* MYSQL_SEED_MYSQL_SEED_CLI_H_ */
