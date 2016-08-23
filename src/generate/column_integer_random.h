#ifndef MYSQL_SEED_GENERATE_COLUMN_INTEGER_RANDOM_H_
#define MYSQL_SEED_GENERATE_COLUMN_INTEGER_RANDOM_H_

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "random/random_generator.h"	/* random generator API */
#include "generate/generator.h"		/* string/parallelization utils */

/* worker thread entry points */
void
build_column_integer_random(void *arg);
void
build_column_integer_random_group(void *arg);
void
build_column_integer_random_from(void *arg);
void
build_column_integer_random_from_group(void *arg);
void
build_column_integer_random_upto(void *arg);
void
build_column_integer_random_upto_group(void *arg);
void
build_column_integer_random_range(void *arg);
void
build_column_integer_random_range_group(void *arg);

#endif /* ifndef MYSQL_SEED_GENERATE_COLUMN_INTEGER_RANDOM_H_ */
