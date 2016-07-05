#ifndef MYSQL_SEED_STRING_STRING_UTILS
#define MYSQL_SEED_STRING_STRING_UTILS


/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <stddef.h>			/* size_t */
#include <unistd.h>			/* ssize_t */
#include <stdint.h>			/* u/intmax_t, UINT16/32/64_MAX */
#include <stdbool.h>			/* bool */
#include "utils/word_utils.h"		/* WORD_SIZE */
#include "string/ascii_utils.h"		/* ascii helper macros, groups, sets */
#include "string/string_macros.h"	/* string helper macros */

#if   (UINTMAX_MAX == UINT64_MAX)
#	define UINT_DIGIT_COUNT_MAX 20u
#elif (UINTMAX_MAX == UINT32_MAX)
#	define UINT_DIGIT_COUNT_MAX 10u
#elif (UINTMAX_MAX == UINT16_MAX)
#	define UINT_DIGIT_COUNT_MAX 5u
#else
#	include <stdio.h>	/* sprintf, snprintf */
#	undef UINT_DIGIT_COUNT_MAX
#endif	/* if (UINTMAX_MAX == UINT64_MAX) */


#if   (UINTPTR_MAX == UINT64_MAX)
#	define POINTER_DIGIT_COUNT_MAX 20u
#	define POINTER_ID_LENGTH_MAX   10u
#elif (UINTPTR_MAX == UINT32_MAX)
#	define POINTER_DIGIT_COUNT_MAX 10u
#	define POINTER_ID_LENGTH_MAX   5u
#elif (UINTPTR_MAX == UINT16_MAX)
#	define POINTER_DIGIT_COUNT_MAX 5u
#	define POINTER_ID_LENGTH_MAX   3u
#elif (UINTPTR_MAX == UINT8_MAX)
#	define POINTER_DIGIT_COUNT_MAX 3u
#	define POINTER_ID_LENGTH_MAX   2u
#else
#	undef  POINTER_DIGIT_COUNT_MAX
#	undef  POINTER_ID_LENGTH_MAX
#endif	/* if (UINTPTR_MAX == UINT64_MAX) */


/* constants
 *─────────────────────────────────────────────────────────────────────────── */
/* UINT8_MAX  = 255			(3  digits) */
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
#ifdef UINT_DIGIT_COUNT_MAX
extern const uintmax_t ten_pow_map[UINT_DIGIT_COUNT_MAX];
#endif	/* ifdef (UINT_DIGIT_COUNT_MAX) */

#ifdef POINTER_ID_LENGTH_MAX
extern const uintptr_t ninety_five_pow_map[POINTER_ID_LENGTH_MAX];
#endif


/* helper functions
 *─────────────────────────────────────────────────────────────────────────── */
#ifdef UINT_DIGIT_COUNT_MAX
inline unsigned int
uint_digit_count(uintmax_t n)
{
#	if (UINT_DIGIT_COUNT_MAX >= 20u)
	if (n < 10000000000llu) {
#	endif	/* if (UINT_DIGIT_COUNT_MAX >= 20u) */

#		if (UINT_DIGIT_COUNT_MAX >= 10u)
		if (n < 100000llu) {
#		endif	/* if (UINT_DIGIT_COUNT_MAX >= 10u) */

			if (n < 1000llu) {
				if (n < 100llu) {
					if (n < 10llu) {
						return  1u;
					} else {
						return  2u;
					}
				} else {
					return  3u;
				}
			} else {
				if (n < 10000llu) {
					return  4u;
				} else {
					return  5u;
				}
			}

#		if (UINT_DIGIT_COUNT_MAX >= 10u)
		} else {
			if (n < 100000000llu) {
				if (n < 10000000llu) {
					if (n < 1000000llu) {
						return  6u;
					} else {
						return  7u;
					}
				} else {
					return  8u;
				}
			} else {
				if (n < 1000000000llu)	{
					return  9u;
				} else {
					return 10u;
				}
			}
		}
#		endif	/* if (UINT_DIGIT_COUNT_MAX >= 10u) */

#	if (UINT_DIGIT_COUNT_MAX >= 20u)
	} else {
		if (n < 1000000000000000llu) {
			if (n < 1000000000000llu) {
				if (n < 100000000000llu) {
					return 11u;
				} else {
					return 12u;
				}
			} else {
				if (n < 10000000000000llu) {
					return 13llu;
				} else {
					if (n < 100000000000000llu) {
						return 14u;
					} else {
						return 15u;
					}
				}
			}
		} else {
			if (n < 100000000000000000llu) {
				if (n < 10000000000000000llu) {
					return 16u;
				} else {
					return 17u;
				}
			} else {
				if (n < 1000000000000000000llu) {
					return 18llu;
				} else {
					if (n < 10000000000000000000llu) {
						return 19u;
					} else {
						return 20u;
					}
				}
			}
		}
	}
}
#	endif	/* if (UINT_DIGIT_COUNT_MAX >= 20u) */

