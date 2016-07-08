#include "mysql_seed.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
		return print_no_mode_flag();

	return mode_dispatch(&argv[1],
			     &argv[argc]);
}

/* parse stdin args
 *─────────────────────────────────────────────────────────────────────────── */
inline int
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
	case '-': break;	/* parse long mode flag */

	case 'g': return (*rem == '\0')
		       ? generate_dispatch(arg_ptr + 1l, until_ptr)
		       : print_invalid_mode_flag(mode_flag);

	case 'h': return (*rem == '\0')
		       ? help_dispatch(arg_ptr + 1l, until_ptr)
		       : print_invalid_mode_flag(mode_flag);

	case 'l': return (*rem == '\0')
		       ? load_dispatch(arg_ptr + 1l, until_ptr)
		       : print_invalid_mode_flag(mode_flag);

	default:  return print_invalid_mode_flag(mode_flag);
	}

	/* parse long mode flag */
	switch (*rem) {
	case 'g': return strings_equal("enerate", rem + 1l)
		       ? generate_dispatch(arg_ptr + 1l, until_ptr)
		       : print_invalid_mode_flag(mode_flag);

	case 'h': return strings_equal("elp",	  rem + 1l)
		       ? help_dispatch(arg_ptr + 1l, until_ptr)
		       : print_invalid_mode_flag(mode_flag);

	case 'l': return strings_equal("oad",	  rem + 1l)
		       ? load_dispatch(arg_ptr + 1l, until_ptr)
		       : print_invalid_mode_flag(mode_flag);

	default:  return print_invalid_mode_flag(mode_flag);
	}
}

/* print error messsage and return 'EXIT_FAILURE'
 *─────────────────────────────────────────────────────────────────────────── */
inline int
print_no_mode_flag(void)
{
	write_muffle(STDERR_FILENO,
		     NO_MODE_FLAG_MESSAGE,
		     sizeof(NO_MODE_FLAG_MESSAGE));

	return EXIT_FAILURE;
}

inline int
print_invalid_mode_flag(char *const restrict mode_flag)
{
	static char buffer[ERROR_BUFFER_SIZE] = {
		INVALID_MODE_FLAG_HEADER
	};

	char *restrict
	ptr = put_string_inspect(&buffer[sizeof(INVALID_MODE_FLAG_HEADER)],
				 mode_flag,
				 FLAG_LENGTH_MAX);

	ptr = put_string_size(ptr,
			      MORE_INFO_MESSAGE,
			      sizeof(MORE_INFO_MESSAGE) - 1lu);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);

	return EXIT_FAILURE;
}
