#ifndef MYSQL_SEED_MYSQL_SEED_H_
#define MYSQL_SEED_MYSQL_SEED_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "mysql_seed_create.h"	/* CreateSpec, string macros */
#include "mysql_seed_run.h"	/* RunSpec */
#include "mysql_seed_help.h"	/* help dispatch, exit utils */


/* cap reads on input strings
 *─────────────────────────────────────────────────────────────────────────── */
#define MESSAGE_BUFFER_LENGTH 512lu
#define OPTION_MAX_LENGTH 128lu


/* error messages
 *─────────────────────────────────────────────────────────────────────────── */
#define ERROR_NO_INPUT_MESSAGE					\
ERROR_HEADER("missing input options\n")

#define ERROR_INVALID_OPTION					\
ERROR_HEADER("invalid option: ")

/* helpful macros
 *─────────────────────────────────────────────────────────────────────────── */
#define CASE_SHORT_OPT(CHAR, HANDLE_MATCH, HANDLE_NOMATCH)	\
case CHAR:							\
	if (opt[2] == '\0') {					\
		HANDLE_MATCH;					\
		return;						\
	}							\
	HANDLE_NOMATCH

#define CASE_LONG_OPT(FIRST, REM, HANDLE_MATCH, HANDLE_NOMATCH)	\
case FIRST:							\
	if (strings_equal(REM,					\
			  &opt[3])) {				\
		HANDLE_MATCH;					\
		return;						\
	}							\
	HANDLE_NOMATCH




inline void
seed_mode_set_exit_help(struct SeedMode *const restrict mode,
			const int argc,
			char *const restrict *const restrict argv)
{
	mode->handle = &seed_exit;

	if (argc == 2)
		goto HELP_USAGE;

	const char *const restrict opt = argv[2];

	if (opt[0] != '-')
		goto HELP_USAGE;

	/* parse short option */
	switch (opt[1]) {
	case '-': break;	/* parse long option */
	CASE_SHORT_OPT('c',
		       seed_exit_spec_set_help_create(&mode->spec.exit),
		       goto HELP_USAGE);
	CASE_SHORT_OPT('r',
		       seed_exit_spec_set_help_run(&mode->spec.exit),
		       goto HELP_USAGE);
	default: goto HELP_USAGE;
	}

	/* parse long option */
	switch (opt[2]) {
	CASE_LONG_OPT('c', "reate",
		      seed_exit_spec_set_help_create(&mode->spec.exit),
		      break);
	CASE_LONG_OPT('r', "un",
		      seed_exit_spec_set_help_run(&mode->spec.exit),
		      break);
	default: break;		/* do nothing */
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


#endif	/* MYSQL_SEED_MYSQL_SEED_H_ */
