CC= gcc
CFLAGS= -Wall -g -pedantic -std=c99 
LDFLAGS= -lm

test_linkedList: linkedList.o test_linkedList.o
	$(CC) $(CFLAGS) $^ -o $@

test_linkedList.o: test_linkedList.c
	$(CC) $(CFLAGS) -c test_linkedList.c

linkedList.o: linkedList.c linkedList.h 
	$(CC) $(CFLAGS) -c linkedList.c

.PHONY:

test: memCheck
	./test_linkedList

memCheck: test_linkedList
	valgrind -s --leak-check=yes ./test_linkedList

clean:
	rm -f *~ *.o test_linkedList
