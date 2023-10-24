CC= gcc
CFLAGS= -Wall -g -pedantic -std=c11 

XXSH = xxsh.c xxsh.h
HEADERS = ../envModule/envVariables.h 
HEADERS += ../history/history.h 
HEADERS += ../binary/binary.h
HEADERS += ../pipe/pipe/h

all: xxsh

xxsh.o: $(XXSH) $(HEADERS)
	$(CC) $(CFLAGS) -c $<

.PHONY:

test:

memCheck: xxsh test_dataStructure
	valgrind -s --leak-check=yes ./xxsh

clean:
	rm -f *~ *.o xxsh