/* linkedlist.h contains function definitions for the doubly linked list data
 structure.
 */

#ifndef LINKED_LIST
#define LINKED_LIST

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Struct for list items */
typedef struct Item{
    // Pointer to next item
    struct Item *next;
    // Pointer to previous item
    struct Item *previous;
    // String containing the item's value
    char *value;
 }Item;

/* Struct for linked list */
typedef struct LinkedList{
     // Pointer to first item in list
    struct Item *first;
     // Pointer to last item in list
    struct Item *last;
     // Integer to track list size
     int size;
 }LinkedList;

// Function declarations

/* Initializes the linked list 
 @return a pointer to the LinkedList object
*/
LinkedList *initialize();

/* Add an item to the list.
 * @param value string to insert into list.
 * @param list LinkedList to insert value into.
 * @return -1 if failure, else 0.
 */
int add(char *value, LinkedList *list);

/* Remove an item from the list
 * @param value string to remove.
 * @param list LinkedList to remove item from.
 * @return -1 if failure, else 0.
 */
int delete_item(char *value, LinkedList *list);

/* Prints all items in the list.
 * @param list LinkedList to print.
 */
void print_list(LinkedList *list);



#endif //LINKED_LIST
