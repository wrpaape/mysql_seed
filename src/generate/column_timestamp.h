#ifndef MYSQL_SEED_GENERATE_COLUMN_TIMESTAMP_H_
#define MYSQL_SEED_GENERATE_COLUMN_TIMESTAMP_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "generate/generator.h" /* Column, thread utils */
#include "time/time_string.h"	/* time, string utils */


/* worker thread entry points */
void
build_column_timestamp_fixed(void *arg);
void
build_column_timestamp_unique(void *arg);
void
build_column_timestamp_unique_group(void *arg);

#endif /* ifndef MYSQL_SEED_GENERATE_COLUMN_TIMESTAMP_H_ */
