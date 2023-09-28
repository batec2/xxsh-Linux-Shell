#include "xxsh.h"

#define MAX_LENGTH 50

int main(void){
    initEnvVars();
    mainLoop();
    return 0;
}
/*Main user input loop*/
void mainLoop(){
    char buffer[MAX_LENGTH];
    char buffer2[MAX_LENGTH];
    char *token;
    char *token2;
    char *token3;
    while((printf("%s@%s:%s>> ",getUser(),getHost(),getPath())>0)
            &&(fgets(buffer,MAX_LENGTH,stdin)!=NULL)){
        /*Clearing stdin*/
        if(buffer[strlen(buffer)-1] != '\n'){
            clearBuffer();
        }
        strcpy(buffer2,buffer);//creates copy of command for insert into history
        token = strtok(buffer,"  \n");
        if(token == NULL){
            continue;
        }
        /*export needs valid key/value*/
        if(strcmp(token,"export")==0){
            token2 = strtok(NULL,"=");
            //Input needs in form of ENVAR=VALUE
            if(token2 != NULL){
                token3 = strtok(NULL,"\n");
            }
            if((token2!=NULL)&&(token3!=NULL)){
                parse(token2,token3);
            }
        }
        /*env needs only env as input*/
        else if(strcmp(token,"env")==0){
            token2 = strtok(NULL,"\n");
            if(token2==NULL){
                printVar();
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
                destroyEnv();
                destroy_history();
                break;
            }
      
        }
        /*exit need exit as input*/
        else if(strcmp(token,"exit")==0){
            token2 = strtok(NULL,"\n");
            if(token2==NULL){
                destroyEnv();
                destroy_history();
                break;
            }
        }
        else{
            printf("%s@%s:%s>> Not a valid command\n",
            getUser(),
            getHost(),
            getPath());
        }
        add_history(buffer2);
    }
}

void parse(char *key,char *value){
    if(checkVar(key)<0){
        return;
    }
    if(strcmp(key,"HISTSIZE")==0){
        if(atoi(value)<=0){
            return;
        }
        setVar(key,value);
    }
    /*any env other than history*/
    else{
        setVar(key,value);
    }
}

void clearBuffer(){
    char c;
    while((c = getchar()!='\n' && c != EOF)){}
}