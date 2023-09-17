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

/**
 * 
*/
HashTable *createTable();

/**
 * 
*/
void setNull(Entry *table,int size);

/**
 * 
*/
void addEntry(char* key, char *value,HashTable *table);

/**
 * 
*/
void destroyTable(HashTable *table);
/**
 * 
*/
unsigned int hash(char* str);

Entry *resize(Entry *table, int size);

int nextOpen(Entry *table,int index,int size);

void printEntrys(HashTable *table);

int findEntry(HashTable *table,char *key);

#endif