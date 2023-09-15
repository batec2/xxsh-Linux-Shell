#ifndef DATA_STRUCTURES
#define DATA_STRUCTURES 

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct entry{
    char *key;
    char *value;
}entry;

typedef struct HashTable{
    int size;
    entry *entryTable;
}HashTable;

HashTable *createTable();

void addEntry(char* key, char *value,int index,HashTable *table);

#endif