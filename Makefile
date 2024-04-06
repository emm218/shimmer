DESTDIR ?= /usr/local
DATADIR ?= $(DESTDIR)/share/shimmer
BINDIR ?= $(DESTDIR)/bin

CC=cc
CFLAGS+=-Wall -Wextra -Werror -Iinclude -DBINDIR=$(BINDIR)

SRC:=$(wildcard *.c) $(wildcard vendor/*.c)

debug: CFLAGS+=-g
debug: DATADIR=share
debug: BINDIR=.
debug: all

release: CFLAGS+=-O2
release: clean all

all: shimmer shimmer-init

shimmer-init: shimmer-init.tmp
	sed '21,22d;s/DATADIR/$(subst /,\/,$(DATADIR))/' $^ > $@
	chmod +x $@

shimmer: $(SRC:.c=.o)

install: release
	install -D -t$(BINDIR) shimmer shimmer-init
	mkdir -p $(DATADIR)
	cp -r share/* $(DATADIR)

compile_commands.json: Makefile
	$(CLEAN)
	bear -- make --no-print-directory --quiet

.depend/%.d: %.c
	@mkdir -p $(dir $@) 
	$(CC) $(CFLAGS) -MM $^ -MF $@

include $(patsubst %.c, .depend/%.d, $(SRC))

clean:
	rm -f *.o shimmer shimmer-init

.PHONY: clean
