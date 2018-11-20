#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h> 
void sighandler(int signo);

int execute(int argc,char** argv){
    if(!strcmp(argv[0],"exit")){
        return -1;
    }
    else if(!strcmp(argv[0],"cd")){
        int i = chdir(argv[1]);
    }
    else{
        int inf = 0;
        int pid;
        if(!(pid = fork())){
            int retval = execvp(argv[0],argv);
            if(retval) 
                printf("%s\n",strerror(errno));
            return retval;
        }
        else{
            signal(SIGINT,sighandler);
        }
        wait(&inf);
    }
    return 0;
}

void sighandler(int signo){
}
