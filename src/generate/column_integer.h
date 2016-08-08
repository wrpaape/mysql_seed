#ifndef MYSQL_SEED_COLUMN_INTEGER_H_
#define MYSQL_SEED_COLUMN_INTEGER_H_

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "generate/counter.h"	/* string/thread utils, Counter */

/* worker thread entry point */
void
build_column_integer_unique(void *arg);

#endif /* ifndef MYSQL_SEED_COLUMN_INTEGER_H_ */
