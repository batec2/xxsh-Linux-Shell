#ifndef FILE_IO
#define FILE_IO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * Takes a file and opens it with fopen
 * @param Valid file name
 * @return FILE pointer
*/
FILE *open_file(char *file_name,char *mode);

/**
 * Takes a FILE and prints it's contents
 * @param file open file pointer
*/
void print_file(FILE * file);

#endif				/*FILE_IO */
