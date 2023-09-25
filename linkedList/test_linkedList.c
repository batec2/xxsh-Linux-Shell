#include <stdio.h>

#include "linkedList.h"


int main()
{
    printf("Testing the LinkedList class...\n");

    LinkedList *list = NULL;
    list = initialize();

    add("Hello World", list);
    add("Hello World1", list);
    add("Hello World2", list);
    add("Hello World3", list);
    add("Hello World4", list);
 
    print_list(list);

}
