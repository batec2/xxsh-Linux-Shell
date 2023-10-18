CC= gcc
CFLAGS= -Wall -g -pedantic -std=c11

ENV = envVariables.c envVariables.h
ENVO = envVariables.o test_envVariables.o

test_envVariables.o: test_envVariables.c
	$(CC) $(CFLAGS) -c $<

envVariables.o: $(ENV) ../hashTable/dataStructure.h ../fileIO/fileIO.h
	$(CC) $(CFLAGS) -c $<

hashTable.o:
	make -C ../hashTable/

fileIO.o:
	make -C ../fileIO/

.PHONY:

test: $(ENVO) ../hashTable/dataStructure.o ../fileIO/fileIO.o
	$(CC) $(CFLAGS) $^ -o $@
	./test

clean:
	rm -f *~ *.o test test.txt