#ifndef MYSQL_SEED_MYSQL_SEED_UTILS_H_
#define MYSQL_SEED_MYSQL_SEED_UTILS_H_


/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <stddef.h>			/* size_t */
#include <unistd.h>			/* ssize_t */
#include <stdint.h>			/* SIZE_MAX, UINT16/32/64_MAX */
#include <stdbool.h>			/* bool */
#include "mysql_seed_string_macros.h"	/* string helper macros */

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


/* copy string of a fixed size
 *─────────────────────────────────────────────────────────────────────────── */
typedef char CharBuffer1;
typedef struct CharBuffer2  { char chars[ 2]; } CharBuffer2;
typedef struct CharBuffer3  { char chars[ 3]; } CharBuffer3;
typedef struct CharBuffer4  { char chars[ 4]; } CharBuffer4;
typedef struct CharBuffer5  { char chars[ 5]; } CharBuffer5;
typedef struct CharBuffer6  { char chars[ 6]; } CharBuffer6;
typedef struct CharBuffer7  { char chars[ 7]; } CharBuffer7;
typedef struct CharBuffer8  { char chars[ 8]; } CharBuffer8;
typedef struct CharBuffer9  { char chars[ 9]; } CharBuffer9;
typedef struct CharBuffer10 { char chars[10]; } CharBuffer10;
typedef struct CharBuffer11 { char chars[11]; } CharBuffer11;
typedef struct CharBuffer12 { char chars[12]; } CharBuffer12;
typedef struct CharBuffer13 { char chars[13]; } CharBuffer13;
typedef struct CharBuffer14 { char chars[14]; } CharBuffer14;
typedef struct CharBuffer15 { char chars[15]; } CharBuffer15;
typedef struct CharBuffer16 { char chars[16]; } CharBuffer16;


/* global variables
 *─────────────────────────────────────────────────────────────────────────── */
#ifdef DIGIT_COUNT_MAX
extern size_t ten_pow_map[DIGIT_COUNT_MAX];
#endif	/* ifdef (DIGIT_COUNT_MAX) */




/* helper functions
 *─────────────────────────────────────────────────────────────────────────── */
#ifdef DIGIT_COUNT_MAX
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
#ifdef DIGIT_COUNT_MAX
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
		  const unsigned int length)
{
#ifdef DIGIT_COUNT_MAX

	if (length == 0lu)
		return buffer;

	const unsigned int count_digits = digit_count(n);

	char *restrict end_ptr;

	if (count_digits > length) {

		end_ptr = buffer + length;

		n /= ten_pow_map[count_digits - length];
	} else {

		end_ptr = buffer + count_digits;
	}

	do_put_digits(end_ptr - 1l,
		      n);

	return end_ptr;
#else
	const unsigned int count_digits = snprintf(buffer,
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
				 end_ptr - buffer);
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
		  unsigned int length)
{
	if (length == 0u)
		return buffer;

	if (n < 0l) {
		PUT_CHAR(buffer, '-');
		--length;
		n = -n;
	}

	return put_digits_length(buffer,
				 n,
				 length);
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
				 end_ptr - buffer);
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

inline size_t
string_length(const char *const restrict string)
{
	register const char *restrict ptr = string;

	while (*ptr != '\0')
		++ptr;

	return ptr - string;
}

inline ssize_t
string_length_limit(const char *const restrict string,
		    ssize_t limit)
{
	const char *restrict ptr = string;

	while (1) {
		if (limit < 0l)
			return limit;

		if ((*ptr) == '\0')
			return ptr - string;

		++ptr;
		--limit;
	}
}


#endif	/* MYSQL_SEED_MYSQL_SEED_UTILS_H_ */
