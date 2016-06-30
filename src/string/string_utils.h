#ifndef MYSQL_SEED_STRING_STRING_UTILS
#define MYSQL_SEED_STRING_STRING_UTILS


/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <stddef.h>			/* size_t */
#include <unistd.h>			/* ssize_t */
#include <stdint.h>			/* SIZE_MAX, UINT16/32/64_MAX */
#include <stdbool.h>			/* bool */
#include "string/string_macros.h"	/* string helper macros */
#include "utils/word_utils.h"		/* WORD_SIZE */

#if   (SIZE_MAX == UINT64_MAX)
#	define DIGIT_COUNT_MAX 20u
#elif (SIZE_MAX == UINT32_MAX)
#	define DIGIT_COUNT_MAX 10u
#elif (SIZE_MAX == UINT16_MAX)
#	define DIGIT_COUNT_MAX 5u
#else
#	include <stdio.h>	/* sprintf */
#	undef DIGIT_COUNT_MAX
#endif	/* if (SIZE_MAX == UINT64_MAX) */

/* constants
 *─────────────────────────────────────────────────────────────────────────── */
/* UINT16_MAX = 65535			(5  digits) */
/* UINT32_MAX = 4294967295		(10 digits) */
/* UINT64_MAX = 18446744073709551615	(20 digits) */


/* typedefs, struct declarations
 *─────────────────────────────────────────────────────────────────────────── */
/* for copying a string of a fixed size */
typedef char   CharBuffer1;
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


union WordPattern {
	word_t word;
	char string[WORD_SIZE];
	CharBuffer1  size_1;
#if (WORD_SIZE > 1lu)
	CharBuffer2  size_2;
#if (WORD_SIZE > 2lu)
	CharBuffer3  size_3;
#if (WORD_SIZE > 3lu)
	CharBuffer4  size_4;
#if (WORD_SIZE > 4lu)
	CharBuffer5  size_5;
#if (WORD_SIZE > 5lu)
	CharBuffer6  size_6;
#if (WORD_SIZE > 6lu)
	CharBuffer7  size_7;
#if (WORD_SIZE > 7lu)
	CharBuffer8  size_8;
#if (WORD_SIZE > 8lu)
	CharBuffer9  size_9;
#if (WORD_SIZE > 9lu)
	CharBuffer10 size_10;
#if (WORD_SIZE > 10lu)
	CharBuffer11 size_11;
#if (WORD_SIZE > 11lu)
	CharBuffer12 size_12;
#if (WORD_SIZE > 12lu)
	CharBuffer13 size_13;
#if (WORD_SIZE > 13lu)
	CharBuffer14 size_14;
#if (WORD_SIZE > 14lu)
	CharBuffer15 size_15;
#if (WORD_SIZE > 15lu)
	CharBuffer16 size_16;
#endif /* if (WORD_SIZE > 1) */
#endif /* if (WORD_SIZE > 2) */
#endif /* if (WORD_SIZE > 3) */
#endif /* if (WORD_SIZE > 4) */
#endif /* if (WORD_SIZE > 5) */
#endif /* if (WORD_SIZE > 6) */
#endif /* if (WORD_SIZE > 7) */
#endif /* if (WORD_SIZE > 8) */
#endif /* if (WORD_SIZE > 9) */
#endif /* if (WORD_SIZE > 10) */
#endif /* if (WORD_SIZE > 11) */
#endif /* if (WORD_SIZE > 12) */
#endif /* if (WORD_SIZE > 13) */
#endif /* if (WORD_SIZE > 14) */
#endif /* if (WORD_SIZE > 15) */
};

