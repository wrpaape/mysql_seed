#ifndef MYSQL_SEED_MYSQL_SEED_HELP_H_
#define MYSQL_SEED_MYSQL_SEED_HELP_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "system/exit_utils.h"		/* exit utils, string macros */

/* help messages
 *─────────────────────────────────────────────────────────────────────────── */
#define HELP_USAGE_MESSAGE						\
UNDERLINE_WRAP("USAGE:") "\n"						\
"\t" ANSI_WRAP(BRIGHT, "mysql_seed [OPTIONS] <INPUTS>") "\n\n"		\
UNDERLINE_WRAP("OPTIONS:") "\n"						\
"\t" ANSI_WRAP(BRIGHT, "-h, --help")   "\tprints this message\n"	\
"\t" ANSI_WRAP(BRIGHT, "-c, --create") "\tcreates a seed file\n"	\
"\t" ANSI_WRAP(BRIGHT, "-r, --run")    "\truns a seed file\n"

#define HELP_CREATE_MESSAGE "OOGA BOOGA"

#define HELP_RUN_MESSAGE "BOOGITY BOO"


/* help dispatch
 *─────────────────────────────────────────────────────────────────────────── */

#endif /* ifndef MYSQL_SEED_MYSQL_SEED_HELP_H_ */
