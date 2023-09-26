/* history module for storing and retrieving shell command history
 */

#include "history.h"


PRIVATE LinkedList *history_ll = NULL;

/* Add a command to history.
 * @param cmd a string representing the command to add.
 */
void add_history(char *cmd)
{
    if (history_ll == NULL)
        history_ll = initialize();
    add(cmd, history_ll);
}

/* Prints the history contents.*/
void history()
{
    if (history_ll == NULL)
        return;
    print_list(history_ll);
}
        
