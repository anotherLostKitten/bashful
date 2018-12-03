#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "parse_args.h"
#include "input.h"

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


int control(){
    char pathToShellHistory[1024];
    sprintf(pathToShellHistory,"/home/%s/.shellhistory",getenv("USER"));
    int fd = open(pathToShellHistory,O_WRONLY|O_CREAT|O_APPEND,00600);
    char* strbuff;
    while(1){
        char pwdbuff[1024];
        getcwd(pwdbuff,1024);
        printf("\033[s"ANSI_COLOR_CYAN"%s"ANSI_COLOR_GREEN" shell$ "ANSI_COLOR_RESET,pwdbuff);
        fflush(stdout);
        strbuff = input();
        if(strlen(strbuff)){
            write(fd,strbuff,strlen(strbuff));
            write(fd,"\n",1);
            if(parse_args(strbuff)){
                return 0;
            }
        }
        free(strbuff);
    }
}

