#include "dataStructures.h"

#define INITIAL_SIZE 10

int main(int argc, char *argv[]){
    HashTable *table = createTable();
    addEntry("Crush","Bate",0,table);
    printf("%s %s\n",table->entryTable[0].key,table->entryTable[0].value);
    return 0;
}

/*create,destroy,get,set,remove,search,print,printspecific*/

/*creates hashTable*/
HashTable *createTable(){
    HashTable *table = malloc(sizeof(HashTable));
    table->size = INITIAL_SIZE;
    table->entryTable = malloc(sizeof(entry)*INITIAL_SIZE);
    return table;
}

void addEntry(char* key, char *value,int index,HashTable *table){
    table->entryTable[index].key = malloc(strlen(key)+1);
    strcpy( table->entryTable[index].key,key);
    table->entryTable[index].value = malloc(strlen(value)+1);
    strcpy( table->entryTable[index].value,value);
}

void destroyTable(HashTable *table){
    for()
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