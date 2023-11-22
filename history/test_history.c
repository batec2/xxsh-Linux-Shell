/* Test file for history module */

#include "history.h"

int main()
{
	init_env_vars();
	init_list();
	printf("Startings history module tests\n\n");
	set_var("HISTSIZE", "5");

	/*Test adding items to history. This is a manual test */
	printf("Adding three items to history\n\n");
	add_history("ls -l\n");
	add_history("pwd\n");
	add_history("ps -ax | grep systemd\n");

	/* Test printing out the history contents. This is a manual test */
	printf("Printing history contents\n");
	history();

	destroy_history();

	printf("Testing complete for history module\n\n");
}
