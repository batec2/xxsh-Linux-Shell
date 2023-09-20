#ifndef DATA_STRUCTURES
#define DATA_STRUCTURES 

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*Entries of HashTable*/
typedef struct Entry{
    char *key;
    char *value;
}Entry;
/*HashTable struct holds, array and information on table*/
typedef struct HashTable{
    int size;
    int items;
    Entry *entryTable;
}HashTable;

/**
 * Arguments: 
 * Returns: Pointer to HashTable of size INITIAL_SIZE(5)
*/
HashTable *createTable();

/**
 * Arguments: Entry,int
 * Returns: 
*/
void setNull(Entry *table,int size);

/**
 * Arguments: char*,char*,HashTable
 * Returns:
*/
void addEntry(char* key, char *value,HashTable *table);

/**
 * Arguments: char*
 * Returns: unsigned int
*/
unsigned int hash(char* str);
/**
 * Arguments: Entry*,int
 * Returns: Pointer to Entry array
*/
Entry *resize(Entry *table, int size);

/**
 * Arguments: Entry *,int,int
 * Returns: index of next NULL after specific index
*/
int nextOpen(Entry *table,int index,int size);

/**
 * Arguments: HashTable*
 * Returns:
*/
void printEntrys(HashTable *table);

/**
 * Arguments: HashTable*,char *
 * Returns:
*/
void printEntry(HashTable *table, char *key);

/**
 * Arguments: HasthTable*,char*
 * Returns: Returns index of key in table
*/
int findEntry(HashTable *table,char *key);

/**
 * Arguments: HashTable*
 * Returns:
*/
void destroyTable(HashTable *table);

/**
 * Arguments: HashTable*,char*
 * Returns: returns string value of key in table
*/
char *getEntry(HashTable *table,char *key);

/**
 * Arguments: HashTable*,char*,char*
 * Returns: 
*/
int setEntry(HashTable *table,char *key, char *value);

/**
 * Arguments: HashTable*,char*
 * Returns: -1 if key exists, index  of key otherwise
*/
int removeEntry(HashTable *table,char *key);

/**
 * Arguments: void*
 * Returns: 
*/
void checkNull(void *check);

#endif