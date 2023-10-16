/* history module for storing and retrieving shell command history
 */

#include "history.h"

// Shells only have one instance of history so this is fine as a global.
PRIVATE LinkedList *history_ll = NULL;

/**
 * 
*/
void init_list(){
	history_ll = initialize();
}

/* Add a command to history.
 * @param cmd a string representing the command to add.
 */
void add_history(char *cmd)
{
	if(cmd[0]=='\n'){
		return;
	}
	// trim list
	while (history_ll->size >= atoi(get_env("HISTSIZE"))) {
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

/*gets a value from history*/
char *get_history(char *inValue){
	Item *item = search_n(inValue,history_ll);
	if(item == NULL){
		return NULL;
	}
	return item->value;
}

/*Gets latest command from history*/
char *get_last(){
	return get_first(history_ll);
}

int history_empty(){
	return is_empty(history_ll);
}
