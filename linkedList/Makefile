CC= gcc
CFLAGS= -Wall -g -pedantic -std=c11
LDFLAGS= -lm

test_linkedList.o: test_linkedList.c
	$(CC) $(CFLAGS) -c test_linkedList.c 

linkedList.o: linkedList.c linkedList.h 
	$(CC) $(CFLAGS) -c linkedList.c

testUtils.o:
	make -C ../test/

.PHONY: test
test: linkedList.o test_linkedList.o ../testUtils/testUtils.o
	$(CC) $(CFLAGS) $^ -o $@
	./test

memCheck: test
	valgrind -s --leak-check=yes ./test

clean:
	rm -f *~ *.o test
