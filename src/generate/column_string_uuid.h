#ifndef MYSQL_SEED_GENERATE_COLUMN_STRING_UUID_H_
#define MYSQL_SEED_GENERATE_COLUMN_STRING_UUID_H_

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "uuid/uuid_utils.h"		/* uuid_state, uuid_string_init */
#include "generate/generator.h"		/* generator components */

/* macro constants
 * ────────────────────────────────────────────────────────────────────────── */
#define UUID_TYPE_STRING   "CHAR(36)"
#define UUID_TYPE_NN_WIDTH 8
#define UUID_TYPE_WIDTH	   9
#define SET_UUID_TYPE(PTR)						\
SET_STRING_WIDTH(PTR, UUID_TYPE_STRING, UUID_TYPE_WIDTH)

void
build_column_string_uuid(void *arg);

#endif /* ifndef MYSQL_SEED_GENERATE_COLUMN_STRING_UUID_H_ */
