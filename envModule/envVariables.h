#ifndef ENV_VARIABLES
#define ENV_VARIABLES

#include "../hashTable/dataStructure.h"

HashTable *initEnvVars();
void setVar(HashTable *table, char *key, char *value);
void printVar(HashTable *table);
char *getUser(HashTable *table);
char *getHost(HashTable *table);
char *getPath(HashTable *table);
void setVar(HashTable *table,char *key, char *value);
int checkVar(HashTable *table,char *key);
#endif