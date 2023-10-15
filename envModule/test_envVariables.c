#include <stdio.h>
#include "envVariables.h"

int main(void)
{
	init_env_vars();
	check_env("test.txt");
	read_env("test.txt");
	print_var();
	printf("Should be: Default->%s\n", get_user());
	printf("Should be: Default->%s\n", get_host());
	printf("Should be: Default->%s\n", get_path());
	set_var("Test", "Test");
	printf("Should be: Test->%s\n", get_env("Test"));
	printf("Should be: 0<%i\n", check_var("Test"));
	printf("Should be: 0>%i\n", check_var("NotHere"));
	destroy_env();
}
