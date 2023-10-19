/* This module adds support for executing binary programs to the shell.
 *
 * It looks for binaries stored in the PATH environment variable directories.
 */

#include <dirent.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

#include "../envModule/envVariables.h"


/* Gets the path to a specified executable
 * @param program name of program to search for
 * @param path pointer to string that will hold the path
 * @return 1 if found, 0 if not found
 */
int get_program(char *program, char** path);

/* Checks if a command ends with an & which indicates to run it in the
 * background
 * @param args
 * returns 1 if it is to run in the background or 0 if foreground
 */
int run_background(char **args);

/* Runs a command
 * @param  args list of arguments
 * @return the exit status of the command
 */
int run_cmd(char **args);
