/* history module for storing and retriving shell command history
 */

#ifndef HISTORY
#define HISTORY

#include "../linkedList/linkedList.h"
#include "../envModule/envVariables.h"

#define PRIVATE static

/**
 * 
*/
void init_list();
/* Add a command to history.
 * @param cmd a string representing the command to add.
 */
void add_history(char *cmd);

/* Prints the history contents.*/
void history();

/* destroys the history */
void destroy_history();

/**
 * @param value String to be found in history
 * @return if string is found it is returned, else NULL
*/
char *get_history(char *value);

/**
 * gets the last command to be entered
 * @return the most recent item in history
*/
char *get_last();

/**
 * checks if history is empty
 * @return returns 1 if the list is empty 0 if it isnt
*/
int history_empty();
#endif				/* HISTORY */
