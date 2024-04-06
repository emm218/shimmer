#include <errno.h>
#include <stdio.h>
#include <unistd.h>

static void usage(FILE *);
static void help(void);

#ifdef DEBUG
#define INIT_PATH "./shimmer-init"
#else
#define INIT_PATH "shimmer-init"
#endif

int
init_main(int argc, char **argv)
{
	int c;

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

	execv(INIT_PATH, argv);
	perror(argv[0]);
	return errno;
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
