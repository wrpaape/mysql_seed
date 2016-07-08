#include "utf8_utils.h"

extern inline unsigned int
utf8_head_width(const octet_t head);

extern inline unsigned int
utf8_width(const octet_t *restrict octets);

extern inline bool
is_utf8_code_point(const char *const restrict bytes);

extern bool
is_utf8_string(const char *const restrict bytes);

extern inline size_t
utf8_string_size(const char *const restrict bytes);

extern inline size_t
utf8_string_size_length(const char *const restrict bytes,
			size_t length);
