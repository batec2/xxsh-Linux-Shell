CC= gcc
CFLAGS= -Wall -g -pedantic -std=c11
LDFLAGS= -lm

all: xxsh

xxsh: ./xxshModule/xxsh.o ./hashTable/dataStructure.o ./envModule/envVariables.o ./linkedList/linkedList.o ./history/history.o
	$(CC) $(CFLAGS) $^ -o $@

xxsh.o:
	make -C ./xxshModule/

envVariables.o:
	make -C ./envModule/

linkedList.o:
	make -C ./linkedList/

dataStructure.o:
	make -C ./hashTable/

history.o: 
	make -C ./history/

.PHONY:

test: memCheck

memCheck: xxsh
	valgrind -s --leak-check=yes ./xxsh

tar:
	make clean
	tar -czvf ../lab01_CrushBate.tar.gz -C .. CMPT360Lab1

clean:
	rm -f *~ *.o xxsh