inline void
do_put_uint(char *restrict buffer,
	    uintmax_t n)
{
	while (1)
	{
		*buffer = (char) ASCII_DIGIT(n % 10llu);
		n /= 10llu;

		if (n == 0llu)
			return;

		--buffer;
	}
}
#endif	/* ifdef (UINT_DIGIT_COUNT_MAX) */



#ifdef POINTER_ID_LENGTH_MAX

/* returns log₉₅(ceil₉₅(ptr_n)), i.e. smallest count of ASCII printable
 * characters to encode a pointer cast to a numberic value */
inline unsigned int
pointer_id_length(const uintptr_t ptr_n)
{
#	if (POINTER_ID_LENGTH_MAX >= 10u)
	if (ptr_n < 7737809375lu) {
#	endif /* if (POINTER_ID_LENGTH_MAX >= 10u) */

#		if (POINTER_ID_LENGTH_MAX >= 5u)
		if (ptr_n < 9025lu) {
#		endif /* if (POINTER_ID_LENGTH_MAX >= 5u) */

			if (ptr_n < 95lu) {
				return 1u;
			} else {

#			if (POINTER_ID_LENGTH_MAX == 3u)
				if (ptr_n < 9025lu) {
#			endif /* if (POINTER_ID_LENGTH_MAX == 3u) */

					return 2u;

#			if (POINTER_ID_LENGTH_MAX == 3u)
				} else {
					return 3u;
				}
#			endif /* if (POINTER_ID_LENGTH_MAX == 3u) */

			}

#		if (POINTER_ID_LENGTH_MAX >= 5u)
		} else {
			if (ptr_n < 81450625lu) {
				if (ptr_n < 857375lu) {
					return 3u;

				} else {
					return 4u;
				}
			} else {
				return 5u;
			}
		}
#		endif /* if (POINTER_ID_LENGTH_MAX >= 5u) */

#	if (POINTER_ID_LENGTH_MAX >= 10u)
	} else {

		if (ptr_n < 6634204312890625lu) {
			if (ptr_n < 735091890625lu) {
				return 6u;
			} else {
				if (ptr_n < 69833729609375lu) {
					return 7u;
				} else {
					return 8u;
				}
			}
		} else {
			if (ptr_n < 630249409724609375lu) {
				return 9u;
			} else {
				return 10u;
			}
		}
	}
#	endif /* if (POINTER_ID_LENGTH_MAX >= 10u) */
}

inline void
#else
inline char *
#endif /* ifdef POINTER_ID_LENGTH_MAX */
do_put_pointer_id(char *restrict buffer,
		  uintptr_t ptr_n)
{
	while (1) {
		*buffer = ASCII_PRINTABLES[ptr_n % ASCII_PRINTABLE_CNT];
		ptr_n  /= ASCII_PRINTABLE_CNT;

		if (ptr_n == 0lu) {
#ifdef POINTER_ID_LENGTH_MAX
			return;
#else
			return buffer;
#endif /* ifdef POINTER_ID_LENGTH_MAX */
		}

		--buffer;
	};
}




/* top-level functions
 *─────────────────────────────────────────────────────────────────────────── */
inline char *
put_uint(char *restrict buffer,
	 uintmax_t n)
{
#ifdef UINT_DIGIT_COUNT_MAX
	char *const restrict until_ptr = buffer + uint_digit_count(n);

	do_put_uint(until_ptr - 1l,
		    n);

	return until_ptr;
#else
	return buffer + sprintf(buffer,
				"%zu",
				n);
#endif /* ifdef(UINT_DIGIT_COUNT_MAX) */
}


