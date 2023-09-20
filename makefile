CC= gcc
CFLAGS= -Wall -g -pedantic -std=c99 
LDFLAGS= -lm

all: test_dataStructure

test_dataStructure: dataStructure.o test_dataStructure.o
	$(CC) $(CFLAGS) $^ -o $@

test_dataStructure.o: test_dataStructure.c
	$(CC) $(CFLAGS) -c test_dataStructure.c

dataStructure.o: dataStructure.c dataStructure.h 
	$(CC) $(CFLAGS) -c dataStructure.c

.PHONY:

test: memCheck
	./test_dataStructure

memCheck: test_dataStructure
	valgrind -s --leak-check=yes ./test_dataStructure

tar:
	make clean
	tar -czvf ../dataStructure.tar.gz -C .. dataStructure

clean:
	rm -f *~ *.o test_dataStructure