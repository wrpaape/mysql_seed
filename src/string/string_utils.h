#ifndef MYSQL_SEED_STRING_STRING_UTILS
#define MYSQL_SEED_STRING_STRING_UTILS


/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <stddef.h>			/* size_t */
#include <unistd.h>			/* ssize_t */
#include "utils/types/word_pattern.h"	/* WordPattern/Ptr, word_attrs */
#include "string/int_string_attrs.h"	/* integer string attributes */
#include "string/ptr_string_attrs.h"	/* pointer string attributes */
#include "string/ascii_utils.h"		/* bool, ascii macros, groups, sets */
#include "string/string_macros.h"	/* string helper macros */

#if !HAVE_INT_STRING_ATTRS
#	include <stdio.h>	/* sprintf, snprintf */
#	include <inttypes.h>	/* stroumax */
#	include <errno.h>	/* errno (checking return of stroumax) */
#endif	/* if !HAVE_INT_STRING_ATTRS */

/* global variables
 *─────────────────────────────────────────────────────────────────────────── */
#if HAVE_INT_STRING_ATTRS
extern const uintmax_t ten_pow_map[DIGIT_COUNT_UINTMAX_MAX];
#endif	/* if HAVE_INT_STRING_ATTRS */

#if HAVE_PTR_STRING_ATTRS
extern const uintptr_t ninety_five_pow_map[LENGTH_MAX_POINTER_ID];
#endif


/* helper macros
 *─────────────────────────────────────────────────────────────────────────── */
