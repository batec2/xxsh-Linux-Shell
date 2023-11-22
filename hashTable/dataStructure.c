/**
 * QUESTION 3:
 * Hashtables time complexity:
 * 	Look-up: 
 * 		Average: O(1) - the hash should directly point to index of key
 * 		Bestcase: O(1) 
 * 		Worstcase: O(n) - A low efficency hash could cause high collision rates
 * 						meaning resorting to linear search which is O(n)
 * 	Insert:
 * 		Average: O(1) - low collision hash would have unique indexs for keys
 * 		Bestcase: O(1) 
 * 		Worstcase: O(n) - high collision rates will make use of linear probing
 * 						which is O(n). Aswell resizing of table will cause
 * 						an increase in insert times, as the table needs
 * 						to be remade and all entries rehashed and reinserted.
 * 	Delete:
 * 		Average: O(1)
 * 		Bestcase: O(1)
 * 		Worstcase: O(n)
*/
#include "dataStructure.h"

/**
 * Allocates memory for Hashtable and initializes members of HashTable
 * Struct. Allocates memory for array that holds entries of hashtable initial
 * size is 5, all entries member variables are initalized to null
 */
HashTable *create_table()
{
	HashTable *table = malloc(sizeof(HashTable));
	check_null(table);
	table->size = INITIAL_SIZE;
	table->items = 0;
	table->tombstones = 0;
	table->entryTable = malloc(sizeof(Entry) * INITIAL_SIZE);
	check_null(table->entryTable);
	set_null(table->entryTable, INITIAL_SIZE);
	return table;
}

/*
 * Initalizes all the member variables of array items to NULL
 */
void set_null(Entry *table, int size)
{
	for (int i = 0; i < size; i++) {
		table[i] = (Entry) {
		.key = NULL,.value = NULL};
	}
}

