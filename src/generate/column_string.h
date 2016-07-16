#ifndef MYSQL_SEED_GENERATE_COLUMN_STRING_H_
#define MYSQL_SEED_GENERATE_COLUMN_STRING_H_


/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "generate/counter.h"	/* string/thread utils, Counter */


/* worker thread entry point */
void
build_column_string_base(void *arg);


#endif /* ifndef MYSQL_SEED_GENERATE_COLUMN_STRING_H_ */
