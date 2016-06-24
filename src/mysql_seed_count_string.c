#include "mysql_seed_count_string.h"





extern inline void
count_string_destroy(char *restrict *string);

struct CountString *
count_string_create(const size_t upto)
{

	struct CountString *restrict string;

	const enum CountStringAllocateFlag
	csa_status = count_string_allocate(&string,
					   upto);

	if (csa_status != CSA_SUCCESS) {
		log_csa_failure(csa_status,
				upto);
		return NULL;
	}

	return string;
}


void
log_csa_failure(const enum CountStringAllocateFlag status,
		const size_t upto)
{

	char *restrict ptr = *log_ptr;

	seed_log_append_string("failed to allocate count string memory for "
			       "'upto' of ");

	seed_log_append_digits(upto);

	seed_log_append_string(" ('UPTO_MAX' = " #UPTO_MAX ")\n"
			       "reason:\n\t");
	switch (status) {

	case CSA_FAILURE_UPTO_MAX_EXCEEDED:
		seed_log_append_string("'UPTO_MAX' exceeded\n\n");
		return;

	case CSA_FAILURE_OUT_OF_MEMORY:
		seed_log_append_string("malloc failure (out of memory)\n\n");
		return;

	default:
		seed_log_append_string("unknown\n\n");
	}
}


/* allocates space for count string 'string' */
enum CountStringAllocateFlag
count_string_allocate(struct CountString *const *restrict string,
		      const size_t upto)
{
	if (upto > UPTO_MAX)
		return CSA_FAILURE_UPTO_MAX_EXCEEDED;

	const size_t size_digits = sizeof(char) * count_string_char_count(upto);


	*string = malloc(sizeof(struct CountString) + size_digits);

	if ((*string) == NULL)
		return CSA_FAILURE_OUT_OF_MEMORY;

	(*string)->digits      = (char *restrict) ((*string) + 1l);
	(*string)->size_digits = size_digits;
	(*string)->upto	       = upto;

	return CSA_SUCCESS;
}
