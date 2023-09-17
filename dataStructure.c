#include "dataStructure.h"

#define INITIAL_SIZE 5
#define LOAD_FACTOR 0.70
#define RESIZE_MULT 2
int main(int argc, char *argv[]){
    HashTable *table = createTable();
    addEntry("Crush","Bate",table);
    printEntrys(table);
    printf("%i\n",findEntry(table,"Crush"));
    addEntry("Crush1","Bate1",table);
    addEntry("Crush2","Bate2",table);
    addEntry("Crush3","Bate3",table);
    addEntry("Crush4","Bate4",table);
    printEntrys(table);
    printf("%i\n",findEntry(table,"Crush"));
    return 0;
}

/*create,destroy,get,set,remove,search,print,printspecific*/

/*creates hashTable*/
HashTable *createTable(){
    HashTable *table = malloc(sizeof(HashTable));
    table->size = INITIAL_SIZE;
    table->entryTable = malloc(sizeof(Entry)*INITIAL_SIZE);
    setNull(table->entryTable,INITIAL_SIZE);
    return table;
}

void setNull(Entry *table,int size){
    for(int i =0; i<size;i++){
        table[i] = (Entry){.key = NULL,.value = NULL};
    }
}

void addEntry(char* key, char *value,HashTable *table){
    table->items++;
    if((table->items/table->size)>LOAD_FACTOR){
        table->entryTable = resize(table->entryTable,table->size);
        table->size *= RESIZE_MULT;
        printf("%i resized\n",table->size);
    }
    int index = nextOpen(table->entryTable,(hash(key)%table->size),table->size);
    table->entryTable[index].key = malloc(strlen(key)+1);
    strcpy( table->entryTable[index].key,key);
    table->entryTable[index].value = malloc(strlen(value)+1);
    strcpy( table->entryTable[index].value,value);
}

Entry *resize(Entry *table, int size){
    int newSize = size*RESIZE_MULT;
    int index = 0;
    Entry *newTable = malloc(newSize*sizeof(Entry));
    setNull(newTable,newSize);
    for(int i = 0; i<size;i++){
        if(table[i].key != NULL){
            index = nextOpen(newTable,hash(table[i].key)%newSize,newSize);
            newTable[index].key = table[i].key;
            newTable[index].value = table[i].value;
            table[i].key = NULL;
            table[i].value = NULL;
        }
    }
    return newTable;
}

int nextOpen(Entry *table,int index,int size){
    while(table[index].key!=NULL){
        if(index == (size-1)){
            index = 0;
        }
        else{
            index++;
        }
    }
    return index;
}
/**
 * found from here: http://www.cse.yorku.ca/~oz/hash.html
 * implemented from here: https://www.programmingalgorithms.com/algorithm/sdbm-hash/c/
*/
unsigned int hash(char* str) {
	unsigned int hash = 0;
	unsigned int i = 0;

	for (i = 0; i < strlen(str); str++, i++)
	{
		hash = (*str) + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}

void checkLoad(){

}

void destroyTable(HashTable *table){
}

void printEntrys(HashTable *table){
    for(int i = 0;i<table->size;i++){
        if(table->entryTable[i].key != NULL){
            printf("%i %s , %s\n",i,table->entryTable[i].key,table->entryTable[i].value);

        }
        else{
            printf("%i NULL\n",i);
        }

    }
}

int findEntry(HashTable *table,char *key){
    int index = hash(key)%table->size;
    if((table->entryTable[index].key!=NULL)&&(strcmp(table->entryTable[index].key,key)==0)){
        return index;
    }
    else{
        while((table->entryTable[index].key!=NULL)&&(strcmp(table->entryTable[index].key,key)!=0)){
            if(index == (table->size-1)){
                index = 0;
            }
            else{
                index++;
            }
        }
        if((table->entryTable[index].key==NULL)){
            return -1;
        }
        else{
            return index;
        }
    }
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