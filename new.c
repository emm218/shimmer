/*
 * Copyright (C) 2024 Emmy Emmycelium
 *
 * This file is part of shimmer
 *
 * Shimmer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Shimmer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>
 */
#include <stdio.h>
#include <unistd.h>

static void usage(FILE *);
static void help(void);

int
new_main(int argc, char **argv)
{
	int c, draft;
	char *type, *out_path;

	draft = 1;

	while ((c = getopt(argc, argv, "hDc:t:")) != -1) {
		switch (c) {
		case 'h':
			usage(stdout);
			help();
			return 0;
		case 'D':
			draft = 0;
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
	(void)draft;

	if (optind == argc) {
		fprintf(stderr, "%s: please provide a path\n", argv[0]);
		usage(stderr);
		return 1;
	} else if (optind + 1 < argc) {
		fprintf(stderr, "%s: extraneous argument '%s'\n", argv[0],
		    argv[optind + 1]);
		usage(stderr);
		return 1;
	}

	out_path = argv[optind];

	printf("%s\n", out_path);

	return 0;
}

void
usage(FILE *out)
{
	fprintf(out, "usage: shimmer new [-hD] [-t TYPE] PATH\n");
}

void
help(void)
{
	// clang-format off
	printf(
"generate a new content file with front matter\n"
"\n"
"arguments:\n"
"  PATH    the path to create the new content file in\n"
"\n"
"options:\n"
"  -h         display help and exit\n"
"  -D         don't mark the newly created file as a draft\n"
"  -t TYPE    the content type for this page. if unspecified will be inferred\n"
"             from PATH. see the documentation for more on content types\n"
	);
	// clang-format on
}
