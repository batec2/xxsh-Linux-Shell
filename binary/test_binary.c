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
    if(!get_program("ls", path))
        printf("Failed to get the path for ls\n");
    else
        printf("PASS: Found path: %s", path);
    free(path);

        

}
