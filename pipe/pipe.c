#include "pipe.h"

/*finds index of pipe operator*/
int check_pipe(char **args){
    int i=0;
    while(args[i]!=NULL){
        if(strcmp(args[i],"|")==0){
            args[i] = NULL;
            return i;
        }
        i++;
    }
    return -1;
}

/*pipes one prog into another*/
int piping(char **args){
    int split_index = 0;
    char *path;
    char *path1;

    if((split_index=check_pipe(args))==-1){
        return -1;
    }

    if((get_program(args[0],&path)==0)||
                        (get_program(args[split_index+1],&path1)==0)){
        return -1;
    }
    
    int file_disc[2]; 
    if(pipe(file_disc) == -1){
        return -1;
    }

    //first process
    int proc = fork();
    if(proc < 0 ){
        return -1;
    }
    
    if(proc == 0){
        dup2(file_disc[1], STDOUT_FILENO);
        close(file_disc[0]);
        close(file_disc[1]);
        execv(path,&args[0]);
    }
    
    //second process
    int proc1 = fork();
    if(proc1 < 0 ){
        return -1;
    }

    if(proc1 == 0){
        dup2(file_disc[0],STDIN_FILENO);
        close(file_disc[0]);
        close(file_disc[1]);
        execv(path1,&args[split_index+1]);
    }
    close(file_disc[1]);
    waitpid(proc,NULL,0);
    waitpid(proc1,NULL,0);
    return 0;
}



