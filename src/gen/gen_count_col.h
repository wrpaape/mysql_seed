#ifndef MYSQL_SEED_GEN_GEN_COUNT_COL_H_
#define MYSQL_SEED_GEN_GEN_COUNT_COL_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "gen/gen_count_string.h"	/* count_string, parallel utils */


/* macro constants
 *─────────────────────────────────────────────────────────────────────────── */
#define FIELD_LENGTH_MAX 64lu	/* mysql max field name length */
#define BASE_LENGTH_MAX  128lu


/* failure messages
 *─────────────────────────────────────────────────────────────────────────── */
#define UPTO_MAX_EXCEEDED_FAILURE_MESSAGE "'UPTO_MAX' exceeded\n"

#define CC_ALLOC_FAILURE_MESSAGE_BEGIN					\
"\n\nfailed to allocate memory for count column having 'field' of "

#define CC_ALLOC_FAILURE_MESSAGE_MIDDLE_1				\
" with string length, 'field_length', of "

#define CC_ALLOC_FAILURE_MESSAGE_MIDDLE_2				\
" ('FIELD_LENGTH_MAX' = " EXPAND_STRINGIFY(BASE_LENGTH_MAX) ", 'base' of "

#define CC_ALLOC_FAILURE_MESSAGE_MIDDLE_3				\
" with string length, 'base_length', of "

#define CC_ALLOC_FAILURE_MESSAGE_MIDDLE_4				\
" ('BASE_LENGTH_MAX' = " EXPAND_STRINGIFY(BASE_LENGTH_MAX) ", and 'upto' of "

#define CC_ALLOC_FAILURE_MESSAGE_MIDDLE_5				\
" ('UPTO_MAX' = " EXPAND_STRINGIFY(UPTO_MAX) ")\nreason:\n\t"


/* struct declarations, typedefs
 *─────────────────────────────────────────────────────────────────────────── */
struct CountColumn {
	const size_t field_length;
	const size_t base_length;
	const char *field;
	const char *base;
	const char *column;
};

inline void
count_column_log_alloc_failure(struct CountColumn *const restrict column,
			       const char *const restrict failure)
{
	seed_log_handle_lock();

	seed_log_append_string(CC_ALLOC_FAILURE_MESSAGE_BEGIN);

	seed_log_append_string(column->base);
	seed_log_append_digits(upto);

	seed_log_append_string(CS_ALLOC_FAILURE_MESSAGE_MIDDLE);

	seed_log_append_string(failure);

	seed_log_handle_unlock();
}

#endif	/* ifndef MYSQL_SEED_GEN_GEN_COUNT_COL_H_ */
