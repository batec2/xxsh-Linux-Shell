#ifndef DATA_STRUCTURES
#define DATA_STRUCTURES 

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 5
#define LOAD_FACTOR 0.70
#define RESIZE_MULT 2

/*Entries of HashTable*/
typedef struct Entry{
    char *key;
    char *value;
}Entry;
/*HashTable struct holds, array and information on table*/
typedef struct HashTable{
    int size;//Total size of table
    int items;//amount of current items in table
    int tombstones;//placeholder for deleted items
    Entry *entryTable;//Array that holds all entries
}HashTable;

/**
 * Initilizes the hashtable with an initial size of INITIAL_SIZE
 * @return returns pointer to empty hashtable
*/
HashTable *createTable();

/**
 * Instantiates all values of table to null
 * @param Pointer to hash table
 * @param int size of hashtable
*/
void setNull(Entry *table,int size);

/**
 * Inserts an entry into the table, does not insert or update if key is
 * already inside table
 * @param Pointer to hashtable
 * @param String of key to be inserted
 * @param String of value of key
 * @return Returns -1 if key is already in table, otherwise returns index
*/
int addEntry(HashTable *table,char *key, char *value);

/**
 * Uses a hash found online and hashes the input string into a an unsigned int
 * @param String of input to be hashed
 * @return Returns hash of inputed string as unsigned int
*/
unsigned int hash(char* str);
/**
 * Resizes existing table by a defined factor and reinserts all entries
 * @param Pointer to hashtable
 * @param Int current size of table
 * @return Returns pointer to new larger table
*/
Entry *resize(Entry *table, int size);

/**
 * Finds the next open slot in the table after a certain index
 * @param Pointer to hashtable 
 * @param int index to start searching from
 * @param int size of the table 
 * @return Returns the next index after the entered index that is NULL
*/
int nextOpen(Entry *table,int index,int size);

/**
 * Prints all entries that are not NULL in the table
 * @param Pointer to hashtable
*/
void printEntrys(HashTable *table);

/**
 * Prints a the value of corresponding key from the table
 * @param Pointer to table
 * @param String of key to be found
*/
void printEntry(HashTable *table, char *key);

/**
 * Finds the index of a key within the table
 * @param Pointer to hash table
 * @param String of key to be found
 * @return returns -1 if key is not found, otherwise the index of the key in
 * the table
*/
int findEntry(HashTable *table,char *key);

/**
 * Free's all memory allocated to key/values and entries within the table
 * @param Pointer to hashtable
*/
void destroyTable(HashTable *table);

/**
 * Gets the value of a key from the table
 * @param Pointer to hash table
 * @param String representing key
 * @return Returns the string value of the key in the table,
 *  if the key is not in the table NULL is returned
*/
char *getEntry(HashTable *table,char *key);

/**
 * Sets the value of the matching key in the hashtable
 * @param Pointer to hash table
 * @param String representing key
 * @param String representing the value being set
 * @return Returns -1 if the key is not in the table, the index of key
 * otherwise. Nothing is done if key is not in table
*/
int setEntry(HashTable *table,char *key, char *value);

/**
 * Removes matching key from hashtable
 * @param Pointer to hash table
 * @param String representing key
 * @return Returns -1 if the key is not in the table, the index of key
 * otherwise.
*/
int removeEntry(HashTable *table,char *key);

/**
 * Pass in pointer and checks if it is a null pointer, exits with EXIT_FAILURE
 * if pointer is null
 * @param Pointer void pointer
*/
void checkNull(void *check);

#endif /*DATA_STRUCTURE*/
