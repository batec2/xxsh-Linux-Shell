#ifndef XXSH
#define XXSH

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "../envModule/envVariables.h"
#include "../history/history.h"
#include "../binary/binary.h"
#include "../pipe/pipe.h"

#define FILE_NAME "config.txt"

/* Struct for list items */
typedef struct command {
	int size;
	char **args_list;	//command and arguments
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
 * Takes command and runs commands with arguments
 * @param command struct with list of arguments
*/
int arg_cmd(command * cmd);

/**
 * parses input and puts arguments into a list
 * @param command struct with list of arguments
*/
void read_flags(char *input, command * cmd);

/**
 * @param command struct with list of arguments
*/
void free_command(command * cmd);

/**
 * checks if there is a pipe operator in the input
 * @param args List of strings
 * @return returns index of pipe, -1 if no pipe
*/
int is_pipe(char **args);

#endif /*XXSH*/
