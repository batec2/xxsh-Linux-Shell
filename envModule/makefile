CC= gcc
CFLAGS= -Wall -g -pedantic -std=c11
LDFLAGS= -lm

all: env

env: env.o  
	$(CC) $(CFLAGS) $^ -o $@

env.o: env.c env.h 
	$(CC) $(CFLAGS) -c env.c

.PHONY:

test:

memCheck: test_dataStructure
	valgrind -s --leak-check=yes ./env

clean:
	rm -f *~ *.o env