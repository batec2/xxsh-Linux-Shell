CC= gcc
CFLAGS= -Wall -g -pedantic -std=c99 
LDFLAGS= -lm

all: dataStructures

dataStructures: dataStructures.o 
	$(CC) $(CFLAGS) $^ -o $@

dataStructures.o: dataStructures.c dataStructures.h 
	$(CC) $(CFLAGS) -c dataStructures.c

tar:

clean:
	rm -f *~ *.o