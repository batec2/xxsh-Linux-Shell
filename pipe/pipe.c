#include "pipe.h"
#include <stdio.h>
#include <string.h>

int piping(char **args,char **args2){
    int file_disc[2]; 
    if(pipe(file_disc) == -1){
        return -1;
    }

    int proc = fork();
    if(proc < 0 ){
        return -1;
    }
    
    if(proc == 0){
        dup2(file_disc[1], STDOUT_FILENO);
        close(file_disc[0]);
        close(file_disc[1]);
        printf("I GOT HERE 1\n");
        execv("/usr/bin/ping",args);
    }

    int proc1 = fork();
    if(proc1 < 0 ){
        return -1;
    }

    if(proc1 == 0){
        dup2(file_disc[0],STDIN_FILENO);
        close(file_disc[0]);
        close(file_disc[1]);
        printf("I GOT HERE 2\n");
        execv("/usr/bin/grep",args2);
    }
    close(file_disc[1]);
    waitpid(proc,NULL,0);
    waitpid(proc1,NULL,0);
    return 0;
}

int check_pipe(char **args){
    int i=0;
    while(args[i]!=NULL){
        if(strcmp(args[i],"|")==0){
            printf("%i\n",i);
        }
        i++;
    }
    return 0;
}


int main(void){
    char *args[] = {"ping","-c","5","google.com",NULL};
    char *args2[] = {"grep","rtt",NULL};
    piping(args,args2);
    char *test[]={"stuff","-s","-s","|","stuff","-s","-s""stuff","-s","-s","|",NULL};
    check_pipe(test);
}
