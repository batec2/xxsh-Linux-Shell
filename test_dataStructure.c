#include "dataStructure.h"

int main(){
    HashTable *table = createTable();
    printf("---%f---%i\n",((float)table->items/table->size),(table->items/table->size));
    addEntry("Crush","Bate",table);
    printEntrys(table);
    printf("%i\n",findEntry(table,"Crush"));
    addEntry("Crush1","Bate1",table);
    addEntry("Crush2","Bate2",table);
    addEntry("Crush3","Bate3",table);
    addEntry("Crush4","Bate4",table);
    printf("---%f---%i\n",((float)table->items/table->size),(table->items/table->size));
    printEntrys(table);
    printf("%i\n",findEntry(table,"Crush"));
    printf("get: %s\n",getEntry(table,"Crush"));
    setEntry(table,"Crush","CHANGED");
    printf("get: %s\n",getEntry(table,"Crush"));
    addEntry("Crush11","Bate11",table);
    addEntry("Crush21","Bate21",table);
    addEntry("Crush31","Bate31",table);
    addEntry("Crush41","Bate41",table);
    removeEntry(table,"Crush");
    printf("---%f---%i\n",((float)table->items/table->size),(table->items/table->size));
    printEntrys(table);
    printf("%i\n",findEntry(table,"Crush"));


    destroyTable(table);
    return 0;
}