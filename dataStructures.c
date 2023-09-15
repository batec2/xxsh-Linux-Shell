#include "dataStructures.h"

#define INITIAL_SIZE 10
#define LOAD_FACTOR 0.75

int main(int argc, char *argv[]){
    HashTable *table = createTable();
    printf("%lu\n", (sizeof((table->entryTable))/sizeof(Entry)));
    addEntry("Crush","Bate",0,table);
    addEntry("Crush1","Bate",1,table);
    printf("%s %s\n",table->entryTable[1].key,table->entryTable[1].value);
    int size = 10;
    int items = 8;

    //printf("%i",((items/size)>LOAD_FACTOR));
    

    return 0;
}

/*create,destroy,get,set,remove,search,print,printspecific*/

/*creates hashTable*/
HashTable *createTable(){
    HashTable *table = malloc(sizeof(HashTable));
    table->size = INITIAL_SIZE;
    table->entryTable = malloc(sizeof(Entry)*INITIAL_SIZE);
    return table;
}

void addEntry(char* key, char *value,int index,HashTable *table){
    if((table->items/table->size)>LOAD_FACTOR){
        table->entryTable = resize(table->entryTable,table->size);
    }
    table->entryTable[index].key = malloc(strlen(key)+1);
    strcpy( table->entryTable[index].key,key);
    table->entryTable[index].value = malloc(strlen(value)+1);
    strcpy( table->entryTable[index].value,value);
}

Entry *resize(Entry *table, int size){
    return realloc(table,(size*1.5)*sizeof(Entry));
}

void checkLoad(){

}

void destroyTable(HashTable *table){
}


/*
void checkNull(HashTable *check){
    if(check == NULL){
        printf("Malloc Failed!");
    }
}

void getEntry(){

}

void setEntry(){

}

void removeEntry(){

}
*/