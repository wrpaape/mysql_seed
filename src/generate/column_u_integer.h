#ifndef MYSQL_SEED_COLUMN_U_INTEGER_H_
#define MYSQL_SEED_COLUMN_U_INTEGER_H_

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "generate/counter.h"		      /* string/thread utils, Counter */
#include "generate/column_u_integer_random.h" /* randomized column builders */

/* worker thread entry points */
void
build_column_u_integer_fixed(void *arg);
void
build_column_u_integer_unique(void *arg);
void
build_column_u_integer_unique_group(void *arg);

#endif /* ifndef MYSQL_SEED_COLUMN_U_INTEGER_H_ */
