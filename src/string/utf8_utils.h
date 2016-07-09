#ifndef MYSQL_SEED_STRING_UTF8_UTILS_H_
#define MYSQL_SEED_STRING_UTF8_UTILS_H_

/* EXTERNAL DEPENDENCIES
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include <stddef.h>		/* size_t */
#include <errno.h>		/* errno */
#include <stdbool.h>		/* bool */
#include "utils/types/octet.h"	/* stdint, octet_t */

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * EXTERNAL DEPENDENCIES
 *
 *
 * CONSTANTS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#define UTF8_WIDTH_MAX 4ul
#define UTF8_SIZE_MAX (UTF8_WIDTH_MAX * sizeof(octet_t))

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * CONSTANTS
 *
 *
 * TYPEDEFS, ENUM AND STRUCT DEFINITIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * TYPEDEFS, ENUM AND STRUCT DEFINITIONS
 *
 *
 * FUNCTION-LIKE MACROS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */
/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * FUNCTION-LIKE MACROS
 *
 *
 * HELPER FUNCTIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

inline unsigned int
utf8_head_width(const octet_t head)
{
	if ((head & 0x80) == 0x00)
		return 1u;	/* ASCII character*/

	if ((head & 0x40) == 0x00)
		return 0u;	/* 10xxxxxx (not utf8) */

	if ((head & 0x20) == 0x00)
		return 2u;	/* 110xxxxx */

	if ((head & 0x10) == 0x00)
		return 3u;	/* 1110xxxx */

	if ((head & 0x08) == 0x00)
		return 4u;	/* 11110xxx */

	return 0u; /* 11111xxx (not utf8) */
}

inline unsigned int
utf8_width(const octet_t *restrict octets)
{
	const unsigned int width = utf8_head_width(*octets);

	if (width == 0u)
		return 0u;

	const octet_t *const restrict last_octet = octets + width;

	while (1) {
		++octets;

		if (octets == last_octet)
			return width;

		if ((((*octets) & 0x80) == 0x00)  /* 0xxxxxxx (not utf8) */
		 || (((*octets) & 0x40) == 0x40)) /* 01xxxxxx (not utf8) */
			return 0u;
	}
}


/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * HELPER FUNCTIONS
 *
 *
 * TOP-LEVEL FUNCTIONS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

inline bool
is_utf8_code_point(const char *const restrict bytes)
{
	return utf8_width((const octet_t *restrict) bytes) > 0u;
}

inline bool
is_utf8_string(const char *const restrict bytes)
{

	const octet_t *restrict octets = (const octet_t *restrict) bytes;

	unsigned int width;

	while (1) {
		width = utf8_width(octets);

		if (width == 0u)
			return false;

		if (*octets == '\0')
			return true;

		octets += width;
	}
}

inline size_t
utf8_string_size(const char *const restrict bytes)
{
	const octet_t *restrict octets = (const octet_t *restrict) bytes;

	unsigned int width;

	while (1) {
		width = utf8_width(octets);

		if (width == 0u)
			return 0lu;

		if (*octets == '\0')
			return (octets + 1l)
			     - ((const octet_t *const restrict) bytes);

		octets += width;
	}
}

inline size_t
utf8_string_size_length(const char *const restrict bytes,
			size_t length)
{

	const octet_t *restrict octets = (const octet_t *restrict) bytes;

	unsigned int width;

	while (1) {
		width = utf8_width(octets);

		if (width == 0u) {
			errno = EINVAL;
			return 0lu;
		}

		if (*octets == '\0')
			return (octets + 1l)
			     - ((const octet_t *const restrict) bytes);

		if (length == 0lu) {
			errno = EOVERFLOW;
			return 0lu;
		}

		--length;

		octets += width;
	}
}


/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * TOP-LEVEL FUNCTIONS */

#ifdef _cplusplus /* close 'extern "C" {' */
}
#endif

#endif /* ifndef MYSQL_SEED_STRING_UTF8_UTILS_H_ */
