CC= gcc
CFLAGS= -Wall -g -pedantic -std=c11

test_linkedList.o: test_linkedList.c
	$(CC) $(CFLAGS) -c $<

linkedList.o: linkedList.c linkedList.h 
	$(CC) $(CFLAGS) -c $<

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
