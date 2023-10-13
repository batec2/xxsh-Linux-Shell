/* This module adds support for executing binary programs to the shell.
 *
 * It looks for binaries stored in the PATH environment variable directories.
 */
#include "binary.h"

/* Gets the path to a specified executable
 * @param program name of program to search for
 * @param path pointer to string that will hold the path
 * @return 1 if found, 0 if not found
 */
int get_program(char  *program, char* path)
{
    // Get the PATH environment variable
    char *path_env = get_path();
    printf("path: %s\n", path_env);

    // TODO: add support for ; in PATH
    // Iterate over the values in PATH (separated by semicolons)
    DIR *directory = opendir(path_env);
    if (directory == NULL)
    {
        printf("Unable to find directory: %s\n", path_env);
        return 0;
    }
    struct dirent *dir;
    while ((dir = readdir(directory)) != NULL)
    {
        printf("binary: %s\n", dir->d_name);
    }

        

    // Return when match is found

    return 0;
}
