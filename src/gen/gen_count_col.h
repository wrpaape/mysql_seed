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

#define GCC_ALLOC_FAILURE_MESSAGE_BEGIN					\
"\n\nfailed to allocate memory for count column having 'field' of "

#define GCC_ALLOC_FAILURE_MESSAGE_MIDDLE_1				\
" with string length, 'field_length', of "

#define GCC_ALLOC_FAILURE_MESSAGE_MIDDLE_2				\
" ('FIELD_LENGTH_MAX' = " EXPAND_STRINGIFY(BASE_LENGTH_MAX) ", 'base' of "

#define GCC_ALLOC_FAILURE_MESSAGE_MIDDLE_3				\
" with string length, 'base_length', of "

#define GCC_ALLOC_FAILURE_MESSAGE_MIDDLE_4				\
" ('BASE_LENGTH_MAX' = " EXPAND_STRINGIFY(BASE_LENGTH_MAX) ", and 'upto' of "

#define GCC_ALLOC_FAILURE_MESSAGE_MIDDLE_5				\
" ('UPTO_MAX' = " EXPAND_STRINGIFY(UPTO_MAX) ")\nreason:\n\t"


/* struct declarations, typedefs
 *─────────────────────────────────────────────────────────────────────────── */
struct CountColumn {
	size_t upto;
	const char *column;
	struct StringTuple field;
	struct StringTuple base;
};

/* misc helper functions
 *─────────────────────────────────────────────────────────────────────────── */
/* count of chars required for "1", "2", ... "upto" null-terminated ascii
 * strings plus a final '\0' character to indicate end */
inline void
count_column_size_count_string(const size_t upto)
{
#ifdef LARGE_UPTO_MAX
	if (upto < MAG_4_MIN) {
#endif	/*  ifdef LARGE_UPTO_MAX */
		if (upto < MAG_2_MIN) {
			return (upto < MAG_1_MIN)
			     ? (SIZE_MAG_0_STR * upto)
			     : (SIZE_MAG_0_1_STR + (SIZE_MAG_1_STR
						    * (upto - MAG_0_MAX)));
		} else {
			return (upto < MAG_3_MIN)
			     ? (SIZE_MAG_0_2_STR + (SIZE_MAG_2_STR
						    * (upto - MAG_1_MAX)))
			     : (SIZE_MAG_0_3_STR + (SIZE_MAG_3_STR
						    * (upto - MAG_2_MAX)));
		}
#ifdef LARGE_UPTO_MAX
	} else {
		if (upto < MAG_6_MIN) {
			return (upto < MAG_5_MIN)
			     ? (SIZE_MAG_0_4_STR + (SIZE_MAG_4_STR
						    * (upto - MAG_3_MAX)))
			     : (SIZE_MAG_0_5_STR + (SIZE_MAG_5_STR
						    * (upto - MAG_4_MAX)));
		} else {
			return (upto < MAG_7_MIN)
			     ? (SIZE_MAG_0_6_STR + (SIZE_MAG_6_STR
						    * (upto - MAG_5_MAX)))
			     : (SIZE_MAG_0_7_STR + (SIZE_MAG_7_STR
						    * (upto - MAG_6_MAX)));
		}
	}
#endif	/*  ifdef LARGE_UPTO_MAX */
}

inline void
count_column_log_alloc_failure(struct CountColumn *const restrict column,
			       const char *const restrict failure)
{
	seed_log_handle_lock();

	seed_log_append_string(GCC_ALLOC_FAILURE_MESSAGE_BEGIN);

	seed_log_append_string(column->field.string);

	seed_log_append_string(CS_ALLOC_FAILURE_MESSAGE_MIDDLE_1);

	seed_log_append_digits(column->field.length);

	seed_log_append_string(CS_ALLOC_FAILURE_MESSAGE_MIDDLE_2);

	seed_log_append_string(column->base.string);

	seed_log_append_string(CS_ALLOC_FAILURE_MESSAGE_MIDDLE_3);

	seed_log_append_digits(column->base.length);

	seed_log_append_string(CS_ALLOC_FAILURE_MESSAGE_MIDDLE_4);

	seed_log_append_digits(column->upto);

	seed_log_append_string(failure);

	seed_log_handle_unlock();
}

#endif	/* ifndef MYSQL_SEED_GEN_GEN_COUNT_COL_H_ */
