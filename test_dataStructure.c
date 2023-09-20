#include "dataStructure.h"

void unitTest();

int main(){
    unitTest();
    return 0;
}

void unitTest(){
    /*Table creation/Adding entry/printing entries/Finding entries*/
    HashTable *table = createTable();
    addEntry(table,"Crush","Bate");
    printEntrys(table);
    printf("---Current Load:%.2f---%i\n",((float)table->items/table->size),(table->items/table->size));
    printf("Find Crush: %i\n",findEntry(table,"Crush"));
    printf("\n");

    /*Resizing/Adding more entries*/
    addEntry(table,"Crush1","Bate1");
    addEntry(table,"Crush2","Bate2");
    printEntrys(table);
    printf("---Current Load:%.2f---%i\n",((float)table->items/table->size),(table->items/table->size));
    addEntry(table,"Crush3","Bate3");
    addEntry(table,"Crush4","Bate4");
    printEntrys(table);
    printf("---Current Load:%.2f---%i\n",((float)table->items/table->size),(table->items/table->size));
    printf("\n");
    
    /*Get/Set/Remove*/
    printf("get: %s\n",getEntry(table,"Crush"));
    setEntry(table,"Crush","CHANGED");
    printf("get: %s\n",getEntry(table,"Crush"));
    addEntry(table,"Crush11","Bate11");
    addEntry(table,"Crush21","Bate21");
    addEntry(table,"Crush31","Bate31");
    addEntry(table,"Crush41","Bate41");
    removeEntry(table,"Crush");
    printf("REMOVE Crush\n");
    printf("Find Crush:%i\n",findEntry(table,"Crush"));
    printEntrys(table);
    printf("---Current Load:%.2f---%i\n",((float)table->items/table->size),(table->items/table->size));
    /*Destroy: Confirmed through valgrind*/
    destroyTable(table);
}

