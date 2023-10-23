#include "pipe.h"

int check_pipe(char **args){
    int i=0;
    while(args[i]!=NULL){
        if(strcmp(args[i],"|")==0){
            args[i] = NULL;
            printf("THIS: %i\n",i);
            return i;
        }
        i++;
    }
    return -1;
}

int piping(char **args){
    int split_index = 0;
    if((split_index=check_pipe(args))==-1){
        return -1;
    }
    
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
        execv("/usr/bin/ping",&args[0]);
    }

    int proc1 = fork();
    if(proc1 < 0 ){
        return -1;
    }

    if(proc1 == 0){
        dup2(file_disc[0],STDIN_FILENO);
        close(file_disc[0]);
        close(file_disc[1]);
        execv("/usr/bin/grep",&args[split_index+1]);
    }
    close(file_disc[1]);
    waitpid(proc,NULL,0);
    waitpid(proc1,NULL,0);
    return 0;
}



int main(void){
    char *args[] = {"ping","-c","5","google.com","|","grep","rtt",NULL};
    piping(args);
    char *test[]={"stuff","-s","-s","|","stuff","-s","-s""stuff","-s","-s","|",NULL};
    check_pipe(test);
}
