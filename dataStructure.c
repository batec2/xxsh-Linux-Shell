#include "dataStructure.h"

#define INITIAL_SIZE 10
#define LOAD_FACTOR 0.75

int main(int argc, char *argv[]){
    unsigned int index;
    HashTable *table = createTable();
    printEntrys(table);
    index = hash("Crush")%table->size;
    addEntry("Crush","Bate",index,table);
    printEntrys(table);
    printf("%hu\n",findEntry(table,"Crush"));
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
    Entry *newTable = malloc((size*1.5)*sizeof(Entry));
    for(int i = 0; i<size;i++){
        
    }
    return newTable;
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