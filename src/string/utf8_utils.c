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

extern inline bool
utf8_string_size_length_status(size_t *const restrict size,
			       const char *const restrict bytes,
			       size_t length);
extern inline void
utf8_string_size_length_muffle(size_t *const restrict size,
			       const char *const restrict bytes,
			       size_t length);
extern inline bool
utf8_string_size_length_report(size_t *const restrict size,
			       const char *const restrict bytes,
			       size_t length,
			       const char *restrict *const restrict failure);
extern inline void
utf8_string_size_length_handle(size_t *const restrict size,
			       const char *const restrict bytes,
			       size_t length,
			       Handler *const handle,
			       void *arg);
extern inline void
utf8_string_size_length_handle_cl(size_t *const restrict size,
				  const char *const restrict bytes,
				  size_t length,
				  const struct HandlerClosure *const restrict fail_cl);
