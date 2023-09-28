CC= gcc
CFLAGS= -Wall -g -pedantic -std=c11
LDFLAGS= -lm

all: test

test_dataStructure.o: test_dataStructure.c
	$(CC) $(CFLAGS) -c test_dataStructure.c

dataStructure.o: dataStructure.c dataStructure.h 
	$(CC) $(CFLAGS) -c dataStructure.c

.PHONY: test
test: dataStructure.o test_dataStructure.o
	$(CC) $(CFLAGS) $^ -o $@
	./test

.PHONY:
memCheck: test
	valgrind -s --leak-check=yes ./test

tar:
	make clean
	tar -czvf ../lab01_CrushBate.tar.gz -C .. CMPT360Lab1

clean:
	rm -f *~ *.o test
