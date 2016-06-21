#ifndef MYSQL_SEED_MYSQL_SEED_H_
#define MYSQL_SEED_MYSQL_SEED_H_

#define DEFAULT_USER_COUNT 25000

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "mysql_seed_create.h"
#include "mysql_seed_run.h"
#include "mysql_seed_exit.h"


/* print message → exit
 *─────────────────────────────────────────────────────────────────────────── */
#define EXIT_MESSAGE(STATUS, STREAM, FORMAT, ...)		\
do {								\
	fprintf(STREAM, FORMAT, ##__VA_ARGS__);			\
	exit(STATUS);						\
} while (0)

#define EXIT_ERROR(FORMAT, ...)					\
EXIT_MESSAGE(EXIT_FAILURE, stderr, FORMAT, ##__VA_ARGS__)

#define EXIT_HELP(MESSAGE)					\
EXIT_MESSAGE(EXIT_SUCCESS, stdout, MESSAGE)


/* ANSI escape sequences
 *─────────────────────────────────────────────────────────────────────────── */
#define ANSI_BRIGHT "\e[1m"
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




void cli_parse_input(struct SeedMode *const restrict mode,
		     const int argc,
		     const char *const restrict *argv);




#endif	/* MYSQL_SEED_MYSQL_SEED_H_ */
