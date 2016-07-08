#ifndef MYSQL_SEED_MYSQL_SEED_INPUT_H_
#define MYSQL_SEED_MYSQL_SEED_INPUT_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "system/exit_utils.h"	/* exit, file, string utils */

/* cap reads on input strings
 *─────────────────────────────────────────────────────────────────────────── */
#define FLAG_LENGTH_MAX (sizeof("--generate") * 2lu)

/* error messages
 *─────────────────────────────────────────────────────────────────────────── */
#define MORE_INFO_MESSAGE "\n\nmysql_seed -h for more info\n"

#define INVALID_SPEC_HEADER(SPEC)					\
ERROR_WRAP("error - invalid " SPEC ": ")

#define INVALID_FLAG_HEADER(FLAG)					\
ERROR_WRAP("error - invalid " FLAG " flag: ")

#define NO_FLAG_MESSAGE(FLAG)						\
ERROR_WRAP("error - no " FLAG " flag specified") MORE_INFO_MESSAGE

#endif	/* MYSQL_SEED_MYSQL_SEED_INPUT_H_ */
