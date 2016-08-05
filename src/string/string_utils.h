#ifndef MYSQL_SEED_STRING_STRING_UTILS
#define MYSQL_SEED_STRING_STRING_UTILS


/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include <unistd.h>			/* ssize_t */
#include "memory/memory_put_array.h"	/* memory_put, size_t */
#include "utils/types/word_pattern.h"	/* WordPattern/Ptr, word_attrs */
#include "string/int_string_attrs.h"	/* integer string attributes */
#include "string/ptr_string_attrs.h"	/* pointer string attributes */
#include "string/ascii_utils.h"		/* bool, ascii macros, groups, sets */
#include "string/utf8_utils.h"		/* utf8 validators, utils */
#include "string/string_macros.h"	/* string helper macros */

#if !HAVE_INT_STRING_ATTRS
#	include <stdio.h>	/* sprintf, snprintf */
#	include <inttypes.h>	/* strtoumax */
#	include <errno.h>	/* errno (checking return of strtoumax) */
#endif	/* if !HAVE_INT_STRING_ATTRS */


/* typedefs, struct declarations
 *─────────────────────────────────────────────────────────────────────────── */
struct String {
	char *bytes;
	size_t length;
};

struct Stub {
	const char *bytes;
	unsigned int width; /* 1 - 16 bytes */
};

struct Label {
	char buffer[WIDTH_MAX_WIDTH];
	unsigned int width; /* 1 - 16 bytes */
};

struct StringInterval {
	char *restrict from;
	const char *restrict until;
};

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
#define CHAR_BUFFER_WIDTH(WIDTH) CharBuffer ## WIDTH

#define SET_STRING_WIDTH(PTR, STRING, WIDTH)				\
*((CHAR_BUFFER_WIDTH(WIDTH) *restrict) (PTR))				\
= *((const CHAR_BUFFER_WIDTH(WIDTH) *const restrict) (STRING))

#define PUT_STRING_WIDTH(PTR, STRING, WIDTH)				\
do {									\
	*((CHAR_BUFFER_WIDTH(WIDTH) *restrict) (PTR))			\
	= *((const CHAR_BUFFER_WIDTH(WIDTH) *const restrict) (STRING));	\
	PTR = (char *restrict)						\
	      (((CHAR_BUFFER_WIDTH(WIDTH) *restrict) PTR) + 1l);	\
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
	char *const restrict until = buffer + uint_digit_count(n);

	do_put_uint(until - 1l,
		    n);

	return until;
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

	char *restrict until;

	if (count_digits > length) {

		until = buffer + length;

		n /= ten_pow_map[count_digits - length];
	} else {

		until = buffer + count_digits;
	}

	do_put_uint(until - 1l,
		    n);

	return until;
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
	       char *const restrict until)
{
	return (buffer > until)
	     ? until
	     : put_uint_length(buffer,
			       n,
			       until - buffer);
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
	      char *const restrict until)
{
	return (buffer > until)
	     ? until
	     : put_int_length(buffer,
			      n,
			      until - buffer);
}

