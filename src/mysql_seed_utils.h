#ifndef MYSQL_SEED_MYSQL_SEED_UTILS_H_
#define MYSQL_SEED_MYSQL_SEED_UTILS_H_


/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <stddef.h>	/* size_t, ssize_t */
#include <stdint.h>	/* SIZE_MAX, UINT16/32/64_MAX */
#include <stdbool.h>	/* bool */

#undef DIGIT_COUNT_MAX

#if (SIZE_MAX == UINT64_MAX)
#	define DIGIT_COUNT_MAX 20u
#elif (SIZE_MAX == UINT32_MAX)
#	define DIGIT_COUNT_MAX 10u
#elif (SIZE_MAX == UINT16_MAX)
#	define DIGIT_COUNT_MAX 5u
#else
#	include <stdio.h>	/* sprintf */
#endif	/* if (SIZE_MAX == UINT64_MAX) */


/* constants
 *─────────────────────────────────────────────────────────────────────────── */
/* UINT16_MAX = 65535			(5  digits) */
/* UINT32_MAX = 4294967295		(10 digits) */
/* UINT64_MAX = 18446744073709551615	(20 digits) */

/* global variables
 *─────────────────────────────────────────────────────────────────────────── */
#ifdef (DIGIT_COUNT_MAX)
extern size_t ten_pow_map[DIGIT_COUNT_MAX + 1u];
#endif	/* ifdef (DIGIT_COUNT_MAX) */


/* helper macros
 *─────────────────────────────────────────────────────────────────────────── */
#define ASCII_DIGIT(DIGIT) ((char) (((unsigned int) (DIGIT)) | 48u))

#define PUT_CHAR(PTR, CHAR)	\
do {				\
	*(PTR) = CHAR;		\
	++(PTR);		\
} while (0)

#define PUTS_CLOSE(PTR)		\
do {				\
	PUT_CHAR(PTR, '\n');	\
	PUT_CHAR(PTR, '\0');	\
} while (0)



/* helper functions
 *─────────────────────────────────────────────────────────────────────────── */
#ifdef (DIGIT_COUNT_MAX)
inline unsigned int
digit_count(size_t n)
{
#	if (DIGIT_COUNT_MAX >= 20u)
	if (n < 10000000000lu) {
#	endif	/* if (DIGIT_COUNT_MAX >= 20u) */

#		if (DIGIT_COUNT_MAX >= 10u)
		if (n < 100000lu) {
#		endif	/* if (DIGIT_COUNT_MAX >= 10u) */

			if (n < 1000lu) {
				if (n < 100lu) {
					if (n < 10lu) {
						return  1u;
					} else {
						return  2u;
					}
				} else {
					return  3u;
				}
			} else {
				if (n < 10000lu) {
					return  4u;
				} else {
					return  5u;
				}
			}

#		if (DIGIT_COUNT_MAX >= 10u)
		} else {
			if (n < 100000000lu) {
				if (n < 10000000lu) {
					if (n < 1000000lu) {
						return  6u;
					} else {
						return  7u;
					}
				} else {
					return  8u;
				}
			} else {
				if (n < 1000000000lu)	{
					return  9u;
				} else {
					return 10u;
				}
			}
		}
#		endif	/* if (DIGIT_COUNT_MAX >= 10u) */

#	if (DIGIT_COUNT_MAX >= 20u)
	} else {
		if (n < 1000000000000000lu) {
			if (n < 1000000000000lu) {
				if (n < 100000000000lu) {
					return 11u;
				} else {
					return 12u;
				}
			} else {
				if (n < 10000000000000lu) {
					return 13lu;
				} else {
					if (n < 100000000000000lu) {
						return 14u;
					} else {
						return 15u;
					}
				}
			}
		} else {
			if (n < 100000000000000000lu) {
				if (n < 10000000000000000lu) {
					return 16u;
				} else {
					return 17u;
				}
			} else {
				if (n < 1000000000000000000lu) {
					return 18lu;
				} else {
					if (n < 10000000000000000000lu) {
						return 19u;
					} else {
						return 20u;
					}
				}
			}
		}
	}
}
#	endif	/* if (DIGIT_COUNT_MAX >= 20u) */

