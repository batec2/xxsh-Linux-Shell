/* Test program for the binary module */

#include <stdio.h>

#include "binary.h"
#include "../testUtils/testUtils.h"

int main()
{
    printf("Testing the binary module...\n\n");
    
    init_env_vars();
    set_var("PATH", "/usr/bin/bin;/usr/bin/bin");

    char *path = NULL;
    test(get_program("ls", &path) == 1, "searching path for program");
    free(path);

    char *arg_array[] = {"ls", "-a", "-l", "/home/dakota/bin", NULL};

    test(run_background(arg_array) == 0, "checking for foreground command");

    test(run_cmd(arg_array) == 0, "running a foreground ls command");

    char *arg_array2[] = {"ls", "&", NULL};
    test(run_background(arg_array2) == 1, "checking for background command");

    char *arg_array3[] = {"xmessage", "Hello, World", "&", NULL};
    test(run_cmd(arg_array3) == 0, "running a background xmessage command");;
    printf("hello, I've returned before xmessage!\n");

    printf("TESTING COMPLETE FOR BINARY MODULE!\n\n");
}
