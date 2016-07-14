#ifndef MYSQL_SEED_MYSQL_SEED_HELP_H_
#define MYSQL_SEED_MYSQL_SEED_HELP_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "mysql_seed_file.h"	/* handle input strings */


#define _H1_(STRING) UNDERLINE_WRAP(STRING) "\n"
#define _H2_(STRING) "\t" ANSI_WRAP(BRIGHT, STRING) "\n"
#define _P1_(STRING) "\t" STRING "\n"
#define _P2_(STRING) "\t\t" STRING "\n"
#define _P3_(STRING) "\t\t\t" STRING "\n"

/* help messages
 *─────────────────────────────────────────────────────────────────────────── */
/* usage */
#define HELP_USAGE_MESSAGE						\
_H1_("USAGE")								\
_H2_("mysql_seed <MODE> [SPECS]")					\
"\n"									\
_H1_("MODES")								\
_H2_("help\t<-h, --help> [MODE]")					\
_P2_("prints operation details for mode 'MODE' or this message if not "	\
     "specified")							\
_P2_("examples:")							\
_P3_("mysql_seed --help")						\
_P3_("mysql_seed -h generate")						\
_P3_("mysql_seed --help l")						\
_H2_("generate\t<-g, --generate> <DB_SPEC_1> [DB_SPEC_2] [DB_SPEC_3] "	\
     "... [DB_SPEC_N]")							\
_P2_("generates seed files for N databases according to their "		\
     "specification, 'DB_SPEC'")					\
_P2_("examples:")							\
_P3_("mysql_seed --generate --database foo_forum --table users 500 "	\
     "--column name STRING NAME FULL --column age UNSIGNED RANGE 18 "	\
     "99 --column email STRING EMAIL")					\
_P3_("mysql_seed -g -d baz_shop -t products 100000 -c name STRING"	\
     "-c price FLOAT MIN 0.10")						\
_H2_("load\t<-l, --load> <DB_NAME> [MYSQL_ARGS]")			\
_P2_("loads seed files found in directory 'db" PATH_DELIM_STRING	\
     "DB_NAME' into the mysql database 'DB_NAME'")			\
_P2_("examples:")							\
_P3_("TODO")								\
"\n"									\
_H1_("NOTATION")							\
_H2_("<MANDATORY INPUT>")						\
_H2_("[OPTIONAL INPUT]")

/* generate mode */
#define HELP_GENERATE_MESSAGE						\
_H1_("GENERATE MODE")							\
_H2_("mysql_seed <-g, --generate> <DB_SPEC_1> [DB_SPEC_2] [DB_SPEC_3] "	\
     "... DB_SPEC_N]")							\
_P1_("generates seed files for N databases according to their "		\
     "specification, 'DB_SPEC'")					\
"\n"									\
_H1_("SPECS")								\
_H2_("DB_SPEC\t<-d, --database> <DB_NAME> <TBL_SPEC_1> [TBL_SPEC_2] "	\
     "[TBL_SPEC_3] ... [TBL_SPEC_N]")					\
_P2_("indicates that the tables described by 'TBL_SPEC's 1 through N "	\
     "belong to the mysql database named 'DB_NAME'")			\
_H2_("TBL_SPEC\t<-t, --table> <TBL_NAME> <ROW_COUNT> <COL_SPEC_1> "	\
     "[COL_SPEC_2] ... [COL_SPEC_N]")					\
_P2_("specifies a database table with name 'TBL_NAME', 'ROW_COUNT' "	\
     "rows, and N columns populated according to their 'COL_SPEC's")	\
_H2_("COL_SPEC\t<-c, --column> <COL_NAME> <COL_TYPE> [COL_TYPE_Q_1] "	\
     "[COL_TYPE_Q_2] ... [COL_TYPE_Q_N]")				\
_P2_("specifies a database column with name 'COL_NAME' and data type "	\
     "'COL_TYPE' - column type qualifiers 'COL_TYPE_Q' 1 through N may"	\
     " be provided to fine-tune data generation for a given type")	\
