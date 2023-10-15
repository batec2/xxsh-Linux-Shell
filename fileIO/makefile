CC= gcc
CFLAGS= -Wall -g -pedantic -std=c11

envVariables.o: fileIO.c fileIO.h
	$(CC) $(CFLAGS) -c $<

.PHONY:

clean:
	rm -f *~ *.o test