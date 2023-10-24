CC= gcc
CFLAGS= -Wall -pedantic -g -std=c11

MODULES = test_pipe.o
MODULES += pipe.o 
MODULES += ../binary/binary.o  
MODULES += ../envModule/envVariables.o
MODULES += ../hashTable/dataStructure.o
MODULES += ../fileIO/fileIO.o

pipe.o: pipe.c pipe.h 
	$(CC) $(CFLAGS) -c $<

test_pipe.o: test_pipe.c 
	$(CC) $(CFLAGS) -c $<

.PHONY: 
test: $(MODULES)
	$(CC) $(CFLAGS) $^ -o $@
	./test

memCheck: test
	valgrind -s --leak-check=yes ./pipe_test

clean:
	rm -f *~ *.o test config.txt