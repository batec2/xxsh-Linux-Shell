#ifndef XXSH
#define XXSH

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../envModule/envVariables.h"
#include "../history/history.h"

void mainLoop(HashTable *table);
char *parse(char *input);
void clearBuffer();

#endif