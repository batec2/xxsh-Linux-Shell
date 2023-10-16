/* Test program for the binary module */

#include <stdio.h>

#include "binary.h"

int main()
{
    printf("Testing the binary module...\n");
    
    init_env_vars();
    set_var("PATH", "/home/dakota/bin");

    printf("Testing program search...\n");
    char *path = NULL;
    if(!get_program("ls", &path))
        printf("Failed to get the path for ls\n");
    else
    {
        printf("PASS: Found path: %s\n\n", path);
        free(path);
    }
        

    char *arg_array[] = {"ls", "-a", "-l", "/home/dakota/bin", NULL};
    run_cmd(arg_array);

    printf("\n\n");
    char *arg_array2[] = {"ls", "-a", "-l", "/home/dakota/bin", "&", NULL};
    run_cmd(arg_array2);
        

}
