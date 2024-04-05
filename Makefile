CC=cc
CFLAGS+=-Wall -Wextra -Werror

SRC:=$(wildcard *.c)

debug: CFLAGS+=-g
debug: shimmer

release: CFLAGS+=-O2
release: clean shimmer

shimmer: $(SRC:.c=.o)

compile_commands.json: Makefile
	$(CLEAN)
	bear -- make --no-print-directory --quiet

.depend/%.d: %.c
	@mkdir -p $(dir $@) 
	$(CC) $(CFLAGS) -MM $^ -MF $@

include $(patsubst %.c, .depend/%.d, $(SRC))

clean:
	rm -f *.o shimmer

.PHONY: clean
