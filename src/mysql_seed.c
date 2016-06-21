#include "mysql_seed.h"


void main(int argc, char *argv[])
{
	struct SeedMode mode;

	cli_parse_input(&mode, argc, argv);

	(*mode.handle)(&mode.spec);
	
	return EXIT_SUCCESS;
}

void cli_parse_input(struct SeedMode *const restrict mode,
		     const int argc,
		     const char *const restrict *argv)
{
	mode->handle = &exit_message;

	struct ExitSpec *const restrict exit = &mode->spec.exit;

	exit_spec_set(&mode->spec.exit,
		      EXIT_SUCCESS,
		      stdout,
		      HELP_USAGE_MESSAGE);
}
		


void exit_message(const union SeedModeSpec *const restrict spec)
{
	const struct ExitSpec *const restrict exit = &spec->exit;

	vfprintf(exit->stream,
		 exit->format,
		 exit->ap);

	exit(exit->status);
}



inline void exit_spec_set(struct ExitSpec *const restrict exit,
			  const int status,
			  const File *const restrict stream,
			  const char *const restrict format,
			  ...)
{
	va_list params;

	exit->status = status;
	exit->stream = stream;
	exit->format = format;

	va_start(params, format);

	va_copy(exit->ap, params);

	va_end(params);
}
