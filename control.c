#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "execute.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int parse_args(char* buff);

int control(){
    char strbuff[256];
    char pwdbuff[256];
    while(1){
        getcwd(pwdbuff,255);
        printf(ANSI_COLOR_CYAN"%s"ANSI_COLOR_GREEN" shell$ "ANSI_COLOR_RESET,pwdbuff);
        fflush(stdout);
        fgets(strbuff,256,stdin);
        strbuff[strcspn(strbuff, "\n")] = 0;//remove trailing newline from fgets
        if(parse_args(strbuff))
            return 0;
    }
}


int parse_args(char* buff){
    int spaces = 0;
    for(int i=0;buff[i];i++){
        if(buff[i]==' ') 
            spaces++;
    }
    char** args = malloc((spaces+1)*sizeof(char*));
    int fewerspaces = 0;
    char* ptr = buff;
    args[0]=ptr;
    for(int c = 1; c<=spaces-fewerspaces;c++){
        while(*(ptr++)!=' ') ;
        *(ptr-1)=0;
        args[c]=ptr;
        if(*(ptr)=='"'){
            ptr++;
            char indicator = 1;
            args[c]++;           
            while(*(ptr++)&&indicator){
                 switch(*ptr){
                     case ' ':
                         fewerspaces++;
                         break;
                     case '"':
                         ptr[0]=0;
                         if(c<spaces-fewerspaces)
                             ptr=&ptr[2];
                         indicator = 0;
                         break;
                 }
            }
        }
    }
    char** temp = malloc((spaces+1-fewerspaces)*sizeof(char*));
    for(int i = 0;i<=spaces+fewerspaces;i++)
        temp[i]=args[i];
    free(args);
    args=temp;
    if(execute(spaces+1,args))
        return -1;
    return 0;
}
