#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "xxsh.h"

#define MAX_LENGTH 15

int main(void){
    mainLoop();
    return 0;
}

void mainLoop(){
    char buffer[MAX_LENGTH];
    char *token;
    while((printf("$xxsh>>")>0)&&(fgets(buffer,MAX_LENGTH,stdin)!=NULL)){
        /*Clearing strdin*/
        if(buffer[strlen(buffer)-1] != '\n'){
            clearBuffer();
            //printf("True\n");
        }
        token = strtok(buffer,"  \n");
        if(token == NULL){
            continue;
        }
        if(strcmp(token,"export")==0){
            strtok(NULL," \n");
            printf("$xxsh>>Export\n");
        }
        else if(strcmp(token,"env")==0){
            strtok(NULL," \n");
            printf("$xxsh>>env\n");
        }
        else if(strcmp(token,"history")==0){
            strtok(NULL," \n");
            printf("$xxsh>>history\n");
        }
        else if(strcmp(token,"quit")==0){
            strtok(NULL," \n");
            printf("$xxsh>>quit\n");
        }
        else if(strcmp(token,"exit")==0){
            strtok(NULL," \n");
            printf("$xxsh>>exit\n");
            return;
        }
        else{
            printf("$xxsh>>Not a valid command\n");
        }
        
    }
}

char *parse(char *input){
    return input;    
}

void clearBuffer(){
    char c;
    while((c = getchar()!='\n' && c != EOF)){}
}