"\n"									\
_H1_("SUPPORTED DATA TYPES")						\
_P1_("TODO")								\
"\n"									\
_H1_("NOTATION")							\
_H2_("<MANDATORY> [OPTIONAL]")

/* load mode */
#define HELP_LOAD_MESSAGE						\
_H1_("LOAD MODE")							\
_H2_("mysql_seed <-l, --load> <DB_NAME> [MYSQL_ARGS]")			\
"\n"									\
_H1_("MYSQL_ARGS")							\
_P1_("TODO")

/* error messages
 *─────────────────────────────────────────────────────────────────────────── */
#define FAILURE_INVALID_MODE_HEADER					\
PARSE_FAILURE_HEADER("invalid MODE")


/* print help then exit on success
 *─────────────────────────────────────────────────────────────────────────── */
inline void
exit_help_usage(void)
{
	exit_success_dump_buffer(HELP_USAGE_MESSAGE,
				 sizeof(HELP_USAGE_MESSAGE));
	__builtin_unreachable();
}

inline void
exit_help_generate(void)
{
	exit_success_dump_buffer(HELP_GENERATE_MESSAGE,
				 sizeof(HELP_GENERATE_MESSAGE));
	__builtin_unreachable();
}

inline void
exit_help_load(void)
{
	exit_success_dump_buffer(HELP_LOAD_MESSAGE,
				 sizeof(HELP_LOAD_MESSAGE));
	__builtin_unreachable();
}

/* print help message, return success status
 *─────────────────────────────────────────────────────────────────────────── */
inline int
help_usage(void)
{
	const char *restrict failure;

	if (write_report(STDOUT_FILENO,
			 HELP_USAGE_MESSAGE,
			 sizeof(HELP_USAGE_MESSAGE),
			 &failure))
		return EXIT_SUCCESS;

	write_muffle(STDERR_FILENO,
		     failure,
		     string_length(failure));

	return EXIT_FAILURE;
}

inline int
help_generate(void)
{
	const char *restrict failure;

	if (write_report(STDOUT_FILENO,
			 HELP_GENERATE_MESSAGE,
			 sizeof(HELP_GENERATE_MESSAGE) - 1lu,
			 &failure))
		return EXIT_SUCCESS;

	write_muffle(STDERR_FILENO,
		     failure,
		     string_length(failure));

	return EXIT_FAILURE;
}

inline int
help_load(void)
{
	const char *restrict failure;

	if (write_report(STDOUT_FILENO,
			 HELP_LOAD_MESSAGE,
			 sizeof(HELP_LOAD_MESSAGE) - 1lu,
			 &failure))
		return EXIT_SUCCESS;

	write_muffle(STDERR_FILENO,
		     failure,
		     string_length(failure));

	return EXIT_FAILURE;
}


/* print error messsage and return 'EXIT_FAILURE'
 *─────────────────────────────────────────────────────────────────────────── */
inline void
print_invalid_mode(char *const restrict mode)
{
	char buffer[ARG_INSPECT_BUFFER_SIZE] = {
		FAILURE_INVALID_MODE_HEADER
	};

	char *restrict
	ptr = put_string_inspect(&buffer[0]
				 + sizeof(FAILURE_INVALID_MODE_HEADER) - 1ul,
				 mode,
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      MORE_INFO_MESSAGE,
			      sizeof(MORE_INFO_MESSAGE));

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}


/* dispatch help mode according to 'arg'
 *─────────────────────────────────────────────────────────────────────────── */
inline int
help_dispatch(char *const restrict *const restrict arg,
	      const int rem_argc)
{
	if (rem_argc == 0)
		return help_usage();

	char *const restrict mode = *arg;
	char *const restrict rem  = mode + 1l;

	switch (*mode) {
	case 'g':
		if ((*rem == '\0') || strings_equal("enerate", rem))
			return help_generate();

		break;

	case 'l':
		if ((*rem == '\0') || strings_equal("enerate", rem))
			return help_load();

		break;


	default:
		break;
	}

       print_invalid_mode(mode);

       return EXIT_FAILURE;
}

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_HELP_H_ */
