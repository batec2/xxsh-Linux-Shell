/* history module for storing and retriving shell command history
 */

#ifndef HISTORY
#define HISTORY

#include "../linkedList/linkedList.h"
#include "../envModule/envVariables.h"

#define PRIVATE static

/* Add a command to history.
 * @param cmd a string representing the command to add.
 */
void add_history(char *cmd);

/* Prints the history contents.*/
void history();

/* destroys the history */
void destroy_history();

#endif /* HISTORY */
