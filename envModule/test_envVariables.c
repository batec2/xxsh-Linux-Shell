#include <stdio.h>
#include "envVariables.h"

int main(void)
{
	init_env_vars();
	read_env();
	print_var();
	set_var("Test", "Test");
	printf("Should be: /usr/bin/->%s\n", get_env("PATH")));
	printf("Should be: 0<%i\n", check_var("USER"));
	printf("Should be: 0>%i\n", check_var("NotHere"));
	destroy_env();
}
