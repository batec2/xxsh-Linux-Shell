#ifndef XXSH
#define XXSH

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../envModule/envVariables.h"
#include "../history/history.h"

void mainLoop(HashTable *table);
void parse(HashTable *table,char *key,char *value);
void clearBuffer();

#endif