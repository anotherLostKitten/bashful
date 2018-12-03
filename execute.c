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
    int argc=sizeof(argv)/sizeof(argv[0]),tmpo=dup(STDOUT_FILENO),tmpi=dup(STDIN_FILENO),tmpe=dup(STDERR_FILENO),fin=0,fout=0;
    

    //for(char**b=argv;*b;b++) printf("[%s]\n",*b);	
    if(!strcmp(argv[0],"exit"))
        return -1;
    else if(!strcmp(argv[0],"cd"))
        chdir(argv[1]);
    else{
        int inf = 0;
        int pid;
        char newargv = 0;
    for(char**b=argv;*b;b++) //printf("[%s]\n",*b);
        if(!strcmp(argv[argc-1],"&")){
            argv[--argc] = NULL;
            newargv = 1;
        }
        for(int i=0;argv[i];){
            int doubt = STDOUT_FILENO;
			if(!strcmp(argv[i],">")){
                if(i-1>=0 && !strcmp(argv[i-1],"2")){
                    doubt = STDERR_FILENO;
                    argv[i-1] = NULL;
                }
                fout = open(argv[1+i], O_WRONLY | O_CREAT | O_TRUNC);
				dup2(fout,doubt);
				for(int j=i;argv[j]=argv[j+2];j++);	
			}else if(!strcmp(argv[i],">>")){
                if(i-1>=0 && !strcmp(argv[i-1],"2")){
                    doubt = STDERR_FILENO;
                    argv[i-1] = NULL;
                }
                fout = open(argv[1+i], O_WRONLY | O_CREAT | O_APPEND);
				dup2(fout,doubt);
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
	dup2(tmpe,STDERR_FILENO);
    return 0;
}

void sighandler(int signo){
}
