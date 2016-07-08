#include "mysql_seed.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
		return print_help_usage();

	return mode_dispatch(&argv[1],
			     &argv[argc]);
}

/* misc helper functions
 *─────────────────────────────────────────────────────────────────────────── */

/* parse stdin args
 *─────────────────────────────────────────────────────────────────────────── */
int
mode_dispatch(char *restrict *const restrict arg_ptr,
	      char *const restrict *const restrict until_ptr)
{

	char *const restrict mode_flag = *arg_ptr;


	if (*mode_flag != '-')
		return print_invalid_mode_flag(mode_flag);

	char *const restrict next = mode_flag + 1l;
	char *const restrict rem  = next + 1l;

	/* parse short mode flag */
	switch (*next) {

	case '-': break;	/* parse long flag */

	case 'g': return (*rem == '\0')
		       ? puts("TODO: dispatch 'generate' mode")
		       : print_invalid_mode_flag(mode_flag);

	case 'h': return (*rem == '\0')
		       ? help_dispatch(arg_ptr + 1l, until_ptr)
		       : print_invalid_mode_flag(mode_flag);

	case 'l': return (*rem == '\0')
		       ? puts("TODO: dispatch 'load' mode")
		       : print_invalid_mode_flag(mode_flag);

	default:  return print_invalid_mode_flag(mode_flag);
	}

	/* parse long mode flag */
	switch (*rem) {

	case 'g': return strings_equal("enerate", rem + 1l)
		       ? puts("TODO: dispatch 'generate' mode")
		       : print_invalid_mode_flag(mode_flag);

	case 'h': return strings_equal("elp",	  rem + 1l)
		       ? help_dispatch(arg_ptr + 1l, until_ptr)
		       : print_invalid_mode_flag(mode_flag);

	case 'l': return strings_equal("oad",	  rem + 1l)
		       ? puts("TODO: dispatch 'load' mode")
		       : print_invalid_mode_flag(mode_flag);

	default:  return print_invalid_mode_flag(mode_flag);
	}
}



/* inspect invalid flag and return 'EXIT_FAILURE'
 *─────────────────────────────────────────────────────────────────────────── */
inline int
print_invalid_mode_flag(char *const restrict mode_flag)
{
	static char buffer[128] = {
		INVALID_MODE_FLAG_MESSAGE_1
	};

	char *restrict
	ptr = put_string_inspect(&buffer[sizeof(INVALID_MODE_FLAG_MESSAGE_1)],
				 mode_flag,
				 MODE_FLAG_MAX_LENGTH);

	(void) memcpy(ptr,
		      INVALID_MODE_FLAG_MESSAGE_2,
		      sizeof(INVALID_MODE_FLAG_MESSAGE_2) - 1lu);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr + sizeof(INVALID_MODE_FLAG_MESSAGE_2) - &buffer[0]);

	return EXIT_FAILURE;
}
