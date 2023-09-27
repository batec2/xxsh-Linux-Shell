#ifndef ENV_VARIABLES
#define ENV_VARIABLES

#include "../hashTable/dataStructure.h"

#define PRIVATE static
/* 
 * @param 
 * @return HashTable pointer with  
 */
void initEnvVars();

/* 
 * @param 
 */
void setVar( char *key, char *value);
/* 
 * @param 
 * @return 
 */
void printVar();
/* 
 * @param 
 * @return 
 */
char *getUser();
/* 
 * @param 
 * @return 
 */
char *getHost();
/* 
 * @param 
 * @return 
 */
char *getPath();

/* 
 * @param 
 * @return 
 */
char *getEnv(char *key);

/* 
 * @param 
 * @return 
 */
void setVar(char *key, char *value);
/* 
 * @param 
 * @return 
 */
int checkVar(char *key);
/* 
 * @param 
 * @return 
 */
void destroyEnv();
#endif /*ENV_VARIABLES*/