union WordPatternPtr {
	word_t *restrict word;
	char *restrict string;
	CharBuffer1  *restrict size_1;
#if (WORD_SIZE > 1lu)
	CharBuffer2  *restrict size_2;
#if (WORD_SIZE > 2lu)
	CharBuffer3  *restrict size_3;
#if (WORD_SIZE > 3lu)
	CharBuffer4  *restrict size_4;
#if (WORD_SIZE > 4lu)
	CharBuffer5  *restrict size_5;
#if (WORD_SIZE > 5lu)
	CharBuffer6  *restrict size_6;
#if (WORD_SIZE > 6lu)
	CharBuffer7  *restrict size_7;
#if (WORD_SIZE > 7lu)
	CharBuffer8  *restrict size_8;
#if (WORD_SIZE > 8lu)
	CharBuffer9  *restrict size_9;
#if (WORD_SIZE > 9lu)
	CharBuffer10 *restrict size_10;
#if (WORD_SIZE > 10lu)
	CharBuffer11 *restrict size_11;
#if (WORD_SIZE > 11lu)
	CharBuffer12 *restrict size_12;
#if (WORD_SIZE > 12lu)
	CharBuffer13 *restrict size_13;
#if (WORD_SIZE > 13lu)
	CharBuffer14 *restrict size_14;
#if (WORD_SIZE > 14lu)
	CharBuffer15 *restrict size_15;
#if (WORD_SIZE > 15lu)
	CharBuffer16 *restrict size_16;
#endif /* if (WORD_SIZE > 1) */
#endif /* if (WORD_SIZE > 2) */
#endif /* if (WORD_SIZE > 3) */
#endif /* if (WORD_SIZE > 4) */
#endif /* if (WORD_SIZE > 5) */
#endif /* if (WORD_SIZE > 6) */
#endif /* if (WORD_SIZE > 7) */
#endif /* if (WORD_SIZE > 8) */
#endif /* if (WORD_SIZE > 9) */
#endif /* if (WORD_SIZE > 10) */
#endif /* if (WORD_SIZE > 11) */
#endif /* if (WORD_SIZE > 12) */
#endif /* if (WORD_SIZE > 13) */
#endif /* if (WORD_SIZE > 14) */
#endif /* if (WORD_SIZE > 15) */
};


struct StringBuffer {
	const char *restrict string;
	size_t size;
};




/* helper macros
 *─────────────────────────────────────────────────────────────────────────── */
