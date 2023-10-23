#ifndef PIPE
#define PIPE
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "../binary/binary.h"

/**
 * Finds the location of the pipe in the arguments
 * @param args array of strings(must terminate with NULL pointer)
 * @return returns -1 if pipe operator is not in args
 * else returns index of pipe
*/
int check_pipe(char **args);
/**
 * Pipes the first command into the second command
 * @param args array of strings(must terminate with NULL pointer)
 * @returns -1 if failed else returns 0
*/
int piping(char **args);

#endif /*PIPE*/