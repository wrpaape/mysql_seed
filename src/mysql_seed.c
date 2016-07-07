#include "mysql_seed.h"

int main(int argc, char *argv[])
{
	if (argc == 1) {
		seed_mode_set_exit_failure(mode,
					    ERROR_NO_INPUT_MESSAGE);
		return;
	}

	return EXIT_SUCCESS;
}

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

	const char *const restrict opt = argv[1];

	if (opt[0] != '-')
		goto EXIT_INVALID_OPTION;

	/* parse short option */
	switch (opt[1]) {
	case '-': break;	/* parse long option */
	CASE_SHORT_OPT('c',
		       puts("TODO: dispatch 'create' mode"),
		       goto EXIT_INVALID_OPTION);
	CASE_SHORT_OPT('h',
		       seed_mode_set_exit_help(mode, argc, argv),
		       goto EXIT_INVALID_OPTION);
	CASE_SHORT_OPT('r',
		       puts("TODO: dispatch 'run' mode"),
		       goto EXIT_INVALID_OPTION);
	default: goto EXIT_INVALID_OPTION;
	}

	/* parse long option */
	switch (opt[2]) {
	CASE_LONG_OPT('c', "reate",
		       puts("TODO: dispatch 'create' mode"),
		       break);
	CASE_LONG_OPT('h', "elp",
		       seed_mode_set_exit_help(mode, argc, argv),
		       break);
	CASE_LONG_OPT('r', "un",
		       puts("TODO: dispatch 'run' mode"),
		       break);
	default: break;		/* do nothing */
	}

EXIT_INVALID_OPTION:
	seed_mode_set_exit_invalid_option(mode,
					  opt);
}
