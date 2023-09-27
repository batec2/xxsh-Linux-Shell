#include "xxsh.h"

#define MAX_LENGTH 50

int main(void){
    HashTable *table = initEnvVars();
    initialize_history(table);
    mainLoop(table);
    return 0;
}

void mainLoop(HashTable *table){
    char buffer[MAX_LENGTH];
    char buffer2[MAX_LENGTH];
    char *token;
    char *token2;
    char *token3;
    while((printf("%s@%s:%s>>",getUser(table),getHost(table),getPath(table))>0)
            &&(fgets(buffer,MAX_LENGTH,stdin)!=NULL)){
        /*Clearing strdin*/
        if(buffer[strlen(buffer)-1] != '\n'){
            clearBuffer();
        }
        strcpy(buffer2,buffer);
        token = strtok(buffer,"  \n");
        if(token == NULL){
            continue;
        }
        /*export needs valid key/value*/
        if(strcmp(token,"export")==0){
            token2 = strtok(NULL,"=");
            if(token2 != NULL){
                printf("FOUND TOKEN2\n");
                token3 = strtok(NULL,"\n");
            }
            if((token2!=NULL)&&(token3!=NULL)){
                printf("WORKING!\n");
                parse(table,token2,token3);
            }
        }
        /*env needs only env as input*/
        else if(strcmp(token,"env")==0){
            token2 = strtok(NULL,"\n");
            if(token2==NULL){
                printVar(table);
            }
        }
        /*history needs only history as input*/
        else if(strcmp(token,"history")==0){
            token2 = strtok(NULL,"\n");
            if(token2==NULL){
                history();
            }
        }
        /*quit needs only quit as input*/
        else if(strcmp(token,"quit")==0){
            token2 = strtok(NULL,"\n");
            if(token2==NULL){
                destroyTable(table);
                break;
            }
      
        }
        /*exit need exit as input*/
        else if(strcmp(token,"exit")==0){
            token2 = strtok(NULL,"\n");
            if(token2==NULL){
                destroyTable(table);
                break;
            }
        }
        else{
            printf("%s@%s:%s>>Not a valid command\n",
            getUser(table),
            getHost(table),
            getPath(table));
        }
        add_history(buffer2);
    }
}

void parse(HashTable *table,char *key,char *value){
    if(findEntry(table,key)<0){
        printf("%s %s<-COULDNT FIND IT\n",key,value);
        return;
    }
    if(strcmp(key,"HISTSIZE")==0){
        if(atoi(value)<=0){
            printf("%s %s<-WRONG\n",key,value);
            return;
        }
        setEntry(table,key,value);
        printf("%s %s<-history\n",key,value);
    }
    else{
        setEntry(table,key,value);
        printf("%s %s<-other\n",key,value);
    }
}

void clearBuffer(){
    char c;
    while((c = getchar()!='\n' && c != EOF)){}
}