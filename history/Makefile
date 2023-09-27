CC= gcc
CFLAGS= -Wall -g -pedantic -std=c11
LDFLAGS= -lm

test: history.o test_history.o ../linkedList/linkedList.o ../hashTable/dataStructure.o
	$(CC) $(CFLAGS) $^ -o $@
	./test

test_history.o: test_history.c 
	$(CC) $(CFLAGS) -c test_history.c

history.o: history.c history.h
	$(CC) $(CFLAGS) -c history.c

dataStructure.o:
	make -C ../hashTable/

linkedList.o:
	make -C ../linkedList/

.PHONY:

memCheck: test_history
	valgrind -s --leak-check=yes ./test

clean:
	rm -f *~ *.o test
