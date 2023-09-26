#include <stdio.h>

#include "linkedList.h"

/* Prints out success message.
 * @param desc description of test.
 */
void PASS(char *desc)
{
    printf("PASS: %s\n\n", desc);
}

/* Prints out failure message.
 * @param desc description of test.
 */
void FAIL(char *desc)
{
    printf("FAIL: %s\n\n", desc);
    exit(1);
}

/* Testing helper function.
 * @param result contains the result of the test: 1 is pass, 0 is fail.
 * @param desc of test being ran
 * TODO: Rewrite it to take a function to execute so it can print the
 * TESTING:.. message before the function runs.
 */
void test(int result, char *desc)
{
    printf("TESTING: %s\n", desc);
    result ? PASS(desc) : FAIL(desc);
}

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
 
    printf("Testing printing of list. This is a manual test. There should be"
            " three items printed.");
    print_list(list);

    // Verify item was added by add and then found by search
    test(search("Hello World3", list) == item3,"Testing search and add");

    // Verify searching for a non-existent value returns NULL
    test(search("I DON'T EXIST!", list) == NULL, "Searching for non-existent value");

    // Verify last item can be deleted
    test(delete_item("Hello World3", list) == 1, "Deleting last item");

    // Verify first item can be deleted
    test(delete_item("Hello World", list) == 1, "Deleting first item");

    // Verify only item can be deleted
    test(delete_item("Hello Mars", list) == 1, "Deleting only item");

    printf("Testing printing of empty list. This is a manual test. There should be"
            " no items printed.");
    print_list(list);

    test(((add("A new beginning", list) != NULL)), "Adding item after clearing list");

    add("Hello 101955 Bennu", list);
    add("Hello OSIRIS-REx", list);
    
    // Verify printing the last item
    printf("Testing printing of last item in list. This is a manual test.\n");
    print_last(list);

    
    // Verify destroy
    destroy_list(list);
    list = NULL;

    printf("\nTesting complete!\n\n");

}
