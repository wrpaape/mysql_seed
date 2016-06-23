#include "mysql_seed.h"

int main(int argc, char *argv[])
{

	struct SeedMode mode;

	seed_cli_parse_input(&mode, argc, &argv[0]);

	(*mode.handle)(&mode.spec);

	return EXIT_SUCCESS;
}
