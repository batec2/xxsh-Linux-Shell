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
int get_program(char  *program, char** path)
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
        if (strcmp(dir->d_name, program) == 0)
        {
            *path = (char*) malloc(strlen(path_env)+strlen(dir->d_name)+1);;
            strcpy(*path, path_env);
            strcat(*path, "/");
            strcat(*path, dir->d_name);
            return 1;
        }
    }
    return 0;
}
