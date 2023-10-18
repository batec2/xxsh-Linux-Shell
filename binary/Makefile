CC= gcc
CFLAGS= -Wall -pedantic -std=c11

MODULES = binary.o 
MODULES += test_binary.o 
MODULES += ../testUtils/testUtils.o 
MODULES += ../envModule/envVariables.o
MODULES += ../hashTable/dataStructure.o


test_binary.o: test_binary.c 
	$(CC) $(CFLAGS) -c $<

binary.o: binary.c binary.h 
	$(CC) $(CFLAGS) -c $^

testUtils.o:
	make -C ../test/

.PHONY: test
test: $(MODULES)
	$(CC) $(CFLAGS) $^ -o $@
	./test

memCheck: test
	valgrind -s --leak-check=yes ./test

clean:
	rm -f *~ *.o test_binary
