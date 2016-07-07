#ifndef MYSQL_SEED_MYSQL_SEED_HELP_H_
#define MYSQL_SEED_MYSQL_SEED_HELP_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "system/exit_utils.h"		/* exit utils, string utils */

#define _H1_(STRING) UNDERLINE_WRAP(STRING) "\n"
#define _H2_(STRING) "\t" ANSI_WRAP(BRIGHT, STRING) "\n"
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
_P3_("mysql_seed -h create")						\
_P3_("mysql_seed --help g")						\
_H2_("generate\t<-g, --generate> <DB_SPEC_1> [DB_SPEC_2] [DB_SPEC_3] "	\
     "... [DB_SPEC_N]")							\
_P2_("creates seed files for 'N' databases according to their "		\
     "specification 'DB_SPEC'")						\
_P2_("examples:")							\
_P3_("mysql_seed --generate --database foo_forum --table users 500 "	\
     "--column name STRING NAME_FULL --column age UNSIGNED RANGE 18 "	\
     "99 --column email STRING EMAIL")					\
_P3_("mysql_seed -g -d baz_shop -t products 100000 -c name STRING"	\
     "-c price FLOAT MIN 0.10")						\
_H2_("run\t<-r, --run> <DB_NAME> [MYSQL_ARGS]")				\
_P2_("loads seed files found in directory 'db" PATH_DELIM "DB_NAME' "	\
     " into the mysql database 'DB_NAME'")				\
_P2_("examples:")							\
_P3_("TODO")								\
"\n"									\
_H1_("NOTATION")							\
_H2_("<MANDATORY INPUT>")						\
_H2_("[OPTIONAL INPUT]")

/* create mode */
#define HELP_CREATE_MESSAGE						\
_H1_("CREATE MODE")							\
_H2_("mysql_seed <-c, --create> <DB_SPEC_1> [DB_SPEC_2] [DB_SPEC_3] "	\
     "... DB_SPEC_N]")							\
"\n"									\
_H1_("SPECS")								\
_H2_("DB_SPEC\t<-d, --database> <DB_NAME> <TBL_SPEC_1> [TBL_SPEC_2] "	\
     "[TBL_SPEC_3] ... [TBL_SPEC_N]")					\
_P2_("indicates that the tables described by 'TBL_SPEC's 1 through N "	\
     "belong to the mysql database named 'DB_NAME'")			\
_H2_("TBL_SPEC\t<-t, --table> <TBL_NAME> <ROW_COUNT> <COL_SPEC_1> "	\
     "[COL_SPEC_2] ... [COL_SPEC_N]")					\
_P2_("specifies a database table with name 'TBL_NAME', 'ROW_COUNT' "	\
     "rows, and 'N' columns populated according to their 'COL_SPEC's")	\
_H2_("COL_SPEC\t<-c, --column> <COL_NAME> <COL_TYPE> [COL_TYPE_SPEC_1]"	\
     " [COL_TYPE_SPEC_2] ... [COL_TYPE_SPEC_N]")			\
"\n"									\
_H1_("NOTATION")							\
_H2_("<MANDATORY> [OPTIONAL]")

#define HELP_CREATE_MESSAGE "OOGA BOOGA"

#define HELP_RUN_MESSAGE "BOOGITY BOO"


/* help dispatch
 *─────────────────────────────────────────────────────────────────────────── */

void
exit_help_usage(void)
{
	exit_success_dump_buffer(HELP_USAGE_MESSAGE,
				 sizeof(HELP_USAGE_MESSAGE));
}

void
exit_help_create(void)

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_HELP_H_ */
