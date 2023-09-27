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
void mainLoop(HashTable *table);
/* 
 * @param 
 * @return 
 */
void parse(HashTable *table,char *key,char *value);
/* 
 * @param 
 * @return 
 */
void clearBuffer();

#endif