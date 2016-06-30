#include "stdio_utils.h"

extern inline size_t shell_command_read(char *restrict buffer,
					const size_t size,
					const char *const restrict command);

extern inline void shell_command_gets(char *restrict buffer,
				      const size_t size,
				      const char *const restrict command);

extern inline void get_stdio_winsize(struct winsize *const restrict window);
