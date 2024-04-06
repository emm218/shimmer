# shimmer

minimalist static site generator to replace hugo for me

# dependencies

building only requires a C compiler, gnu `make`, and `sed`. running the program
requires a working `sh` for the `shimmer init` command but otherwise should just
work. the make target for `compilation_commands.json` also requires `bear`, but
isn't needed unless developing the program and using clangd.

in the future i might add a `configure` script and try to make this portable to
more systems but for now `make install` should suffice.