/**
 * Finds index for key and allocates memory for key, the key is then
 * inserted in the table.
*/
int add_entry(HashTable *table, char *key, char *value)
{
	//does nothing if key is already inside the table
	if (find_entry(table, key) != -1) {
		return -1;
	}

	table->items++;
	//Resizes table if tombstones and items become too much
	if (((float)(table->items + table->tombstones) / table->size) >
	    LOAD_FACTOR) {
		table->entryTable = resize(table->entryTable, table->size);
		table->size *= RESIZE_MULT;
		table->tombstones = 0;
	}
	//Key and value are malloced for and entered
	int index = next_open(table->entryTable, (hash(key) % table->size),
			      table->size);
	table->entryTable[index].key = malloc(strlen(key) + 1);
	check_null(table->entryTable[index].key);
	strcpy(table->entryTable[index].key, key);

	table->entryTable[index].value = malloc(strlen(value) + 1);
	check_null(table->entryTable[index].value);
	strcpy(table->entryTable[index].value, value);
	return index;
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
	unsigned int length = strlen(str);
	for (i = 0; i < length; str++, i++) {
		hash = (*str) + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}

/**
 * Creates new array double the size of original and rehashes key,value pairs
 * and inserts into new array
*/
Entry *resize(Entry *table, int size)
{
	int new_size = size * RESIZE_MULT;
	int index = 0;
	//Creates new table and initalizes all entries to NULL
	Entry *new_table = malloc(new_size * sizeof(Entry));
	check_null(new_table);
	set_null(new_table, new_size);
	//Keys are rehashed and key/value pair pointers are passed to new table
	for (int i = 0; i < size; i++) {
		if (table[i].key != NULL) {
			//Tombstones freed seperatly to avoid call free on null value
			if ((strcmp(table[i].key, "TOMBSTONE") == 0)
			    && (table[i].value == NULL)) {
				free(table[i].key);
				table[i].key = NULL;
			} else {	//key values are hashed and passed to new table
				index =
				    next_open(new_table,
					      hash(table[i].key) % new_size,
					      new_size);
				new_table[index].key = table[i].key;
				new_table[index].value = table[i].value;
				table[i].key = NULL;
				table[i].value = NULL;
			}
		}
	}
	free(table);
	table = NULL;
	return new_table;
}

/**
 * Looks for the next available spot in array after specified index
 * and returns index number
*/
int next_open(Entry *table, int index, int size)
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
void print_entrys(HashTable *table, FILE *file)
{
	for (int i = 0; i < table->size; i++) {
		if (table->entryTable[i].key != NULL) {
			if(strcmp(table->entryTable[i].key,"PWD")==0||
								strcmp(table->entryTable[i].key,"OLDPWD")==0){
				continue;
			}
			if (file != NULL) {
				fprintf(file, "%s,%s\n",
					table->entryTable[i].key,
					table->entryTable[i].value);
			} else {
				printf("%s,%s\n", table->entryTable[i].key,
				       table->entryTable[i].value);
			}
		}
	}
}

/**
 * Prints the key/value pair of a specified key in array
*/
void print_entry(HashTable *table, char *key)
{
	int index = find_entry(table, key);
	if (index == -1) {
		printf("%s does not exist.\n", key);
	} else {
		printf("%s,%s\n", key, table->entryTable[index].value);
	}
}

/**
 * Finds specified key in array and returns it's index if found, -1 is 
 * returned if key does not exist
*/
int find_entry(HashTable *table, char *key)
{
	int index = hash(key) % table->size;
	if ((table->entryTable[index].key != NULL)
	    && (strcmp(table->entryTable[index].key, key) == 0)) {
		return index;
	} else {
		//Linear probing to find the next NULL
		while ((table->entryTable[index].key != NULL)
		       && (strcmp(table->entryTable[index].key, key) != 0)) {
			//if probing hits the end of the table goes back to start
			if (index == (table->size - 1)) {
				index = 0;
			} else {
				index++;
			}
		}
		//if loops finishes key must either have been found or not
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
void destroy_table(HashTable *table)
{
	for (int i = 0; i < table->size; i++) {
		if (table->entryTable[i].key != NULL) {
			if ((strcmp(table->entryTable[i].key, "TOMBSTONE") == 0)
			    && (table->entryTable[i].value == NULL)) {
				free(table->entryTable[i].key);
				table->entryTable[i].key = NULL;
			} else {
				free(table->entryTable[i].key);
				free(table->entryTable[i].value);
				table->entryTable[i].key = NULL;
				table->entryTable[i].value = NULL;
			}
		}
	}
	free(table->entryTable);
	table->entryTable = NULL;
	free(table);
	table = NULL;
}

/**
 * Gets the value of a specific key in the array, returns NULL if key does
 * not exist
*/
char *get_entry(HashTable *table, char *key)
{
	int index = find_entry(table, key);
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
int set_entry(HashTable *table, char *key, char *value)
{
	int index = find_entry(table, key);
	if (index == -1)
		return add_entry(table, key, value);

	table->entryTable[index].value =
	    (char *)realloc(table->entryTable[index].value,
			    (strlen(value) + 1));
	strcpy(table->entryTable[index].value, value);
	return index;
}

/**
 * Remove's key and value in table, frees allocated memory and sets pointers
 * to NULL
*/
int remove_entry(HashTable *table, char *key)
{
	int index = find_entry(table, key);
	if (index == -1) {
		return index;
	} else {
		free(table->entryTable[index].key);
		free(table->entryTable[index].value);
		table->entryTable[index].value = NULL;
		table->entryTable[index].key = malloc(10);
		strcpy(table->entryTable[index].key, "TOMBSTONE");
		table->items--;
		table->tombstones++;
		return index;
	}
}

/**
 * checks if a pointer is NULL and exits program if true
*/
void check_null(void *check)
{
	if (check == NULL) {
		printf("Malloc Failed!");
		exit(EXIT_FAILURE);
	}
}
