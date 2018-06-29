TARGETS=$(patsubst %.c, %.out, $(wildcard *.c))
CFLAGS=-O2 -Wno-unused-result
all: $(TARGETS)

.c.out:
	@$(CC) $(CFLAGS) -o $@ $<
	
clean:
	rm -f *.out

test:
	@$(foreach f, $(TARGETS), echo "\033[0;31m./$(f)\033[0m:";valgrind --leak-check=full ./$(f) 2>&1|grep HEAP\ SUMMARY -A 4;echo "";)
