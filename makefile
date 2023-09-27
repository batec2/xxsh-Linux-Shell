CC= gcc
CFLAGS= -Wall -g -pedantic -std=c11
LDFLAGS= -lm

all: xxsh

xxsh: xxsh.o dataStructure.o envVariables.o linkedList.o history.o
	$(CC) $(CFLAGS) $^ -o $@

xxsh.o: ./xxshModule/xxsh.c ./xxshModule/xxsh.h ./envModule/envVariables.h ./history/history.h
	$(CC) $(CFLAGS) -c ./xxshModule/xxsh.c

dataStructure.o: ./hashTable/dataStructure.c ./hashTable/dataStructure.h 
	$(CC) $(CFLAGS) -c ./hashTable/dataStructure.c

envVariables.o: ./envModule/envVariables.c ./envModule/envVariables.h ./hashTable/dataStructure.h 
	$(CC) $(CFLAGS) -c ./envModule/envVariables.c

linkedList.o: ./linkedList/linkedList.c ./linkedList/linkedList.h
	$(CC) $(CFLAGS) -c ./linkedList/linkedList.c

history.o: ./history/history.c ./history/history.h ./linkedList/linkedList.h
	$(CC) $(CFLAGS) -c ./history/history.c

.PHONY:

test: memCheck

memCheck: xxsh
	valgrind -s --leak-check=yes ./xxsh

tar:
	make clean
	tar -czvf ../lab01_CrushBate.tar.gz -C .. CMPT360Lab1

clean:
	rm -f *~ *.o xxsh