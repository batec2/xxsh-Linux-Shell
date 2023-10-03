CC= gcc
CFLAGS= -Wall -g -pedantic -std=c11

all: test

test_dataStructure.o: test_dataStructure.c
	$(CC) $(CFLAGS) -c $<

dataStructure.o: dataStructure.c dataStructure.h 
	$(CC) $(CFLAGS) -c $<

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
