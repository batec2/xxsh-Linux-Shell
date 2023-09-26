CC= gcc
CFLAGS= -Wall -g -pedantic -std=c99 
LDFLAGS= -lm

test_linkedList: linkedList.o test_linkedList.o ../test/testUtils.o
	$(CC) $(CFLAGS) $^ -o $@

test_linkedList.o: test_linkedList.c
	$(CC) $(CFLAGS) -c test_linkedList.c 

linkedList.o: linkedList.c linkedList.h 
	$(CC) $(CFLAGS) -c linkedList.c

testUtils.o:
	make -C ../test/

.PHONY:

test: memCheck
	./test_linkedList

memCheck: test_linkedList
	valgrind -s --leak-check=yes ./test_linkedList

clean:
	rm -f *~ *.o test_linkedList