inline char *
put_uint_length(char *restrict buffer,
		uintmax_t n,
		const size_t length)
{
#ifdef UINT_DIGIT_COUNT_MAX
	if (length == 0lu)
		return buffer;

	const unsigned int count_digits = uint_digit_count(n);

	char *restrict until_ptr;

	if (count_digits > length) {

		until_ptr = buffer + length;

		n /= ten_pow_map[count_digits - length];
	} else {

		until_ptr = buffer + count_digits;
	}

	do_put_uint(until_ptr - 1l,
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
#endif /* ifdef (UINT_DIGIT_COUNT_MAX) */
}

inline char *
put_uint_until(char *restrict buffer,
	       const uintmax_t n,
	       char *const restrict until_ptr)
{
	return (buffer > until_ptr)
	     ? until_ptr
	     : put_uint_length(buffer,
			       n,
			       until_ptr - buffer);
}

inline char *
put_int(char *restrict buffer,
	intmax_t n)
{
	if (n < 0l) {
		PUT_CHAR(buffer, '-');
		n = -n;
	}

	return put_uint(buffer,
			n);
}

inline char *
put_int_length(char *restrict buffer,
	       intmax_t n,
	       unsigned int length)
{
	if (length == 0u)
		return buffer;

	if (n < 0l) {
		PUT_CHAR(buffer, '-');
		--length;
		n = -n;
	}

	return put_uint_length(buffer,
			       n,
			       length);
}

inline char *
put_int_until(char *restrict buffer,
	      const intmax_t n,
	      char *const restrict until_ptr)
{
	return (buffer > until_ptr)
	     ? until_ptr
	     : put_int_length(buffer,
			      n,
			      until_ptr - buffer);
}

inline char *
put_pointer_id(char *restrict buffer,
	       void *const restrict pointer)
{
#ifdef POINTER_ID_LENGTH_MAX
	char *const restrict until_ptr = buffer
				       + pointer_id_length((uintptr_t) pointer);

	do_put_pointer_id(until_ptr - 1l,
			  (uintptr_t) pointer);

	return until_ptr;
#else
	char id_buffer[64lu];

	char *const restrict last_ptr = &id_buffer[63lu];

	char *restrict id_ptr = do_put_pointer_id(last_ptr,
						  (uintptr_t) pointer);

	while (1) {
		*buffer = *id_ptr;
		++buffer;

		if (id_ptr == last_ptr)
			return buffer;

		++id_ptr;
	}
#endif /* ifdef POINTER_ID_LENGTH_MAX */
}

inline char *
put_pointer_id_length(char *restrict buffer,
		      void *const restrict pointer,
		      const unsigned int length)
{
	if (length == 0lu)
		return buffer;
#ifdef POINTER_ID_LENGTH_MAX

	uintptr_t ptr_n = (uintptr_t) pointer;

	const unsigned int length_id = pointer_id_length(ptr_n);

	char *restrict until_ptr;

	if (length_id > length) {

		until_ptr = buffer + length;

		ptr_n /= ninety_five_pow_map[length_id - length];
	} else {

		until_ptr = buffer + length_id;
	}

	do_put_pointer_id(until_ptr - 1l,
			  ptr_n);

	return until_ptr;
#else
	char id_buffer[64lu];

	char *const restrict last_ptr = &id_buffer[63lu];

	char *restrict id_ptr = do_put_pointer_id(last_ptr,
						  (uintptr_t) pointer);

	const size_t length_id = last_ptr - id_ptr;

	char *const restrict until_ptr = id_ptr + ((length_id > length)
						   ? length
						   : length_id);

	while (1) {
		*buffer = *id_ptr;
		++buffer;

		if (id_ptr == last_ptr)
			return buffer;

		++id_ptr;
	}
#endif /* ifdef POINTER_ID_LENGTH_MAX */
}

inline char *
put_pointer_id_until(char *restrict buffer,
		     void *const restrict pointer,
		     char *const restrict until_ptr)
{
	return (buffer > until_ptr)
	     ? until_ptr
	     : put_pointer_id_length(buffer,
				     pointer,
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

	union WordPatternPtr ptr = (union WordPatternPtr) buffer;

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

	union WordPatternPtr base = ptr;

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
	default: /* fall through */;
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
	for (const char *restrict ptr = string; limit > 0l; ++ptr, --limit)
		if ((*ptr) == '\0')
			return ptr - string;

	return limit;
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

extern inline bool
parse_uint(uintmax_t *const restrict n,
	   char *restrict string);

#endif	/* MYSQL_SEED_STRING_STRING_UTILS */
