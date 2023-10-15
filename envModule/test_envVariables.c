#include <stdio.h>
#include "envVariables.h"

int main(void)
{
	init_env_vars();
	print_var();
	printf("Should be: Default->%s\n", get_user());
	printf("Should be: Default->%s\n", get_host());
	printf("Should be: Default->%s\n", get_path());
	set_var("Test", "Test");
	printf("Should be: Test->%s\n", get_env("Test"));
	printf("Should be: 0<%i\n", check_var("Test"));
	printf("Should be: 0>%i\n", check_var("NotHere"));
	write_env("test.txt");
	destroy_env();
}
