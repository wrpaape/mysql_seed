#include "mysql_seed_count_string.h"

#define SIZE_1_9		18lu		/* (1 digit  + '\0') * 9 */
#define SIZE_10_99		270lu		/* (2 digits + '\0') * 90 */
#define SIZE_100_999		3600lu		/* (3 digits + '\0') * 900 */
#define SIZE_1000_9999		45000lu		/* (3 digits + '\0') * 9000 */
#define SIZE_10000_99999	540000lu	/* (4 digits + '\0') * 90000 */
#define SIZE_100000_999999	6300000lu	/* (5 digits + '\0') * 900000 */
#define SIZE_1000000_9999999	72000000lu	/* (6 digits + '\0') * 9000000 */

#define SIZE_1_99	(SIZE_1_9	+ SIZE_10_99)
#define SIZE_1_999	(SIZE_1_99	+ SIZE_100_999)
#define SIZE_1_9999	(SIZE_1_999	+ SIZE_1000_9999)
#define SIZE_1_99999	(SIZE_1_9999	+ SIZE_10000_99999)
#define SIZE_1_999999	(SIZE_1_99999	+ SIZE_100000_999999)
#define SIZE_1_9999999	(SIZE_1_999999	+ SIZE_1000000_9999999)

#define UPTO_MAX 99999999lu

extern inline void
count_string_destroy(char *restrict *string);

char **
count_string_create(char *const *restrict log_ptr,
		    const size_t upto)
{
	char **string_ptrs;
	char *digits;


	const enum CountStringAllocateFlag
	csa_status = count_string_allocate(&string_ptrs,
					   &digits,
					   upto);

	if (csa_status != CSA_SUCCESS) {
		csa_failure(log_ptr,
			    csa_status,
			    upto);
		return NULL;
	}




}

void
csa_failure(char *const *restrict log_ptr,
	    const enum CountStringAllocateFlag status,
	    const size_t upto)
{

	char *restrict ptr = *log_ptr;

	ptr = put_string(ptr,
			 "failed to allocate count string memory for 'upto' "
			 "of ");

	ptr = put_digits(ptr,
			 upto);

	ptr = put_string(ptr,
			 " ('UPTO_MAX' = " #UPTO_MAX ")\n"
			 "reason:\n"):


	switch (status) {

	case CSA_FAILURE_UPTO_MAX_EXCEEDED:
		ptr = put_string(ptr,
				 "'UPTO_MAX' exceeded\n\n");
		break;

	case CSA_FAILURE_OUT_OF_MEMORY:
		ptr = stpcpy(ptr,
				 "malloc failure (out of memory)\n\n");
		break;

	default:
		ptr = stpcpy(ptr,
				 "malloc failure (out of memory)\n\n");

		seed_exit_spec_init_failure(spec,
					    "unknown failure to allocate"
					    " count string memory");
	}

	if (spec->status == EXIT_SUCCESS)
		seed_exit_spec_init_failure(spec,
					    &message_buffer[0]);
}





/* allocates space for count string 'string_ptrs' and 'digits' buffer */
enum CountStringAllocateFlag
count_string_allocate(char *const *restrict *string_ptrs,
		      char *const *restrict digits,
		      const size_t upto)
{
	if (upto > UPTO_MAX)
		return CSA_FAILURE_UPTO_MAX_EXCEEDED;

	/* room for string ptrs + 1 (NULL terminator) */
	const size_t size_string_ptrs = sizeof(char *) * (upto + 1lu);

	size_t count_chars;

	if (upto < 10000lu) {
		if (upto < 100lu) {
			count_chars = (upto < 10lu)
				    ? (upto * 2lu)
				    : (upto * 3lu) + SIZE_1_99;
		} else {
			count_chars = (upto < 1000lu)
				    ? (upto * 4lu) + SIZE_1_999
				    : (upto * 5lu) + SIZE_1_9999;
		}
	} else {
		if (upto < 1000000lu) {
			count_chars = (upto < 100000lu)
				    ? (upto * 6lu) + SIZE_1_99999
				    : (upto * 7lu) + SIZE_1_999999;
		} else {
			count_chars = (upto < 10000000lu)
				    ? (upto * 8lu) + SIZE_1_9999999
				    : (upto * 9lu) + SIZE_1_99999999;
		}
	}

	*string_ptrs = malloc(size_string_ptrs
			      + (sizeof(char) * count_chars));

	if ((*string_ptrs) == NULL)
		return CSA_FAILURE_OUT_OF_MEMORY;

	*digits	= (*string_ptrs) + size_string_ptrs;

	return CSA_SUCCESS;
}


