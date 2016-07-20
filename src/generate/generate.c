#include "generate/generate.h"

/* Generator/DatbaseCounter operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
generator_counter_update(struct GeneratorCounter *const restrict generator,
			 struct DatabaseCounter *const restrict database);

/* print error messsage
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
generate_failure_malloc(void);

/* generate mode
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
mysql_seed_generate(const struct GeneratorCounter *const restrict count,
		    const struct DbSpec *restrict db_spec,
		    int *const restrict exit_status);
