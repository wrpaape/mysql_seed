#ifndef MYSQL_SEED_MYSQL_SEED_UTILS_H_
#define MYSQL_SEED_MYSQL_SEED_UTILS_H_


/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <stddef.h>	/* size_t */
#include <stdint.h>	/* SIZE_MAX, UINT16/32/64_MAX */

#if (SIZE_MAX > UINT64_MAX)
#include <stdio.h>	/* sprintf */
#endif	/* if (SIZE_MAX > UINT64_MAX) */


/* constants
 *─────────────────────────────────────────────────────────────────────────── */
/* UINT16_MAX = 65535			(5  digits) */
/* UINT32_MAX = 4294967295		(10 digits) */
/* UINT64_MAX = 18446744073709551615	(20 digits) */



/* ascii helper macros
 *─────────────────────────────────────────────────────────────────────────── */
#define ASCII_DIGIT(DIGIT) ((char) (((unsigned int) (DIGIT)) | 48u))


/* helper functions
 *─────────────────────────────────────────────────────────────────────────── */
#if (SIZE_MAX <= UINT64_MAX)
inline unsigned int
digit_count(size_t num)
{
#	if (SIZE_MAX > UINT32_MAX)
	if (num < 10000000000lu) {
#	endif	/* if (SIZE_MAX > UINT32_MAX) */

#		if (SIZE_MAX > UINT16_MAX)
		if (num < 100000lu) {
#		endif	/* if (SIZE_MAX > UINT16_MAX) */

			if (num < 1000lu) {
				if (num < 100lu) {
					if (num < 10lu) {
						return  1u;
					} else {
						return  2u;
					}
				} else {
					return  3u;
				}
			} else {
				if (num < 10000lu) {
					return  4u;
				} else {
					return  5u;
				}
			}

#		if (SIZE_MAX > UINT16_MAX)
		} else {
			if (num < 100000000lu) {
				if (num < 10000000lu) {
					if (num < 1000000lu) {
						return  6u;
					} else {
						return  7u;
					}
				} else {
					return  8u;
				}
			} else {
				if (num < 1000000000lu)	{
					return  9u;
				} else {
					return 10u;
				}
			}
		}
#		endif	/* if (SIZE_MAX > UINT16_MAX) */

#	if (SIZE_MAX > UINT32_MAX)
	} else {
		if (num < 1000000000000000lu) {
			if (num < 1000000000000lu) {
				if (num < 100000000000lu) {
					return 11u;
				} else {
					return 12u;
				}
			} else {
				if (num < 10000000000000lu) {
					return 13lu;
				} else {
					if (num < 100000000000000lu) {
						return 14u;
					} else {
						return 15u;
					}
				}
			}
		} else {
			if (num < 100000000000000000lu) {
				if (num < 10000000000000000lu) {
					return 16u;
				} else {
					return 17u;
				}
			} else {
				if (num < 1000000000000000000lu) {
					return 18lu;
				} else {
					if (num < 10000000000000000000lu) {
						return 19u;
					} else {
						return 20u;
					}
				}
			}
		}
	}
}
#	endif	/* if (SIZE_MAX > UINT32_MAX) */
#endif	/* if (SIZE_MAX <= UINT64_MAX) */



/* top-level functions
 *─────────────────────────────────────────────────────────────────────────── */
inline char *
put_digits(char *restrict buffer,
	   size_t num)
{
#if (SIZE_MAX > UINT64_MAX)
	return buffer + sprintf(buffer, "%zu", num);
#else
	char *const restrict end_ptr = buffer + digit_count(num);

	buffer = end_ptr - 1l;

	while (1)
	{
		*buffer = ASCII_DIGIT(num % 10lu);

		if (num < 10lu)
			return end_ptr;

		num /= 10lu;

		--buffer;
	}
#endif
}



#endif	/* MYSQL_SEED_MYSQL_SEED_UTILS_H_ */
