CC= gcc
CFLAGS= -Wall -g -pedantic -std=c99 
LDFLAGS= -lm

all: xxsh

xxsh: xxsh.o 
	$(CC) $(CFLAGS) $^ -o $@

xxsh.o: xxsh.c xxsh.h 
	$(CC) $(CFLAGS) -c xxsh.c

.PHONY:

test:

memCheck: test_dataStructure
	valgrind -s --leak-check=yes ./xxsh

clean:
	rm -f *~ *.o xxsh