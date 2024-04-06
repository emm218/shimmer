#include <stdio.h>
#include <unistd.h>

static void usage(FILE *);
static void help(void);

int
init_main(int argc, char **argv)
{
	int c;
	char *dir;

	dir = ".";

	while ((c = getopt(argc, argv, "h")) != -1) {
		switch (c) {
		case 'h':
			usage(stdout);
			help();
			return 0;
		case '?':
			usage(stderr);
			return 1;
		}
	}

	if (optind == argc - 1)
		dir = argv[optind];
	else if (optind + 1 < argc) {
		fprintf(stderr, "%s: extraneous argument '%s'\n", argv[0],
		    argv[optind + 1]);
		usage(stderr);
		return 1;
	}

	printf("%s\n", dir);

	return 0;
}

void
usage(FILE *out)
{
	fprintf(out, "usage: shimmer init [-h] [DIR]\n");
}

void
help(void)
{
	// clang-format off
	printf(
"create a new shimmer project\n"
"\n"
"arguments:\n"
"  DIR   the directory to initialize the project in. defaults to .\n"
"\n"
"options:\n"
"  -h    display help and exit\n"
	);
	// clang-format on
}
