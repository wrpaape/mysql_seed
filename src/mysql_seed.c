#include "mysql_seed.h"

int main(int argc, char *argv[])
{
	if (argc < 2) {
		print_no_mode_flag();
		return EXIT_FAILURE;
	}

	return mode_dispatch(&argv[1],
			     argc - 2);
}

/* parse stdin args
 *─────────────────────────────────────────────────────────────────────────── */
inline int
mode_dispatch(char *const *const restrict from,
	      const int rem_argc)
{
	char *const restrict flag = *from;

	if (*flag != '-')
		goto INVALID_MODE_FLAG;

	const char *const restrict arg = flag + 1l;
	const char *const restrict rem = arg + 1l;

	/* parse short mode flag */
	switch (*arg) {
	case '-':
		break;	/* parse long mode flag */

	case 'g':
		if (*rem == '\0')
			return generate_dispatch(from + 1l, rem_argc);

		goto INVALID_MODE_FLAG;


	case 'h':
		if (*rem == '\0')
			return help_dispatch(from + 1l, rem_argc);

		goto INVALID_MODE_FLAG;


	case 'l':
		if (*rem == '\0')
			return load_dispatch(from + 1l, rem_argc);

		goto INVALID_MODE_FLAG;

	case 'r':
		if (*rem == '\0')
			return remove_dispatch(from + 1l);

	default:
		goto INVALID_MODE_FLAG;
	}

	/* parse long mode flag */
	switch (*rem) {
	case 'g':
		if (strings_equal("enerate", rem + 1l))
			return generate_dispatch(from + 1l, rem_argc);

		break;

	case 'h':
		if (strings_equal("elp", rem + 1l))
			return help_dispatch(from + 1l, rem_argc);

		break;

	case 'l':
		if (strings_equal("oad", rem + 1l))
			return load_dispatch(from + 1l, rem_argc);

		break;

	case 'r':
		if (strings_equal("emove", rem + 1l))
			return remove_dispatch(from + 1l);

	default:
		break;
	}

INVALID_MODE_FLAG:
	print_invalid_mode_flag(flag);

	return EXIT_FAILURE;
}

/* print error messsage and return 'EXIT_FAILURE'
 *─────────────────────────────────────────────────────────────────────────── */
inline void
print_no_mode_flag(void)
{
	write_muffle(STDERR_FILENO,
		     FAILURE_NO_MODE_FLAG,
		     sizeof(FAILURE_NO_MODE_FLAG) - 1lu);
}

inline void
print_invalid_mode_flag(char *const restrict arg)
{
	static char buffer[ARG_INSPECT_BUFFER_SIZE] = {
		FAILURE_INVALID_MODE_FLAG_HEADER
	};

	char *restrict
	ptr = put_string_inspect(&buffer[0]
				 + sizeof(FAILURE_INVALID_MODE_FLAG_HEADER)
				 - 1lu,
				 arg,
				 LENGTH_INSPECT_MAX);

	ptr = put_string_size(ptr,
			      MORE_INFO_MESSAGE,
			      sizeof(MORE_INFO_MESSAGE) - 1lu);

	write_muffle(STDERR_FILENO,
		     &buffer[0],
		     ptr - &buffer[0]);
}
