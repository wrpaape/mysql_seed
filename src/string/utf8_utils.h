#ifndef MYSQL_SEED_STRING_UTF8_UTILS_H_
#define MYSQL_SEED_STRING_UTF8_UTILS_H_

/* EXTERNAL DEPENDENCIES
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#include <stddef.h>			/* size_t */
#include <stdbool.h>			/* bool */
#include "string/string_macros.h"	/* error macros */
#include "utils/closure.h"		/* Handler, HandlerClosure */
#include "utils/types/octet.h"		/* stdint, octet_t */
#include "utils/char_attrs.h"		/* OCTET_CHAR */

/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * EXTERNAL DEPENDENCIES
 *
 *
 * CONSTANTS
 * ▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼▼ */

#define UTF8_WIDTH_MAX 4ul

#if HAVE_CHAR_ATTRS
#	define UTF8_SIZE_MAX (UTF8_WIDTH_MAX * OCTET_CHAR)
#else
#	warning "UTF8_SIZE_MAX unknown at compile time"
#endif /* if HAVE_CHAR_ATTRS */

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

inline bool
utf8_string_size_length_status(size_t *const restrict size,
			       const char *const restrict bytes,
			       size_t length)
{
	const octet_t *restrict octets = (const octet_t *restrict) bytes;

	unsigned int width;

	while (1) {
		width = utf8_width(octets);

		if (width == 0u)
			return false;

		if (*octets == '\0')
			*size = (octets + 1l)
			      - ((const octet_t *const restrict) bytes);
			return true;

		if (length == 0lu)
			return false;

		--length;

		octets += width;
	}
}

inline void
utf8_string_size_length_muffle(size_t *const restrict size,
			       const char *const restrict bytes,
			       size_t length)
{

	const octet_t *restrict octets = (const octet_t *restrict) bytes;

	unsigned int width;

	while (1) {
		width = utf8_width(octets);

		if (width == 0u)
			return;

		if (*octets == '\0') {
			*size = (octets + 1l)
			      - ((const octet_t *const restrict) bytes);
			return;
		}

		if (length == 0lu)
			return;

		--length;

		octets += width;
	}
}

inline bool
utf8_string_size_length_report(size_t *const restrict size,
			       const char *const restrict bytes,
			       size_t length,
			       const char *restrict *const restrict failure)
{

	const octet_t *restrict octets = (const octet_t *restrict) bytes;

	unsigned int width;

	while (1) {
		width = utf8_width(octets);

		if (width == 0u) {
			*failure = FAILURE_REASON("utf8_string_size_length",
						  "'bytes' contains byte "
						  "sequence(s) that are not "
						  "valid UTF-8 code points");
			return false;
		}

		if (*octets == '\0') {
			*size = (octets + 1l)
			      - ((const octet_t *const restrict) bytes);

			return true;
		}

		if (length == 0lu) {
			*failure = FAILURE_REASON("utf8_string_size_length",
						  "'bytes' exceeds maximum "
						  "UTF-8 code point length '"
						  "length'");
			return false;
		}

		--length;

		octets += width;
	}
}

inline void
utf8_string_size_length_handle(size_t *const restrict size,
			       const char *const restrict bytes,
			       size_t length,
			       Handler *const handle,
			       void *arg)
{
	const char *restrict failure;

	if (utf8_string_size_length_report(size,
					   bytes,
					   length,
					   &failure))
		return;

	handle(arg,
	       failure);
	__builtin_unreachable();
}

inline void
utf8_string_size_length_handle_cl(size_t *const restrict size,
				  const char *const restrict bytes,
				  size_t length,
				  const struct HandlerClosure *const restrict fail_cl)
{
	const char *restrict failure;

	if (utf8_string_size_length_report(size,
					   bytes,
					   length,
					   &failure))
		return;

	fail_cl->handle(fail_cl->arg,
			failure);
	__builtin_unreachable();
}



/* ▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲
 * TOP-LEVEL FUNCTIONS */

#ifdef _cplusplus /* close 'extern "C" {' */
}
#endif

#endif /* ifndef MYSQL_SEED_STRING_UTF8_UTILS_H_ */
