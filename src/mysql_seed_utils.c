#include "mysql_seed_utils.h"

#if (SIZE_MAX <= UINT64_MAX)
extern inline unsigned int
digit_count(size_t num);
#endif	/* if (SIZE_MAX <= UINT64_MAX) */

extern inline char *
put_digits(char *restrict buffer,
	   size_t num);

