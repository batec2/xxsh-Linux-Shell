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
    DIR * directory = NULL;
    // Get the PATH environment variable
    char *tmp = get_path();
    char *path_env = malloc(strlen(tmp)+1);;
    strcpy(path_env, tmp);

    // Iterate over the values in PATH (separated by semicolons)
    char *dir_path = strtok(path_env, ";");
    while( dir_path != NULL)
    {
        directory = opendir(dir_path);
        if (directory == NULL)
        {
            printf("Unable to find directory: %s\n", dir_path);
            //closedir(directory);
            return 0;
        }
        struct dirent *dir;
        // Search for matching binary in directory
        while ((dir = readdir(directory)) != NULL)
        {
            if (strcmp(dir->d_name, program) == 0)
            {
                *path = (char*) malloc(strlen(dir_path)+strlen(dir->d_name)+2);;
                strcpy(*path, dir_path);
                strcat(*path, "/");//this + null term =2
                strcat(*path, dir->d_name);
                free(path_env);
                path_env=NULL;
                closedir(directory);
                return 1;
            }
        }
        dir_path = strtok(NULL, ";");
    }
    free(path_env);
    closedir(directory);
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
        // If the command ends with a & then run in background
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
    pid_t pid;
    int status = 0;
    char *path = NULL;

    /*checks if program is in path*/
    if (!get_program(args[0],  &path))
    {
        return(0);
    }
    pid = fork();
    if(pid >0)
    {
        wait(&status); //parent is waiting
    }
    else
    {
        //char *path = NULL;
        if (run_background(args))
        {
            pid_t pid2 = fork();
            if(pid2 > 0)
            {
                exit(0); // Middle process
            }
            else
            {
                execv(path, args);
                exit(0);
            }
        }
        else
        {
            execv(path, args);
        }
        exit(0);
    }
    free(path);
    return status==0?1:0;
}

