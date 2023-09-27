/* Test file for history module */

#include "history.h"

int main()
{
    initEnvVars();
    printf("Startings history module tests\n\n");

    /*Test adding items to history. This is a manual test*/
    printf("Adding three items to history\n\n");
    add_history("ls -l");
    add_history("pwd");
    add_history("ps -ax | grep systemd");

    /* Test printing out the history contents. This is a manual test */
    printf("Printing history contents\n");
    history();

    destroy_history();

    printf("Testing complete for history module\n\n");
}
