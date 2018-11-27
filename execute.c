#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h> 
void sighandler(int signo);

int execute(char** argv){
    if(!argv[0])
        return 0;
    int argc = sizeof(argv)/sizeof(argv[0]);

	//for(char**b=argv;*b;b++)printf("[%s]\n",*b);
	
    if(!strcmp(argv[0],"exit")){
        return -1;
    }
    else if(!strcmp(argv[0],"cd")){
        int i = chdir(argv[1]);
    }
    else{
        int inf = 0;
        int pid;
        char newargv = 0;
        if(!strcmp(argv[argc-1],"&")){
            argv[--argc] = NULL;
            newargv = 1;
        }
        
        if(!(pid = fork())){
            int retval = execvp(argv[0],argv);
            if(retval) 
                printf("%s\n",strerror(errno));
            return retval;
        }
        else{
            signal(SIGINT,sighandler);
        }
        if(!newargv)
            waitpid(-1,&inf,0);
        else
            waitpid(-1,&inf,WNOHANG);
    }
    return 0;
}

void sighandler(int signo){
}
