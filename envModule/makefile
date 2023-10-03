CC= gcc
CFLAGS= -Wall -g -pedantic -std=c11

test_envVariables.o: test_envVariables.c
	$(CC) $(CFLAGS) -c $<


envVariables.o: envVariables.c envVariables.h ../hashTable/dataStructure.h
	$(CC) $(CFLAGS) -c $<

hashTable.o:
	make -C ../hashTable/
.PHONY:

test: envVariables.o test_envVariables.o ../hashTable/dataStructure.o
	$(CC) $(CFLAGS) $^ -o $@
	./test

clean:
	rm -f *~ *.o test