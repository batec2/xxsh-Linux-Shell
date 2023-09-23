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
    char *token;
    while((printf("$xxsh>>")>0)&&(fgets(buffer,MAX_LENGTH,stdin)!=NULL)){
        printf("$xxsh>>");
        token = strtok(buffer," \n");
        if(token == NULL){
            return;
        }
        if(strcmp(token,"export")==0){
            printf("%s\n",strtok(NULL," \n"));
        }
        else if(strcmp(token,"env")==0){
            printf("%s\n",strtok(NULL," \n"));
        }
        else if(strcmp(token,"history")==0){
            printf("%s\n",strtok(NULL," \n"));
        }
        else if(strcmp(token,"quit")==0){
            printf("%s\n",strtok(NULL," \n"));
        }
        else if(strcmp(token,"exit")==0){
            printf("%s\n",strtok(NULL," \n"));
            return;
        }
        else{
            printf("Not a valid command\n");
        }
    }
}

char *parse(char *input){
    return input;    
}