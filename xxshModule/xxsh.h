#ifndef XXSH
#define XXSH

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../envModule/envVariables.h"
#include "../history/history.h"

/* 
 * @param 
 * @return 
 */
void mainLoop();
/* 
 * @param 
 * @return 
 */
void parse(char *key,char *value);
/* 
 * @param 
 * @return 
 */
void clearBuffer();

#endif