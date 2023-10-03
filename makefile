CC= gcc
CFLAGS= -Wall -g -pedantic -std=c11

all: xxsh

xxsh: ./xxshModule/xxsh.o ./hashTable/dataStructure.o ./envModule/envVariables.o ./linkedList/linkedList.o ./history/history.o
	$(CC) $(CFLAGS) $^ -o $@

xxsh.o:
	# Recursive make: https://www.gnu.org/software/make/manual/html_node/Recursion.html
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

test: xxsh
	make test -C ./hashTable/
	make test -C ./history/
	make test -C ./linkedList/
	make test -C ./envModule/
	./test.sh

memCheck: xxsh
	valgrind -s --leak-check=yes ./xxsh

tar:
	make clean
	tar -czvf ../lab02_CrushBate_DakotaDoolaege.tar.gz -C .. CMPT360Lab1

clean:
	rm -f *~ *.o xxsh
	make clean -C ./envModule/
	make clean -C ./hashTable/
	make clean -C ./history/
	make clean -C ./linkedList/
	make clean -C ./xxshModule/
	make clean -C ./testUtils/
