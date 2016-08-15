#ifndef MYSQL_SEED_GENERATE_COLUMN_DATETIME_H_
#define MYSQL_SEED_GENERATE_COLUMN_DATETIME_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "generate/generator.h" /* Column, thread utils */
#include "time/time_string.h"	/* time, string utils */


/* worker thread entry points */
void
build_column_datetime_fixed(void *arg);
void
build_column_datetime_unique(void *arg);
void
build_column_datetime_unique_group(void *arg);

#endif /* ifndef MYSQL_SEED_GENERATE_COLUMN_DATETIME_H_ */
