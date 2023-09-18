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
unsigned int hash(char* str);

Entry *resize(Entry *table, int size);

int nextOpen(Entry *table,int index,int size);

void printEntrys(HashTable *table);

void printEntry(HashTable *table, char *key);

int findEntry(HashTable *table,char *key);

void destroyTable(HashTable *table);

char *getEntry(HashTable *table,char *key);

int setEntry(HashTable *table,char *key, char *value);

int removeEntry(HashTable *table,char *key);

void checkNull(void *check);

#endif