inline void
do_put_digits(char *restrict buffer,
	      size_t n)
{
	while (1)
	{
		*buffer = ASCII_DIGIT(n % 10lu);

		if (n < 10lu)
			return;

		n /= 10lu;

		--buffer;
	}
}
#endif	/* ifdef (DIGIT_COUNT_MAX) */


/* top-level functions
 *─────────────────────────────────────────────────────────────────────────── */
inline char *
put_digits(char *restrict buffer,
	   size_t n)
{
#ifdef (DIGIT_COUNT_MAX)
	char *const restrict end_ptr = buffer + digit_count(n);

	do_put_digits(end_ptr - 1l,
		      n);

	return end_ptr;
#else
	return buffer + sprintf(buffer,
				"%zu",
				n);
#endif /* ifdef(DIGIT_COUNT_MAX) */
}


inline char *
put_digits_length(char *restrict buffer,
		  size_t n,
		  const size_t length)
{
#ifdef (DIGIT_COUNT_MAX)

	if (length == 0lu)
		return buffer;

	const unsigned int count_digits = digit_count(n);

	char *restrict end_ptr;

	if (((size_t) count_digits) > length) {

		end_ptr = buffer + length;

		n /= ten_pow_map[count_digits - length];
	} else {

		end_ptr = buffer + count_digits;
	}

	do_put_digits(end_ptr - 1l,
		      n);

	return end_ptr;
#else
	const size_t count_digits = (size_t) snprintf(buffer,
						      length,
						      "%zu",
						      n);

	return buffer + ((count_digits > length)
			 ? length
			 : count_digits);
#endif /* ifdef (DIGIT_COUNT_MAX) */
}

inline char *
put_digits_until(char *restrict buffer,
		 const size_t n,
		 char *const restrict end_ptr)
{
	return (buffer > end_ptr)
	     ? end_ptr
	     : put_digits_length(buffer,
				 n,
				 buffer - end_ptr);
}

inline char *
put_number(char *restrict buffer,
	   ssize_t n)
{
	if (n < 0l) {
		PUT_CHAR(buffer, '-');
		n = -n;
	}

	return put_digits(buffer,
			  n);
}

inline char *
put_number_length(char *restrict buffer,
		  ssize_t n,
		  const size_t length)
{
	if (length == 0lu)
		return buffer;

	if (n < 0l) {
		PUT_CHAR(buffer, '-');
		n = -n;
	}

	return put_digits_length(buffer,
				 n,
				 length - 1lu);
}

inline char *
put_number_until(char *restrict buffer,
		 const ssize_t n,
		 char *const restrict end_ptr)
{
	return (buffer > end_ptr)
	     ? end_ptr
	     : put_number_length(buffer,
				 n,
				 buffer - end_ptr);
}


inline char *
put_string(char *restrict buffer,
	   const char *restrict string)
{
	while (*string != '\0') {
		*buffer = *string;
		++buffer;
		++string;
	}

	return buffer;
}

inline size_t
string_length(const char *const restrict string)
{
	register const char *restrict ptr = string;

	while (*ptr != '\0')
		++ptr;

	return ptr - string;
}


inline char *
put_string_length(char *restrict buffer,
		  const char *restrict string,
		  size_t length)
{
	while ((length > 0lu) && (*string != '\0')) {
		*buffer = *string;
		++buffer;
		++string;
		--length;
	}

	return buffer;
}

inline char *
put_string_until(char *restrict buffer,
		 const char *restrict string,
		 char *const restrict end_ptr)
{
	while ((buffer != end_ptr) && (*string != '\0')) {
		*buffer = *string;
		++buffer;
		++string;
	}

	return buffer;
}

inline bool
strings_equal(const char *restrict string1,
	      const char *restrict string2)
{
	while (1) {
		if (*string1 != *string2)
			return false;

		if (*string1 == '\0')
			return true;

		++string1;
		++string2;
	}
}


#endif	/* MYSQL_SEED_MYSQL_SEED_UTILS_H_ */
