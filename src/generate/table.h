#ifndef MYSQL_SEED_GENERATE_TABLE_H_
#define MYSQL_SEED_GENERATE_TABLE_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "generate/generator.h"	/* Table, string/thread utils */

inline size_t
table_size_contents(const struct Table *const restrict table)
{
	return 
}

void
build_table_header_exit_cleanup(void *arg);

/* thread worker entry
 *─────────────────────────────────────────────────────────────────────────── */
void
build_table_header(void *arg);

#endif /* ifndef MYSQL_SEED_GENERATE_TABLE_H_ */
