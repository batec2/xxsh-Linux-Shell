#ifndef XXSH
#define XXSH

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../envModule/envVariables.h"
#include "../history/history.h"
#define FILE_NAME "env_variables.txt"


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
void parse(char *key, char *value);
/** 
 *Clears StdIn buffer of leftover characters
 */
void clear_buffer();

int arg_cmd(char *token,char *token2,char *token3);
int no_arg_cmd(char *token);

#endif
