#include "pipe.h"

/*finds index of pipe operator*/
int check_pipe(char **args){
    int i=0;
    while(args[i]!=NULL){
        if(strcmp(args[i],"|")==0){
            free(args[i]);
            args[i] = NULL;//uses NULL to split the two args
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
    //file_disc[0] data read from
    //file_disc[1] data written to
    int file_disc[2]; 

    if((split_index=check_pipe(args))==-1){
        return 0;
    }

    if((get_program(args[0],&path)==0)||
                        (get_program(args[split_index+1],&path1)==0)){
        return 0;
    }
    
    if(pipe(file_disc) == -1){
        return 0;
    }

    //first process
    int proc = fork();
    if(proc < 0 ){
        return 0;
    }
    
    if(proc == 0){
        dup2(file_disc[1], STDOUT_FILENO);//sets stdout to pipes write end
        close(file_disc[0]);//closes unused
        close(file_disc[1]);//closes unused
        execv(path,&args[0]);
    }

    //second process
    int proc1 = fork();
    if(proc1 < 0 ){
        return 0;
    }

    if(proc1 == 0){
        dup2(file_disc[0],STDIN_FILENO);//sets stdin to the pipes read end
        //need to close unused file discriptors so call program does not stay
        //active
        close(file_disc[0]);//closes unused
        close(file_disc[1]);//closes unused 
        execv(path1,&args[split_index+1]);
    }
    close(file_disc[1]);//to close second process
    waitpid(proc,NULL,0);
    waitpid(proc1,NULL,0);
    free(path);
    free(path1);
    return 1;
}



