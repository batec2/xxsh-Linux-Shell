/* linkedlist.c contains function implementations for the doubly linked list data
 structure.
 */

#include "linkedList.h"


/* Initializes the linked list 
 @return a pointer to the LinkedList object
*/
LinkedList *initialize()
{
    LinkedList *list = malloc(sizeof(LinkedList));
    list->first = NULL;
    list->last = NULL;
    list->size = 0;

    return list;
}

/* Add an item to the list.
 * @param value string to insert into list.
 * @param list LinkedList to insert value into.
 * @return -1 if failure, else 0.
 */
int add(char *value, LinkedList *list)
{
    // Create a new item and assign the value
    Item *item = (Item*) malloc(sizeof(Item));
    item->value = malloc(strlen(value));
    strcpy(item->value, value);
    // Add item to the end of the list and increment list counter
    Item *first_item = list->first;
    if (!first_item)
    {
        printf("Adding first item to list\n");
        list->first = item;
    }
    Item *last_item = list->last;
    if (last_item)
        last_item->next = item;
    list->last = item;
    list->size++;

    //TODO: Add failure checks
    return 0;
}

/* Prints all items in the list.
 * @param list LinkedList to print.
 */
void print_list(LinkedList *list){
    printf("\nLinked List Items:\n");
    for (Item *item = list->first; item != NULL; item = item->next)
        printf("%s\n", item->value);
    printf("\n");
}
