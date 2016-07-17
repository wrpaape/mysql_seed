#ifndef MYSQL_SEED_GEN_GEN_COUNT_COLUMN_H_
#define MYSQL_SEED_GEN_GEN_COUNT_COLUMN_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "gen/gen_count_string.h"	/* CountString, parallelization utils */


/* macro constants
 *─────────────────────────────────────────────────────────────────────────── */
#define FIELD_LENGTH_MAX 64lu	/* mysql max field name length */
#define BASE_LENGTH_MAX  128lu


/* failure messages
 *─────────────────────────────────────────────────────────────────────────── */
#define UPTO_MAX_EXCEEDED_FAILURE_MESSAGE "'UPTO_MAX' exceeded\n"

#define GCC_ALLOC_FAILURE_MESSAGE_1					\
"\n\nfailed to allocate memory for count column having 'field' of "

#define GCC_ALLOC_FAILURE_MESSAGE_2					\
" with string length, 'field_length', of "

#define GCC_ALLOC_FAILURE_MESSAGE_3					\
" ('FIELD_LENGTH_MAX' = " EXPAND_STRINGIFY(BASE_LENGTH_MAX) ", 'base' of "

#define GCC_ALLOC_FAILURE_MESSAGE_4					\
" with string length, 'base_length', of "

#define GCC_ALLOC_FAILURE_MESSAGE_5					\
" ('BASE_LENGTH_MAX' = " EXPAND_STRINGIFY(BASE_LENGTH_MAX) ", and 'upto' of "

#define GCC_ALLOC_FAILURE_MESSAGE_6					\
" ('UPTO_MAX' = " EXPAND_STRINGIFY(UPTO_MAX) ")\nreason:\n\t"


/* struct declarations, typedefs
 *─────────────────────────────────────────────────────────────────────────── */
struct CountColumn {
	struct CountString *count_string;
	char *field;
	char *base;
	char *rows;
	struct StringBuffer rows; /* pointer to StringBuffer returned */
};

/* misc helper functions
 *─────────────────────────────────────────────────────────────────────────── */


inline SeedWorkerID
count_column_init(struct CountColumn *const restrict column,
		  struct CountString *const restrict count_string,
		  const char *const restrict field_string,
		  const char *const restrict base_string)
{
	column->count_string = count_string;

	return seed_worker_spawn_awaitable(&count_column_do_init,
					   string);
}

inline void
count_column_log_alloc_failure(struct CountColumn *const restrict column,
			       const char *const restrict failure)
{
	seed_log_handle_lock();

	seed_log_append_string(GCC_ALLOC_FAILURE_MESSAGE_1);

	seed_log_append_string(column->field.string);

	seed_log_append_string(CS_ALLOC_FAILURE_MESSAGE_2);

	seed_log_append_digits(column->field.length);

	seed_log_append_string(CS_ALLOC_FAILURE_MESSAGE_3);

	seed_log_append_string(column->base.string);

	seed_log_append_string(CS_ALLOC_FAILURE_MESSAGE_4);

	seed_log_append_digits(column->base.length);

	seed_log_append_string(CS_ALLOC_FAILURE_MESSAGE_5);

	seed_log_append_digits(column->upto);

	seed_log_append_string(failure);

	seed_log_handle_unlock();
}

#endif	/* ifndef MYSQL_SEED_GEN_GEN_COUNT_COLUMN_H_ */
