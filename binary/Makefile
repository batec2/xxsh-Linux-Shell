CC= gcc
CFLAGS= -Wall -pedantic -std=c11

test_binary.o: test_binary.c 
	$(CC) $(CFLAGS) -c $<

binary.o: binary.c binary.h 
	$(CC) $(CFLAGS) -c $^

testUtils.o:
	make -C ../test/

.PHONY: test
test: binary.o test_binary.o ../testUtils/testUtils.o ../envModule/envVariables.o ../hashTable/dataStructure.o
	$(CC) $(CFLAGS) $^ -o $@
	./test

memCheck: test
	valgrind -s --leak-check=yes ./test

clean:
	rm -f *~ *.o test_binary
