#ifndef MYSQL_SEED_MYSQL_SEED_H_
#define MYSQL_SEED_MYSQL_SEED_H_

#define DEFAULT_USER_COUNT 25000


/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <stdlib.h>	/* exit */
#include <stdio.h>	/* fprintf */
#include <stdarg.h>	/* va_list */


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


typespec void SeedModeHandler(const union SeedModeSpec *const restrict spec);

enum SeedMode {
	HELP;
	CREATE;
	RUN;
};


struct FieldSpec {
	const char *field_name;
	const char *base_value;	/* optional */
};

struct TableSpec {
	const char *table_name;
	struct FieldSpec *fields;
	unsigned int field_count;
};

struct SeedTableSpec {
	struct TableSpec table;
	unsigned int seed_count;
};

struct SeedDatabaseSpec {
	const char *name;
	struct SeedTableSpec *seed_tables;
	unsigned int table_count;
};


struct CreateSpec {
	const char *filename;
	struct SeedDatabaseSpec *seed_databases;
	unsigned int database_count;
};


struct RunSpec {
	const char *filename;
	const char *user;
	const char *password;
};


struct ExitSpec {
	int status;
	FILE *stream;
	const char *format;
	va_list ap;
};


union SeedModeSpec {
	struct CreateSpec create;
	struct RunSpec run;
	struct ExitSpec exit;
};


struct SeedMode {
	SeedModeHandler *handle;
	union SeedModeSpec spec;
};


void cli_parse_input(struct SeedMode *const restrict mode,
		     const int argc,
		     const char *const restrict *argv)

/* 'SeedModeHandler' dispatch functions
 *─────────────────────────────────────────────────────────────────────────── */
void exit_message(const union SeedModeSpec *const restrict spec);


/* misc helper functions
 *─────────────────────────────────────────────────────────────────────────── */
static inline void exit_spec_set(struct ExitSpec *const restrict exit,
				 const int status,
				 const File *const restrict stream,
				 const char *const restrict format,
				 ...);

#endif	/* MYSQL_SEED_MYSQL_SEED_H_ */
