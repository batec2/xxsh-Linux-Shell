#include "xxsh.h"

#define MAX_LENGTH 50

int main(void){
    HashTable *table = initEnvVars();
    mainLoop(table);
    return 0;
}

void mainLoop(HashTable *table){
    char buffer[MAX_LENGTH];
    char *token;
    char *token2;
    char *token3;
    while((printf("%s@%s:%s>>",getUser(table),getHost(table),getPath(table))>0)
            &&(fgets(buffer,MAX_LENGTH,stdin)!=NULL)){
        
        /*Clearing strdin*/
        if(buffer[strlen(buffer)-1] != '\n'){
            clearBuffer();
        }

        token = strtok(buffer,"  \n");
        if(token == NULL){
            continue;
        }

        token2 = strtok(NULL,"= \n");
        if(token2 != NULL){
            token3 = strtok(NULL,"\n");
        }
        if(strcmp(token,"export")==0){
            if((token2!=NULL)&&(token2!=NULL)&&(checkVar(table,token2)>=0)){
                
            }
 
        }
        else if(strcmp(token,"env")==0){
            if(token2==NULL){
                printVar(table);
            }
        }
        else if(strcmp(token,"history")==0){
            
        }
        else if(strcmp(token,"quit")==0){
            if(token2==NULL){
                destroyTable(table);
                break;
            }
      
        }
        else if(strcmp(token,"exit")==0){
            if(token2==NULL){
                destroyTable(table);
                break;
            }
        }
        else{
            printf("%s@%s:%s>>Not a valid command",
            getUser(table),
            getHost(table),
            getPath(table));
        }
        
    }
}

char *parse(char *input){
     char *token;
     int value;
     if(input!=NULL){
        token = strtok(input,"=");
        if(token!=NULL){
            printf("%s\n",token);
            value = atoi(strtok(NULL,"\n"));
            if(value!=0){
                printf("%i\n",value);
                return NULL;
            }
            return NULL;
        }
        else{
            return NULL;
        }
     }
     else{
        return NULL;
     }
}

void clearBuffer(){
    char c;
    while((c = getchar()!='\n' && c != EOF)){}
}