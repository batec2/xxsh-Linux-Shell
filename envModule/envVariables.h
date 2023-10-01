#ifndef ENV_VARIABLES
#define ENV_VARIABLES

#include "../hashTable/dataStructure.h"

#define PRIVATE static
/**
 * Initializes the environment table and all the default environment variables
 */
void initEnvVars();

/** 
 * Prints all the environment variables
 */
void printVar();
/** 
 * Gets the current value of the USER environment variable
 * @return the string value of USER
 */
char *getUser();
/** 
 * Gets the current value of the HOST environment variable
 * @return the string value of HOST
 */
char *getHost();
/** 
 * Gets the current value of the PATH environment variable
 * @return the string value of PATH
 */
char *getPath();

/** 
 * Gets the what the environment variable is currently set to
 * @param String name of environment variable
 * @return Returns NULL if environment variable doesnt exists, else returns
 * the string value
 */
char *getEnv(char *key);

/** 
 * @param String name of environment variable
 * @param String value of environment variable
 * @return 
 */
void setVar(char *key, char *value);
/** 
 * Checks if Environment variable already exists in table
 * @param String name of environment variable
 * @return returns the index of the variable, -1 if variable does not exist
 */
int checkVar(char *key);
/** 
 * Frees all mememory allocated to environment variable hashtable
 */
void destroyEnv();
#endif				/*ENV_VARIABLES */
