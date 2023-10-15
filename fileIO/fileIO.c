#include "fileIO.h"

/**
 * Opens files
 * I just realized this basically does the same thing as fopen
*/
FILE *open_file(char *file_name,char *mode)
{
	FILE *file;
	file = fopen(file_name, mode);
	if (file != NULL) {
		return file;
	} else {
		return NULL;
	}
}

/**
 * Reads and prints file
*/
void print_file(FILE * file)
{
	char buffer[256];
	while (fgets(buffer, 256, file) != NULL) {
		printf("%s", buffer);
	}
	fclose(file);
}





