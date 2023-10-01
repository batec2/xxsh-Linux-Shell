#ifndef XXSH
#define XXSH

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../envModule/envVariables.h"
#include "../history/history.h"

/**
 * Main program loop that takes in user input and calls corresponding 
 * functions
 */
void mainLoop();
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
void clearBuffer();

#endif
