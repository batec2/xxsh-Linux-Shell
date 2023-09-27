CC= gcc
CFLAGS= -Wall -g -pedantic -std=c99 
LDFLAGS= -lm

test_history: history.o test_history.o ../linkedList/linkedList.o ../hashTable/dataStructure.o
	$(CC) $(CFLAGS) $^ -o $@

test_history.o: test_history.c 
	$(CC) $(CFLAGS) -c test_history.c

history.o: history.c history.h
	$(CC) $(CFLAGS) -c history.c

dataStructure.o:
	make -C ../hashTable/

linkedList.o:
	make -C ../linkedList/

.PHONY:

test: memCheck
	./test_history

memCheck: test_history
	valgrind -s --leak-check=yes ./test_history

clean:
	rm -f *~ *.o test_history
