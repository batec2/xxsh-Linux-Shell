#include "pipe.h"

int main(void){
    init_env_vars();
    set_var("PATH", "/usr/bin");
    char *args[] = {"ps","-e","|","grep","-i","bash",NULL};
    piping(args);
    char *test[]={"stuff","-s","-s","|","stuff","-s","-s""stuff","-s","-s","|",NULL};
    check_pipe(test);
}