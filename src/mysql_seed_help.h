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
_H2_("help    \t<-h, --help> [MODE]")					\
_P2_("prints operation details for mode 'MODE' or this message if not "	\
     "specified")							\
_P2_("examples:")							\
_P3_("mysql_seed --help")						\
_P3_("mysql_seed -h generate")						\
_P3_("mysql_seed --help e")						\
_H2_("generate\t<-g, --generate> <DB_SPEC_1> [DB_SPEC_2] ... ["		\
     "DB_SPEC_N]")							\
_P2_("generates seed files for N databases according to their "		\
     "specification, 'DB_SPEC'")					\
_P2_("examples:")							\
_P3_("mysql_seed --generate --database foo_forum --table users 500 "	\
     "--column name --string --names-full --column age "		\
     "--unsigned-integer --random --range 18 99 --column password "	\
     "--string --hash 128")						\
_P3_("mysql_seed -g -d baz_shop -t products 100000 -c name -s "		\
     "-c price -f -m 0.10")						\
_H2_("execute  \t<-e, --execute> <DB_NAME> [MYSQL_ARGS]")		\
_P2_("creates database 'DB_NAME' and loads generated table files found"	\
     " under the directory 'database" PATH_DELIM_STRING	"DB_NAME' into"	\
     " MySQL")								\
_P2_("examples:")							\
_P3_("TODO")								\
_H2_("remove  \t<-r, --remove> <-a, --all | DB_NAME_1> [DB_NAME_2] ..."	\
     " [DB_NAME_N]")							\
"\n"									\
_H1_("NOTATION")							\
_H2_("<MANDATORY>")							\
_H2_("[OPTIONAL]")							\
_H2_("THIS AND THAT | OR THESE")					\
_H2_("HOMOGENOUS INPUT ... SEQUENCE")

/* generate mode */
#define HELP_GENERATE_MESSAGE						\
_H1_("GENERATE MODE")							\
_H2_("mysql_seed <-g, --generate> <DB_SPEC_1> [DB_SPEC_2] ... ["	\
     "DB_SPEC_N]")							\
_P1_("generates seed files for N databases according to their "		\
     "specification, 'DB_SPEC'")					\
"\n"									\
_H1_("SPECS")								\
_H2_("DB_SPEC  \t<-d, --database> <DB_NAME> <TBL_SPEC_1> [TBL_SPEC_2] "	\
     "... [TBL_SPEC_N]")						\
_P2_("indicates that the tables described by 'TBL_SPEC's 1 through N "	\
     "belong to the MySQL database named 'DB_NAME'")			\
"\n"									\
_H2_("TBL_SPEC \t<-t, --table> <TBL_NAME> <ROW_COUNT> <COL_SPEC_1> "	\
     "[COL_SPEC_2] ... [COL_SPEC_N]")					\
_P2_("specifies a database table with name 'TBL_NAME' having '"		\
     "ROW_COUNT' rows and N columns populated according to their '"	\
     "respective COL_SPEC's")						\
"\n"									\
_H2_("COL_SPEC \t<-c, --column> <COL_NAME> <COL_TYPE> [COL_TYPE_Q_1] "	\
     "[COL_TYPE_Q_2] ... [COL_TYPE_Q_N] [GRP_SPEC]")			\
_P2_("specifies a database column with name 'COL_NAME' and data type "	\
     "'COL_TYPE' - column type qualifiers 'COL_TYPE_Q' 1 through N may"	\
     " be provided to fine-tune data generation for a given type")	\
"\n"									\
_H2_("GRP_SPEC \t<-g, --group> <GRP_COUNT> [<-e, --even> | <-l, "	\
     "--linear>]")							\
