#include <stdio.h>
#include "envVariables.h"

int main(void)
{
	initEnvVars();
	printVar();
	printf("Should be: Default->%s\n", getUser());
	printf("Should be: Default->%s\n", getHost());
	printf("Should be: Default->%s\n", getPath());
	setVar("Test", "Test");
	printf("Should be: Test->%s\n", getEnv("Test"));
	printf("Should be: 0<%i\n", checkVar("Test"));
	printf("Should be: 0>%i\n", checkVar("NoHere"));
	destroyEnv();

}
