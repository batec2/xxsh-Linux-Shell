#include "dataStructure.h"

#define INITIAL_SIZE 5
#define LOAD_FACTOR 0.70
#define RESIZE_MULT 2
#define MAX_INPUT_SIZE 8

/**
 * Allocates memory for Hashtable and initializes members of HashTable
 * Struct. Allocates memory for array that holds entries of hashtable initial
 * size is 5, all entries member variables are initalized to null
 */
HashTable *createTable()
{
	HashTable *table = malloc(sizeof(HashTable));
	checkNull(table);
	table->size = INITIAL_SIZE;
	table->items = 0;
	table->entryTable = malloc(sizeof(Entry) * INITIAL_SIZE);
	checkNull(table->entryTable);
	setNull(table->entryTable, INITIAL_SIZE);
	return table;
}

/*
 * Initalizes all the member variables of array items to NULL
 */
void setNull(Entry * table, int size)
{
	for (int i = 0; i < size; i++) {
		table[i] = (Entry) {
		.key = NULL,.value = NULL};
	}
}

void addEntry(char *key, char *value, HashTable * table)
{
	table->items++;
	if (((float)table->items / table->size) > LOAD_FACTOR) {
		table->entryTable = resize(table->entryTable, table->size);
		table->size *= RESIZE_MULT;
	}

	int index =
	    nextOpen(table->entryTable, (hash(key) % table->size), table->size);
	table->entryTable[index].key = malloc(strlen(key) + 1);
	checkNull(table->entryTable[index].key);
	strcpy(table->entryTable[index].key, key);

	table->entryTable[index].value = malloc(strlen(value) + 1);
	checkNull(table->entryTable[index].value);
	strcpy(table->entryTable[index].value, value);
}

/**
 * found from here: http://www.cse.yorku.ca/~oz/hash.html
 * implemented from here: 
 * https://www.programmingalgorithms.com/algorithm/sdbm-hash/c/
*/
unsigned int hash(char *str)
{
	unsigned int hash = 0;
	unsigned int i = 0;

	for (i = 0; i < strlen(str); str++, i++) {
		hash = (*str) + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}

/**
 * Creates new array double the size of original and rehashes key,value pairs
 * and inserts into new array
*/
Entry *resize(Entry * table, int size)
{
	int newSize = size * RESIZE_MULT;
	int index = 0;
	Entry *newTable = malloc(newSize * sizeof(Entry));
	checkNull(newTable);
	setNull(newTable, newSize);
	for (int i = 0; i < size; i++) {
		if (table[i].key != NULL) {
			index =
			    nextOpen(newTable, hash(table[i].key) % newSize,
				     newSize);
			newTable[index].key = table[i].key;
			newTable[index].value = table[i].value;
			table[i].key = NULL;
			table[i].value = NULL;
		}
	}
	free(table);
	table = NULL;
	return newTable;
}

/**
 * Looks for the next available spot in array after specified index
 * and returns index number
*/
int nextOpen(Entry * table, int index, int size)
{
	while (table[index].key != NULL) {
		if (index == (size - 1)) {
			index = 0;
		} else {
			index++;
		}
	}
	return index;
}

/**
 * Prints all key/value pairs in hash table, empty spots in table are
 * printed out as NULL
*/
void printEntrys(HashTable * table)
{
	for (int i = 0; i < table->size; i++) {
		if (table->entryTable[i].key != NULL) {
			printf("%i %s , %s\n", i, table->entryTable[i].key,
			       table->entryTable[i].value);
		} else if (table->entryTable[i].key == NULL) {
			printf("%i NULL\n", i);
		}

	}
}

/**
 * Prints the key/value pair of a specified key in array
*/
void printEntry(HashTable * table, char *key)
{
	int index = findEntry(table, key);
	if (index == -1) {
		printf("%s does not exist.", key);
	} else {
		printf("%s, %s", key, table->entryTable[index].value);
	}
}

/**
 * Finds specified key in array and returns it's index if found, -1 is 
 * returned if key does not exist
*/
int findEntry(HashTable * table, char *key)
{
	int index = hash(key) % table->size;
	if ((table->entryTable[index].key != NULL)
	    && (strcmp(table->entryTable[index].key, key) == 0)) {
		return index;
	} else {
		while ((table->entryTable[index].key != NULL)
		       && (strcmp(table->entryTable[index].key, key) != 0)) {
			if (index == (table->size - 1)) {
				index = 0;
			} else {
				index++;
			}
		}
		if ((table->entryTable[index].key == NULL)) {
			return -1;
		} else {
			return index;
		}
	}
}

/**
 * Frees all memory allocated to hash table including all entries and 
 * sets pointers to NULL
*/
void destroyTable(HashTable * table)
{
	for (int i = 0; i < table->size; i++) {
		if (table->entryTable[i].key != NULL) {
			free(table->entryTable[i].key);
			free(table->entryTable[i].value);
			table->entryTable[i].key = NULL;
			table->entryTable[i].value = NULL;
		}
	}
	free(table->entryTable);
	table->entryTable = NULL;
	free(table);
	table = NULL;
}

/**
 * Gets the index of a specific key in the array, returns NULL if key does
 * not exist
*/
char *getEntry(HashTable * table, char *key)
{
	int index = findEntry(table, key);
	if (index == -1) {
		return NULL;
	} else {
		return table->entryTable[index].value;
	}
}

/**
 * Sets the value of specific existing key in array, returns -1 if key is not
 * in the table, otherwise returns the index of key
*/
int setEntry(HashTable * table, char *key, char *value)
{
	int index = findEntry(table, key);
	if (index == -1) {
		return index;
	} else {
		table->entryTable[index].value =
		    realloc(table->entryTable[index].value,
			    (strlen(value) + 1));
		strcpy(table->entryTable[index].value, value);
		return index;
	}
}

/**
 * Remove's key and value in table, frees allocated memory and sets pointers
 * to NULL
*/
int removeEntry(HashTable * table, char *key)
{
	int index = findEntry(table, key);
	if (index == -1) {
		return index;
	} else {
		free(table->entryTable[index].key);
		free(table->entryTable[index].value);
		table->entryTable[index].key = NULL;
		table->entryTable[index].value = NULL;
		return index;
	}
}

/**
 * checks if a pointer is NULL and exits program if true
*/
void checkNull(void *check)
{
	if (check == NULL) {
		printf("Malloc Failed!");
		exit(EXIT_FAILURE);
	}
}
