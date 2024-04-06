#include <stdio.h>
#include <unistd.h>

static void usage(FILE *);
static void help(void);

int
new_main(int argc, char **argv)
{
	int c;
	char *type, *config_path, *out_path;

	while ((c = getopt(argc, argv, "hc:t:")) != -1) {
		switch (c) {
		case 'h':
			usage(stdout);
			help();
			return 0;
		case 'c':
			config_path = optarg;
			break;
		case 't':
			type = optarg;
			break;
		case '?':
			usage(stderr);
			return 1;
		}
	}

	(void)type;
	(void)config_path;

	if (optind == argc - 1)
		out_path = argv[optind];
	else if (optind == argc) {
		fprintf(stderr, "%s: please provide a path\n", argv[0]);
		usage(stderr);
		return 1;

	} else if (optind + 1 < argc) {
		fprintf(stderr, "%s: extraneous argument '%s'\n", argv[0],
		    argv[optind + 1]);
		usage(stderr);
		return 1;
	}

	printf("%s\n", out_path);

	return 0;
}

void
usage(FILE *out)
{
	fprintf(out, "usage: shimmer new [-h] [-c FILE] [-t TYPE] PATH\n");
}

void
help(void)
{
	// clang-format off
	printf(
"simple static site generator - new subcommand\n"
"\n"
"arguments:\n"
"  PATH    the path to create the new content file in\n"
"\n"
"options:\n"
"  -h         display help and exit\n"
"  -c FILE    use the config file FILE. if unspecified, the parent directories\n"
"             will be searched for a `shimmer.yaml` file\n"
"  -t TYPE    the content type for this page. if unspecified will be inferred\n"
"             from PATH. see the documentation for more on content types\n"
	);
	// clang-format on
}
