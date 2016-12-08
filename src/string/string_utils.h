#ifndef MYSQL_SEED_STRING_STRING_UTILS
#define MYSQL_SEED_STRING_STRING_UTILS


/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#ifdef WIN32
#	include <windows.h>	/* FormatMessage, LocalFree */
#endif /* ifdef WIN32 */

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
	unsigned int width; /* 1 - 32 bytes */
};

struct Label {
	char buffer[CHAR_BUFFER_WIDTH_MAX];
	unsigned int width; /* 1 - 32 bytes */
};

struct StringInterval {
	struct String *restrict from;
	const struct String *restrict until;
};

typedef char *
PutStringWidth(char *const restrict buffer,
	       const char *const restrict bytes);

struct PutStubClosure {
	const char *bytes;
	PutStringWidth *put;
};

struct PutLabelClosure {
	char buffer[CHAR_BUFFER_WIDTH_MAX];
	PutStringWidth *put;
};

struct StubBuilder {
	struct PutStubClosure put_cl;
	unsigned int width;
};

struct PutStringClosure {
	const word_t *restrict words;
	const char *restrict rem;
	PutStringWidth *put_rem;
};

struct MobilePutStringClosure {
	const word_t *restrict words;
	const char *restrict rem;
	PutStringWidth *put_rem;
	size_t length_words;
};

struct StringBuilder {
	struct PutStringClosure put_cl;
	size_t length;
};




/* global variables
 *─────────────────────────────────────────────────────────────────────────── */
#if HAVE_INT_STRING_ATTRS
extern const uintmax_t ten_pow_map[DIGIT_COUNT_UINTMAX_MAX];
#endif	/* if HAVE_INT_STRING_ATTRS */

#if HAVE_PTR_STRING_ATTRS
extern const uintptr_t ninety_five_pow_map[LENGTH_MAX_POINTER_ID];
#endif

extern PutStringWidth *const PUT_STRING_WIDTH_MAP[CHAR_BUFFER_WIDTH_MAX + 1];
extern PutStringWidth *const PUT_STRING_STOP_WIDTH_MAP[CHAR_BUFFER_WIDTH_MAX + 1];

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

inline void
copy_string_stop(char *restrict buffer,
		 const char *restrict string)
{
	while (1) {
		*buffer = *string;

		if (*string == '\0')
			return;

		++string;
		++buffer;
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

inline void
put_string_closure_init(struct PutStringClosure *const restrict closure,
			const char *const restrict bytes,
			const size_t size)
{
	const size_t length_words = DIV_WORD_SIZE(size);
	const size_t rem_size     = REM_WORD_SIZE(size);

	closure->words = (const word_t *restrict) bytes;
	closure->rem
	= (const char *restrict) (((const word_t *restrict) bytes)
	+ length_words);
	closure->put_rem = PUT_STRING_WIDTH_MAP[rem_size];
}

inline char *
put_string_closure_call(const struct PutStringClosure *const restrict closure,
			char *restrict buffer)
{
	const word_t *restrict word = closure->words;

	while (word < (const word_t *restrict) closure->rem) {
		*((word_t *restrict) buffer) = *word;
		buffer += WORD_SIZE;
		++word;
	}

	return closure->put_rem(buffer,
				closure->rem);
}

inline void
mobile_put_string_closure_init(struct MobilePutStringClosure *const restrict closure,
			       const char *const restrict bytes,
			       const size_t size)
{
	const size_t length_words = DIV_WORD_SIZE(size);
	const size_t rem_size     = REM_WORD_SIZE(size);

	closure->words = (const word_t *restrict) bytes;
	closure->rem
	= (const char *restrict) (((const word_t *restrict) bytes)
	+ length_words);
	closure->put_rem = PUT_STRING_WIDTH_MAP[rem_size];
	closure->length_words = length_words;
}

inline void
mobile_put_string_closure_move(struct MobilePutStringClosure *const restrict closure,
			       const char *const restrict new_bytes)
{
	closure->words = (const word_t *restrict) new_bytes;
	closure->rem
	= (const char *restrict) (((const word_t *restrict) new_bytes)
	+ closure->length_words);
}

inline char *
mobile_put_string_closure_call(const struct MobilePutStringClosure *const restrict closure,
			       char *restrict buffer)
{
	const word_t *restrict word = closure->words;

	while (word < (const word_t *restrict) closure->rem) {
		*((word_t *restrict) buffer) = *word;
		buffer += WORD_SIZE;
		++word;
	}

	return closure->put_rem(buffer,
				closure->rem);
}

inline void
string_builder_init(struct StringBuilder *const restrict builder,
		    const char *const restrict bytes,
		    const size_t length)
{
	put_string_closure_init(&builder->put_cl,
				bytes,
				length);
	builder->length = length;
}


inline char *
put_string_width(char *const restrict buffer,
		 const char *const restrict string,
		 const unsigned int width)
{
	switch (width) {
	case  0u: return buffer;

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

	case 16u:   *((CharBuffer16 *const restrict) buffer)
		  = *((CharBuffer16 *const restrict) string);
		  return buffer + 16l;

	case 17u:   *((CharBuffer17 *const restrict) buffer)
		  = *((CharBuffer17 *const restrict) string);
		  return buffer + 17l;

	case 18u:   *((CharBuffer18 *const restrict) buffer)
		  = *((CharBuffer18 *const restrict) string);
		  return buffer + 18l;

	case 19u:   *((CharBuffer19 *const restrict) buffer)
		  = *((CharBuffer19 *const restrict) string);
		  return buffer + 19l;

	case 20u:   *((CharBuffer20 *const restrict) buffer)
		  = *((CharBuffer20 *const restrict) string);
		  return buffer + 20l;

	case 21u:   *((CharBuffer21 *const restrict) buffer)
		  = *((CharBuffer21 *const restrict) string);
		  return buffer + 21l;

	case 22u:   *((CharBuffer22 *const restrict) buffer)
		  = *((CharBuffer22 *const restrict) string);
		  return buffer + 22l;

	case 23u:   *((CharBuffer23 *const restrict) buffer)
		  = *((CharBuffer23 *const restrict) string);
		  return buffer + 23l;

	case 24u:   *((CharBuffer24 *const restrict) buffer)
		  = *((CharBuffer24 *const restrict) string);
		  return buffer + 24l;

	case 25u:   *((CharBuffer25 *const restrict) buffer)
		  = *((CharBuffer25 *const restrict) string);
		  return buffer + 25l;

	case 26u:   *((CharBuffer26 *const restrict) buffer)
		  = *((CharBuffer26 *const restrict) string);
		  return buffer + 26l;

	case 27u:   *((CharBuffer27 *const restrict) buffer)
		  = *((CharBuffer27 *const restrict) string);
		  return buffer + 27l;

	case 28u:   *((CharBuffer28 *const restrict) buffer)
		  = *((CharBuffer28 *const restrict) string);
		  return buffer + 28l;

	case 29u:   *((CharBuffer29 *const restrict) buffer)
		  = *((CharBuffer29 *const restrict) string);
		  return buffer + 29l;

	case 30u:   *((CharBuffer30 *const restrict) buffer)
		  = *((CharBuffer30 *const restrict) string);
		  return buffer + 30l;

	case 31u:   *((CharBuffer31 *const restrict) buffer)
		  = *((CharBuffer31 *const restrict) string);
		  return buffer + 31l;

	default:    *((CharBuffer32 *const restrict) buffer)
		  = *((CharBuffer32 *const restrict) string);
		  return buffer + 32l;
	}
}


inline char *
put_string_stop_width(char *const restrict buffer,
		      const char *const restrict string,
		      const unsigned int width)
{
	switch (width) {
	case  0u: *buffer = '\0';
		  return buffer + 1l;

	case  1u:   *((CharBuffer2 *const restrict) buffer)
		  = *((CharBuffer2 *const restrict) string);
		  return buffer + 2l;

	case  2u:   *((CharBuffer3 *const restrict) buffer)
		  = *((CharBuffer3 *const restrict) string);
		  return buffer + 3l;

	case  3u:   *((CharBuffer4 *const restrict) buffer)
		  = *((CharBuffer4 *const restrict) string);
		  return buffer + 4l;

	case  4u:   *((CharBuffer5 *const restrict) buffer)
		  = *((CharBuffer5 *const restrict) string);
		  return buffer + 5l;

	case  5u:   *((CharBuffer6 *const restrict) buffer)
		  = *((CharBuffer6 *const restrict) string);
		  return buffer + 6l;

	case  6u:   *((CharBuffer7 *const restrict) buffer)
		  = *((CharBuffer7 *const restrict) string);
		  return buffer + 7l;

	case  7u:   *((CharBuffer8 *const restrict) buffer)
		  = *((CharBuffer8 *const restrict) string);
		  return buffer + 8l;

	case  8u:   *((CharBuffer9 *const restrict) buffer)
		  = *((CharBuffer9 *const restrict) string);
		  return buffer + 9l;

	case  9u:   *((CharBuffer10 *const restrict) buffer)
		  = *((CharBuffer10 *const restrict) string);
		  return buffer + 10l;

	case 10u:   *((CharBuffer11 *const restrict) buffer)
		  = *((CharBuffer11 *const restrict) string);
		  return buffer + 11l;

	case 11u:   *((CharBuffer12 *const restrict) buffer)
		  = *((CharBuffer12 *const restrict) string);
		  return buffer + 12l;

	case 12u:   *((CharBuffer13 *const restrict) buffer)
		  = *((CharBuffer13 *const restrict) string);
		  return buffer + 13l;

	case 13u:   *((CharBuffer14 *const restrict) buffer)
		  = *((CharBuffer14 *const restrict) string);
		  return buffer + 14l;

	case 14u:   *((CharBuffer15 *const restrict) buffer)
		  = *((CharBuffer15 *const restrict) string);
		  return buffer + 15l;

	case 15u:   *((CharBuffer16 *const restrict) buffer)
		  = *((CharBuffer16 *const restrict) string);
		  return buffer + 16l;

	case 16u:   *((CharBuffer17 *const restrict) buffer)
		  = *((CharBuffer17 *const restrict) string);
		  return buffer + 17l;

	case 17u:   *((CharBuffer18 *const restrict) buffer)
		  = *((CharBuffer18 *const restrict) string);
		  return buffer + 18l;

	case 18u:   *((CharBuffer19 *const restrict) buffer)
		  = *((CharBuffer19 *const restrict) string);
		  return buffer + 19l;

	case 19u:   *((CharBuffer20 *const restrict) buffer)
		  = *((CharBuffer20 *const restrict) string);
		  return buffer + 20l;

	case 20u:   *((CharBuffer21 *const restrict) buffer)
		  = *((CharBuffer21 *const restrict) string);
		  return buffer + 21l;

	case 21u:   *((CharBuffer22 *const restrict) buffer)
		  = *((CharBuffer22 *const restrict) string);
		  return buffer + 22l;

	case 22u:   *((CharBuffer23 *const restrict) buffer)
		  = *((CharBuffer23 *const restrict) string);
		  return buffer + 23l;

	case 23u:   *((CharBuffer24 *const restrict) buffer)
		  = *((CharBuffer24 *const restrict) string);
		  return buffer + 24l;

	case 24u:   *((CharBuffer25 *const restrict) buffer)
		  = *((CharBuffer25 *const restrict) string);
		  return buffer + 25l;

	case 25u:   *((CharBuffer26 *const restrict) buffer)
		  = *((CharBuffer26 *const restrict) string);
		  return buffer + 26l;

	case 26u:   *((CharBuffer27 *const restrict) buffer)
		  = *((CharBuffer27 *const restrict) string);
		  return buffer + 27l;

	case 27u:   *((CharBuffer28 *const restrict) buffer)
		  = *((CharBuffer28 *const restrict) string);
		  return buffer + 28l;

	case 28u:   *((CharBuffer29 *const restrict) buffer)
		  = *((CharBuffer29 *const restrict) string);
		  return buffer + 29l;

	case 29u:   *((CharBuffer30 *const restrict) buffer)
		  = *((CharBuffer30 *const restrict) string);
		  return buffer + 30l;

	case 30u:   *((CharBuffer31 *const restrict) buffer)
		  = *((CharBuffer31 *const restrict) string);
		  return buffer + 31l;

	case 31u:   *((CharBuffer32 *const restrict) buffer)
		  = *((CharBuffer32 *const restrict) string);
		  return buffer + 32l;

	default:    *((CharBuffer33 *const restrict) buffer)
		  = *((CharBuffer33 *const restrict) string);
		  return buffer + 33l;
	}
}

inline char *
put_string_width0(char *const restrict buffer,
		  const char *const restrict bytes)
{
	return buffer;
}

#define DEFINE_PUT_STRING_WIDTH(WIDTH)					\
inline char *								\
put_string_width ## WIDTH (char *const restrict buffer,			\
			   const char *const restrict bytes)		\
{									\
	*((CHAR_BUFFER_WIDTH(WIDTH) *const restrict) buffer)		\
	= *((const CHAR_BUFFER_WIDTH(WIDTH) *const restrict) bytes);	\
	return buffer + WIDTH;						\
}
FOR_ALL_CHAR_BUFFER_WIDTHS(DEFINE_PUT_STRING_WIDTH)

inline char *
put_string_stop_width0(char *const restrict buffer,
		       const char *const restrict bytes)
{
	*buffer = '\0';
	return buffer + 1l;
}

#define DEFINE_PUT_STRING_STOP_WIDTH(WIDTH, WIDTH_STOP)			\
inline char *								\
put_string_stop_width ## WIDTH (char *const restrict buffer,		\
				const char *const restrict bytes)	\
{									\
	*((CHAR_BUFFER_WIDTH(WIDTH_STOP) *const restrict) buffer)	\
	= *((const CHAR_BUFFER_WIDTH(WIDTH_STOP) *const restrict)	\
	    bytes);							\
	return buffer + WIDTH_STOP;					\
}
FOR_ALL_CHAR_BUFFER_WIDTHS_STOP(DEFINE_PUT_STRING_STOP_WIDTH)


