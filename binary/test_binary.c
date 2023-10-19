/* Test program for the binary module */

#include <stdio.h>

#include "binary.h"
#include "../testUtils/testUtils.h"

int main()
{
	printf("Testing the binary module...\n\n");

	init_env_vars();

	set_var("PATH", "/usr/bin");

	char *path = NULL;
	test(get_program("ls", &path) == 1, "searching path for program");
	free(path);

	char *arg_array[] = { "ls", "-a", "-l", "/home", NULL };

	test(run_background(arg_array) == 0, "checking for foreground command");

	test(run_cmd(arg_array) == 1, "running a foreground ls command");

	char *tmp = malloc(2);
	strcpy(tmp, "&");
	char *arg_array2[] = { "ls", tmp, NULL };
	test(run_background(arg_array2) == 1,
	     "checking for background command");
	printf("here!!!\n");

	tmp = malloc(2);
	strcpy(tmp, "&");
	char *arg_array3[] = { "xmessage", "Hello, World", tmp, NULL };
	test(run_cmd(arg_array3) == 1,
	     "running a background xmessage command");;
	printf("hello, I've returned before xmessage!\n");

	printf("TESTING COMPLETE FOR BINARY MODULE!\n\n");
}
