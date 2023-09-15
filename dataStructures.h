#ifndef DATA_STRUCTURES
#define DATA_STRUCTURES 

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Entry{
    char *key;
    char *value;
}Entry;

typedef struct HashTable{
    int size;
    int items;
    Entry *entryTable;
}HashTable;
/*
*/
HashTable *createTable();
/*
*/
void addEntry(char* key, char *value,int index,HashTable *table);
/*
*/
void destroyTable(HashTable *table);

Entry *resize(Entry *table, int size);

#endif