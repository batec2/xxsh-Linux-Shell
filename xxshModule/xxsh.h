#ifndef XXSH
#define XXSH

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../envModule/envVariables.h"
#include "../history/history.h"
#include "../binary/binary.h"
#define FILE_NAME "env_variables.txt"
/* Struct for list items */
typedef struct command {
    int size;
	char **args_list;
} command;

/**
 * Main program loop that takes in user input and calls corresponding 
 * functions
 */
void main_loop();
/**
 * Checks if input strings are valid, and changes corresponding value
 * if key is valid.
 * @param String representing Env variable
 * @param String representing users input
 */
void parse(char *args);
/** 
 *Clears StdIn buffer of leftover characters
 */
void clear_buffer();

/**
 * 
*/
int mult_arg_cmd(command *cmd);

/**
 * 
*/
int no_arg_cmd(command *cmd);
/**
 * 
*/
void read_flags(char *input,command *cmd);

/**
 * 
*/
void free_command(command *cmd);

#endif
