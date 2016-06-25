#include "mysql_seed_count_string.h"



extern inline struct CountString *
count_string_create(const size_t upto);

extern inline void
count_string_destroy(struct CountString *restrict string);



void
log_csa_failure(const enum CountStringAllocateFlag status,
		const size_t upto)
{

	seed_log_handle_lock();

	seed_log_append_string("failed to allocate count string memory for "
			       "'upto' of ");

	seed_log_append_digits(upto);

	seed_log_append_string(" ('UPTO_MAX' = " EXPAND_STRINGIFY(UPTO_MAX)
			       ")\n"
			       "reason:\n\t");
	switch (status) {

	case CSA_FAILURE_UPTO_MAX_EXCEEDED:
		seed_log_append_string("'UPTO_MAX' exceeded\n\n");
		break;

	case CSA_FAILURE_OUT_OF_MEMORY:
		seed_log_append_string("malloc failure (out of memory)\n\n");
		break;

	default:
		seed_log_append_string("unknown\n\n");
	}

	seed_log_handle_unlock();
}


/* allocates space for count string 'string' */
enum CountStringAllocateFlag
count_string_allocate(struct CountString *restrict *const restrict string,
		      const size_t upto)
{
	if (upto > UPTO_MAX)
		return CSA_FAILURE_UPTO_MAX_EXCEEDED;

	const size_t count_chars = sizeof(char) * count_string_char_count(upto);

	*string = malloc(sizeof(struct CountString)
			 + (sizeof(char) * count_chars));

	if ((*string) == NULL)
		return CSA_FAILURE_OUT_OF_MEMORY;

	(*string)->digits      = (char *restrict) ((*string) + 1l);
	(*string)->count_chars = count_chars;

	return CSA_SUCCESS;
}
