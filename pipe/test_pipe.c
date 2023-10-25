#include "pipe.h"

int main(void){
    init_env_vars();
    set_var("PATH", "/usr/bin"); 
    //char *args[] = {"ps","-e","|","grep","-i","bash",NULL};
    char **args = malloc(sizeof(char *)*7);
    args[0] = malloc(sizeof("ls")+1);
    strcpy(args[0],"ls");
    args[1] = malloc(sizeof("-l")+1);
    strcpy(args[1],"-l");
    args[2] = malloc(sizeof("|")+1);
    strcpy(args[2],"|");
    args[3] = malloc(sizeof("grep")+1);
    strcpy(args[3],"grep");
    args[4] = malloc(sizeof("-i")+1);
    strcpy(args[4],"-i");
    args[5] = malloc(sizeof("p")+1);
    strcpy(args[5],"p");
    args[6] = NULL;
    piping(args);
    free(args[0]);
    free(args[1]);
    free(args[2]);
    free(args[3]);
    free(args[4]);
    free(args[5]);
    free(args);
    destroy_env();
}