#define PUT_CHAR_BUFF(PTR, BUFFER, WIDTH)			\
do {								\
	*((CharBuff ## WIDTH *restrict) PTR)			\
	= (CharBuff ## WIDTH) BUFFER;				\
	PTR = (__type_of__(PTR))				\
	      (((CharBuff ## WIDTH *restrict) PTR) + 1l);	\
} while (0)


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
	char *const restrict until_ptr = buffer + digit_count(n);

	do_put_digits(until_ptr - 1l,
		      n);

	return until_ptr;
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

	char *restrict until_ptr;

	if (count_digits > length) {

		until_ptr = buffer + length;

		n /= ten_pow_map[count_digits - length];
	} else {

		until_ptr = buffer + count_digits;
	}

	do_put_digits(until_ptr - 1l,
		      n);

	return until_ptr;
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
		 char *const restrict until_ptr)
{
	return (buffer > until_ptr)
	     ? until_ptr
	     : put_digits_length(buffer,
				 n,
				 until_ptr - buffer);
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
		 char *const restrict until_ptr)
{
	return (buffer > until_ptr)
	     ? until_ptr
	     : put_number_length(buffer,
				 n,
				 until_ptr - buffer);
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
		 char *const restrict until_ptr)
{
	while ((buffer != until_ptr) && (*string != '\0')) {
		*buffer = *string;
		++buffer;
		++string;
	}

	return buffer;
}


#if (WORD_SIZE == 1lu)
inline char *
put_char_times(char *restrict buffer,
	       const char byte,
	       size_t times)
{
	while (times > 0lu) {
		*buffer = byte;
		++buffer;
		--times;
	}

	return buffer;
}

#else
inline char *
put_char_times(char *const restrict buffer,
	       const char byte,
	       const size_t times)
{

	WordPatternPtr ptr = (WordPatternPtr) buffer;

	size_t length_words   = DIV_WORD_SIZE(times);
	const size_t rem_size = REM_WORD_SIZE(times);

	if (length_words == 0lu)
		switch (rem_size) {
#	if (WORD_SIZE > 15lu)
		case 15: *(ptr.string++) = byte;
#	endif /* if (WORD_SIZE > 15) */
#	if (WORD_SIZE > 14lu)
		case 14: *(ptr.string++) = byte;
#	endif /* if (WORD_SIZE > 14) */
#	if (WORD_SIZE > 13lu)
		case 13: *(ptr.string++) = byte;
#	endif /* if (WORD_SIZE > 13) */
#	if (WORD_SIZE > 12lu)
		case 12: *(ptr.string++) = byte;
#	endif /* if (WORD_SIZE > 12) */
#	if (WORD_SIZE > 11lu)
		case 11: *(ptr.string++) = byte;
#	endif /* if (WORD_SIZE > 11) */
#	if (WORD_SIZE > 10lu)
		case 10: *(ptr.string++) = byte;
#	endif /* if (WORD_SIZE > 10) */
#	if (WORD_SIZE > 9lu)
		case 9:  *(ptr.string++) = byte;
#	endif /* if (WORD_SIZE > 9) */
#	if (WORD_SIZE > 8lu)
		case 8:  *(ptr.string++) = byte;
#	endif /* if (WORD_SIZE > 8) */
#	if (WORD_SIZE > 7lu)
		case 7:  *(ptr.string++) = byte;
#	endif /* if (WORD_SIZE > 7) */
#	if (WORD_SIZE > 6lu)
		case 6:  *(ptr.string++) = byte;
#	endif /* if (WORD_SIZE > 6) */
#	if (WORD_SIZE > 5lu)
		case 5:  *(ptr.string++) = byte;
#	endif /* if (WORD_SIZE > 5) */
#	if (WORD_SIZE > 4lu)
		case 4:  *(ptr.string++) = byte;
#	endif /* if (WORD_SIZE > 4) */
#	if (WORD_SIZE > 3lu)
		case 3:  *(ptr.string++) = byte;
#	endif /* if (WORD_SIZE > 3) */
#	if (WORD_SIZE > 2lu)
		case 2:  *(ptr.string++) = byte;
#	endif /* if (WORD_SIZE > 2) */
		case 1:  *(ptr.string++) = byte;
		default: return ptr.string;
		}

	WordPatternPtr base = ptr;

	*(ptr.string++) = byte;
	*(ptr.string++) = byte;
#	if (WORD_SIZE > 2lu)
	*(ptr.string++) = byte;
#	if (WORD_SIZE > 3lu)
	*(ptr.string++) = byte;
#	if (WORD_SIZE > 4lu)
	*(ptr.string++) = byte;
#	if (WORD_SIZE > 5lu)
	*(ptr.string++) = byte;
#	if (WORD_SIZE > 6lu)
	*(ptr.string++) = byte;
#	if (WORD_SIZE > 7lu)
	*(ptr.string++) = byte;
#	if (WORD_SIZE > 8lu)
	*(ptr.string++) = byte;
#	if (WORD_SIZE > 9lu)
	*(ptr.string++) = byte;
#	if (WORD_SIZE > 10lu)
	*(ptr.string++) = byte;
#	if (WORD_SIZE > 11lu)
	*(ptr.string++) = byte;
#	if (WORD_SIZE > 12lu)
	*(ptr.string++) = byte;
#	if (WORD_SIZE > 13lu)
	*(ptr.string++) = byte;
#	if (WORD_SIZE > 14lu)
	*(ptr.string++) = byte;
#	if (WORD_SIZE > 15lu)
	*(ptr.string++) = byte;
#	endif /* if (WORD_SIZE > 15lu) */
#	endif /* if (WORD_SIZE > 14lu) */
#	endif /* if (WORD_SIZE > 13lu) */
#	endif /* if (WORD_SIZE > 12lu) */
#	endif /* if (WORD_SIZE > 11lu) */
#	endif /* if (WORD_SIZE > 10lu) */
#	endif /* if (WORD_SIZE > 9lu) */
#	endif /* if (WORD_SIZE > 8lu) */
#	endif /* if (WORD_SIZE > 7lu) */
#	endif /* if (WORD_SIZE > 6lu) */
#	endif /* if (WORD_SIZE > 5lu) */
#	endif /* if (WORD_SIZE > 4lu) */
#	endif /* if (WORD_SIZE > 3lu) */
#	endif /* if (WORD_SIZE > 2lu) */

	switch (rem_size) {
	case 1:  *(ptr.size_1++)  = *(base.size_1);  break;
#	if (WORD_SIZE > 2lu)
	case 2:  *(ptr.size_2++)  = *(base.size_2);  break;
#	if (WORD_SIZE > 3lu)
	case 3:  *(ptr.size_3++)  = *(base.size_3);  break;
#	if (WORD_SIZE > 4lu)
	case 4:  *(ptr.size_4++)  = *(base.size_4);  break;
#	if (WORD_SIZE > 5lu)
	case 5:  *(ptr.size_5++)  = *(base.size_5);  break;
#	if (WORD_SIZE > 6lu)
	case 6:  *(ptr.size_6++)  = *(base.size_6);  break;
#	if (WORD_SIZE > 7lu)
	case 7:  *(ptr.size_7++)  = *(base.size_7);  break;
#	if (WORD_SIZE > 8lu)
	case 8:  *(ptr.size_8++)  = *(base.size_8);  break;
#	if (WORD_SIZE > 9lu)
	case 9:  *(ptr.size_9++)  = *(base.size_9);  break;
#	if (WORD_SIZE > 10lu)
	case 10: *(ptr.size_10++) = *(base.size_10); break;
#	if (WORD_SIZE > 11lu)
	case 11: *(ptr.size_11++) = *(base.size_11); break;
#	if (WORD_SIZE > 12lu)
	case 12: *(ptr.size_12++) = *(base.size_12); break;
#	if (WORD_SIZE > 13lu)
	case 13: *(ptr.size_13++) = *(base.size_13); break;
#	if (WORD_SIZE > 14lu)
	case 14: *(ptr.size_14++) = *(base.size_14); break;
#	if (WORD_SIZE > 15lu)
	case 15: *(ptr.size_15++) = *(base.size_15);
#	endif /* if (WORD_SIZE > 15lu) */
#	endif /* if (WORD_SIZE > 14lu) */
#	endif /* if (WORD_SIZE > 13lu) */
#	endif /* if (WORD_SIZE > 12lu) */
#	endif /* if (WORD_SIZE > 11lu) */
#	endif /* if (WORD_SIZE > 10lu) */
#	endif /* if (WORD_SIZE > 9lu) */
#	endif /* if (WORD_SIZE > 8lu) */
#	endif /* if (WORD_SIZE > 7lu) */
#	endif /* if (WORD_SIZE > 6lu) */
#	endif /* if (WORD_SIZE > 5lu) */
#	endif /* if (WORD_SIZE > 4lu) */
#	endif /* if (WORD_SIZE > 3lu) */
#	endif /* if (WORD_SIZE > 2lu) */
	default: /* fall through */
	}

	while (--length_words > 0lu)
		*(ptr.word++) = *(base.word);

	return ptr.string;
}
#endif /* if (WORD_SIZE == 1lu) */

inline char *
put_char_times_length(char *restrict buffer,
		      const char byte,
		      size_t times,
		      size_t length)
{
	return put_char_times(buffer,
			      byte,
			      (times > length) ? length : times);
}

inline char *
put_char_times_until(char *restrict buffer,
		     const char byte,
		     size_t times,
		     char *const restrict until_ptr)
{
	return put_char_times_length(buffer,
				     byte,
				     times,
				     until_ptr - buffer);
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

inline size_t
string_size(const char *const restrict string)
{
	return string_length(string) + 1lu;
}

/* returns size_t b/c string must be at least 1 byte, so 0 signals error */
inline size_t
string_size_limit(const char *const restrict string,
		  size_t limit)
{
	const char *restrict ptr = string;

	while (1) {
		if (limit == 0lu)
			return 0lu;

		if ((*ptr) == '\0')
			return ptr - string + 1lu;

		++ptr;
		--limit;
	}
}

#endif	/* MYSQL_SEED_STRING_STRING_UTILS */
