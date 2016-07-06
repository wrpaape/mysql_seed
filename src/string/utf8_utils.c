#include "utf8_utils.h"

extern inline unsigned int utf8_head_width(const octet_t head);
extern inline unsigned int utf8_width(const octet_t *restrict bytes);
extern inline bool is_utf8(const octet_t *restrict bytes);
extern inline void utf8_char_init(struct UTF8Char *restrict utf8_char,
				  const char *const restrict *buffer);

bool is_utf8_string(const octet_t *restrict string)
{
	unsigned int width;

	while (1) {
		width = utf8_width(string);

		if (width == 0u)
			return false;

		if (*string == '\0')
			return true;

		string += width;
	}
}

/* returns pointer to '\0' terminator or NULL if error/immediate EOF */
char *fgets_utf8(char *const restrict char_buffer,
		 int count,
		 FILE *restrict stream)
{
	octet_t *restrict byte_buffer = (octet_t *restrict)
				       fgets(char_buffer,
					     count * ((int) UTF8_MAX_SIZE),
					     stream);

	if (byte_buffer == NULL) /* will catch case of 'count <= 0' */
		return NULL;

	unsigned int width;

	while (1) {
		width = utf8_width(byte_buffer);

		if (width == 0u)
			return NULL;

		byte_buffer += width;

		if ((*((char *) byte_buffer)) == '\0')
			return (char *) byte_buffer;

		if (count < 2) {
			*((char *) byte_buffer) = '\0';
			return (char *) byte_buffer;
		}

		--count;
	}
}
