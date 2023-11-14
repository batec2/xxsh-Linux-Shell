#ifndef ENV_VARIABLES
#define ENV_VARIABLES
#define FILE_N "config.txt"
#include "../hashTable/dataStructure.h"
#include "../fileIO/fileIO.h"
#define MAX_COUNT 256
#define PRIVATE static

/**
 * Initializes the environment table and all the default environment variables
 */
void init_env_vars();

/** 
 * Prints all the environment variables
 */
void print_var();
/** 
 * Gets the current value of the USER environment variable
 * @return the string value of USER
 */
char *get_user();
/** 
 * Gets the current value of the HOST environment variable
 * @return the string value of HOST
 */
char *get_host();
/** 
 * Gets the current value of the PATH environment variable
 * @return the string value of PATH
 */
char *get_path();

/** 
 * Gets the what the environment variable is currently set to
 * @param String name of environment variable
 * @return Returns NULL if environment variable doesnt exists, else returns
 * the string value
 */
char *get_env(char *key);

/** 
 * @param String name of environment variable
 * @param String value of environment variable
 */
void set_var(char *key, char *value);

/** 
 * Only sets the environment variable if it isn't already set.
 * @param String name of environment variable
 * @param String value of environment variable
 */
void check_set_var(char *key, char *value);

/** 
 * Checks if Environment variable already exists in table
 * @param String name of environment variable
 * @return returns the index of the variable, -1 if variable does not exist
 */
int check_var(char *key);
/** 
 * Frees all mememory allocated to environment variable hashtable
 */
void destroy_env();
/**
 * env vars are written to file
 * @param file file for env vars to be written to
*/
void write_env(char *file_name);
/**
 * Checks if file exists, if not a new file is made and env are written to it
 * @param file file to be checked and or written to
*/
void check_env(char *file_name);

/**
 * Takes env  variables from list and sets into hashmap
 * @param file_name
*/
void read_env(char *file_name);

/**
 * Finds a user entry in etc/passwd
 * @param: id the user ID
 * @param: environment variable hash table
 * @returns: 1 on success, 0 on failure
 */
int get_user_info(int uid, HashTable *table);

#endif				/*ENV_VARIABLES */
