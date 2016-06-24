#ifndef MYSQL_SEED_MYSQL_SEED_EXIT_H_
#define MYSQL_SEED_MYSQL_SEED_EXIT_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <stdlib.h>		/* exit */
#include "mysql_seed_log.h"	/* seed_log, string utils */
#include "mysql_seed_mode.h"	/* <stdio.h>, SeedExitSpec, SeedModeSpec */


/* cap reads on input strings
 *─────────────────────────────────────────────────────────────────────────── */
#define MESSAGE_BUFFER_LENGTH 512lu
#define OPTION_MAX_LENGTH 128lu


/* ANSI escape sequences
 *─────────────────────────────────────────────────────────────────────────── */
#define ANSI_BRIGHT "\e[1m"
#define ANSI_RED "\e[31m"
#define ANSI_RESET "\e[0m"
#define ANSI_UNDERLINE "\e[4m"
#define ANSI_NO_UNDERLINE "\e[24m"

#define UNDERLINE(STRING) ANSI_UNDERLINE STRING ANSI_NO_UNDERLINE
#define BRIGHTEN(STRING)  ANSI_BRIGHT    STRING ANSI_RESET


/* help messages
 *─────────────────────────────────────────────────────────────────────────── */
#define HELP_USAGE_MESSAGE					\
UNDERLINE("USAGE:") "\n"					\
"\t" BRIGHTEN("mysql_seed [OPTIONS] <INPUTS>") "\n\n"		\
UNDERLINE("OPTIONS:") "\n"					\
"\t" BRIGHTEN("-h, --help")   "\tprints this message\n"		\
"\t" BRIGHTEN("-c, --create") "\tcreates a seed file\n"		\
"\t" BRIGHTEN("-r, --run")    "\truns a seed file\n"

#define HELP_CREATE_MESSAGE "OOGA BOOGA"

#define HELP_RUN_MESSAGE "BOOGITY BOO"

/* error messages
 *─────────────────────────────────────────────────────────────────────────── */
#define ERROR_HEADER(STRING) ANSI_BRIGHT ANSI_RED STRING ANSI_RESET

#define ERROR_NO_INPUT_MESSAGE					\
ERROR_HEADER("missing input options\n")

#define ERROR_INVALID_OPTION					\
ERROR_HEADER("invalid option: ")


/* 'SeedModeHandler' dispatch function
 *─────────────────────────────────────────────────────────────────────────── */
void
seed_exit(const union SeedModeSpec *const restrict mode_spec)
__attribute__((noreturn));


void
seed_exit_spec_exit(const struct SeedExitSpec *const restrict spec)
__attribute__((noreturn));

/* misc helper functions
 *─────────────────────────────────────────────────────────────────────────── */
inline void
seed_exit_spec_set(struct SeedExitSpec *const restrict spec,
		    const int status,
		    FILE *const restrict stream,
		    const char *const restrict message)
{
	spec->status  = status;
	spec->stream  = stream;
	spec->message = message;
}

inline void
seed_exit_spec_set_failure(struct SeedExitSpec *const restrict spec,
			    const char *const restrict reason)
{
	seed_exit_spec_set(spec,
			    EXIT_FAILURE,
			    stderr,
			    reason);
}

inline void
seed_exit_spec_set_invalid_option(struct SeedExitSpec *const restrict spec,
				  const char *const restrict option)
{
	seed_log_append_string(ERROR_INVALID_OPTION);


	seed_log_append_string_length(option,
				      OPTION_MAX_LENGTH);

	seed_log_append_string("\n\n");

	seed_exit_spec_set_failure(spec,
				   seed_log_buffer_ptr());
}

inline void
seed_exit_spec_set_help(struct SeedExitSpec *const restrict spec,
			 const char *const restrict message)
{
	seed_exit_spec_set(spec,
			    EXIT_SUCCESS,
			    stdout,
			    message);
}

inline void
seed_exit_spec_set_help_usage(struct SeedExitSpec *const restrict spec)
{
	seed_exit_spec_set_help(spec,
				 HELP_USAGE_MESSAGE);
}

inline void
seed_exit_spec_set_help_create(struct SeedExitSpec *const restrict spec)
{
	seed_exit_spec_set_help(spec,
				 HELP_CREATE_MESSAGE);
}

inline void
seed_exit_spec_set_help_run(struct SeedExitSpec *const restrict spec)
{
	seed_exit_spec_set_help(spec,
				 HELP_RUN_MESSAGE);
}

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_EXIT_H_ */
