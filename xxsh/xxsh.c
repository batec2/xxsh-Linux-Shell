#include <stdio.h>
#include <String.h>
#include <stdlib.h>
#include "xxsh.h"

#define MAX_LENGTH 256

int main(void){
    return 0;
}

void mainLoop(){
    char buffer[MAX_LENGTH];
    if(fgets(buffer,MAX_LENGTH,stdin)!=NULL){
        printf(buffer);
    }
}

char *parse(char *input){
    
}