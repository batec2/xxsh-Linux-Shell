/* linkedlist.c contains function implementations for the doubly linked list
 * data structure.
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

/* Search for an item in the list.
 * @param value to search for.
 * @param list LinkedList to search.
 * @return pointer to the Item.
 */
Item *search(char *value, LinkedList * list)
{
	for (Item * item = list->first; item != NULL; item = item->next)
		if (strcmp(item->value, value) == 0)
			return item;
	return NULL;
}

/* Search for an item in the list, will get get the first item that matchs
 * @param value to search for.
 * @param list LinkedList to search.
 * @return pointer to the Item.
 */
Item *search_n(char *value, LinkedList * list)
{
	for (Item * item = list->last; item != NULL; item = item->previous)
		if (strncmp(value, item->value,strlen(value)) == 0)
			return item;
	return NULL;
}

/* Add an item to the list.
 * @param value string to insert into list.
 * @param list LinkedList to insert value into.
 * @return the address of the new item or NULL.
 */
Item *add(char *value, LinkedList * list)
{
	// Create a new item and assign the value
	Item *item = (Item *) malloc(sizeof(Item));
	item->value = malloc(strlen(value) + 1);
	strcpy(item->value, value);
	// Add item to the end of the list and increment list counter

	if (!list->first) {
		item->previous = NULL;
		list->last = item;
	}
	Item *second_item = list->first;
	if (second_item) {
		second_item->previous = item;
		item->next = second_item;
	}
	item->previous = NULL;
	list->first = item;
	list->size++;

	//TODO: Add failure checks
	return item;
}

/* Remove an item from the list
 * @param value string to remove.
 * @param list LinkedList to remove item from.
 * @return 0 if failure, else 1.
 */
int delete_item(char *value, LinkedList * list)
{
	Item *item = NULL;
	// Search for the item in the list
	if (!(item = search(value, list))) {
		printf("ERROR: Unable to find item in list: %s\n", value);
		return 0;
	}
	// remove item from list
	if (item->previous) {
		// Middle of the list
		if (item->next) {
			item->previous->next = item->next;
			item->next->previous = item->previous;
		}
		// End of list
		else {
			item->previous->next = NULL;
			list->last = item->previous;
		}
	}
	// Start of list
	else if (item->next) {
		item->next->previous = NULL;
		list->first = item->next;
	}
	//Only item in list
	else {
		list->first = NULL;
		list->last = NULL;
	}

	// free item
	free(item);
	list->size--;
	return 1;
}

/* Remove the first (oldest) item from the list
 * @param list LinkedList to remove item from.
 * @return -1 if failure, else 0.
 */
int delete_first(LinkedList * list)
{
	if (list->size < 1)
		return 1;
	Item *item = list->first;
	list->first = item->next;
	free(item->value);
	item->value = NULL;
	free(item);
	item = NULL;
	list->size--;
	return 1;
}

/* Prints all items in the list.
 * @param list LinkedList to print.
 */
void print_list(LinkedList * list)
{
	for (Item * item = list->first; item != NULL; item = item->next)
		printf("%s\n", item->value);
}

/* Prints the last item in the list.
 * @param list LinkedList to print item from.
 */
void print_last(LinkedList * list)
{
	printf("%s\n", list->last->value);
}

/* Destroy the linked list and free all memory.
 * @param list the LinkedList to destroy.
 */
void destroy_list(LinkedList * list)
{
	Item *item = list->first;
	while (item != NULL) {
		Item *cache = item->next;
		list->first = cache;
		free(item->value);
		item->value = NULL;
		free(item);
		item = cache;
	}
	free(list);
	list = NULL;
}

/*gets first item in list*/
char *get_first(LinkedList * list)
{
	return list->first->value;
}

/*checks if list is empty*/
int is_empty(LinkedList * list)
{
	return list->size == 0;
}