inline char *
put_string_width_until(char *const restrict buffer,
		       const char *const restrict string,
		       const unsigned int width,
		       const char *const restrict until)
{
	const size_t size_until = until - buffer;

	return put_string_width(buffer,
				string,
				(size_until < width)
				? ((const unsigned int) size_until)
				: width);
}

inline void
put_stub_closure_init(struct PutStubClosure *const restrict closure,
		      const char *const restrict bytes,
		      const unsigned int width)
{
	closure->bytes = bytes;
	closure->put   = PUT_STRING_WIDTH_MAP[width];
}

inline void
put_stub_closure_stop_init(struct PutStubClosure *const restrict closure,
			   const char *const restrict bytes,
			   const unsigned int width)
{
	closure->bytes = bytes;
	closure->put   = PUT_STRING_STOP_WIDTH_MAP[width];
}

inline char *
put_stub_closure_call(const struct PutStubClosure *const restrict closure,
		      char *const restrict buffer)
{
	return closure->put(buffer,
			    closure->bytes);
}

inline void
stub_builder_init(struct StubBuilder *const restrict builder,
		  const char *const restrict bytes,
		  const unsigned int width)
{
	put_stub_closure_init(&builder->put_cl,
			      bytes,
			      width);
	builder->width = width;
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
put_stub_stop(char *const restrict buffer,
	      const struct Stub *const restrict stub)
{
	return put_string_stop_width(buffer,
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
put_label_stop(char *const restrict buffer,
	       const struct Label *const restrict label)
{
	return put_string_stop_width(buffer,
				     &label->buffer[0],
				     label->width);
}

inline char *
put_label_closure_call(const struct PutLabelClosure *const restrict closure,
		       char *const restrict buffer)
{
	return closure->put(buffer,
			    &closure->buffer[0]);
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
		   const size_t length)
{
	const char *const restrict until = string + length;

	while (1) {
		if (string == until) {
			PUT_STRING_WIDTH(buffer,
					 "...",
					 3);
			return buffer;
		}

		if (*string == '\0')
			return buffer;

		*buffer = *string;
		++buffer;
		++string;
	}
}


inline char *
put_octet_hex_lower(char *const restrict buffer,
		    const octet_t octet)
{
	switch (octet) {
	case 0x00: SET_STRING_WIDTH(buffer, "00", 2); return buffer + 2l;
	case 0x01: SET_STRING_WIDTH(buffer, "01", 2); return buffer + 2l;
	case 0x02: SET_STRING_WIDTH(buffer, "02", 2); return buffer + 2l;
	case 0x03: SET_STRING_WIDTH(buffer, "03", 2); return buffer + 2l;
	case 0x04: SET_STRING_WIDTH(buffer, "04", 2); return buffer + 2l;
	case 0x05: SET_STRING_WIDTH(buffer, "05", 2); return buffer + 2l;
	case 0x06: SET_STRING_WIDTH(buffer, "06", 2); return buffer + 2l;
	case 0x07: SET_STRING_WIDTH(buffer, "07", 2); return buffer + 2l;
	case 0x08: SET_STRING_WIDTH(buffer, "08", 2); return buffer + 2l;
	case 0x09: SET_STRING_WIDTH(buffer, "09", 2); return buffer + 2l;
	case 0x0a: SET_STRING_WIDTH(buffer, "0a", 2); return buffer + 2l;
	case 0x0b: SET_STRING_WIDTH(buffer, "0b", 2); return buffer + 2l;
	case 0x0c: SET_STRING_WIDTH(buffer, "0c", 2); return buffer + 2l;
	case 0x0d: SET_STRING_WIDTH(buffer, "0d", 2); return buffer + 2l;
	case 0x0e: SET_STRING_WIDTH(buffer, "0e", 2); return buffer + 2l;
	case 0x0f: SET_STRING_WIDTH(buffer, "0f", 2); return buffer + 2l;
	case 0x10: SET_STRING_WIDTH(buffer, "10", 2); return buffer + 2l;
	case 0x11: SET_STRING_WIDTH(buffer, "11", 2); return buffer + 2l;
	case 0x12: SET_STRING_WIDTH(buffer, "12", 2); return buffer + 2l;
	case 0x13: SET_STRING_WIDTH(buffer, "13", 2); return buffer + 2l;
	case 0x14: SET_STRING_WIDTH(buffer, "14", 2); return buffer + 2l;
	case 0x15: SET_STRING_WIDTH(buffer, "15", 2); return buffer + 2l;
	case 0x16: SET_STRING_WIDTH(buffer, "16", 2); return buffer + 2l;
	case 0x17: SET_STRING_WIDTH(buffer, "17", 2); return buffer + 2l;
	case 0x18: SET_STRING_WIDTH(buffer, "18", 2); return buffer + 2l;
	case 0x19: SET_STRING_WIDTH(buffer, "19", 2); return buffer + 2l;
	case 0x1a: SET_STRING_WIDTH(buffer, "1a", 2); return buffer + 2l;
	case 0x1b: SET_STRING_WIDTH(buffer, "1b", 2); return buffer + 2l;
	case 0x1c: SET_STRING_WIDTH(buffer, "1c", 2); return buffer + 2l;
	case 0x1d: SET_STRING_WIDTH(buffer, "1d", 2); return buffer + 2l;
	case 0x1e: SET_STRING_WIDTH(buffer, "1e", 2); return buffer + 2l;
	case 0x1f: SET_STRING_WIDTH(buffer, "1f", 2); return buffer + 2l;
	case 0x20: SET_STRING_WIDTH(buffer, "20", 2); return buffer + 2l;
	case 0x21: SET_STRING_WIDTH(buffer, "21", 2); return buffer + 2l;
	case 0x22: SET_STRING_WIDTH(buffer, "22", 2); return buffer + 2l;
	case 0x23: SET_STRING_WIDTH(buffer, "23", 2); return buffer + 2l;
	case 0x24: SET_STRING_WIDTH(buffer, "24", 2); return buffer + 2l;
	case 0x25: SET_STRING_WIDTH(buffer, "25", 2); return buffer + 2l;
	case 0x26: SET_STRING_WIDTH(buffer, "26", 2); return buffer + 2l;
	case 0x27: SET_STRING_WIDTH(buffer, "27", 2); return buffer + 2l;
	case 0x28: SET_STRING_WIDTH(buffer, "28", 2); return buffer + 2l;
	case 0x29: SET_STRING_WIDTH(buffer, "29", 2); return buffer + 2l;
	case 0x2a: SET_STRING_WIDTH(buffer, "2a", 2); return buffer + 2l;
	case 0x2b: SET_STRING_WIDTH(buffer, "2b", 2); return buffer + 2l;
	case 0x2c: SET_STRING_WIDTH(buffer, "2c", 2); return buffer + 2l;
	case 0x2d: SET_STRING_WIDTH(buffer, "2d", 2); return buffer + 2l;
	case 0x2e: SET_STRING_WIDTH(buffer, "2e", 2); return buffer + 2l;
	case 0x2f: SET_STRING_WIDTH(buffer, "2f", 2); return buffer + 2l;
	case 0x30: SET_STRING_WIDTH(buffer, "30", 2); return buffer + 2l;
	case 0x31: SET_STRING_WIDTH(buffer, "31", 2); return buffer + 2l;
	case 0x32: SET_STRING_WIDTH(buffer, "32", 2); return buffer + 2l;
	case 0x33: SET_STRING_WIDTH(buffer, "33", 2); return buffer + 2l;
	case 0x34: SET_STRING_WIDTH(buffer, "34", 2); return buffer + 2l;
	case 0x35: SET_STRING_WIDTH(buffer, "35", 2); return buffer + 2l;
	case 0x36: SET_STRING_WIDTH(buffer, "36", 2); return buffer + 2l;
	case 0x37: SET_STRING_WIDTH(buffer, "37", 2); return buffer + 2l;
	case 0x38: SET_STRING_WIDTH(buffer, "38", 2); return buffer + 2l;
	case 0x39: SET_STRING_WIDTH(buffer, "39", 2); return buffer + 2l;
	case 0x3a: SET_STRING_WIDTH(buffer, "3a", 2); return buffer + 2l;
	case 0x3b: SET_STRING_WIDTH(buffer, "3b", 2); return buffer + 2l;
	case 0x3c: SET_STRING_WIDTH(buffer, "3c", 2); return buffer + 2l;
	case 0x3d: SET_STRING_WIDTH(buffer, "3d", 2); return buffer + 2l;
	case 0x3e: SET_STRING_WIDTH(buffer, "3e", 2); return buffer + 2l;
	case 0x3f: SET_STRING_WIDTH(buffer, "3f", 2); return buffer + 2l;
	case 0x40: SET_STRING_WIDTH(buffer, "40", 2); return buffer + 2l;
	case 0x41: SET_STRING_WIDTH(buffer, "41", 2); return buffer + 2l;
	case 0x42: SET_STRING_WIDTH(buffer, "42", 2); return buffer + 2l;
	case 0x43: SET_STRING_WIDTH(buffer, "43", 2); return buffer + 2l;
	case 0x44: SET_STRING_WIDTH(buffer, "44", 2); return buffer + 2l;
	case 0x45: SET_STRING_WIDTH(buffer, "45", 2); return buffer + 2l;
	case 0x46: SET_STRING_WIDTH(buffer, "46", 2); return buffer + 2l;
	case 0x47: SET_STRING_WIDTH(buffer, "47", 2); return buffer + 2l;
	case 0x48: SET_STRING_WIDTH(buffer, "48", 2); return buffer + 2l;
	case 0x49: SET_STRING_WIDTH(buffer, "49", 2); return buffer + 2l;
	case 0x4a: SET_STRING_WIDTH(buffer, "4a", 2); return buffer + 2l;
	case 0x4b: SET_STRING_WIDTH(buffer, "4b", 2); return buffer + 2l;
	case 0x4c: SET_STRING_WIDTH(buffer, "4c", 2); return buffer + 2l;
	case 0x4d: SET_STRING_WIDTH(buffer, "4d", 2); return buffer + 2l;
	case 0x4e: SET_STRING_WIDTH(buffer, "4e", 2); return buffer + 2l;
	case 0x4f: SET_STRING_WIDTH(buffer, "4f", 2); return buffer + 2l;
	case 0x50: SET_STRING_WIDTH(buffer, "50", 2); return buffer + 2l;
	case 0x51: SET_STRING_WIDTH(buffer, "51", 2); return buffer + 2l;
	case 0x52: SET_STRING_WIDTH(buffer, "52", 2); return buffer + 2l;
	case 0x53: SET_STRING_WIDTH(buffer, "53", 2); return buffer + 2l;
	case 0x54: SET_STRING_WIDTH(buffer, "54", 2); return buffer + 2l;
	case 0x55: SET_STRING_WIDTH(buffer, "55", 2); return buffer + 2l;
	case 0x56: SET_STRING_WIDTH(buffer, "56", 2); return buffer + 2l;
	case 0x57: SET_STRING_WIDTH(buffer, "57", 2); return buffer + 2l;
	case 0x58: SET_STRING_WIDTH(buffer, "58", 2); return buffer + 2l;
	case 0x59: SET_STRING_WIDTH(buffer, "59", 2); return buffer + 2l;
	case 0x5a: SET_STRING_WIDTH(buffer, "5a", 2); return buffer + 2l;
	case 0x5b: SET_STRING_WIDTH(buffer, "5b", 2); return buffer + 2l;
	case 0x5c: SET_STRING_WIDTH(buffer, "5c", 2); return buffer + 2l;
	case 0x5d: SET_STRING_WIDTH(buffer, "5d", 2); return buffer + 2l;
	case 0x5e: SET_STRING_WIDTH(buffer, "5e", 2); return buffer + 2l;
	case 0x5f: SET_STRING_WIDTH(buffer, "5f", 2); return buffer + 2l;
	case 0x60: SET_STRING_WIDTH(buffer, "60", 2); return buffer + 2l;
	case 0x61: SET_STRING_WIDTH(buffer, "61", 2); return buffer + 2l;
	case 0x62: SET_STRING_WIDTH(buffer, "62", 2); return buffer + 2l;
	case 0x63: SET_STRING_WIDTH(buffer, "63", 2); return buffer + 2l;
	case 0x64: SET_STRING_WIDTH(buffer, "64", 2); return buffer + 2l;
	case 0x65: SET_STRING_WIDTH(buffer, "65", 2); return buffer + 2l;
	case 0x66: SET_STRING_WIDTH(buffer, "66", 2); return buffer + 2l;
	case 0x67: SET_STRING_WIDTH(buffer, "67", 2); return buffer + 2l;
	case 0x68: SET_STRING_WIDTH(buffer, "68", 2); return buffer + 2l;
	case 0x69: SET_STRING_WIDTH(buffer, "69", 2); return buffer + 2l;
	case 0x6a: SET_STRING_WIDTH(buffer, "6a", 2); return buffer + 2l;
	case 0x6b: SET_STRING_WIDTH(buffer, "6b", 2); return buffer + 2l;
	case 0x6c: SET_STRING_WIDTH(buffer, "6c", 2); return buffer + 2l;
	case 0x6d: SET_STRING_WIDTH(buffer, "6d", 2); return buffer + 2l;
	case 0x6e: SET_STRING_WIDTH(buffer, "6e", 2); return buffer + 2l;
	case 0x6f: SET_STRING_WIDTH(buffer, "6f", 2); return buffer + 2l;
	case 0x70: SET_STRING_WIDTH(buffer, "70", 2); return buffer + 2l;
	case 0x71: SET_STRING_WIDTH(buffer, "71", 2); return buffer + 2l;
	case 0x72: SET_STRING_WIDTH(buffer, "72", 2); return buffer + 2l;
	case 0x73: SET_STRING_WIDTH(buffer, "73", 2); return buffer + 2l;
	case 0x74: SET_STRING_WIDTH(buffer, "74", 2); return buffer + 2l;
	case 0x75: SET_STRING_WIDTH(buffer, "75", 2); return buffer + 2l;
	case 0x76: SET_STRING_WIDTH(buffer, "76", 2); return buffer + 2l;
	case 0x77: SET_STRING_WIDTH(buffer, "77", 2); return buffer + 2l;
	case 0x78: SET_STRING_WIDTH(buffer, "78", 2); return buffer + 2l;
	case 0x79: SET_STRING_WIDTH(buffer, "79", 2); return buffer + 2l;
	case 0x7a: SET_STRING_WIDTH(buffer, "7a", 2); return buffer + 2l;
	case 0x7b: SET_STRING_WIDTH(buffer, "7b", 2); return buffer + 2l;
	case 0x7c: SET_STRING_WIDTH(buffer, "7c", 2); return buffer + 2l;
	case 0x7d: SET_STRING_WIDTH(buffer, "7d", 2); return buffer + 2l;
	case 0x7e: SET_STRING_WIDTH(buffer, "7e", 2); return buffer + 2l;
	case 0x7f: SET_STRING_WIDTH(buffer, "7f", 2); return buffer + 2l;
	case 0x80: SET_STRING_WIDTH(buffer, "80", 2); return buffer + 2l;
	case 0x81: SET_STRING_WIDTH(buffer, "81", 2); return buffer + 2l;
	case 0x82: SET_STRING_WIDTH(buffer, "82", 2); return buffer + 2l;
	case 0x83: SET_STRING_WIDTH(buffer, "83", 2); return buffer + 2l;
	case 0x84: SET_STRING_WIDTH(buffer, "84", 2); return buffer + 2l;
	case 0x85: SET_STRING_WIDTH(buffer, "85", 2); return buffer + 2l;
	case 0x86: SET_STRING_WIDTH(buffer, "86", 2); return buffer + 2l;
	case 0x87: SET_STRING_WIDTH(buffer, "87", 2); return buffer + 2l;
	case 0x88: SET_STRING_WIDTH(buffer, "88", 2); return buffer + 2l;
	case 0x89: SET_STRING_WIDTH(buffer, "89", 2); return buffer + 2l;
	case 0x8a: SET_STRING_WIDTH(buffer, "8a", 2); return buffer + 2l;
	case 0x8b: SET_STRING_WIDTH(buffer, "8b", 2); return buffer + 2l;
	case 0x8c: SET_STRING_WIDTH(buffer, "8c", 2); return buffer + 2l;
	case 0x8d: SET_STRING_WIDTH(buffer, "8d", 2); return buffer + 2l;
	case 0x8e: SET_STRING_WIDTH(buffer, "8e", 2); return buffer + 2l;
	case 0x8f: SET_STRING_WIDTH(buffer, "8f", 2); return buffer + 2l;
	case 0x90: SET_STRING_WIDTH(buffer, "90", 2); return buffer + 2l;
	case 0x91: SET_STRING_WIDTH(buffer, "91", 2); return buffer + 2l;
	case 0x92: SET_STRING_WIDTH(buffer, "92", 2); return buffer + 2l;
	case 0x93: SET_STRING_WIDTH(buffer, "93", 2); return buffer + 2l;
	case 0x94: SET_STRING_WIDTH(buffer, "94", 2); return buffer + 2l;
	case 0x95: SET_STRING_WIDTH(buffer, "95", 2); return buffer + 2l;
	case 0x96: SET_STRING_WIDTH(buffer, "96", 2); return buffer + 2l;
	case 0x97: SET_STRING_WIDTH(buffer, "97", 2); return buffer + 2l;
	case 0x98: SET_STRING_WIDTH(buffer, "98", 2); return buffer + 2l;
	case 0x99: SET_STRING_WIDTH(buffer, "99", 2); return buffer + 2l;
	case 0x9a: SET_STRING_WIDTH(buffer, "9a", 2); return buffer + 2l;
	case 0x9b: SET_STRING_WIDTH(buffer, "9b", 2); return buffer + 2l;
	case 0x9c: SET_STRING_WIDTH(buffer, "9c", 2); return buffer + 2l;
	case 0x9d: SET_STRING_WIDTH(buffer, "9d", 2); return buffer + 2l;
	case 0x9e: SET_STRING_WIDTH(buffer, "9e", 2); return buffer + 2l;
	case 0x9f: SET_STRING_WIDTH(buffer, "9f", 2); return buffer + 2l;
	case 0xa0: SET_STRING_WIDTH(buffer, "a0", 2); return buffer + 2l;
	case 0xa1: SET_STRING_WIDTH(buffer, "a1", 2); return buffer + 2l;
	case 0xa2: SET_STRING_WIDTH(buffer, "a2", 2); return buffer + 2l;
	case 0xa3: SET_STRING_WIDTH(buffer, "a3", 2); return buffer + 2l;
	case 0xa4: SET_STRING_WIDTH(buffer, "a4", 2); return buffer + 2l;
	case 0xa5: SET_STRING_WIDTH(buffer, "a5", 2); return buffer + 2l;
	case 0xa6: SET_STRING_WIDTH(buffer, "a6", 2); return buffer + 2l;
	case 0xa7: SET_STRING_WIDTH(buffer, "a7", 2); return buffer + 2l;
	case 0xa8: SET_STRING_WIDTH(buffer, "a8", 2); return buffer + 2l;
	case 0xa9: SET_STRING_WIDTH(buffer, "a9", 2); return buffer + 2l;
	case 0xaa: SET_STRING_WIDTH(buffer, "aa", 2); return buffer + 2l;
	case 0xab: SET_STRING_WIDTH(buffer, "ab", 2); return buffer + 2l;
	case 0xac: SET_STRING_WIDTH(buffer, "ac", 2); return buffer + 2l;
	case 0xad: SET_STRING_WIDTH(buffer, "ad", 2); return buffer + 2l;
	case 0xae: SET_STRING_WIDTH(buffer, "ae", 2); return buffer + 2l;
	case 0xaf: SET_STRING_WIDTH(buffer, "af", 2); return buffer + 2l;
	case 0xb0: SET_STRING_WIDTH(buffer, "b0", 2); return buffer + 2l;
	case 0xb1: SET_STRING_WIDTH(buffer, "b1", 2); return buffer + 2l;
	case 0xb2: SET_STRING_WIDTH(buffer, "b2", 2); return buffer + 2l;
	case 0xb3: SET_STRING_WIDTH(buffer, "b3", 2); return buffer + 2l;
	case 0xb4: SET_STRING_WIDTH(buffer, "b4", 2); return buffer + 2l;
	case 0xb5: SET_STRING_WIDTH(buffer, "b5", 2); return buffer + 2l;
	case 0xb6: SET_STRING_WIDTH(buffer, "b6", 2); return buffer + 2l;
	case 0xb7: SET_STRING_WIDTH(buffer, "b7", 2); return buffer + 2l;
	case 0xb8: SET_STRING_WIDTH(buffer, "b8", 2); return buffer + 2l;
	case 0xb9: SET_STRING_WIDTH(buffer, "b9", 2); return buffer + 2l;
	case 0xba: SET_STRING_WIDTH(buffer, "ba", 2); return buffer + 2l;
	case 0xbb: SET_STRING_WIDTH(buffer, "bb", 2); return buffer + 2l;
	case 0xbc: SET_STRING_WIDTH(buffer, "bc", 2); return buffer + 2l;
	case 0xbd: SET_STRING_WIDTH(buffer, "bd", 2); return buffer + 2l;
	case 0xbe: SET_STRING_WIDTH(buffer, "be", 2); return buffer + 2l;
	case 0xbf: SET_STRING_WIDTH(buffer, "bf", 2); return buffer + 2l;
	case 0xc0: SET_STRING_WIDTH(buffer, "c0", 2); return buffer + 2l;
	case 0xc1: SET_STRING_WIDTH(buffer, "c1", 2); return buffer + 2l;
	case 0xc2: SET_STRING_WIDTH(buffer, "c2", 2); return buffer + 2l;
	case 0xc3: SET_STRING_WIDTH(buffer, "c3", 2); return buffer + 2l;
	case 0xc4: SET_STRING_WIDTH(buffer, "c4", 2); return buffer + 2l;
	case 0xc5: SET_STRING_WIDTH(buffer, "c5", 2); return buffer + 2l;
	case 0xc6: SET_STRING_WIDTH(buffer, "c6", 2); return buffer + 2l;
	case 0xc7: SET_STRING_WIDTH(buffer, "c7", 2); return buffer + 2l;
	case 0xc8: SET_STRING_WIDTH(buffer, "c8", 2); return buffer + 2l;
	case 0xc9: SET_STRING_WIDTH(buffer, "c9", 2); return buffer + 2l;
	case 0xca: SET_STRING_WIDTH(buffer, "ca", 2); return buffer + 2l;
	case 0xcb: SET_STRING_WIDTH(buffer, "cb", 2); return buffer + 2l;
	case 0xcc: SET_STRING_WIDTH(buffer, "cc", 2); return buffer + 2l;
	case 0xcd: SET_STRING_WIDTH(buffer, "cd", 2); return buffer + 2l;
	case 0xce: SET_STRING_WIDTH(buffer, "ce", 2); return buffer + 2l;
	case 0xcf: SET_STRING_WIDTH(buffer, "cf", 2); return buffer + 2l;
	case 0xd0: SET_STRING_WIDTH(buffer, "d0", 2); return buffer + 2l;
	case 0xd1: SET_STRING_WIDTH(buffer, "d1", 2); return buffer + 2l;
	case 0xd2: SET_STRING_WIDTH(buffer, "d2", 2); return buffer + 2l;
	case 0xd3: SET_STRING_WIDTH(buffer, "d3", 2); return buffer + 2l;
	case 0xd4: SET_STRING_WIDTH(buffer, "d4", 2); return buffer + 2l;
	case 0xd5: SET_STRING_WIDTH(buffer, "d5", 2); return buffer + 2l;
	case 0xd6: SET_STRING_WIDTH(buffer, "d6", 2); return buffer + 2l;
	case 0xd7: SET_STRING_WIDTH(buffer, "d7", 2); return buffer + 2l;
	case 0xd8: SET_STRING_WIDTH(buffer, "d8", 2); return buffer + 2l;
	case 0xd9: SET_STRING_WIDTH(buffer, "d9", 2); return buffer + 2l;
	case 0xda: SET_STRING_WIDTH(buffer, "da", 2); return buffer + 2l;
	case 0xdb: SET_STRING_WIDTH(buffer, "db", 2); return buffer + 2l;
	case 0xdc: SET_STRING_WIDTH(buffer, "dc", 2); return buffer + 2l;
	case 0xdd: SET_STRING_WIDTH(buffer, "dd", 2); return buffer + 2l;
	case 0xde: SET_STRING_WIDTH(buffer, "de", 2); return buffer + 2l;
	case 0xdf: SET_STRING_WIDTH(buffer, "df", 2); return buffer + 2l;
	case 0xe0: SET_STRING_WIDTH(buffer, "e0", 2); return buffer + 2l;
	case 0xe1: SET_STRING_WIDTH(buffer, "e1", 2); return buffer + 2l;
	case 0xe2: SET_STRING_WIDTH(buffer, "e2", 2); return buffer + 2l;
	case 0xe3: SET_STRING_WIDTH(buffer, "e3", 2); return buffer + 2l;
	case 0xe4: SET_STRING_WIDTH(buffer, "e4", 2); return buffer + 2l;
	case 0xe5: SET_STRING_WIDTH(buffer, "e5", 2); return buffer + 2l;
	case 0xe6: SET_STRING_WIDTH(buffer, "e6", 2); return buffer + 2l;
	case 0xe7: SET_STRING_WIDTH(buffer, "e7", 2); return buffer + 2l;
	case 0xe8: SET_STRING_WIDTH(buffer, "e8", 2); return buffer + 2l;
	case 0xe9: SET_STRING_WIDTH(buffer, "e9", 2); return buffer + 2l;
	case 0xea: SET_STRING_WIDTH(buffer, "ea", 2); return buffer + 2l;
	case 0xeb: SET_STRING_WIDTH(buffer, "eb", 2); return buffer + 2l;
	case 0xec: SET_STRING_WIDTH(buffer, "ec", 2); return buffer + 2l;
	case 0xed: SET_STRING_WIDTH(buffer, "ed", 2); return buffer + 2l;
	case 0xee: SET_STRING_WIDTH(buffer, "ee", 2); return buffer + 2l;
	case 0xef: SET_STRING_WIDTH(buffer, "ef", 2); return buffer + 2l;
	case 0xf0: SET_STRING_WIDTH(buffer, "f0", 2); return buffer + 2l;
	case 0xf1: SET_STRING_WIDTH(buffer, "f1", 2); return buffer + 2l;
	case 0xf2: SET_STRING_WIDTH(buffer, "f2", 2); return buffer + 2l;
	case 0xf3: SET_STRING_WIDTH(buffer, "f3", 2); return buffer + 2l;
	case 0xf4: SET_STRING_WIDTH(buffer, "f4", 2); return buffer + 2l;
	case 0xf5: SET_STRING_WIDTH(buffer, "f5", 2); return buffer + 2l;
	case 0xf6: SET_STRING_WIDTH(buffer, "f6", 2); return buffer + 2l;
	case 0xf7: SET_STRING_WIDTH(buffer, "f7", 2); return buffer + 2l;
	case 0xf8: SET_STRING_WIDTH(buffer, "f8", 2); return buffer + 2l;
	case 0xf9: SET_STRING_WIDTH(buffer, "f9", 2); return buffer + 2l;
	case 0xfa: SET_STRING_WIDTH(buffer, "fa", 2); return buffer + 2l;
	case 0xfb: SET_STRING_WIDTH(buffer, "fb", 2); return buffer + 2l;
	case 0xfc: SET_STRING_WIDTH(buffer, "fc", 2); return buffer + 2l;
	case 0xfd: SET_STRING_WIDTH(buffer, "fd", 2); return buffer + 2l;
	case 0xfe: SET_STRING_WIDTH(buffer, "fe", 2); return buffer + 2l;
	default:   SET_STRING_WIDTH(buffer, "ff", 2); return buffer + 2l;
	}
}

inline char *
put_octet_hex_upper(char *const restrict buffer,
		    const octet_t octet)
{
	switch (octet) {
	case 0x00: SET_STRING_WIDTH(buffer, "00", 2); return buffer + 2l;
	case 0x01: SET_STRING_WIDTH(buffer, "01", 2); return buffer + 2l;
	case 0x02: SET_STRING_WIDTH(buffer, "02", 2); return buffer + 2l;
	case 0x03: SET_STRING_WIDTH(buffer, "03", 2); return buffer + 2l;
	case 0x04: SET_STRING_WIDTH(buffer, "04", 2); return buffer + 2l;
	case 0x05: SET_STRING_WIDTH(buffer, "05", 2); return buffer + 2l;
	case 0x06: SET_STRING_WIDTH(buffer, "06", 2); return buffer + 2l;
	case 0x07: SET_STRING_WIDTH(buffer, "07", 2); return buffer + 2l;
	case 0x08: SET_STRING_WIDTH(buffer, "08", 2); return buffer + 2l;
	case 0x09: SET_STRING_WIDTH(buffer, "09", 2); return buffer + 2l;
	case 0x0A: SET_STRING_WIDTH(buffer, "0A", 2); return buffer + 2l;
	case 0x0B: SET_STRING_WIDTH(buffer, "0B", 2); return buffer + 2l;
	case 0x0C: SET_STRING_WIDTH(buffer, "0C", 2); return buffer + 2l;
	case 0x0D: SET_STRING_WIDTH(buffer, "0D", 2); return buffer + 2l;
	case 0x0E: SET_STRING_WIDTH(buffer, "0E", 2); return buffer + 2l;
	case 0x0F: SET_STRING_WIDTH(buffer, "0F", 2); return buffer + 2l;
	case 0x10: SET_STRING_WIDTH(buffer, "10", 2); return buffer + 2l;
	case 0x11: SET_STRING_WIDTH(buffer, "11", 2); return buffer + 2l;
	case 0x12: SET_STRING_WIDTH(buffer, "12", 2); return buffer + 2l;
	case 0x13: SET_STRING_WIDTH(buffer, "13", 2); return buffer + 2l;
	case 0x14: SET_STRING_WIDTH(buffer, "14", 2); return buffer + 2l;
	case 0x15: SET_STRING_WIDTH(buffer, "15", 2); return buffer + 2l;
	case 0x16: SET_STRING_WIDTH(buffer, "16", 2); return buffer + 2l;
	case 0x17: SET_STRING_WIDTH(buffer, "17", 2); return buffer + 2l;
	case 0x18: SET_STRING_WIDTH(buffer, "18", 2); return buffer + 2l;
	case 0x19: SET_STRING_WIDTH(buffer, "19", 2); return buffer + 2l;
	case 0x1A: SET_STRING_WIDTH(buffer, "1A", 2); return buffer + 2l;
	case 0x1B: SET_STRING_WIDTH(buffer, "1B", 2); return buffer + 2l;
	case 0x1C: SET_STRING_WIDTH(buffer, "1C", 2); return buffer + 2l;
	case 0x1D: SET_STRING_WIDTH(buffer, "1D", 2); return buffer + 2l;
	case 0x1E: SET_STRING_WIDTH(buffer, "1E", 2); return buffer + 2l;
	case 0x1F: SET_STRING_WIDTH(buffer, "1F", 2); return buffer + 2l;
	case 0x20: SET_STRING_WIDTH(buffer, "20", 2); return buffer + 2l;
	case 0x21: SET_STRING_WIDTH(buffer, "21", 2); return buffer + 2l;
	case 0x22: SET_STRING_WIDTH(buffer, "22", 2); return buffer + 2l;
	case 0x23: SET_STRING_WIDTH(buffer, "23", 2); return buffer + 2l;
	case 0x24: SET_STRING_WIDTH(buffer, "24", 2); return buffer + 2l;
	case 0x25: SET_STRING_WIDTH(buffer, "25", 2); return buffer + 2l;
	case 0x26: SET_STRING_WIDTH(buffer, "26", 2); return buffer + 2l;
	case 0x27: SET_STRING_WIDTH(buffer, "27", 2); return buffer + 2l;
	case 0x28: SET_STRING_WIDTH(buffer, "28", 2); return buffer + 2l;
	case 0x29: SET_STRING_WIDTH(buffer, "29", 2); return buffer + 2l;
	case 0x2A: SET_STRING_WIDTH(buffer, "2A", 2); return buffer + 2l;
	case 0x2B: SET_STRING_WIDTH(buffer, "2B", 2); return buffer + 2l;
	case 0x2C: SET_STRING_WIDTH(buffer, "2C", 2); return buffer + 2l;
	case 0x2D: SET_STRING_WIDTH(buffer, "2D", 2); return buffer + 2l;
	case 0x2E: SET_STRING_WIDTH(buffer, "2E", 2); return buffer + 2l;
	case 0x2F: SET_STRING_WIDTH(buffer, "2F", 2); return buffer + 2l;
	case 0x30: SET_STRING_WIDTH(buffer, "30", 2); return buffer + 2l;
	case 0x31: SET_STRING_WIDTH(buffer, "31", 2); return buffer + 2l;
	case 0x32: SET_STRING_WIDTH(buffer, "32", 2); return buffer + 2l;
	case 0x33: SET_STRING_WIDTH(buffer, "33", 2); return buffer + 2l;
	case 0x34: SET_STRING_WIDTH(buffer, "34", 2); return buffer + 2l;
	case 0x35: SET_STRING_WIDTH(buffer, "35", 2); return buffer + 2l;
	case 0x36: SET_STRING_WIDTH(buffer, "36", 2); return buffer + 2l;
	case 0x37: SET_STRING_WIDTH(buffer, "37", 2); return buffer + 2l;
	case 0x38: SET_STRING_WIDTH(buffer, "38", 2); return buffer + 2l;
	case 0x39: SET_STRING_WIDTH(buffer, "39", 2); return buffer + 2l;
	case 0x3A: SET_STRING_WIDTH(buffer, "3A", 2); return buffer + 2l;
	case 0x3B: SET_STRING_WIDTH(buffer, "3B", 2); return buffer + 2l;
	case 0x3C: SET_STRING_WIDTH(buffer, "3C", 2); return buffer + 2l;
	case 0x3D: SET_STRING_WIDTH(buffer, "3D", 2); return buffer + 2l;
	case 0x3E: SET_STRING_WIDTH(buffer, "3E", 2); return buffer + 2l;
	case 0x3F: SET_STRING_WIDTH(buffer, "3F", 2); return buffer + 2l;
	case 0x40: SET_STRING_WIDTH(buffer, "40", 2); return buffer + 2l;
	case 0x41: SET_STRING_WIDTH(buffer, "41", 2); return buffer + 2l;
	case 0x42: SET_STRING_WIDTH(buffer, "42", 2); return buffer + 2l;
	case 0x43: SET_STRING_WIDTH(buffer, "43", 2); return buffer + 2l;
	case 0x44: SET_STRING_WIDTH(buffer, "44", 2); return buffer + 2l;
	case 0x45: SET_STRING_WIDTH(buffer, "45", 2); return buffer + 2l;
	case 0x46: SET_STRING_WIDTH(buffer, "46", 2); return buffer + 2l;
	case 0x47: SET_STRING_WIDTH(buffer, "47", 2); return buffer + 2l;
	case 0x48: SET_STRING_WIDTH(buffer, "48", 2); return buffer + 2l;
	case 0x49: SET_STRING_WIDTH(buffer, "49", 2); return buffer + 2l;
	case 0x4A: SET_STRING_WIDTH(buffer, "4A", 2); return buffer + 2l;
	case 0x4B: SET_STRING_WIDTH(buffer, "4B", 2); return buffer + 2l;
	case 0x4C: SET_STRING_WIDTH(buffer, "4C", 2); return buffer + 2l;
	case 0x4D: SET_STRING_WIDTH(buffer, "4D", 2); return buffer + 2l;
	case 0x4E: SET_STRING_WIDTH(buffer, "4E", 2); return buffer + 2l;
	case 0x4F: SET_STRING_WIDTH(buffer, "4F", 2); return buffer + 2l;
	case 0x50: SET_STRING_WIDTH(buffer, "50", 2); return buffer + 2l;
	case 0x51: SET_STRING_WIDTH(buffer, "51", 2); return buffer + 2l;
	case 0x52: SET_STRING_WIDTH(buffer, "52", 2); return buffer + 2l;
	case 0x53: SET_STRING_WIDTH(buffer, "53", 2); return buffer + 2l;
	case 0x54: SET_STRING_WIDTH(buffer, "54", 2); return buffer + 2l;
	case 0x55: SET_STRING_WIDTH(buffer, "55", 2); return buffer + 2l;
	case 0x56: SET_STRING_WIDTH(buffer, "56", 2); return buffer + 2l;
	case 0x57: SET_STRING_WIDTH(buffer, "57", 2); return buffer + 2l;
	case 0x58: SET_STRING_WIDTH(buffer, "58", 2); return buffer + 2l;
	case 0x59: SET_STRING_WIDTH(buffer, "59", 2); return buffer + 2l;
	case 0x5A: SET_STRING_WIDTH(buffer, "5A", 2); return buffer + 2l;
	case 0x5B: SET_STRING_WIDTH(buffer, "5B", 2); return buffer + 2l;
	case 0x5C: SET_STRING_WIDTH(buffer, "5C", 2); return buffer + 2l;
	case 0x5D: SET_STRING_WIDTH(buffer, "5D", 2); return buffer + 2l;
	case 0x5E: SET_STRING_WIDTH(buffer, "5E", 2); return buffer + 2l;
	case 0x5F: SET_STRING_WIDTH(buffer, "5F", 2); return buffer + 2l;
	case 0x60: SET_STRING_WIDTH(buffer, "60", 2); return buffer + 2l;
	case 0x61: SET_STRING_WIDTH(buffer, "61", 2); return buffer + 2l;
	case 0x62: SET_STRING_WIDTH(buffer, "62", 2); return buffer + 2l;
	case 0x63: SET_STRING_WIDTH(buffer, "63", 2); return buffer + 2l;
	case 0x64: SET_STRING_WIDTH(buffer, "64", 2); return buffer + 2l;
	case 0x65: SET_STRING_WIDTH(buffer, "65", 2); return buffer + 2l;
	case 0x66: SET_STRING_WIDTH(buffer, "66", 2); return buffer + 2l;
	case 0x67: SET_STRING_WIDTH(buffer, "67", 2); return buffer + 2l;
	case 0x68: SET_STRING_WIDTH(buffer, "68", 2); return buffer + 2l;
	case 0x69: SET_STRING_WIDTH(buffer, "69", 2); return buffer + 2l;
	case 0x6A: SET_STRING_WIDTH(buffer, "6A", 2); return buffer + 2l;
	case 0x6B: SET_STRING_WIDTH(buffer, "6B", 2); return buffer + 2l;
	case 0x6C: SET_STRING_WIDTH(buffer, "6C", 2); return buffer + 2l;
	case 0x6D: SET_STRING_WIDTH(buffer, "6D", 2); return buffer + 2l;
	case 0x6E: SET_STRING_WIDTH(buffer, "6E", 2); return buffer + 2l;
	case 0x6F: SET_STRING_WIDTH(buffer, "6F", 2); return buffer + 2l;
	case 0x70: SET_STRING_WIDTH(buffer, "70", 2); return buffer + 2l;
	case 0x71: SET_STRING_WIDTH(buffer, "71", 2); return buffer + 2l;
	case 0x72: SET_STRING_WIDTH(buffer, "72", 2); return buffer + 2l;
	case 0x73: SET_STRING_WIDTH(buffer, "73", 2); return buffer + 2l;
	case 0x74: SET_STRING_WIDTH(buffer, "74", 2); return buffer + 2l;
	case 0x75: SET_STRING_WIDTH(buffer, "75", 2); return buffer + 2l;
	case 0x76: SET_STRING_WIDTH(buffer, "76", 2); return buffer + 2l;
	case 0x77: SET_STRING_WIDTH(buffer, "77", 2); return buffer + 2l;
	case 0x78: SET_STRING_WIDTH(buffer, "78", 2); return buffer + 2l;
	case 0x79: SET_STRING_WIDTH(buffer, "79", 2); return buffer + 2l;
	case 0x7A: SET_STRING_WIDTH(buffer, "7A", 2); return buffer + 2l;
	case 0x7B: SET_STRING_WIDTH(buffer, "7B", 2); return buffer + 2l;
	case 0x7C: SET_STRING_WIDTH(buffer, "7C", 2); return buffer + 2l;
	case 0x7D: SET_STRING_WIDTH(buffer, "7D", 2); return buffer + 2l;
	case 0x7E: SET_STRING_WIDTH(buffer, "7E", 2); return buffer + 2l;
	case 0x7F: SET_STRING_WIDTH(buffer, "7F", 2); return buffer + 2l;
	case 0x80: SET_STRING_WIDTH(buffer, "80", 2); return buffer + 2l;
	case 0x81: SET_STRING_WIDTH(buffer, "81", 2); return buffer + 2l;
	case 0x82: SET_STRING_WIDTH(buffer, "82", 2); return buffer + 2l;
	case 0x83: SET_STRING_WIDTH(buffer, "83", 2); return buffer + 2l;
	case 0x84: SET_STRING_WIDTH(buffer, "84", 2); return buffer + 2l;
	case 0x85: SET_STRING_WIDTH(buffer, "85", 2); return buffer + 2l;
	case 0x86: SET_STRING_WIDTH(buffer, "86", 2); return buffer + 2l;
	case 0x87: SET_STRING_WIDTH(buffer, "87", 2); return buffer + 2l;
	case 0x88: SET_STRING_WIDTH(buffer, "88", 2); return buffer + 2l;
	case 0x89: SET_STRING_WIDTH(buffer, "89", 2); return buffer + 2l;
	case 0x8A: SET_STRING_WIDTH(buffer, "8A", 2); return buffer + 2l;
	case 0x8B: SET_STRING_WIDTH(buffer, "8B", 2); return buffer + 2l;
	case 0x8C: SET_STRING_WIDTH(buffer, "8C", 2); return buffer + 2l;
	case 0x8D: SET_STRING_WIDTH(buffer, "8D", 2); return buffer + 2l;
	case 0x8E: SET_STRING_WIDTH(buffer, "8E", 2); return buffer + 2l;
	case 0x8F: SET_STRING_WIDTH(buffer, "8F", 2); return buffer + 2l;
	case 0x90: SET_STRING_WIDTH(buffer, "90", 2); return buffer + 2l;
	case 0x91: SET_STRING_WIDTH(buffer, "91", 2); return buffer + 2l;
	case 0x92: SET_STRING_WIDTH(buffer, "92", 2); return buffer + 2l;
	case 0x93: SET_STRING_WIDTH(buffer, "93", 2); return buffer + 2l;
	case 0x94: SET_STRING_WIDTH(buffer, "94", 2); return buffer + 2l;
	case 0x95: SET_STRING_WIDTH(buffer, "95", 2); return buffer + 2l;
	case 0x96: SET_STRING_WIDTH(buffer, "96", 2); return buffer + 2l;
	case 0x97: SET_STRING_WIDTH(buffer, "97", 2); return buffer + 2l;
	case 0x98: SET_STRING_WIDTH(buffer, "98", 2); return buffer + 2l;
	case 0x99: SET_STRING_WIDTH(buffer, "99", 2); return buffer + 2l;
	case 0x9A: SET_STRING_WIDTH(buffer, "9A", 2); return buffer + 2l;
	case 0x9B: SET_STRING_WIDTH(buffer, "9B", 2); return buffer + 2l;
	case 0x9C: SET_STRING_WIDTH(buffer, "9C", 2); return buffer + 2l;
	case 0x9D: SET_STRING_WIDTH(buffer, "9D", 2); return buffer + 2l;
	case 0x9E: SET_STRING_WIDTH(buffer, "9E", 2); return buffer + 2l;
	case 0x9F: SET_STRING_WIDTH(buffer, "9F", 2); return buffer + 2l;
	case 0xA0: SET_STRING_WIDTH(buffer, "A0", 2); return buffer + 2l;
	case 0xA1: SET_STRING_WIDTH(buffer, "A1", 2); return buffer + 2l;
	case 0xA2: SET_STRING_WIDTH(buffer, "A2", 2); return buffer + 2l;
	case 0xA3: SET_STRING_WIDTH(buffer, "A3", 2); return buffer + 2l;
	case 0xA4: SET_STRING_WIDTH(buffer, "A4", 2); return buffer + 2l;
	case 0xA5: SET_STRING_WIDTH(buffer, "A5", 2); return buffer + 2l;
	case 0xA6: SET_STRING_WIDTH(buffer, "A6", 2); return buffer + 2l;
	case 0xA7: SET_STRING_WIDTH(buffer, "A7", 2); return buffer + 2l;
	case 0xA8: SET_STRING_WIDTH(buffer, "A8", 2); return buffer + 2l;
	case 0xA9: SET_STRING_WIDTH(buffer, "A9", 2); return buffer + 2l;
	case 0xAA: SET_STRING_WIDTH(buffer, "AA", 2); return buffer + 2l;
	case 0xAB: SET_STRING_WIDTH(buffer, "AB", 2); return buffer + 2l;
	case 0xAC: SET_STRING_WIDTH(buffer, "AC", 2); return buffer + 2l;
	case 0xAD: SET_STRING_WIDTH(buffer, "AD", 2); return buffer + 2l;
	case 0xAE: SET_STRING_WIDTH(buffer, "AE", 2); return buffer + 2l;
	case 0xAF: SET_STRING_WIDTH(buffer, "AF", 2); return buffer + 2l;
	case 0xB0: SET_STRING_WIDTH(buffer, "B0", 2); return buffer + 2l;
	case 0xB1: SET_STRING_WIDTH(buffer, "B1", 2); return buffer + 2l;
	case 0xB2: SET_STRING_WIDTH(buffer, "B2", 2); return buffer + 2l;
	case 0xB3: SET_STRING_WIDTH(buffer, "B3", 2); return buffer + 2l;
	case 0xB4: SET_STRING_WIDTH(buffer, "B4", 2); return buffer + 2l;
	case 0xB5: SET_STRING_WIDTH(buffer, "B5", 2); return buffer + 2l;
	case 0xB6: SET_STRING_WIDTH(buffer, "B6", 2); return buffer + 2l;
	case 0xB7: SET_STRING_WIDTH(buffer, "B7", 2); return buffer + 2l;
	case 0xB8: SET_STRING_WIDTH(buffer, "B8", 2); return buffer + 2l;
	case 0xB9: SET_STRING_WIDTH(buffer, "B9", 2); return buffer + 2l;
	case 0xBA: SET_STRING_WIDTH(buffer, "BA", 2); return buffer + 2l;
	case 0xBB: SET_STRING_WIDTH(buffer, "BB", 2); return buffer + 2l;
	case 0xBC: SET_STRING_WIDTH(buffer, "BC", 2); return buffer + 2l;
	case 0xBD: SET_STRING_WIDTH(buffer, "BD", 2); return buffer + 2l;
	case 0xBE: SET_STRING_WIDTH(buffer, "BE", 2); return buffer + 2l;
	case 0xBF: SET_STRING_WIDTH(buffer, "BF", 2); return buffer + 2l;
	case 0xC0: SET_STRING_WIDTH(buffer, "C0", 2); return buffer + 2l;
	case 0xC1: SET_STRING_WIDTH(buffer, "C1", 2); return buffer + 2l;
	case 0xC2: SET_STRING_WIDTH(buffer, "C2", 2); return buffer + 2l;
	case 0xC3: SET_STRING_WIDTH(buffer, "C3", 2); return buffer + 2l;
	case 0xC4: SET_STRING_WIDTH(buffer, "C4", 2); return buffer + 2l;
	case 0xC5: SET_STRING_WIDTH(buffer, "C5", 2); return buffer + 2l;
	case 0xC6: SET_STRING_WIDTH(buffer, "C6", 2); return buffer + 2l;
	case 0xC7: SET_STRING_WIDTH(buffer, "C7", 2); return buffer + 2l;
	case 0xC8: SET_STRING_WIDTH(buffer, "C8", 2); return buffer + 2l;
	case 0xC9: SET_STRING_WIDTH(buffer, "C9", 2); return buffer + 2l;
	case 0xCA: SET_STRING_WIDTH(buffer, "CA", 2); return buffer + 2l;
	case 0xCB: SET_STRING_WIDTH(buffer, "CB", 2); return buffer + 2l;
	case 0xCC: SET_STRING_WIDTH(buffer, "CC", 2); return buffer + 2l;
	case 0xCD: SET_STRING_WIDTH(buffer, "CD", 2); return buffer + 2l;
	case 0xCE: SET_STRING_WIDTH(buffer, "CE", 2); return buffer + 2l;
	case 0xCF: SET_STRING_WIDTH(buffer, "CF", 2); return buffer + 2l;
	case 0xD0: SET_STRING_WIDTH(buffer, "D0", 2); return buffer + 2l;
	case 0xD1: SET_STRING_WIDTH(buffer, "D1", 2); return buffer + 2l;
	case 0xD2: SET_STRING_WIDTH(buffer, "D2", 2); return buffer + 2l;
	case 0xD3: SET_STRING_WIDTH(buffer, "D3", 2); return buffer + 2l;
	case 0xD4: SET_STRING_WIDTH(buffer, "D4", 2); return buffer + 2l;
	case 0xD5: SET_STRING_WIDTH(buffer, "D5", 2); return buffer + 2l;
	case 0xD6: SET_STRING_WIDTH(buffer, "D6", 2); return buffer + 2l;
	case 0xD7: SET_STRING_WIDTH(buffer, "D7", 2); return buffer + 2l;
	case 0xD8: SET_STRING_WIDTH(buffer, "D8", 2); return buffer + 2l;
	case 0xD9: SET_STRING_WIDTH(buffer, "D9", 2); return buffer + 2l;
	case 0xDA: SET_STRING_WIDTH(buffer, "DA", 2); return buffer + 2l;
	case 0xDB: SET_STRING_WIDTH(buffer, "DB", 2); return buffer + 2l;
	case 0xDC: SET_STRING_WIDTH(buffer, "DC", 2); return buffer + 2l;
	case 0xDD: SET_STRING_WIDTH(buffer, "DD", 2); return buffer + 2l;
	case 0xDE: SET_STRING_WIDTH(buffer, "DE", 2); return buffer + 2l;
	case 0xDF: SET_STRING_WIDTH(buffer, "DF", 2); return buffer + 2l;
	case 0xE0: SET_STRING_WIDTH(buffer, "E0", 2); return buffer + 2l;
	case 0xE1: SET_STRING_WIDTH(buffer, "E1", 2); return buffer + 2l;
	case 0xE2: SET_STRING_WIDTH(buffer, "E2", 2); return buffer + 2l;
	case 0xE3: SET_STRING_WIDTH(buffer, "E3", 2); return buffer + 2l;
	case 0xE4: SET_STRING_WIDTH(buffer, "E4", 2); return buffer + 2l;
	case 0xE5: SET_STRING_WIDTH(buffer, "E5", 2); return buffer + 2l;
	case 0xE6: SET_STRING_WIDTH(buffer, "E6", 2); return buffer + 2l;
	case 0xE7: SET_STRING_WIDTH(buffer, "E7", 2); return buffer + 2l;
	case 0xE8: SET_STRING_WIDTH(buffer, "E8", 2); return buffer + 2l;
	case 0xE9: SET_STRING_WIDTH(buffer, "E9", 2); return buffer + 2l;
	case 0xEA: SET_STRING_WIDTH(buffer, "EA", 2); return buffer + 2l;
	case 0xEB: SET_STRING_WIDTH(buffer, "EB", 2); return buffer + 2l;
	case 0xEC: SET_STRING_WIDTH(buffer, "EC", 2); return buffer + 2l;
	case 0xED: SET_STRING_WIDTH(buffer, "ED", 2); return buffer + 2l;
	case 0xEE: SET_STRING_WIDTH(buffer, "EE", 2); return buffer + 2l;
	case 0xEF: SET_STRING_WIDTH(buffer, "EF", 2); return buffer + 2l;
	case 0xF0: SET_STRING_WIDTH(buffer, "F0", 2); return buffer + 2l;
	case 0xF1: SET_STRING_WIDTH(buffer, "F1", 2); return buffer + 2l;
	case 0xF2: SET_STRING_WIDTH(buffer, "F2", 2); return buffer + 2l;
	case 0xF3: SET_STRING_WIDTH(buffer, "F3", 2); return buffer + 2l;
	case 0xF4: SET_STRING_WIDTH(buffer, "F4", 2); return buffer + 2l;
	case 0xF5: SET_STRING_WIDTH(buffer, "F5", 2); return buffer + 2l;
	case 0xF6: SET_STRING_WIDTH(buffer, "F6", 2); return buffer + 2l;
	case 0xF7: SET_STRING_WIDTH(buffer, "F7", 2); return buffer + 2l;
	case 0xF8: SET_STRING_WIDTH(buffer, "F8", 2); return buffer + 2l;
	case 0xF9: SET_STRING_WIDTH(buffer, "F9", 2); return buffer + 2l;
	case 0xFA: SET_STRING_WIDTH(buffer, "FA", 2); return buffer + 2l;
	case 0xFB: SET_STRING_WIDTH(buffer, "FB", 2); return buffer + 2l;
	case 0xFC: SET_STRING_WIDTH(buffer, "FC", 2); return buffer + 2l;
	case 0xFD: SET_STRING_WIDTH(buffer, "FD", 2); return buffer + 2l;
	case 0xFE: SET_STRING_WIDTH(buffer, "FE", 2); return buffer + 2l;
	default:   SET_STRING_WIDTH(buffer, "FF", 2); return buffer + 2l;
	}
}

inline char *
put_word_hex_lower(char *restrict buffer,
		   const word_t word)
{
#ifdef OCTET_WORD
	buffer = put_octet_hex_lower(buffer,
				     (octet_t) word);
#if (OCTET_WORD > 1)
	buffer = put_octet_hex_lower(buffer,
				     (octet_t) (word >> 8));
#if (OCTET_WORD > 2)
	buffer = put_octet_hex_lower(buffer,
				     (octet_t) (word >> 16));
#if (OCTET_WORD > 3)
	buffer = put_octet_hex_lower(buffer,
				     (octet_t) (word >> 24));
#if (OCTET_WORD > 4)
	buffer = put_octet_hex_lower(buffer,
				     (octet_t) (word >> 32));
#if (OCTET_WORD > 5)
	buffer = put_octet_hex_lower(buffer,
				     (octet_t) (word >> 40));
#if (OCTET_WORD > 6)
	buffer = put_octet_hex_lower(buffer,
				     (octet_t) (word >> 48));
#if (OCTET_WORD > 7)
	buffer = put_octet_hex_lower(buffer,
				     (octet_t) (word >> 56));
#endif /* if (OCTET_WORD > 7) */
#endif /* if (OCTET_WORD > 6) */
#endif /* if (OCTET_WORD > 5) */
#endif /* if (OCTET_WORD > 4) */
#endif /* if (OCTET_WORD > 3) */
#endif /* if (OCTET_WORD > 2) */
#endif /* if (OCTET_WORD > 1) */
	return buffer;
#else
	return buffer + sprintf(buffer,
				"%x",
				word);
#endif /* ifdef OCTET_WORD */
}


inline char *
put_word_hex_upper(char *restrict buffer,
		   const word_t word)
{
#ifdef OCTET_WORD
	buffer = put_octet_hex_upper(buffer,
				     (octet_t) word);
#if (OCTET_WORD > 1)
	buffer = put_octet_hex_upper(buffer,
				     (octet_t) (word >> 8));
#if (OCTET_WORD > 2)
	buffer = put_octet_hex_upper(buffer,
				     (octet_t) (word >> 16));
#if (OCTET_WORD > 3)
	buffer = put_octet_hex_upper(buffer,
				     (octet_t) (word >> 24));
#if (OCTET_WORD > 4)
	buffer = put_octet_hex_upper(buffer,
				     (octet_t) (word >> 32));
#if (OCTET_WORD > 5)
	buffer = put_octet_hex_upper(buffer,
				     (octet_t) (word >> 40));
#if (OCTET_WORD > 6)
	buffer = put_octet_hex_upper(buffer,
				     (octet_t) (word >> 48));
#if (OCTET_WORD > 7)
	buffer = put_octet_hex_upper(buffer,
				     (octet_t) (word >> 56));
#endif /* if (OCTET_WORD > 7) */
#endif /* if (OCTET_WORD > 6) */
#endif /* if (OCTET_WORD > 5) */
#endif /* if (OCTET_WORD > 4) */
#endif /* if (OCTET_WORD > 3) */
#endif /* if (OCTET_WORD > 2) */
#endif /* if (OCTET_WORD > 1) */
	return buffer;
#else
	return buffer + sprintf(buffer,
				"%X",
				word);
#endif /* ifdef OCTET_WORD */
}

inline int
string_compare(const char *restrict string1,
	       const char *restrict string2)
{
	unsigned int token1;
	unsigned int token2;

	while (1) {
		token1 = (unsigned int) *string1;
		token2 = (unsigned int) *string2;

		if (token1 != token2)
			return token1 - token2;

		if (token1 == 0)
			return 0;

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
inline char *
do_parse_uint(uintmax_t *const restrict n,
	      const char *restrict string,
	      const unsigned int digit_count_max,
	      const char *const restrict max_string)
{
	while (*string == '0') {
		++string;

		if (*string == '\0') {
			*n = 0llu;
			return (char *) string;
		}
	}

	if ((*string > '9') || (*string < '0'))
		return NULL;

	const char *const restrict start_ptr = string;

	unsigned int count_digits = 1u;

	while (1) {
		++string;

		if (*string == '\0')
			break;

		if ((*string > '9') || (*string < '0'))
			return NULL;

		++count_digits;

		if (count_digits == digit_count_max) {

			if (string_compare(start_ptr,
					   max_string) > 0)
				return NULL;

			++string;

			if (*string != '\0')
				return NULL;

			break;
		}
	}

	char *const restrict end_ptr = (char *const restrict) string;

	--string;

	*n = (uintmax_t) ASCII_TO_DIGIT(*string);

	const uintmax_t *restrict power       = &ten_pow_map[1];

	const uintptr_t *const restrict until = &ten_pow_map[count_digits];


	while (power < until) {

		--string;

		(*n) += (((uintmax_t) ASCII_TO_DIGIT(*string)) * (*power));

		++power;
	}

	return end_ptr;
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

inline char *
parse_uint(uintmax_t *const restrict n,
	   const char *restrict string)
{
#if HAVE_INT_STRING_ATTRS

	return do_parse_uint(n,
			     string,
			     DIGIT_COUNT_UINTMAX_MAX,
			     DIGIT_STRING_UINTMAX_MAX);
#else
	char *const restrict end_ptr;

	*n = strtoimax(string,
		       &end_ptr,
		       10);

	return ((*n != 0llu) || (errno != 0))
	     ? end_ptr
	     : NULL;
#endif /* if HAVE_INT_STRING_ATTRS  */
}

inline char *
parse_int(intmax_t *const restrict n,
	  const char *restrict string)
{
#if HAVE_INT_STRING_ATTRS
	if (*string == '-') {
		++string;

		char *const restrict end_ptr
		= do_parse_uint((uintmax_t *const restrict) n,
				string,
				DIGIT_COUNT_INTMAX_MIN,
				DIGIT_STRING_INTMAX_MIN);

		if (end_ptr != NULL)
			*n = -(*n);

		return end_ptr;
	}

	return do_parse_uint((uintmax_t *const restrict) n,
			     string,
			     DIGIT_COUNT_INTMAX_MAX,
			     DIGIT_STRING_INTMAX_MAX);
#else
	char *const restrict end_ptr;

	*n = strtoimax(string,
		       &end_ptr,
		       10);

	return ((*n != 0ll) || (errno != 0))
	     ? end_ptr
	     : NULL;
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

		if (stop_ptr != NULL)
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
		     struct String *const restrict from,
		     const struct String *const restrict until)
{
	interval->from	= from;
	interval->until = until;
}

#ifdef WIN32
/* Win32 error formatting
 * ────────────────────────────────────────────────────────────────────────── */
#define WIN32_FAILURE_BUFFER_SIZE 1024lu

#define WIN32_FAILURE_HEADER_1						\
"\n" ERROR_OPEN ANSI_UNDERLINE
#define PUT_WIN32_FAILURE_HEADER_1(PTR)					\
PTR = put_string_width(PTR,						\
		       WIN32_FAILURE_HEADER_1,				\
		       sizeof(WIN32_FAILURE_HEADER_1) - 1u)

#define WIN32_FAILURE_HEADER_2						\
" failure" ANSI_NO_UNDERLINE " - reason:\n\t- "
#define PUT_WIN32_FAILURE_HEADER_2(PTR)					\
PTR = put_string_width(PTR,						\
		       WIN32_FAILURE_HEADER_2,				\
		       sizeof(WIN32_FAILURE_HEADER_2) - 1u)

#define WIN32_FAILURE_CLOSE						\
"\n" ANSI_RESET "\n"

#define WIN32_FAILURE_UNKNOWN_CLOSE					\
"unknown" WIN32_FAILURE_CLOSE


inline char *
put_win32_failure(char *restrict buffer,
		  const char *const restrict source,
		  const unsigned int width_source,
		  const DWORD error_code)
{
	char *const restrict message;

	PUT_WIN32_FAILURE_HEADER_1(buffer);

	buffer = put_string_width(buffer,
				  source,
				  width_source);

	PUT_WIN32_FAILURE_HEADER_2(buffer);

	const DWORD size = FormatMessage(  FORMAT_MESSAGE_FROM_SYSTEM
					 | FORMAT_MESSAGE_IGNORE_INSERTS
					 | FORMAT_MESSAGE_ARGUMENT_ARRAY
					 | FORMAT_MESSAGE_ALLOCATE_BUFFER,
					 NULL,
					 error_code,
					 0,
					 (LPSTR) &message,
					 0,
					 NULL);

	if (size == 0lu)
		return put_string_width(buffer,
					WIN32_FAILURE_UNKNOWN_CLOSE,
					sizeof(WIN32_FAILURE_UNKNOWN_CLOSE) - 1u);

	buffer = put_string_size(buffer,
				 message,
				 size);

	(void) LocalFree(message);

	return put_string_width(buffer,
				WIN32_FAILURE_CLOSE,
				sizeof(WIN32_FAILURE_CLOSE) - 1u);
}
#endif /* ifdef WIN32 */
#endif	/* MYSQL_SEED_STRING_STRING_UTILS */
