#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "execute.h"

char** parse_args(char* buff);

int control(){
    char strbuff[256];
    while(1){
        printf("shell$ ");
        fflush(stdout);
        fgets(strbuff,256,stdin);
        strbuff[strcspn(strbuff, "\n")] = 0;//remove trailing newline from fgets
        parse_args(strbuff);
    }
}


char** parse_args(char* buff){
    int spaces = 0;
    for(int i=0;buff[i];i++){
        if(buff[i]==' ') 
            spaces++;
    }
    char** args = malloc((spaces+1)*sizeof(char*));
    for(int c = 0; c<=spaces ;c++)
        args[c]=strsep(&buff," ");
    execute(spaces+1,args);
}
