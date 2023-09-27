#ifndef ENV_VARIABLES
#define ENV_VARIABLES

#include "../hashTable/dataStructure.h"
/* 
 * @param 
 * @return HashTable pointer with  
 */
HashTable *initEnvVars();

/* 
 * @param 
 */
void setVar(HashTable *table, char *key, char *value);
/* 
 * @param 
 * @return 
 */
void printVar(HashTable *table);
/* 
 * @param 
 * @return 
 */
char *getUser(HashTable *table);
/* 
 * @param 
 * @return 
 */
char *getHost(HashTable *table);
/* 
 * @param 
 * @return 
 */
char *getPath(HashTable *table);
/* 
 * @param 
 * @return 
 */
void setVar(HashTable *table,char *key, char *value);
/* 
 * @param 
 * @return 
 */
int checkVar(HashTable *table,char *key);
#endif ENV_VARIABLES