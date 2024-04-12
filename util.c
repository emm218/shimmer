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
#define _GNU_SOURCE
#define _POSIX_C_SOURCE >= 200809L

#include <sys/stat.h>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "util.h"

int
project_root(const char *const prog_name)
{
	int fd1, fd2;
	struct stat st;

	// search parent directories for a shimmer.toml file
	if ((fd1 = open(".", O_PATH | O_DIRECTORY)) == -1) {
		perror(prog_name);
		fprintf(stderr, "%s: unable to find project root\n", prog_name);
		return -1;
	}
	while (fstatat(fd1, "shimmer.toml", &st, 0) == -1) {
		printf("up\n");
		fstat(fd1, &st);
		if (st.st_ino == 2) {
			fprintf(stderr, "%s: not in a shimmer project\n",
			    prog_name);
			return -1;
		}
		if (errno != ENOENT ||
		    (fd2 = openat(fd1, "..", O_PATH | O_DIRECTORY)) == -1) {
			perror(prog_name);
			fprintf(stderr, "%s: unable to find project root\n",
			    prog_name);
			close(fd1);
			return -1;
		}
		close(fd1);
		fd1 = fd2;
	}

	return fd1;
}
