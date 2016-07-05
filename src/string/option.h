#ifndef MYSQL_SEED_STRING_OPTION_H_
#define MYSQL_SEED_STRING_OPTION_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "string/string_utils.h"	/* string utils, macros, ascii utils */

/* typedefs, struct declarations
 *─────────────────────────────────────────────────────────────────────────── */


struct Option {
	const char flag;
	const char *rem_alias;
};

struct OptionMap {
	size_t max_length;
};

#endif /* ifndef MYSQL_SEED_STRING_OPTION_H_ */
