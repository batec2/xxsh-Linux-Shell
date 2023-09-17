CC= gcc
CFLAGS= -Wall -g -pedantic -std=c99 
LDFLAGS= -lm

all: dataStructure

dataStructures: dataStructure.o 
	$(CC) $(CFLAGS) $^ -o $@

dataStructures.o: dataStructure.c dataStructure.h 
	$(CC) $(CFLAGS) -c dataStructure.c

tar:

clean:
	rm -f *~ *.o