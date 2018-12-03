#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h> 
#include <fcntl.h>

void sighandler(int signo);

int execute(char** argv){
    if(!argv[0])
        return 0;
    int argc=0,tmpo=dup(STDOUT_FILENO),tmpi=dup(STDIN_FILENO),fin=0,fout=0;
	for(;argv[argc];argc++);
    
	
    if(!strcmp(argv[0],"exit"))
        return -1;
    else if(!strcmp(argv[0],"cd"))
        chdir(argv[1]);
    else{
        int inf = 0;
        int pid;
        char newargv = 0;
        if(!strcmp(argv[argc-1],"&")){
            argv[--argc] = NULL;
            newargv = 1;
        }
        for(int i=0;argv[i];){
			if(!strcmp(argv[i],">")){
				fout = open(argv[i+1], O_WRONLY | O_CREAT);
				dup2(fout,STDOUT_FILENO);
				for(int j=i;argv[j]=argv[j+2];j++);	
			}else if(!strcmp(argv[i],"<")){
				fin = open(argv[i+1], O_RDONLY | O_CREAT, 0644);
				if(fin==-1){
					printf("%s\n",strerror(errno));
					return 0;
				}
				dup2(fin,STDIN_FILENO);
				for(int j=i;argv[j]=argv[j+2];j++);
			}else i++;		
		}

		//for(char**b=argv;*b;b++)printf("[%s]\n",*b);
		
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
	dup2(tmpi,STDIN_FILENO);
	dup2(tmpo,STDOUT_FILENO);
    return 0;
}

void sighandler(int signo){
}
