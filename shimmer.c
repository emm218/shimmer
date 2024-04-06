/*
 * Copyright (C) 2024 Emmy Emmycelium
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define STR(S)	#S
#define XSTR(S) STR(S)
#define VERSION "0.1.0"

int new_main(int, char **);

static void usage(FILE *);
static void help(void);

int verbose = 1;
#define MESSAGE(msg, ...) \
	if (verbose)      \
		printf("%s: " msg, prog_name, ##__VA_ARGS__);

int
main(int argc, char **argv)
{
	int c;
	char *config_path, *out_path;

	config_path = NULL;
	out_path = "public";

	while ((c = getopt(argc, argv, "+hvqc:o:")) != -1) {
		switch (c) {
		case 'h':
			usage(stdout);
			help();
			return 0;
		case 'v':
			printf(VERSION "\n");
			return 0;
		case 'q':
			verbose = 0;
			break;
		case 'c':
			config_path = optarg;
			break;
		case 'o':
			out_path = optarg;
			break;
		case '?':
			usage(stderr);
			return 1;
		}
	}
	if (optind == 1 && argc > 1) {
		if (strncmp(argv[1], "init", 5) == 0) {
			argv[1] = argv[0];
			execv(XSTR(BINDIR) "/shimmer-init", argv + 1);
			perror(argv[0]);
			return 1;
		} else if (strncmp(argv[1], "new", 4) == 0) {
			argv[1] = argv[0];
			return new_main(argc - 1, argv + 1);
		} else {
			fprintf(stderr, "%s: unrecognized subcommand '%s'\n",
			    argv[0], argv[1]);
			usage(stderr);
			return 1;
		}
	} else if (optind < argc) {
		fprintf(stderr, "%s: extraneous argument '%s'\n", argv[0],
		    argv[optind]);
		usage(stderr);
		return 1;
	}

	(void)config_path;
	(void)out_path;
	(void)verbose;

	return 0;
}

void
usage(FILE *out)
{
	fprintf(out,
	    "usage: shimmer [-hvq] [-c FILE] [-o DIR]\n"
	    "       shimmer init [-h] [DIR]\n"
	    "       shimmer new  [-hD] [-t TYPE] PATH\n");
}

void
help(void)
{
	// clang-format off
	printf(
"builds a static site from a project directory\n"
"\n"
"options:\n"
"  -h         display help and exit\n"
"  -v         display version information and exit\n"
"  -q         suppress output during build process\n"
"  -c FILE    use the config file FILE. if unspecified, the parent directories\n"
"             will be searched for a `shimmer.toml` file\n"
"  -o DIR     write output to DIR. overrides the value specified in the config\n"
"             file. defaults to 'public'\n"
"\n"
"subcommands:\n"
"  init    create a shimmer project\n"
"  new     create a new content file in a project\n"
"\n"
"try shimmer COMMAND -h for help on subcommands\n"
	);
	// clang-format on
}
