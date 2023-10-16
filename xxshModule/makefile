CC= gcc
CFLAGS= -Wall -g -pedantic -std=c11 

all: xxsh

xxsh.o: xxsh.c xxsh.h ../envModule/envVariables.h ../history/history.h ../binary/binary.h
	$(CC) $(CFLAGS) -c $<

.PHONY:

test:

memCheck: xxsh test_dataStructure
	valgrind -s --leak-check=yes ./xxsh

clean:
	rm -f *~ *.o xxsh