"\n"									\
_H1_("SUPPORTED DATA TYPES")						\
_H2_("<-s, --string>")							\
_H2_("<-i, --integer>")							\
_H2_("<-u, --unsigned-integer>")					\
_H2_("<-dt, --datetime>")						\
_H2_("<-ts, --timestamp>")						\
_P1_("TODO")								\
"\n"									\
_H1_("NOTATION")							\
_H2_("<MANDATORY>")							\
_H2_("[OPTIONAL]")							\
_H2_("THIS | OR THAT | OR THESE")					\
_H2_("HOMOGENOUS INPUT ... SEQUENCE")

/* execute mode */
#define HELP_EXECUTE_MESSAGE						\
_H1_("EXECUTE MODE")							\
_H2_("mysql_seed <-e, --execute> <DB_NAME> [MYSQL_ARGS]")		\
"\n"									\
_H1_("MYSQL_ARGS")							\
_P1_("TODO")

/* remove mode */
#define HELP_REMOVE_MESSAGE						\
_H1_("REMOVE MODE")							\
_H2_("mysql_seed <-r, --remove> <-a, -all | DB_NAME_1> [DB_NAME_2] ..."	\
     " [DB_NAME_N]")							\
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
				 sizeof(HELP_USAGE_MESSAGE) - 1lu);
	__builtin_unreachable();
}

inline void
exit_help_generate(void)
{
	exit_success_dump_buffer(HELP_GENERATE_MESSAGE,
				 sizeof(HELP_GENERATE_MESSAGE) - 1lu);
	__builtin_unreachable();
}

inline void
exit_help_execute(void)
{
	exit_success_dump_buffer(HELP_EXECUTE_MESSAGE,
				 sizeof(HELP_EXECUTE_MESSAGE) - 1lu);
	__builtin_unreachable();
}

/* print help message, return success status
 *─────────────────────────────────────────────────────────────────────────── */
inline int
help_usage(void)
{
	const char *restrict failure;

	if (LIKELY(write_report(STDOUT_FILENO,
				HELP_USAGE_MESSAGE,
				sizeof(HELP_USAGE_MESSAGE) - 1lu,
				&failure)))
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

	if (LIKELY(write_report(STDOUT_FILENO,
				HELP_GENERATE_MESSAGE,
				sizeof(HELP_GENERATE_MESSAGE) - 1lu,
				&failure)))
		return EXIT_SUCCESS;

	write_muffle(STDERR_FILENO,
		     failure,
		     string_length(failure));

	return EXIT_FAILURE;
}

inline int
help_execute(void)
{
	const char *restrict failure;

	if (LIKELY(write_report(STDOUT_FILENO,
				HELP_EXECUTE_MESSAGE,
				sizeof(HELP_EXECUTE_MESSAGE) - 1lu,
				&failure)))
		return EXIT_SUCCESS;

	write_muffle(STDERR_FILENO,
		     failure,
		     string_length(failure));

	return EXIT_FAILURE;
}


/* print error messsage and return 'EXIT_FAILURE'
 *─────────────────────────────────────────────────────────────────────────── */
inline void
invalid_mode(char *const restrict mode)
{
	char buffer[ARG_INSPECT_BUFFER_SIZE];

	char *restrict
	ptr = put_string_size(&buffer[0],
			      FAILURE_INVALID_MODE_HEADER,
			      sizeof(FAILURE_INVALID_MODE_HEADER) - 1lu);

	ptr = put_string_inspect(ptr,
				 mode,
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      MORE_INFO_MESSAGE,
			      sizeof(MORE_INFO_MESSAGE) - 1lu);

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
		if (LIKELY(((*rem == '\0') || strings_equal("enerate", rem))))
			return help_generate();
		break;

	case 'h':
		if (LIKELY(((*rem == '\0') || strings_equal("elp", rem))))
			return help_usage();
		break;

	case 'e':
		if (LIKELY(((*rem == '\0') || strings_equal("xecute", rem))))
			return help_execute();
		break;

	default:
		break;
	}

       invalid_mode(mode);
       return EXIT_FAILURE;
}

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_HELP_H_ */
