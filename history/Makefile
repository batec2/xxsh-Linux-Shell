CC= gcc
CFLAGS= -Wall -g -pedantic -std=c11

MODULES = ../linkedList/linkedList.o
MODULES += ../envModule/envVariables.o 
MODULES += ../hashTable/dataStructure.o
MODULES += ../fileIO/fileIO.o

test_history.o: test_history.c 
	$(CC) $(CFLAGS) -c $<

history.o: history.c history.h
	$(CC) $(CFLAGS) -c $<

envVariables.o:
	make -C ../envVariables/

linkedList.o:
	make -C ../linkedList/

dataStructure.o:
	make -C ../hashTable/

fileIO.o:
	make -C ../fileIO/

.PHONY: test
test: history.o test_history.o $(MODULES)
	$(CC) $(CFLAGS) $^ -o $@
	./test


memCheck: test_history
	valgrind -s --leak-check=yes ./test

clean:
	rm -f *~ *.o test
