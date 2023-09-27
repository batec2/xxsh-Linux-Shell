/* history module for storing and retrieving shell command history
 */

#include "history.h"

// Shells only have one instance of history so this is fine as a global.
PRIVATE LinkedList *history_ll = NULL;
// Keep a pointer to the hash table that we can use to check the HISTSIZE entry.
PRIVATE HashTable *hash_table = NULL;

/* Initialize history
 * @param hasha pointer to the hash table to get hist_size.
 */
void initialize_history(HashTable *hash)
{
    hash_table = hash;
}

/* Add a command to history.
 * @param cmd a string representing the command to add.
 */
void add_history(char *cmd)
{
    // Check if history is full
    if (history_ll->size >= atoi(getEntry(hash_table, "HISTSIZE")))
    {
        printf("GETS HERE\n");
        // Need to remove the first entry
        delete_first(history_ll);
    } 

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
        
