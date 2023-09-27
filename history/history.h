/* history module for storing and retriving shell command history
 */

#ifndef HISTORY
#define HISTORY

#include "../linkedList/linkedList.h"
#include "../hashTable/dataStructure.h"

#define PRIVATE static

/* Initialize history
 * @param hash pointer to the hash table to get hist_size.
 */
void initialize_history(HashTable *hash);

/* Add a command to history.
 * @param cmd a string representing the command to add.
 */
void add_history(char *cmd);

/* Prints the history contents.*/
void history();

#endif /* HISTORY */