#define PUT_STRING_WIDTH(PTR, STRING, WIDTH)				\
do {									\
	*((CharBuffer ## WIDTH *restrict) PTR)				\
	= *((const CharBuffer ## WIDTH *const restrict) STRING);	\
	PTR = (char *restrict)						\
	      (((CharBuffer ## WIDTH *restrict) PTR) + 1l);		\
} while (0)

/* helper functions
 *─────────────────────────────────────────────────────────────────────────── */
#if HAVE_INT_STRING_ATTRS
inline unsigned int
uint_digit_count(uintmax_t n)
{
#	if (DIGIT_COUNT_UINTMAX_MAX >= 20u)
	if (n < 10000000000llu) {
#	endif	/* if (DIGIT_COUNT_UINTMAX_MAX >= 20u) */

#		if (DIGIT_COUNT_UINTMAX_MAX >= 10u)
		if (n < 100000llu) {
#		endif	/* if (DIGIT_COUNT_UINTMAX_MAX >= 10u) */

#			if (DIGIT_COUNT_UINTMAX_MAX >= 5u)
			if (n < 1000llu) {
#			endif	/* if (DIGIT_COUNT_UINTMAX_MAX >= 5u) */

				if (n < 100llu) {
					if (n < 10llu) {
						return  1u;
					} else {
						return  2u;
					}
				} else {
					return  3u;
				}

#			if (DIGIT_COUNT_UINTMAX_MAX >= 5u)
			} else {
				if (n < 10000llu) {
					return  4u;
				} else {
					return  5u;
				}
			}
#			endif	/* if (DIGIT_COUNT_UINTMAX_MAX >= 5u) */

#		if (DIGIT_COUNT_UINTMAX_MAX >= 10u)
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
#		endif	/* if (DIGIT_COUNT_UINTMAX_MAX >= 10u) */

#	if (DIGIT_COUNT_UINTMAX_MAX >= 20u)
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
#	endif	/* if (DIGIT_COUNT_UINTMAX_MAX >= 20u) */

inline void
do_put_uint(char *restrict buffer,
	    uintmax_t n)
{
	while (1)
	{
		*buffer = (char) DIGIT_TO_ASCII(n % 10llu);
		n /= 10llu;

		if (n == 0llu)
			return;

		--buffer;
	}
}
#endif	/* if HAVE_INT_STRING_ATTRS */



#if HAVE_PTR_STRING_ATTRS

/* returns log₉₅(ceil₉₅(ptr_n)), i.e. smallest count of ASCII printable
 * characters to encode a pointer cast to a numberic value */
inline unsigned int
pointer_id_length(const uintptr_t ptr_n)
{
#	if (LENGTH_MAX_POINTER_ID >= 10u)
	if (ptr_n < 7737809375lu) {
#	endif /* if (LENGTH_MAX_POINTER_ID >= 10u) */

#		if (LENGTH_MAX_POINTER_ID >= 5u)
		if (ptr_n < 9025lu) {
#		endif /* if (LENGTH_MAX_POINTER_ID >= 5u) */

			if (ptr_n < 95lu) {
				return 1u;
			} else {

#			if (LENGTH_MAX_POINTER_ID == 3u)
				if (ptr_n < 9025lu) {
#			endif /* if (LENGTH_MAX_POINTER_ID == 3u) */

					return 2u;

#			if (LENGTH_MAX_POINTER_ID == 3u)
				} else {
					return 3u;
				}
#			endif /* if (LENGTH_MAX_POINTER_ID == 3u) */

			}

#		if (LENGTH_MAX_POINTER_ID >= 5u)
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
#		endif /* if (LENGTH_MAX_POINTER_ID >= 5u) */

#	if (LENGTH_MAX_POINTER_ID >= 10u)
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
#	endif /* if (LENGTH_MAX_POINTER_ID >= 10u) */
}

inline void
#else
inline char *
#endif /* if HAVE_PTR_STRING_ATTRS */
do_put_pointer_id(char *restrict buffer,
		  uintptr_t ptr_n)
{
	while (1) {
		*buffer = ASCII_PRINTABLES[ptr_n % ASCII_PRINTABLE_CNT];
		ptr_n  /= ASCII_PRINTABLE_CNT;

		if (ptr_n == 0lu) {
#if HAVE_PTR_STRING_ATTRS
			return;
#else
			return buffer;
#endif /* if HAVE_PTR_STRING_ATTRS */
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
#if HAVE_INT_STRING_ATTRS
	char *const restrict until_ptr = buffer + uint_digit_count(n);

	do_put_uint(until_ptr - 1l,
		    n);

	return until_ptr;
#else
	return buffer + sprintf(buffer,
				"%zu",
				n);
#endif /* if HAVE_INT_STRING_ATTRS */
}


inline char *
put_uint_length(char *restrict buffer,
		uintmax_t n,
		const size_t length)
{
#if HAVE_INT_STRING_ATTRS
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
#endif /* if HAVE_INT_STRING_ATTRS */
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
#if HAVE_PTR_STRING_ATTRS
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
#endif /* if HAVE_PTR_STRING_ATTRS */
}

inline char *
put_pointer_id_length(char *restrict buffer,
		      void *const restrict pointer,
		      const unsigned int length)
{
	if (length == 0lu)
		return buffer;
#if HAVE_PTR_STRING_ATTRS

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
#endif /* if HAVE_PTR_STRING_ATTRS */
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

inline char *
put_char_times(char *const restrict buffer,
	       const char byte,
	       const size_t times)
{
#if (WORD_SIZE == 1lu)
	while (times > 0lu) {
		*buffer = byte;
		++buffer;
		--times;
	}

	return buffer;
#else
	union WordPatternPtr ptr = (union WordPatternPtr) buffer;

	size_t length_words   = DIV_WORD_SIZE(times);
	const size_t rem_size = REM_WORD_SIZE(times);

	if (length_words == 0lu)
		switch (rem_size) {
#		if (WORD_SIZE > 15lu)
		case 15: *(ptr.string++) = byte;
#		endif /* if (WORD_SIZE > 15) */
#		if (WORD_SIZE > 14lu)
		case 14: *(ptr.string++) = byte;
#		endif /* if (WORD_SIZE > 14) */
#		if (WORD_SIZE > 13lu)
		case 13: *(ptr.string++) = byte;
#		endif /* if (WORD_SIZE > 13) */
#		if (WORD_SIZE > 12lu)
		case 12: *(ptr.string++) = byte;
#		endif /* if (WORD_SIZE > 12) */
#		if (WORD_SIZE > 11lu)
		case 11: *(ptr.string++) = byte;
#		endif /* if (WORD_SIZE > 11) */
#		if (WORD_SIZE > 10lu)
		case 10: *(ptr.string++) = byte;
#		endif /* if (WORD_SIZE > 10) */
#		if (WORD_SIZE > 9lu)
		case 9:  *(ptr.string++) = byte;
#		endif /* if (WORD_SIZE > 9) */
#		if (WORD_SIZE > 8lu)
		case 8:  *(ptr.string++) = byte;
#		endif /* if (WORD_SIZE > 8) */
#		if (WORD_SIZE > 7lu)
		case 7:  *(ptr.string++) = byte;
#		endif /* if (WORD_SIZE > 7) */
#		if (WORD_SIZE > 6lu)
		case 6:  *(ptr.string++) = byte;
#		endif /* if (WORD_SIZE > 6) */
#		if (WORD_SIZE > 5lu)
		case 5:  *(ptr.string++) = byte;
#		endif /* if (WORD_SIZE > 5) */
#		if (WORD_SIZE > 4lu)
		case 4:  *(ptr.string++) = byte;
#		endif /* if (WORD_SIZE > 4) */
#		if (WORD_SIZE > 3lu)
		case 3:  *(ptr.string++) = byte;
#		endif /* if (WORD_SIZE > 3) */
#		if (WORD_SIZE > 2lu)
		case 2:  *(ptr.string++) = byte;
#		endif /* if (WORD_SIZE > 2) */
		case 1:  *(ptr.string++) = byte;
		default: return ptr.string;
		}

	union WordPatternPtr base = ptr;

	*(ptr.string++) = byte;
	*(ptr.string++) = byte;
#		if (WORD_SIZE > 2lu)
	*(ptr.string++) = byte;
#		if (WORD_SIZE > 3lu)
	*(ptr.string++) = byte;
#		if (WORD_SIZE > 4lu)
	*(ptr.string++) = byte;
#		if (WORD_SIZE > 5lu)
	*(ptr.string++) = byte;
#		if (WORD_SIZE > 6lu)
	*(ptr.string++) = byte;
#		if (WORD_SIZE > 7lu)
	*(ptr.string++) = byte;
#		if (WORD_SIZE > 8lu)
	*(ptr.string++) = byte;
#		if (WORD_SIZE > 9lu)
	*(ptr.string++) = byte;
#		if (WORD_SIZE > 10lu)
	*(ptr.string++) = byte;
#		if (WORD_SIZE > 11lu)
	*(ptr.string++) = byte;
#		if (WORD_SIZE > 12lu)
	*(ptr.string++) = byte;
#		if (WORD_SIZE > 13lu)
	*(ptr.string++) = byte;
#		if (WORD_SIZE > 14lu)
	*(ptr.string++) = byte;
#		if (WORD_SIZE > 15lu)
	*(ptr.string++) = byte;
#		endif /* if (WORD_SIZE > 15lu) */
#		endif /* if (WORD_SIZE > 14lu) */
#		endif /* if (WORD_SIZE > 13lu) */
#		endif /* if (WORD_SIZE > 12lu) */
#		endif /* if (WORD_SIZE > 11lu) */
#		endif /* if (WORD_SIZE > 10lu) */
#		endif /* if (WORD_SIZE > 9lu) */
#		endif /* if (WORD_SIZE > 8lu) */
#		endif /* if (WORD_SIZE > 7lu) */
#		endif /* if (WORD_SIZE > 6lu) */
#		endif /* if (WORD_SIZE > 5lu) */
#		endif /* if (WORD_SIZE > 4lu) */
#		endif /* if (WORD_SIZE > 3lu) */
#		endif /* if (WORD_SIZE > 2lu) */

	switch (rem_size) {
	case 1:  *(ptr.size_1++)  = *(base.size_1);  break;
#		if (WORD_SIZE > 2lu)
	case 2:  *(ptr.size_2++)  = *(base.size_2);  break;
#		if (WORD_SIZE > 3lu)
	case 3:  *(ptr.size_3++)  = *(base.size_3);  break;
#		if (WORD_SIZE > 4lu)
	case 4:  *(ptr.size_4++)  = *(base.size_4);  break;
#		if (WORD_SIZE > 5lu)
	case 5:  *(ptr.size_5++)  = *(base.size_5);  break;
#		if (WORD_SIZE > 6lu)
	case 6:  *(ptr.size_6++)  = *(base.size_6);  break;
#		if (WORD_SIZE > 7lu)
	case 7:  *(ptr.size_7++)  = *(base.size_7);  break;
#		if (WORD_SIZE > 8lu)
	case 8:  *(ptr.size_8++)  = *(base.size_8);  break;
#		if (WORD_SIZE > 9lu)
	case 9:  *(ptr.size_9++)  = *(base.size_9);  break;
#		if (WORD_SIZE > 10lu)
	case 10: *(ptr.size_10++) = *(base.size_10); break;
#		if (WORD_SIZE > 11lu)
	case 11: *(ptr.size_11++) = *(base.size_11); break;
#		if (WORD_SIZE > 12lu)
	case 12: *(ptr.size_12++) = *(base.size_12); break;
#		if (WORD_SIZE > 13lu)
	case 13: *(ptr.size_13++) = *(base.size_13); break;
#		if (WORD_SIZE > 14lu)
	case 14: *(ptr.size_14++) = *(base.size_14); break;
#		if (WORD_SIZE > 15lu)
	case 15: *(ptr.size_15++) = *(base.size_15);
#		endif /* if (WORD_SIZE > 15lu) */
#		endif /* if (WORD_SIZE > 14lu) */
#		endif /* if (WORD_SIZE > 13lu) */
#		endif /* if (WORD_SIZE > 12lu) */
#		endif /* if (WORD_SIZE > 11lu) */
#		endif /* if (WORD_SIZE > 10lu) */
#		endif /* if (WORD_SIZE > 9lu) */
#		endif /* if (WORD_SIZE > 8lu) */
#		endif /* if (WORD_SIZE > 7lu) */
#		endif /* if (WORD_SIZE > 6lu) */
#		endif /* if (WORD_SIZE > 5lu) */
#		endif /* if (WORD_SIZE > 4lu) */
#		endif /* if (WORD_SIZE > 3lu) */
#		endif /* if (WORD_SIZE > 2lu) */
	default: /* fall through */;
	}

	while (--length_words > 0lu)
		*(ptr.word++) = *(base.word);

	return ptr.string;
#endif /* if (WORD_SIZE == 1lu) */
}

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

inline char *
put_string_inspect(char *restrict buffer,
		   const char *restrict string,
		   size_t length)
{
	while (1) {
		if (*string == '\0')
			return buffer;

		if (length == 0lu) {
			PUT_STRING_WIDTH(buffer,
					 "...",
					 3);
			return buffer;
		}

		*buffer = *string;
		++buffer;
		++string;
		--length;
	}
}

inline int
string_compare(const char *restrict string1,
	       const char *restrict string2)
{
	int comparison;

	while (1) {
		comparison = (*string1) - (*string2);

		if ((*string1 == '\0') || (comparison != 0))
			return comparison;

		++string1;
		++string2;
	}
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
		if (*ptr == '\0')
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

		if (*ptr == '\0')
			return ptr - string + 1lu;

		++ptr;
		--limit;
	}
}

#if HAVE_INT_STRING_ATTRS
inline bool
do_parse_digits(uintmax_t *const restrict n,
		const char *restrict string,
		const unsigned int digit_count_max,
		const char *const restrict max_string)
{
	while (*string == '0') {
		++string;

		if (*string == '\0') {
			*n = 0llu;
			return true;
		}
	}

	if ((*string > '9' ) || (*string < '0' ))
		return false;

	const char *const restrict start_ptr = string;

	unsigned int count_digits = 1u;

	while (1) {
		++string;

		if (*string == '\0')
			break;

		if ((*string > '9') || (*string < '0'))
			return false;

		++count_digits;

		if (count_digits == digit_count_max) {

			if (string_compare(start_ptr,
					   max_string) > 0)
				return false;

			++string;

			if (*string != '\0')
				return false;

			break;
		}
	}

	--string;

	*n = (uintmax_t) ASCII_TO_DIGIT(*string);

	const uintmax_t *restrict pow_ptr	  = &ten_pow_map[1];

	const uintptr_t *const restrict until_ptr = &ten_pow_map[count_digits];


	while (pow_ptr < until_ptr) {

		--string;

		(*n) += (((uintmax_t) ASCII_TO_DIGIT(*string)) * (*pow_ptr));

		++pow_ptr;
	}

	return true;
}

inline char *
do_parse_digits_stop(uintmax_t *const restrict n,
		     char *restrict string,
		     const char stop,
		     const unsigned int digit_count_max,
		     const char *const restrict max_string)
{
	while (*string == '0') {
		++string;

		if ((*string == stop) || (*string == '\0')) {
			*n = 0llu;
			return string;
		}
	}

	if ((*string > '9' ) || (*string < '0' ))
		return NULL;

	const char *const restrict start_ptr = string;

	unsigned int count_digits = 1u;

	while (1) {
		++string;

		if ((*string == stop) || (*string == '\0'))
			break;

		if ((*string > '9') || (*string < '0'))
			return NULL;

		++count_digits;

		if (count_digits == digit_count_max) {

			if (string_compare(start_ptr,
					   max_string) > 0)
				return NULL;

			++string;

			if ((*string != stop) || (*string != '\0'))
				return NULL;

			break;
		}
	}

	char *const restrict stop_ptr = string;

	--string;

	*n = (uintmax_t) ASCII_TO_DIGIT(*string);

	const uintmax_t *restrict pow_ptr	  = &ten_pow_map[1];

	const uintptr_t *const restrict until_ptr = &ten_pow_map[count_digits];


	while (pow_ptr < until_ptr) {

		--string;

		(*n) += (((uintmax_t) ASCII_TO_DIGIT(*string)) * (*pow_ptr));

		++pow_ptr;
	}

	return stop_ptr;
}
#endif /* if HAVE_INT_STRING_ATTRS  */

inline bool
parse_uint(uintmax_t *const restrict n,
	   const char *restrict string)
{
#if HAVE_INT_STRING_ATTRS

	return do_parse_digits(n,
			       string,
			       DIGIT_COUNT_UINTMAX_MAX,
			       DIGIT_STRING_UINTMAX_MAX);
#else
	*n = strtoumax(string,
		       NULL,
		       10);

	return (*n != 0llu) || (errno != 0);
#endif /* if HAVE_INT_STRING_ATTRS  */
}

inline bool
parse_int(intmax_t *const restrict n,
	  const char *restrict string)
{
#if HAVE_INT_STRING_ATTRS
	if (*string == '-') {
		++string;

		if (do_parse_digits((uintmax_t *const restrict) n,
				    string,
				    DIGIT_COUNT_INTMAX_MIN,
				    DIGIT_STRING_INTMAX_MIN)) {
			*n = -(*n);
			return true;
		}

		return false;
	}

	return do_parse_digits((uintmax_t *const restrict) n,
			       string,
			       DIGIT_COUNT_INTMAX_MAX,
			       DIGIT_STRING_INTMAX_MAX);
#else
	*n = strtoimax(string,
		       NULL,
		       10);

	return (*n != 0ll) || (errno != 0);
#endif /* if HAVE_INT_STRING_ATTRS  */
}

inline char *
parse_uint_stop(uintmax_t *const restrict n,
		char *restrict string,
		const char stop)
{
#if HAVE_INT_STRING_ATTRS
	return do_parse_digits_stop(n,
				    string,
				    stop,
				    DIGIT_COUNT_UINTMAX_MAX,
				    DIGIT_STRING_UINTMAX_MAX);
#else
	char *restrict stop_ptr;

	*n = strtoumax(string,
		       &stop_ptr,
		       10);

	return (((*n != 0llu) || (errno != 0)) && (*stop_ptr == stop))
	     ? stop_ptr
	     : NULL;
#endif /* if HAVE_INT_STRING_ATTRS  */
}

inline char *
parse_int_stop(intmax_t *const restrict n,
	       char *restrict string,
	       const char stop)
{
#if HAVE_INT_STRING_ATTRS
	if (*string == '-') {
		++string;

		char *const restrict
		stop_ptr = do_parse_digits_stop((uintmax_t *const restrict) n,
						string,
						stop,
						DIGIT_COUNT_INTMAX_MIN,
						DIGIT_STRING_INTMAX_MIN);

		if (stop_ptr == NULL)
			return NULL;

		*n = -(*n);
		return stop_ptr;
	}

	return do_parse_digits_stop((uintmax_t *const restrict) n,
				    string,
				    stop,
				    DIGIT_COUNT_INTMAX_MAX,
				    DIGIT_STRING_INTMAX_MAX);
#else
	char *restrict stop_ptr;

	*n = strtoimax(string,
		       &stop_ptr,
		       10);

	return (((*n != 0ll) || (errno != 0)) && (*stop_ptr == stop))
	     ? stop_ptr
	     : NULL;
#endif /* if HAVE_INT_STRING_ATTRS  */
}

#endif	/* MYSQL_SEED_STRING_STRING_UTILS */
