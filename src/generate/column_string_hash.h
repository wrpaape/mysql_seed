#ifndef MYSQL_SEED_COLUMN_STRING_HASH_H_
#define MYSQL_SEED_COLUMN_STRING_HASH_H_

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "generate/generator.h"	/* string/thread utils */
#include "time/time_utils.h"	/* for seeding hash state */

void
build_column_string_hash(void *arg);


#endif /* ifndef MYSQL_SEED_COLUMN_STRING_HASH_H_ */
