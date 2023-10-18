CC= gcc
CFLAGS= -Wall -g -pedantic -std=c11

MODULES = ./xxshModule/xxsh.o
MODULES += ./hashTable/dataStructure.o
MODULES += ./envModule/envVariables.o 
MODULES += ./linkedList/linkedList.o
MODULES += ./linkedList/linkedList.o 
MODULES += ./history/history.o
MODULES += ./fileIO/fileIO.o
MODULES += ./binary/binary.o

all: xxsh

xxsh: $(MODULES)
	$(CC) $(CFLAGS) $^ -o $@

xxsh.o:
	# Recursive make: 
	# https://www.gnu.org/software/make/manual/html_node/Recursion.html
	make -C ./xxshModule/

envVariables.o:
	make -C ./envModule/

linkedList.o:
	make -C ./linkedList/

dataStructure.o:
	make -C ./hashTable/

history.o: 
	make -C ./history/
	
fileIO.o: 
	make -C ./fileIO/

binary.o:
	make -C ./binary/

.PHONY:

test: xxsh
	make test -C ./hashTable/
	make test -C ./history/
	make test -C ./linkedList/
	make test -C ./envModule/

memCheck: xxsh
	valgrind -s --leak-check=yes --show-leak-kinds=all ./xxsh

tar:
	make clean
	tar -czvf ../lab02_CrushBate_DakotaDoolaege.tar.gz -C .. CMPT360Lab

clean:
	rm -f *~ *.o xxsh
	make clean -C ./envModule/
	make clean -C ./hashTable/
	make clean -C ./history/
	make clean -C ./linkedList/
	make clean -C ./xxshModule/
	make clean -C ./testUtils/
	make clean -C ./fileIO/
	make clean -C ./binary/
