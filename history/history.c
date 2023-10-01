/* history module for storing and retrieving shell command history
 */

#include "history.h"

// Shells only have one instance of history so this is fine as a global.
PRIVATE LinkedList *history_ll = NULL;

/* Add a command to history.
 * @param cmd a string representing the command to add.
 */
void add_history(char *cmd)
{
	// Check if history is full
	if (history_ll == NULL) {
		history_ll = initialize();
	}
	// trim list
	while (history_ll->size >= atoi(getEnv("HISTSIZE"))) {
		// Need to remove the first entry
		delete_first(history_ll);
	}

	add(cmd, history_ll);
}

/* Prints the history contents.*/
void history()
{
	if (history_ll == NULL)
		return;
	print_list(history_ll);
}

/* destroys the history */
void destroy_history()
{
	destroy_list(history_ll);
}
