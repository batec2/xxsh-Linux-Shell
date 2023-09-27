CC= gcc
CFLAGS= -Wall -g -pedantic -std=c11

envVariables.o: envVariables.c envVariables.h ../hashTable/dataStructure.h
	$(CC) $(CFLAGS) -c envVariables.c

hashTable.o:
	make -C ../hashTable/
.PHONY:

test:

clean:
	rm -f *~ *.o 