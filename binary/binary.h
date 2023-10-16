/* This module adds support for executing binary programs to the shell.
 *
 * It looks for binaries stored in the PATH environment variable directories.
 */

#include <dirent.h>

#include "../envModule/envVariables.h"


/* Gets the path to a specified executable
 * @param program name of program to search for
 * @param path pointer to string that will hold the path
 * @return 1 if found, 0 if not found
 */
int get_program(char *program, char** path);

