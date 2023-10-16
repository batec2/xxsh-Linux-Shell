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

/* Checks if a command ends with an & which indicates to run it in the
 * background
 * @param args
 * returns 1 if it is to run in the background or 0 if foreground
 */
int run_background(char **args)
{
    int i = 0;
    while(args[i] != NULL)
    {
        if (strcmp(args[i], "&") == 0)
        {
            // Nullify the & (always at the end)
            args[i] = NULL;
            return 1;
        }
        i++;
    }
    return 0;
}

/* Runs a command
 * @param  args list of arguments
 * @return the exit status of the command 
 */
int run_cmd(char **args)
{
    char *path = NULL;
    pid_t pid;
    pid = fork();
    if(pid >0)
    {
        wait(NULL);
    }
    else
    {
        char *path = NULL;
        if (!get_program(args[0],  &path))
        {
            printf("Failed to find the program: %s\n", args[0]);
            exit(1);
        }
        printf("Running: %s\n", path);
        if (run_background(args))
        {
            printf("Running in background\n");
            // Strip &
            execv(path, args);
        }
        else
        {
            printf("Running in foreground\n");
            execv(path, args);
        }
        exit(0);
    }
    free(path);

    return 0;
}

