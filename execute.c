#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
int execute(int argc,char** argv){
    if(!strcmp(argv[0],"exit")){
        kill(getpid(),15);
    }
    else if(!strcmp(argv[0],"cd")){
        int i = chdir(argv[1]);
    }
    else{
        int inf = 0;
        if(!fork()){
            int retval = execvp(argv[0],argv);
            if(retval) 
                printf("%s\n",strerror(errno));
            return retval;
        }
        wait(&inf);
    }
}
