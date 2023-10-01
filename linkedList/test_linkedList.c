#include <stdio.h>

#include "linkedList.h"
#include "../testUtils/testUtils.h"

int main()
{
	printf("Testing the LinkedList class...\n");

	// Test test helper function
	test(1, "This should pass");

	LinkedList *list = NULL;
	test(((list = initialize()) != NULL), "Initializing LinkedList");

	test(((add("Hello World", list) != NULL)), "Adding item");
	add("Hello Mars", list);
	Item *item3 = add("Hello World3", list);

	printf
	    ("Testing printing of list. This is a manual test. There should be"
	     " three items printed.");
	print_list(list);

	// Verify item was added by add and then found by search
	test(search("Hello World3", list) == item3, "Testing search and add");

	// Verify searching for a non-existent value returns NULL
	test(search("I DON'T EXIST!", list) == NULL,
	     "Searching for non-existent value");

	// Verify last item can be deleted
	test(delete_item("Hello World3", list) == 1, "Deleting last item");

	// Verify first item can be deleted
	test(delete_item("Hello World", list) == 1, "Deleting first item");

	// Verify only item can be deleted
	test(delete_item("Hello Mars", list) == 1, "Deleting only item");

	print_list(list);
	// Test deleteing the first item
	test(delete_first(list) == 1, "Deleting first item in list");

	printf
	    ("Testing printing of empty list. This is a manual test. There should be"
	     " no items printed.");
	print_list(list);

	test(((add("A new beginning", list) != NULL)),
	     "Adding item after clearing list");

	add("Hello 101955 Bennu", list);
	add("Hello OSIRIS-REx", list);

	// Verify printing the last item
	printf
	    ("Testing printing of last item in list. This is a manual test.\n");
	print_last(list);

	// Verify destroy
	destroy_list(list);
	list = NULL;

	printf("\nTesting complete!\n\n");

}
