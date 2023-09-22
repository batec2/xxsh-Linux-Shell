#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "xxsh.h"

#define MAX_LENGTH 256

int main(void){
    mainLoop();
    return 0;
}

void mainLoop(){
    char buffer[MAX_LENGTH];
    if(fgets(buffer,MAX_LENGTH,stdin)!=NULL){
        puts(buffer);
    }
}

char *parse(char *input){
    return input;    
}