inline char *
put_pointer_id(char *restrict buffer,
	       void *const restrict pointer)
{
#if HAVE_PTR_STRING_ATTRS
	char *const restrict until = buffer
				       + pointer_id_length((uintptr_t) pointer);

	do_put_pointer_id(until - 1l,
			  (uintptr_t) pointer);

	return until;
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

	char *restrict until;

	if (length_id > length) {

		until = buffer + length;

		ptr_n /= ninety_five_pow_map[length_id - length];
	} else {

		until = buffer + length_id;
	}

	do_put_pointer_id(until - 1l,
			  ptr_n);

	return until;
#else
	char id_buffer[64lu];

	char *const restrict last_ptr = &id_buffer[63lu];

	char *restrict id_ptr = do_put_pointer_id(last_ptr,
						  (uintptr_t) pointer);

	const size_t length_id = last_ptr - id_ptr;

	char *const restrict until = id_ptr + ((length_id > length)
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
		     char *const restrict until)
{
	return (buffer > until)
	     ? until
	     : put_pointer_id_length(buffer,
				     pointer,
				     until - buffer);
}


inline void
copy_string(char *restrict buffer,
	    const char *restrict string)
{
	while (*string != '\0') {
		*buffer = *string;
		++buffer;
		++string;
	}
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
put_string_stop(char *restrict buffer,
		const char *restrict string)
{
	while (1) {
		*buffer = *string;
		++buffer;

		if (*string == '\0')
			return buffer;

		++string;
	}
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
		 char *const restrict until)
{
	while ((buffer != until) && (*string != '\0')) {
		*buffer = *string;
		++buffer;
		++string;
	}

	return buffer;
}

inline char *
put_string_size(char *restrict buffer,
		const char *const restrict string,
		const size_t size)
{
	return (char *) memory_put(buffer,
				   string,
				   size);
}

inline char *
put_string_size_until(char *restrict buffer,
		      const char *const restrict string,
		      const size_t size,
		      char *const restrict until)
{
	const size_t rem_size = until - buffer;

	return put_string_size(buffer,
			       string,
			       (size > rem_size) ? rem_size : size);
}

inline char *
put_string_width(char *const restrict buffer,
		 const char *const restrict string,
		 const unsigned int width)
{
	switch (width) {
	case  1u: *buffer = *string;
		  return buffer + 1l;

	case  2u:   *((CharBuffer2 *const restrict) buffer)
		  = *((CharBuffer2 *const restrict) string);
		  return buffer + 2l;

	case  3u:   *((CharBuffer3 *const restrict) buffer)
		  = *((CharBuffer3 *const restrict) string);
		  return buffer + 3l;

	case  4u:   *((CharBuffer4 *const restrict) buffer)
		  = *((CharBuffer4 *const restrict) string);
		  return buffer + 4l;

	case  5u:   *((CharBuffer5 *const restrict) buffer)
		  = *((CharBuffer5 *const restrict) string);
		  return buffer + 5l;

	case  6u:   *((CharBuffer6 *const restrict) buffer)
		  = *((CharBuffer6 *const restrict) string);
		  return buffer + 6l;

	case  7u:   *((CharBuffer7 *const restrict) buffer)
		  = *((CharBuffer7 *const restrict) string);
		  return buffer + 7l;

	case  8u:   *((CharBuffer8 *const restrict) buffer)
		  = *((CharBuffer8 *const restrict) string);
		  return buffer + 8l;

	case  9u:   *((CharBuffer9 *const restrict) buffer)
		  = *((CharBuffer9 *const restrict) string);
		  return buffer + 9l;

	case 10u:   *((CharBuffer10 *const restrict) buffer)
		  = *((CharBuffer10 *const restrict) string);
		  return buffer + 10l;

	case 11u:   *((CharBuffer11 *const restrict) buffer)
		  = *((CharBuffer11 *const restrict) string);
		  return buffer + 11l;

	case 12u:   *((CharBuffer12 *const restrict) buffer)
		  = *((CharBuffer12 *const restrict) string);
		  return buffer + 12l;

	case 13u:   *((CharBuffer13 *const restrict) buffer)
		  = *((CharBuffer13 *const restrict) string);
		  return buffer + 13l;

	case 14u:   *((CharBuffer14 *const restrict) buffer)
		  = *((CharBuffer14 *const restrict) string);
		  return buffer + 14l;

	case 15u:   *((CharBuffer15 *const restrict) buffer)
		  = *((CharBuffer15 *const restrict) string);
		  return buffer + 15l;

	default:    *((CharBuffer16 *const restrict) buffer)
		  = *((CharBuffer16 *const restrict) string);
		  return buffer + 16l;
	}
}

inline char *
put_stub(char *const restrict buffer,
	 const struct Stub *const restrict stub)
{
	return put_string_width(buffer,
				stub->bytes,
				stub->width);
}

inline char *
put_label(char *const restrict buffer,
	  const struct Label *const restrict label)
{
	return put_string_width(buffer,
				&label->buffer[0],
				label->width);
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
		     char *const restrict until)
{
	return put_char_times_length(buffer,
				     byte,
				     times,
				     until - buffer);
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

inline char *
put_octet_hex_lower(char *const restrict buffer,
		    const octet_t octet)
{
	switch (octet) {
	case   0u: SET_STRING_WIDTH(buffer, "00", 2); return buffer + 2l;
	case   1u: SET_STRING_WIDTH(buffer, "01", 2); return buffer + 2l;
	case   2u: SET_STRING_WIDTH(buffer, "02", 2); return buffer + 2l;
	case   3u: SET_STRING_WIDTH(buffer, "03", 2); return buffer + 2l;
	case   4u: SET_STRING_WIDTH(buffer, "04", 2); return buffer + 2l;
	case   5u: SET_STRING_WIDTH(buffer, "05", 2); return buffer + 2l;
	case   6u: SET_STRING_WIDTH(buffer, "06", 2); return buffer + 2l;
	case   7u: SET_STRING_WIDTH(buffer, "07", 2); return buffer + 2l;
	case   8u: SET_STRING_WIDTH(buffer, "08", 2); return buffer + 2l;
	case   9u: SET_STRING_WIDTH(buffer, "09", 2); return buffer + 2l;
	case  10u: SET_STRING_WIDTH(buffer, "0a", 2); return buffer + 2l;
	case  11u: SET_STRING_WIDTH(buffer, "0b", 2); return buffer + 2l;
	case  12u: SET_STRING_WIDTH(buffer, "0c", 2); return buffer + 2l;
	case  13u: SET_STRING_WIDTH(buffer, "0d", 2); return buffer + 2l;
	case  14u: SET_STRING_WIDTH(buffer, "0e", 2); return buffer + 2l;
	case  15u: SET_STRING_WIDTH(buffer, "0f", 2); return buffer + 2l;
	case  16u: SET_STRING_WIDTH(buffer, "10", 2); return buffer + 2l;
	case  17u: SET_STRING_WIDTH(buffer, "11", 2); return buffer + 2l;
	case  18u: SET_STRING_WIDTH(buffer, "12", 2); return buffer + 2l;
	case  19u: SET_STRING_WIDTH(buffer, "13", 2); return buffer + 2l;
	case  20u: SET_STRING_WIDTH(buffer, "14", 2); return buffer + 2l;
	case  21u: SET_STRING_WIDTH(buffer, "15", 2); return buffer + 2l;
	case  22u: SET_STRING_WIDTH(buffer, "16", 2); return buffer + 2l;
	case  23u: SET_STRING_WIDTH(buffer, "17", 2); return buffer + 2l;
	case  24u: SET_STRING_WIDTH(buffer, "18", 2); return buffer + 2l;
	case  25u: SET_STRING_WIDTH(buffer, "19", 2); return buffer + 2l;
	case  26u: SET_STRING_WIDTH(buffer, "1a", 2); return buffer + 2l;
	case  27u: SET_STRING_WIDTH(buffer, "1b", 2); return buffer + 2l;
	case  28u: SET_STRING_WIDTH(buffer, "1c", 2); return buffer + 2l;
	case  29u: SET_STRING_WIDTH(buffer, "1d", 2); return buffer + 2l;
	case  30u: SET_STRING_WIDTH(buffer, "1e", 2); return buffer + 2l;
	case  31u: SET_STRING_WIDTH(buffer, "1f", 2); return buffer + 2l;
	case  32u: SET_STRING_WIDTH(buffer, "20", 2); return buffer + 2l;
	case  33u: SET_STRING_WIDTH(buffer, "21", 2); return buffer + 2l;
	case  34u: SET_STRING_WIDTH(buffer, "22", 2); return buffer + 2l;
	case  35u: SET_STRING_WIDTH(buffer, "23", 2); return buffer + 2l;
	case  36u: SET_STRING_WIDTH(buffer, "24", 2); return buffer + 2l;
	case  37u: SET_STRING_WIDTH(buffer, "25", 2); return buffer + 2l;
	case  38u: SET_STRING_WIDTH(buffer, "26", 2); return buffer + 2l;
	case  39u: SET_STRING_WIDTH(buffer, "27", 2); return buffer + 2l;
	case  40u: SET_STRING_WIDTH(buffer, "28", 2); return buffer + 2l;
	case  41u: SET_STRING_WIDTH(buffer, "29", 2); return buffer + 2l;
	case  42u: SET_STRING_WIDTH(buffer, "2a", 2); return buffer + 2l;
	case  43u: SET_STRING_WIDTH(buffer, "2b", 2); return buffer + 2l;
	case  44u: SET_STRING_WIDTH(buffer, "2c", 2); return buffer + 2l;
	case  45u: SET_STRING_WIDTH(buffer, "2d", 2); return buffer + 2l;
	case  46u: SET_STRING_WIDTH(buffer, "2e", 2); return buffer + 2l;
	case  47u: SET_STRING_WIDTH(buffer, "2f", 2); return buffer + 2l;
	case  48u: SET_STRING_WIDTH(buffer, "30", 2); return buffer + 2l;
	case  49u: SET_STRING_WIDTH(buffer, "31", 2); return buffer + 2l;
	case  50u: SET_STRING_WIDTH(buffer, "32", 2); return buffer + 2l;
	case  51u: SET_STRING_WIDTH(buffer, "33", 2); return buffer + 2l;
	case  52u: SET_STRING_WIDTH(buffer, "34", 2); return buffer + 2l;
	case  53u: SET_STRING_WIDTH(buffer, "35", 2); return buffer + 2l;
	case  54u: SET_STRING_WIDTH(buffer, "36", 2); return buffer + 2l;
	case  55u: SET_STRING_WIDTH(buffer, "37", 2); return buffer + 2l;
	case  56u: SET_STRING_WIDTH(buffer, "38", 2); return buffer + 2l;
	case  57u: SET_STRING_WIDTH(buffer, "39", 2); return buffer + 2l;
	case  58u: SET_STRING_WIDTH(buffer, "3a", 2); return buffer + 2l;
	case  59u: SET_STRING_WIDTH(buffer, "3b", 2); return buffer + 2l;
	case  60u: SET_STRING_WIDTH(buffer, "3c", 2); return buffer + 2l;
	case  61u: SET_STRING_WIDTH(buffer, "3d", 2); return buffer + 2l;
	case  62u: SET_STRING_WIDTH(buffer, "3e", 2); return buffer + 2l;
	case  63u: SET_STRING_WIDTH(buffer, "3f", 2); return buffer + 2l;
	case  64u: SET_STRING_WIDTH(buffer, "40", 2); return buffer + 2l;
	case  65u: SET_STRING_WIDTH(buffer, "41", 2); return buffer + 2l;
	case  66u: SET_STRING_WIDTH(buffer, "42", 2); return buffer + 2l;
	case  67u: SET_STRING_WIDTH(buffer, "43", 2); return buffer + 2l;
	case  68u: SET_STRING_WIDTH(buffer, "44", 2); return buffer + 2l;
	case  69u: SET_STRING_WIDTH(buffer, "45", 2); return buffer + 2l;
	case  70u: SET_STRING_WIDTH(buffer, "46", 2); return buffer + 2l;
	case  71u: SET_STRING_WIDTH(buffer, "47", 2); return buffer + 2l;
	case  72u: SET_STRING_WIDTH(buffer, "48", 2); return buffer + 2l;
	case  73u: SET_STRING_WIDTH(buffer, "49", 2); return buffer + 2l;
	case  74u: SET_STRING_WIDTH(buffer, "4a", 2); return buffer + 2l;
	case  75u: SET_STRING_WIDTH(buffer, "4b", 2); return buffer + 2l;
	case  76u: SET_STRING_WIDTH(buffer, "4c", 2); return buffer + 2l;
	case  77u: SET_STRING_WIDTH(buffer, "4d", 2); return buffer + 2l;
	case  78u: SET_STRING_WIDTH(buffer, "4e", 2); return buffer + 2l;
	case  79u: SET_STRING_WIDTH(buffer, "4f", 2); return buffer + 2l;
	case  80u: SET_STRING_WIDTH(buffer, "50", 2); return buffer + 2l;
	case  81u: SET_STRING_WIDTH(buffer, "51", 2); return buffer + 2l;
	case  82u: SET_STRING_WIDTH(buffer, "52", 2); return buffer + 2l;
	case  83u: SET_STRING_WIDTH(buffer, "53", 2); return buffer + 2l;
	case  84u: SET_STRING_WIDTH(buffer, "54", 2); return buffer + 2l;
	case  85u: SET_STRING_WIDTH(buffer, "55", 2); return buffer + 2l;
	case  86u: SET_STRING_WIDTH(buffer, "56", 2); return buffer + 2l;
	case  87u: SET_STRING_WIDTH(buffer, "57", 2); return buffer + 2l;
	case  88u: SET_STRING_WIDTH(buffer, "58", 2); return buffer + 2l;
	case  89u: SET_STRING_WIDTH(buffer, "59", 2); return buffer + 2l;
	case  90u: SET_STRING_WIDTH(buffer, "5a", 2); return buffer + 2l;
	case  91u: SET_STRING_WIDTH(buffer, "5b", 2); return buffer + 2l;
	case  92u: SET_STRING_WIDTH(buffer, "5c", 2); return buffer + 2l;
	case  93u: SET_STRING_WIDTH(buffer, "5d", 2); return buffer + 2l;
	case  94u: SET_STRING_WIDTH(buffer, "5e", 2); return buffer + 2l;
	case  95u: SET_STRING_WIDTH(buffer, "5f", 2); return buffer + 2l;
	case  96u: SET_STRING_WIDTH(buffer, "60", 2); return buffer + 2l;
	case  97u: SET_STRING_WIDTH(buffer, "61", 2); return buffer + 2l;
	case  98u: SET_STRING_WIDTH(buffer, "62", 2); return buffer + 2l;
	case  99u: SET_STRING_WIDTH(buffer, "63", 2); return buffer + 2l;
	case 100u: SET_STRING_WIDTH(buffer, "64", 2); return buffer + 2l;
	case 101u: SET_STRING_WIDTH(buffer, "65", 2); return buffer + 2l;
	case 102u: SET_STRING_WIDTH(buffer, "66", 2); return buffer + 2l;
	case 103u: SET_STRING_WIDTH(buffer, "67", 2); return buffer + 2l;
	case 104u: SET_STRING_WIDTH(buffer, "68", 2); return buffer + 2l;
	case 105u: SET_STRING_WIDTH(buffer, "69", 2); return buffer + 2l;
	case 106u: SET_STRING_WIDTH(buffer, "6a", 2); return buffer + 2l;
	case 107u: SET_STRING_WIDTH(buffer, "6b", 2); return buffer + 2l;
	case 108u: SET_STRING_WIDTH(buffer, "6c", 2); return buffer + 2l;
	case 109u: SET_STRING_WIDTH(buffer, "6d", 2); return buffer + 2l;
	case 110u: SET_STRING_WIDTH(buffer, "6e", 2); return buffer + 2l;
	case 111u: SET_STRING_WIDTH(buffer, "6f", 2); return buffer + 2l;
	case 112u: SET_STRING_WIDTH(buffer, "70", 2); return buffer + 2l;
	case 113u: SET_STRING_WIDTH(buffer, "71", 2); return buffer + 2l;
	case 114u: SET_STRING_WIDTH(buffer, "72", 2); return buffer + 2l;
	case 115u: SET_STRING_WIDTH(buffer, "73", 2); return buffer + 2l;
	case 116u: SET_STRING_WIDTH(buffer, "74", 2); return buffer + 2l;
	case 117u: SET_STRING_WIDTH(buffer, "75", 2); return buffer + 2l;
	case 118u: SET_STRING_WIDTH(buffer, "76", 2); return buffer + 2l;
	case 119u: SET_STRING_WIDTH(buffer, "77", 2); return buffer + 2l;
	case 120u: SET_STRING_WIDTH(buffer, "78", 2); return buffer + 2l;
	case 121u: SET_STRING_WIDTH(buffer, "79", 2); return buffer + 2l;
	case 122u: SET_STRING_WIDTH(buffer, "7a", 2); return buffer + 2l;
	case 123u: SET_STRING_WIDTH(buffer, "7b", 2); return buffer + 2l;
	case 124u: SET_STRING_WIDTH(buffer, "7c", 2); return buffer + 2l;
	case 125u: SET_STRING_WIDTH(buffer, "7d", 2); return buffer + 2l;
	case 126u: SET_STRING_WIDTH(buffer, "7e", 2); return buffer + 2l;
	case 127u: SET_STRING_WIDTH(buffer, "7f", 2); return buffer + 2l;
	case 128u: SET_STRING_WIDTH(buffer, "80", 2); return buffer + 2l;
	case 129u: SET_STRING_WIDTH(buffer, "81", 2); return buffer + 2l;
	case 130u: SET_STRING_WIDTH(buffer, "82", 2); return buffer + 2l;
	case 131u: SET_STRING_WIDTH(buffer, "83", 2); return buffer + 2l;
	case 132u: SET_STRING_WIDTH(buffer, "84", 2); return buffer + 2l;
	case 133u: SET_STRING_WIDTH(buffer, "85", 2); return buffer + 2l;
	case 134u: SET_STRING_WIDTH(buffer, "86", 2); return buffer + 2l;
	case 135u: SET_STRING_WIDTH(buffer, "87", 2); return buffer + 2l;
	case 136u: SET_STRING_WIDTH(buffer, "88", 2); return buffer + 2l;
	case 137u: SET_STRING_WIDTH(buffer, "89", 2); return buffer + 2l;
	case 138u: SET_STRING_WIDTH(buffer, "8a", 2); return buffer + 2l;
	case 139u: SET_STRING_WIDTH(buffer, "8b", 2); return buffer + 2l;
	case 140u: SET_STRING_WIDTH(buffer, "8c", 2); return buffer + 2l;
	case 141u: SET_STRING_WIDTH(buffer, "8d", 2); return buffer + 2l;
	case 142u: SET_STRING_WIDTH(buffer, "8e", 2); return buffer + 2l;
	case 143u: SET_STRING_WIDTH(buffer, "8f", 2); return buffer + 2l;
	case 144u: SET_STRING_WIDTH(buffer, "90", 2); return buffer + 2l;
	case 145u: SET_STRING_WIDTH(buffer, "91", 2); return buffer + 2l;
	case 146u: SET_STRING_WIDTH(buffer, "92", 2); return buffer + 2l;
	case 147u: SET_STRING_WIDTH(buffer, "93", 2); return buffer + 2l;
	case 148u: SET_STRING_WIDTH(buffer, "94", 2); return buffer + 2l;
	case 149u: SET_STRING_WIDTH(buffer, "95", 2); return buffer + 2l;
	case 150u: SET_STRING_WIDTH(buffer, "96", 2); return buffer + 2l;
	case 151u: SET_STRING_WIDTH(buffer, "97", 2); return buffer + 2l;
	case 152u: SET_STRING_WIDTH(buffer, "98", 2); return buffer + 2l;
	case 153u: SET_STRING_WIDTH(buffer, "99", 2); return buffer + 2l;
	case 154u: SET_STRING_WIDTH(buffer, "9a", 2); return buffer + 2l;
	case 155u: SET_STRING_WIDTH(buffer, "9b", 2); return buffer + 2l;
	case 156u: SET_STRING_WIDTH(buffer, "9c", 2); return buffer + 2l;
	case 157u: SET_STRING_WIDTH(buffer, "9d", 2); return buffer + 2l;
	case 158u: SET_STRING_WIDTH(buffer, "9e", 2); return buffer + 2l;
	case 159u: SET_STRING_WIDTH(buffer, "9f", 2); return buffer + 2l;
	case 160u: SET_STRING_WIDTH(buffer, "a0", 2); return buffer + 2l;
	case 161u: SET_STRING_WIDTH(buffer, "a1", 2); return buffer + 2l;
	case 162u: SET_STRING_WIDTH(buffer, "a2", 2); return buffer + 2l;
	case 163u: SET_STRING_WIDTH(buffer, "a3", 2); return buffer + 2l;
	case 164u: SET_STRING_WIDTH(buffer, "a4", 2); return buffer + 2l;
	case 165u: SET_STRING_WIDTH(buffer, "a5", 2); return buffer + 2l;
	case 166u: SET_STRING_WIDTH(buffer, "a6", 2); return buffer + 2l;
	case 167u: SET_STRING_WIDTH(buffer, "a7", 2); return buffer + 2l;
	case 168u: SET_STRING_WIDTH(buffer, "a8", 2); return buffer + 2l;
	case 169u: SET_STRING_WIDTH(buffer, "a9", 2); return buffer + 2l;
	case 170u: SET_STRING_WIDTH(buffer, "aa", 2); return buffer + 2l;
	case 171u: SET_STRING_WIDTH(buffer, "ab", 2); return buffer + 2l;
	case 172u: SET_STRING_WIDTH(buffer, "ac", 2); return buffer + 2l;
	case 173u: SET_STRING_WIDTH(buffer, "ad", 2); return buffer + 2l;
	case 174u: SET_STRING_WIDTH(buffer, "ae", 2); return buffer + 2l;
	case 175u: SET_STRING_WIDTH(buffer, "af", 2); return buffer + 2l;
	case 176u: SET_STRING_WIDTH(buffer, "b0", 2); return buffer + 2l;
	case 177u: SET_STRING_WIDTH(buffer, "b1", 2); return buffer + 2l;
	case 178u: SET_STRING_WIDTH(buffer, "b2", 2); return buffer + 2l;
	case 179u: SET_STRING_WIDTH(buffer, "b3", 2); return buffer + 2l;
	case 180u: SET_STRING_WIDTH(buffer, "b4", 2); return buffer + 2l;
	case 181u: SET_STRING_WIDTH(buffer, "b5", 2); return buffer + 2l;
	case 182u: SET_STRING_WIDTH(buffer, "b6", 2); return buffer + 2l;
	case 183u: SET_STRING_WIDTH(buffer, "b7", 2); return buffer + 2l;
	case 184u: SET_STRING_WIDTH(buffer, "b8", 2); return buffer + 2l;
	case 185u: SET_STRING_WIDTH(buffer, "b9", 2); return buffer + 2l;
	case 186u: SET_STRING_WIDTH(buffer, "ba", 2); return buffer + 2l;
	case 187u: SET_STRING_WIDTH(buffer, "bb", 2); return buffer + 2l;
	case 188u: SET_STRING_WIDTH(buffer, "bc", 2); return buffer + 2l;
	case 189u: SET_STRING_WIDTH(buffer, "bd", 2); return buffer + 2l;
	case 190u: SET_STRING_WIDTH(buffer, "be", 2); return buffer + 2l;
	case 191u: SET_STRING_WIDTH(buffer, "bf", 2); return buffer + 2l;
	case 192u: SET_STRING_WIDTH(buffer, "c0", 2); return buffer + 2l;
	case 193u: SET_STRING_WIDTH(buffer, "c1", 2); return buffer + 2l;
	case 194u: SET_STRING_WIDTH(buffer, "c2", 2); return buffer + 2l;
	case 195u: SET_STRING_WIDTH(buffer, "c3", 2); return buffer + 2l;
	case 196u: SET_STRING_WIDTH(buffer, "c4", 2); return buffer + 2l;
	case 197u: SET_STRING_WIDTH(buffer, "c5", 2); return buffer + 2l;
	case 198u: SET_STRING_WIDTH(buffer, "c6", 2); return buffer + 2l;
	case 199u: SET_STRING_WIDTH(buffer, "c7", 2); return buffer + 2l;
	case 200u: SET_STRING_WIDTH(buffer, "c8", 2); return buffer + 2l;
	case 201u: SET_STRING_WIDTH(buffer, "c9", 2); return buffer + 2l;
	case 202u: SET_STRING_WIDTH(buffer, "ca", 2); return buffer + 2l;
	case 203u: SET_STRING_WIDTH(buffer, "cb", 2); return buffer + 2l;
	case 204u: SET_STRING_WIDTH(buffer, "cc", 2); return buffer + 2l;
	case 205u: SET_STRING_WIDTH(buffer, "cd", 2); return buffer + 2l;
	case 206u: SET_STRING_WIDTH(buffer, "ce", 2); return buffer + 2l;
	case 207u: SET_STRING_WIDTH(buffer, "cf", 2); return buffer + 2l;
	case 208u: SET_STRING_WIDTH(buffer, "d0", 2); return buffer + 2l;
	case 209u: SET_STRING_WIDTH(buffer, "d1", 2); return buffer + 2l;
	case 210u: SET_STRING_WIDTH(buffer, "d2", 2); return buffer + 2l;
	case 211u: SET_STRING_WIDTH(buffer, "d3", 2); return buffer + 2l;
	case 212u: SET_STRING_WIDTH(buffer, "d4", 2); return buffer + 2l;
	case 213u: SET_STRING_WIDTH(buffer, "d5", 2); return buffer + 2l;
	case 214u: SET_STRING_WIDTH(buffer, "d6", 2); return buffer + 2l;
	case 215u: SET_STRING_WIDTH(buffer, "d7", 2); return buffer + 2l;
	case 216u: SET_STRING_WIDTH(buffer, "d8", 2); return buffer + 2l;
	case 217u: SET_STRING_WIDTH(buffer, "d9", 2); return buffer + 2l;
	case 218u: SET_STRING_WIDTH(buffer, "da", 2); return buffer + 2l;
	case 219u: SET_STRING_WIDTH(buffer, "db", 2); return buffer + 2l;
	case 220u: SET_STRING_WIDTH(buffer, "dc", 2); return buffer + 2l;
	case 221u: SET_STRING_WIDTH(buffer, "dd", 2); return buffer + 2l;
	case 222u: SET_STRING_WIDTH(buffer, "de", 2); return buffer + 2l;
	case 223u: SET_STRING_WIDTH(buffer, "df", 2); return buffer + 2l;
	case 224u: SET_STRING_WIDTH(buffer, "e0", 2); return buffer + 2l;
	case 225u: SET_STRING_WIDTH(buffer, "e1", 2); return buffer + 2l;
	case 226u: SET_STRING_WIDTH(buffer, "e2", 2); return buffer + 2l;
	case 227u: SET_STRING_WIDTH(buffer, "e3", 2); return buffer + 2l;
	case 228u: SET_STRING_WIDTH(buffer, "e4", 2); return buffer + 2l;
	case 229u: SET_STRING_WIDTH(buffer, "e5", 2); return buffer + 2l;
	case 230u: SET_STRING_WIDTH(buffer, "e6", 2); return buffer + 2l;
	case 231u: SET_STRING_WIDTH(buffer, "e7", 2); return buffer + 2l;
	case 232u: SET_STRING_WIDTH(buffer, "e8", 2); return buffer + 2l;
	case 233u: SET_STRING_WIDTH(buffer, "e9", 2); return buffer + 2l;
	case 234u: SET_STRING_WIDTH(buffer, "ea", 2); return buffer + 2l;
	case 235u: SET_STRING_WIDTH(buffer, "eb", 2); return buffer + 2l;
	case 236u: SET_STRING_WIDTH(buffer, "ec", 2); return buffer + 2l;
	case 237u: SET_STRING_WIDTH(buffer, "ed", 2); return buffer + 2l;
	case 238u: SET_STRING_WIDTH(buffer, "ee", 2); return buffer + 2l;
	case 239u: SET_STRING_WIDTH(buffer, "ef", 2); return buffer + 2l;
	case 240u: SET_STRING_WIDTH(buffer, "f0", 2); return buffer + 2l;
	case 241u: SET_STRING_WIDTH(buffer, "f1", 2); return buffer + 2l;
	case 242u: SET_STRING_WIDTH(buffer, "f2", 2); return buffer + 2l;
	case 243u: SET_STRING_WIDTH(buffer, "f3", 2); return buffer + 2l;
	case 244u: SET_STRING_WIDTH(buffer, "f4", 2); return buffer + 2l;
	case 245u: SET_STRING_WIDTH(buffer, "f5", 2); return buffer + 2l;
	case 246u: SET_STRING_WIDTH(buffer, "f6", 2); return buffer + 2l;
	case 247u: SET_STRING_WIDTH(buffer, "f7", 2); return buffer + 2l;
	case 248u: SET_STRING_WIDTH(buffer, "f8", 2); return buffer + 2l;
	case 249u: SET_STRING_WIDTH(buffer, "f9", 2); return buffer + 2l;
	case 250u: SET_STRING_WIDTH(buffer, "fa", 2); return buffer + 2l;
	case 251u: SET_STRING_WIDTH(buffer, "fb", 2); return buffer + 2l;
	case 252u: SET_STRING_WIDTH(buffer, "fc", 2); return buffer + 2l;
	case 253u: SET_STRING_WIDTH(buffer, "fd", 2); return buffer + 2l;
	case 254u: SET_STRING_WIDTH(buffer, "fe", 2); return buffer + 2l;
	default:   SET_STRING_WIDTH(buffer, "ff", 2); return buffer + 2l;
	}
}

inline char *
put_octet_hex_upper(char *const restrict buffer,
		    const octet_t octet)
{
	switch (octet) {
	case   0u: SET_STRING_WIDTH(buffer, "00", 2); return buffer + 2l;
	case   1u: SET_STRING_WIDTH(buffer, "01", 2); return buffer + 2l;
	case   2u: SET_STRING_WIDTH(buffer, "02", 2); return buffer + 2l;
	case   3u: SET_STRING_WIDTH(buffer, "03", 2); return buffer + 2l;
	case   4u: SET_STRING_WIDTH(buffer, "04", 2); return buffer + 2l;
	case   5u: SET_STRING_WIDTH(buffer, "05", 2); return buffer + 2l;
	case   6u: SET_STRING_WIDTH(buffer, "06", 2); return buffer + 2l;
	case   7u: SET_STRING_WIDTH(buffer, "07", 2); return buffer + 2l;
	case   8u: SET_STRING_WIDTH(buffer, "08", 2); return buffer + 2l;
	case   9u: SET_STRING_WIDTH(buffer, "09", 2); return buffer + 2l;
	case  10u: SET_STRING_WIDTH(buffer, "0A", 2); return buffer + 2l;
	case  11u: SET_STRING_WIDTH(buffer, "0B", 2); return buffer + 2l;
	case  12u: SET_STRING_WIDTH(buffer, "0C", 2); return buffer + 2l;
	case  13u: SET_STRING_WIDTH(buffer, "0D", 2); return buffer + 2l;
	case  14u: SET_STRING_WIDTH(buffer, "0E", 2); return buffer + 2l;
	case  15u: SET_STRING_WIDTH(buffer, "0F", 2); return buffer + 2l;
	case  16u: SET_STRING_WIDTH(buffer, "10", 2); return buffer + 2l;
	case  17u: SET_STRING_WIDTH(buffer, "11", 2); return buffer + 2l;
	case  18u: SET_STRING_WIDTH(buffer, "12", 2); return buffer + 2l;
	case  19u: SET_STRING_WIDTH(buffer, "13", 2); return buffer + 2l;
	case  20u: SET_STRING_WIDTH(buffer, "14", 2); return buffer + 2l;
	case  21u: SET_STRING_WIDTH(buffer, "15", 2); return buffer + 2l;
	case  22u: SET_STRING_WIDTH(buffer, "16", 2); return buffer + 2l;
	case  23u: SET_STRING_WIDTH(buffer, "17", 2); return buffer + 2l;
	case  24u: SET_STRING_WIDTH(buffer, "18", 2); return buffer + 2l;
	case  25u: SET_STRING_WIDTH(buffer, "19", 2); return buffer + 2l;
	case  26u: SET_STRING_WIDTH(buffer, "1A", 2); return buffer + 2l;
	case  27u: SET_STRING_WIDTH(buffer, "1B", 2); return buffer + 2l;
	case  28u: SET_STRING_WIDTH(buffer, "1C", 2); return buffer + 2l;
	case  29u: SET_STRING_WIDTH(buffer, "1D", 2); return buffer + 2l;
	case  30u: SET_STRING_WIDTH(buffer, "1E", 2); return buffer + 2l;
	case  31u: SET_STRING_WIDTH(buffer, "1F", 2); return buffer + 2l;
	case  32u: SET_STRING_WIDTH(buffer, "20", 2); return buffer + 2l;
	case  33u: SET_STRING_WIDTH(buffer, "21", 2); return buffer + 2l;
	case  34u: SET_STRING_WIDTH(buffer, "22", 2); return buffer + 2l;
	case  35u: SET_STRING_WIDTH(buffer, "23", 2); return buffer + 2l;
	case  36u: SET_STRING_WIDTH(buffer, "24", 2); return buffer + 2l;
	case  37u: SET_STRING_WIDTH(buffer, "25", 2); return buffer + 2l;
	case  38u: SET_STRING_WIDTH(buffer, "26", 2); return buffer + 2l;
	case  39u: SET_STRING_WIDTH(buffer, "27", 2); return buffer + 2l;
	case  40u: SET_STRING_WIDTH(buffer, "28", 2); return buffer + 2l;
	case  41u: SET_STRING_WIDTH(buffer, "29", 2); return buffer + 2l;
	case  42u: SET_STRING_WIDTH(buffer, "2A", 2); return buffer + 2l;
	case  43u: SET_STRING_WIDTH(buffer, "2B", 2); return buffer + 2l;
	case  44u: SET_STRING_WIDTH(buffer, "2C", 2); return buffer + 2l;
	case  45u: SET_STRING_WIDTH(buffer, "2D", 2); return buffer + 2l;
	case  46u: SET_STRING_WIDTH(buffer, "2E", 2); return buffer + 2l;
	case  47u: SET_STRING_WIDTH(buffer, "2F", 2); return buffer + 2l;
	case  48u: SET_STRING_WIDTH(buffer, "30", 2); return buffer + 2l;
	case  49u: SET_STRING_WIDTH(buffer, "31", 2); return buffer + 2l;
	case  50u: SET_STRING_WIDTH(buffer, "32", 2); return buffer + 2l;
	case  51u: SET_STRING_WIDTH(buffer, "33", 2); return buffer + 2l;
	case  52u: SET_STRING_WIDTH(buffer, "34", 2); return buffer + 2l;
	case  53u: SET_STRING_WIDTH(buffer, "35", 2); return buffer + 2l;
	case  54u: SET_STRING_WIDTH(buffer, "36", 2); return buffer + 2l;
	case  55u: SET_STRING_WIDTH(buffer, "37", 2); return buffer + 2l;
	case  56u: SET_STRING_WIDTH(buffer, "38", 2); return buffer + 2l;
	case  57u: SET_STRING_WIDTH(buffer, "39", 2); return buffer + 2l;
	case  58u: SET_STRING_WIDTH(buffer, "3A", 2); return buffer + 2l;
	case  59u: SET_STRING_WIDTH(buffer, "3B", 2); return buffer + 2l;
	case  60u: SET_STRING_WIDTH(buffer, "3C", 2); return buffer + 2l;
	case  61u: SET_STRING_WIDTH(buffer, "3D", 2); return buffer + 2l;
	case  62u: SET_STRING_WIDTH(buffer, "3E", 2); return buffer + 2l;
	case  63u: SET_STRING_WIDTH(buffer, "3F", 2); return buffer + 2l;
	case  64u: SET_STRING_WIDTH(buffer, "40", 2); return buffer + 2l;
	case  65u: SET_STRING_WIDTH(buffer, "41", 2); return buffer + 2l;
	case  66u: SET_STRING_WIDTH(buffer, "42", 2); return buffer + 2l;
	case  67u: SET_STRING_WIDTH(buffer, "43", 2); return buffer + 2l;
	case  68u: SET_STRING_WIDTH(buffer, "44", 2); return buffer + 2l;
	case  69u: SET_STRING_WIDTH(buffer, "45", 2); return buffer + 2l;
	case  70u: SET_STRING_WIDTH(buffer, "46", 2); return buffer + 2l;
	case  71u: SET_STRING_WIDTH(buffer, "47", 2); return buffer + 2l;
	case  72u: SET_STRING_WIDTH(buffer, "48", 2); return buffer + 2l;
	case  73u: SET_STRING_WIDTH(buffer, "49", 2); return buffer + 2l;
	case  74u: SET_STRING_WIDTH(buffer, "4A", 2); return buffer + 2l;
	case  75u: SET_STRING_WIDTH(buffer, "4B", 2); return buffer + 2l;
	case  76u: SET_STRING_WIDTH(buffer, "4C", 2); return buffer + 2l;
	case  77u: SET_STRING_WIDTH(buffer, "4D", 2); return buffer + 2l;
	case  78u: SET_STRING_WIDTH(buffer, "4E", 2); return buffer + 2l;
	case  79u: SET_STRING_WIDTH(buffer, "4F", 2); return buffer + 2l;
	case  80u: SET_STRING_WIDTH(buffer, "50", 2); return buffer + 2l;
	case  81u: SET_STRING_WIDTH(buffer, "51", 2); return buffer + 2l;
	case  82u: SET_STRING_WIDTH(buffer, "52", 2); return buffer + 2l;
	case  83u: SET_STRING_WIDTH(buffer, "53", 2); return buffer + 2l;
	case  84u: SET_STRING_WIDTH(buffer, "54", 2); return buffer + 2l;
	case  85u: SET_STRING_WIDTH(buffer, "55", 2); return buffer + 2l;
	case  86u: SET_STRING_WIDTH(buffer, "56", 2); return buffer + 2l;
	case  87u: SET_STRING_WIDTH(buffer, "57", 2); return buffer + 2l;
	case  88u: SET_STRING_WIDTH(buffer, "58", 2); return buffer + 2l;
	case  89u: SET_STRING_WIDTH(buffer, "59", 2); return buffer + 2l;
	case  90u: SET_STRING_WIDTH(buffer, "5A", 2); return buffer + 2l;
	case  91u: SET_STRING_WIDTH(buffer, "5B", 2); return buffer + 2l;
	case  92u: SET_STRING_WIDTH(buffer, "5C", 2); return buffer + 2l;
	case  93u: SET_STRING_WIDTH(buffer, "5D", 2); return buffer + 2l;
	case  94u: SET_STRING_WIDTH(buffer, "5E", 2); return buffer + 2l;
	case  95u: SET_STRING_WIDTH(buffer, "5F", 2); return buffer + 2l;
	case  96u: SET_STRING_WIDTH(buffer, "60", 2); return buffer + 2l;
	case  97u: SET_STRING_WIDTH(buffer, "61", 2); return buffer + 2l;
	case  98u: SET_STRING_WIDTH(buffer, "62", 2); return buffer + 2l;
	case  99u: SET_STRING_WIDTH(buffer, "63", 2); return buffer + 2l;
	case 100u: SET_STRING_WIDTH(buffer, "64", 2); return buffer + 2l;
	case 101u: SET_STRING_WIDTH(buffer, "65", 2); return buffer + 2l;
	case 102u: SET_STRING_WIDTH(buffer, "66", 2); return buffer + 2l;
	case 103u: SET_STRING_WIDTH(buffer, "67", 2); return buffer + 2l;
	case 104u: SET_STRING_WIDTH(buffer, "68", 2); return buffer + 2l;
	case 105u: SET_STRING_WIDTH(buffer, "69", 2); return buffer + 2l;
	case 106u: SET_STRING_WIDTH(buffer, "6A", 2); return buffer + 2l;
	case 107u: SET_STRING_WIDTH(buffer, "6B", 2); return buffer + 2l;
	case 108u: SET_STRING_WIDTH(buffer, "6C", 2); return buffer + 2l;
	case 109u: SET_STRING_WIDTH(buffer, "6D", 2); return buffer + 2l;
	case 110u: SET_STRING_WIDTH(buffer, "6E", 2); return buffer + 2l;
	case 111u: SET_STRING_WIDTH(buffer, "6F", 2); return buffer + 2l;
	case 112u: SET_STRING_WIDTH(buffer, "70", 2); return buffer + 2l;
	case 113u: SET_STRING_WIDTH(buffer, "71", 2); return buffer + 2l;
	case 114u: SET_STRING_WIDTH(buffer, "72", 2); return buffer + 2l;
	case 115u: SET_STRING_WIDTH(buffer, "73", 2); return buffer + 2l;
	case 116u: SET_STRING_WIDTH(buffer, "74", 2); return buffer + 2l;
	case 117u: SET_STRING_WIDTH(buffer, "75", 2); return buffer + 2l;
	case 118u: SET_STRING_WIDTH(buffer, "76", 2); return buffer + 2l;
	case 119u: SET_STRING_WIDTH(buffer, "77", 2); return buffer + 2l;
	case 120u: SET_STRING_WIDTH(buffer, "78", 2); return buffer + 2l;
	case 121u: SET_STRING_WIDTH(buffer, "79", 2); return buffer + 2l;
	case 122u: SET_STRING_WIDTH(buffer, "7A", 2); return buffer + 2l;
	case 123u: SET_STRING_WIDTH(buffer, "7B", 2); return buffer + 2l;
	case 124u: SET_STRING_WIDTH(buffer, "7C", 2); return buffer + 2l;
	case 125u: SET_STRING_WIDTH(buffer, "7D", 2); return buffer + 2l;
	case 126u: SET_STRING_WIDTH(buffer, "7E", 2); return buffer + 2l;
	case 127u: SET_STRING_WIDTH(buffer, "7F", 2); return buffer + 2l;
	case 128u: SET_STRING_WIDTH(buffer, "80", 2); return buffer + 2l;
	case 129u: SET_STRING_WIDTH(buffer, "81", 2); return buffer + 2l;
	case 130u: SET_STRING_WIDTH(buffer, "82", 2); return buffer + 2l;
	case 131u: SET_STRING_WIDTH(buffer, "83", 2); return buffer + 2l;
	case 132u: SET_STRING_WIDTH(buffer, "84", 2); return buffer + 2l;
	case 133u: SET_STRING_WIDTH(buffer, "85", 2); return buffer + 2l;
	case 134u: SET_STRING_WIDTH(buffer, "86", 2); return buffer + 2l;
	case 135u: SET_STRING_WIDTH(buffer, "87", 2); return buffer + 2l;
	case 136u: SET_STRING_WIDTH(buffer, "88", 2); return buffer + 2l;
	case 137u: SET_STRING_WIDTH(buffer, "89", 2); return buffer + 2l;
	case 138u: SET_STRING_WIDTH(buffer, "8A", 2); return buffer + 2l;
	case 139u: SET_STRING_WIDTH(buffer, "8B", 2); return buffer + 2l;
	case 140u: SET_STRING_WIDTH(buffer, "8C", 2); return buffer + 2l;
	case 141u: SET_STRING_WIDTH(buffer, "8D", 2); return buffer + 2l;
	case 142u: SET_STRING_WIDTH(buffer, "8E", 2); return buffer + 2l;
	case 143u: SET_STRING_WIDTH(buffer, "8F", 2); return buffer + 2l;
	case 144u: SET_STRING_WIDTH(buffer, "90", 2); return buffer + 2l;
	case 145u: SET_STRING_WIDTH(buffer, "91", 2); return buffer + 2l;
	case 146u: SET_STRING_WIDTH(buffer, "92", 2); return buffer + 2l;
	case 147u: SET_STRING_WIDTH(buffer, "93", 2); return buffer + 2l;
	case 148u: SET_STRING_WIDTH(buffer, "94", 2); return buffer + 2l;
	case 149u: SET_STRING_WIDTH(buffer, "95", 2); return buffer + 2l;
	case 150u: SET_STRING_WIDTH(buffer, "96", 2); return buffer + 2l;
	case 151u: SET_STRING_WIDTH(buffer, "97", 2); return buffer + 2l;
	case 152u: SET_STRING_WIDTH(buffer, "98", 2); return buffer + 2l;
	case 153u: SET_STRING_WIDTH(buffer, "99", 2); return buffer + 2l;
	case 154u: SET_STRING_WIDTH(buffer, "9A", 2); return buffer + 2l;
	case 155u: SET_STRING_WIDTH(buffer, "9B", 2); return buffer + 2l;
	case 156u: SET_STRING_WIDTH(buffer, "9C", 2); return buffer + 2l;
	case 157u: SET_STRING_WIDTH(buffer, "9D", 2); return buffer + 2l;
	case 158u: SET_STRING_WIDTH(buffer, "9E", 2); return buffer + 2l;
	case 159u: SET_STRING_WIDTH(buffer, "9F", 2); return buffer + 2l;
	case 160u: SET_STRING_WIDTH(buffer, "A0", 2); return buffer + 2l;
	case 161u: SET_STRING_WIDTH(buffer, "A1", 2); return buffer + 2l;
	case 162u: SET_STRING_WIDTH(buffer, "A2", 2); return buffer + 2l;
	case 163u: SET_STRING_WIDTH(buffer, "A3", 2); return buffer + 2l;
	case 164u: SET_STRING_WIDTH(buffer, "A4", 2); return buffer + 2l;
	case 165u: SET_STRING_WIDTH(buffer, "A5", 2); return buffer + 2l;
	case 166u: SET_STRING_WIDTH(buffer, "A6", 2); return buffer + 2l;
	case 167u: SET_STRING_WIDTH(buffer, "A7", 2); return buffer + 2l;
	case 168u: SET_STRING_WIDTH(buffer, "A8", 2); return buffer + 2l;
	case 169u: SET_STRING_WIDTH(buffer, "A9", 2); return buffer + 2l;
	case 170u: SET_STRING_WIDTH(buffer, "AA", 2); return buffer + 2l;
	case 171u: SET_STRING_WIDTH(buffer, "AB", 2); return buffer + 2l;
	case 172u: SET_STRING_WIDTH(buffer, "AC", 2); return buffer + 2l;
	case 173u: SET_STRING_WIDTH(buffer, "AD", 2); return buffer + 2l;
	case 174u: SET_STRING_WIDTH(buffer, "AE", 2); return buffer + 2l;
	case 175u: SET_STRING_WIDTH(buffer, "AF", 2); return buffer + 2l;
	case 176u: SET_STRING_WIDTH(buffer, "B0", 2); return buffer + 2l;
	case 177u: SET_STRING_WIDTH(buffer, "B1", 2); return buffer + 2l;
	case 178u: SET_STRING_WIDTH(buffer, "B2", 2); return buffer + 2l;
	case 179u: SET_STRING_WIDTH(buffer, "B3", 2); return buffer + 2l;
	case 180u: SET_STRING_WIDTH(buffer, "B4", 2); return buffer + 2l;
	case 181u: SET_STRING_WIDTH(buffer, "B5", 2); return buffer + 2l;
	case 182u: SET_STRING_WIDTH(buffer, "B6", 2); return buffer + 2l;
	case 183u: SET_STRING_WIDTH(buffer, "B7", 2); return buffer + 2l;
	case 184u: SET_STRING_WIDTH(buffer, "B8", 2); return buffer + 2l;
	case 185u: SET_STRING_WIDTH(buffer, "B9", 2); return buffer + 2l;
	case 186u: SET_STRING_WIDTH(buffer, "BA", 2); return buffer + 2l;
	case 187u: SET_STRING_WIDTH(buffer, "BB", 2); return buffer + 2l;
	case 188u: SET_STRING_WIDTH(buffer, "BC", 2); return buffer + 2l;
	case 189u: SET_STRING_WIDTH(buffer, "BD", 2); return buffer + 2l;
	case 190u: SET_STRING_WIDTH(buffer, "BE", 2); return buffer + 2l;
	case 191u: SET_STRING_WIDTH(buffer, "BF", 2); return buffer + 2l;
	case 192u: SET_STRING_WIDTH(buffer, "C0", 2); return buffer + 2l;
	case 193u: SET_STRING_WIDTH(buffer, "C1", 2); return buffer + 2l;
	case 194u: SET_STRING_WIDTH(buffer, "C2", 2); return buffer + 2l;
	case 195u: SET_STRING_WIDTH(buffer, "C3", 2); return buffer + 2l;
	case 196u: SET_STRING_WIDTH(buffer, "C4", 2); return buffer + 2l;
	case 197u: SET_STRING_WIDTH(buffer, "C5", 2); return buffer + 2l;
	case 198u: SET_STRING_WIDTH(buffer, "C6", 2); return buffer + 2l;
	case 199u: SET_STRING_WIDTH(buffer, "C7", 2); return buffer + 2l;
	case 200u: SET_STRING_WIDTH(buffer, "C8", 2); return buffer + 2l;
	case 201u: SET_STRING_WIDTH(buffer, "C9", 2); return buffer + 2l;
	case 202u: SET_STRING_WIDTH(buffer, "CA", 2); return buffer + 2l;
	case 203u: SET_STRING_WIDTH(buffer, "CB", 2); return buffer + 2l;
	case 204u: SET_STRING_WIDTH(buffer, "CC", 2); return buffer + 2l;
	case 205u: SET_STRING_WIDTH(buffer, "CD", 2); return buffer + 2l;
	case 206u: SET_STRING_WIDTH(buffer, "CE", 2); return buffer + 2l;
	case 207u: SET_STRING_WIDTH(buffer, "CF", 2); return buffer + 2l;
	case 208u: SET_STRING_WIDTH(buffer, "D0", 2); return buffer + 2l;
	case 209u: SET_STRING_WIDTH(buffer, "D1", 2); return buffer + 2l;
	case 210u: SET_STRING_WIDTH(buffer, "D2", 2); return buffer + 2l;
	case 211u: SET_STRING_WIDTH(buffer, "D3", 2); return buffer + 2l;
	case 212u: SET_STRING_WIDTH(buffer, "D4", 2); return buffer + 2l;
	case 213u: SET_STRING_WIDTH(buffer, "D5", 2); return buffer + 2l;
	case 214u: SET_STRING_WIDTH(buffer, "D6", 2); return buffer + 2l;
	case 215u: SET_STRING_WIDTH(buffer, "D7", 2); return buffer + 2l;
	case 216u: SET_STRING_WIDTH(buffer, "D8", 2); return buffer + 2l;
	case 217u: SET_STRING_WIDTH(buffer, "D9", 2); return buffer + 2l;
	case 218u: SET_STRING_WIDTH(buffer, "DA", 2); return buffer + 2l;
	case 219u: SET_STRING_WIDTH(buffer, "DB", 2); return buffer + 2l;
	case 220u: SET_STRING_WIDTH(buffer, "DC", 2); return buffer + 2l;
	case 221u: SET_STRING_WIDTH(buffer, "DD", 2); return buffer + 2l;
	case 222u: SET_STRING_WIDTH(buffer, "DE", 2); return buffer + 2l;
	case 223u: SET_STRING_WIDTH(buffer, "DF", 2); return buffer + 2l;
	case 224u: SET_STRING_WIDTH(buffer, "E0", 2); return buffer + 2l;
	case 225u: SET_STRING_WIDTH(buffer, "E1", 2); return buffer + 2l;
	case 226u: SET_STRING_WIDTH(buffer, "E2", 2); return buffer + 2l;
	case 227u: SET_STRING_WIDTH(buffer, "E3", 2); return buffer + 2l;
	case 228u: SET_STRING_WIDTH(buffer, "E4", 2); return buffer + 2l;
	case 229u: SET_STRING_WIDTH(buffer, "E5", 2); return buffer + 2l;
	case 230u: SET_STRING_WIDTH(buffer, "E6", 2); return buffer + 2l;
	case 231u: SET_STRING_WIDTH(buffer, "E7", 2); return buffer + 2l;
	case 232u: SET_STRING_WIDTH(buffer, "E8", 2); return buffer + 2l;
	case 233u: SET_STRING_WIDTH(buffer, "E9", 2); return buffer + 2l;
	case 234u: SET_STRING_WIDTH(buffer, "EA", 2); return buffer + 2l;
	case 235u: SET_STRING_WIDTH(buffer, "EB", 2); return buffer + 2l;
	case 236u: SET_STRING_WIDTH(buffer, "EC", 2); return buffer + 2l;
	case 237u: SET_STRING_WIDTH(buffer, "ED", 2); return buffer + 2l;
	case 238u: SET_STRING_WIDTH(buffer, "EE", 2); return buffer + 2l;
	case 239u: SET_STRING_WIDTH(buffer, "EF", 2); return buffer + 2l;
	case 240u: SET_STRING_WIDTH(buffer, "F0", 2); return buffer + 2l;
	case 241u: SET_STRING_WIDTH(buffer, "F1", 2); return buffer + 2l;
	case 242u: SET_STRING_WIDTH(buffer, "F2", 2); return buffer + 2l;
	case 243u: SET_STRING_WIDTH(buffer, "F3", 2); return buffer + 2l;
	case 244u: SET_STRING_WIDTH(buffer, "F4", 2); return buffer + 2l;
	case 245u: SET_STRING_WIDTH(buffer, "F5", 2); return buffer + 2l;
	case 246u: SET_STRING_WIDTH(buffer, "F6", 2); return buffer + 2l;
	case 247u: SET_STRING_WIDTH(buffer, "F7", 2); return buffer + 2l;
	case 248u: SET_STRING_WIDTH(buffer, "F8", 2); return buffer + 2l;
	case 249u: SET_STRING_WIDTH(buffer, "F9", 2); return buffer + 2l;
	case 250u: SET_STRING_WIDTH(buffer, "FA", 2); return buffer + 2l;
	case 251u: SET_STRING_WIDTH(buffer, "FB", 2); return buffer + 2l;
	case 252u: SET_STRING_WIDTH(buffer, "FC", 2); return buffer + 2l;
	case 253u: SET_STRING_WIDTH(buffer, "FD", 2); return buffer + 2l;
	case 254u: SET_STRING_WIDTH(buffer, "FE", 2); return buffer + 2l;
	default:   SET_STRING_WIDTH(buffer, "FF", 2); return buffer + 2l;
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

inline char *
string_starts_with(const char *restrict string1,
		   const char *restrict string2)
{
	while (1) {
		if (*string1 != *string2)
			return (*string2 == '\0')
			     ? (char *) string1
			     : NULL;

		if (*string1 == '\0')
			return (char *) string1;

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
do_parse_uint(uintmax_t *const restrict n,
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

	const uintmax_t *restrict power       = &ten_pow_map[1];

	const uintptr_t *const restrict until = &ten_pow_map[count_digits];


	while (power < until) {

		--string;

		(*n) += (((uintmax_t) ASCII_TO_DIGIT(*string)) * (*power));

		++power;
	}

	return true;
}

inline char *
do_parse_uint_stop(uintmax_t *const restrict n,
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

	const uintmax_t *restrict power	      = &ten_pow_map[1];

	const uintptr_t *const restrict until = &ten_pow_map[count_digits];


	while (power < until) {

		--string;

		(*n) += (((uintmax_t) ASCII_TO_DIGIT(*string)) * (*power));

		++power;
	}

	return stop_ptr;
}
#endif /* if HAVE_INT_STRING_ATTRS  */

inline bool
parse_uint(uintmax_t *const restrict n,
	   const char *restrict string)
{
#if HAVE_INT_STRING_ATTRS

	return do_parse_uint(n,
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

		if (do_parse_uint((uintmax_t *const restrict) n,
				  string,
				  DIGIT_COUNT_INTMAX_MIN,
				  DIGIT_STRING_INTMAX_MIN)) {
			*n = -(*n);
			return true;
		}

		return false;
	}

	return do_parse_uint((uintmax_t *const restrict) n,
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
	return do_parse_uint_stop(n,
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
		stop_ptr = do_parse_uint_stop((uintmax_t *const restrict) n,
					      string,
					      stop,
					      DIGIT_COUNT_INTMAX_MIN,
					      DIGIT_STRING_INTMAX_MIN);

		if (stop_ptr == NULL)
			return NULL;

		*n = -(*n);
		return stop_ptr;
	}

	return do_parse_uint_stop((uintmax_t *const restrict) n,
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

/* String operations
 * ────────────────────────────────────────────────────────────────────────── */
inline void
string_init(struct String *const restrict string,
	    char *const restrict bytes,
	    const size_t length)
{
	string->bytes  = bytes;
	string->length = length;
}

/* StringInterval operations
 * ────────────────────────────────────────────────────────────────────────── */
inline void
string_interval_init(struct StringInterval *const restrict interval,
		     char *const restrict from,
		     const char *const restrict until)
{
	interval->from	= from;
	interval->until = until;
}

#endif	/* MYSQL_SEED_STRING_STRING_UTILS */
