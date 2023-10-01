CC= gcc
CFLAGS= -Wall -g -pedantic -std=c11

test_envVariables.o: envVariables.o
	$(CC) $(CFLAGS) -c test_envVariables.c


envVariables.o: envVariables.c envVariables.h ../hashTable/dataStructure.h
	$(CC) $(CFLAGS) -c envVariables.c

hashTable.o:
	make -C ../hashTable/
.PHONY:

test: envVariables.o test_envVariables.o ../hashTable/dataStructure.o
	$(CC) $(CFLAGS) $^ -o $@
	./test

clean:
	rm -f *~ *.o test