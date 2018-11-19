#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char** split_args(char* buff){
    int spaces = 0;
    for(int i=0;buff[i];i++){
        if(buff[i]==' ') 
            spaces++;
    }
    char** args = malloc((spaces+1)*sizeof(char*));
    args[0]=buff;
    for(int c = 1; c<=spaces ;c++)
        args[c]=strsep(&buff," ");
    return args;
}

int control(){
    char strbuff[256];
    while(1){
        printf("shell$ ");
        fflush(stdout);
        fgets(strbuff,256,stdin);
        strbuff[strcspn(strbuff, "\n")] = 0;//remove trailing newline from fgets
        
        char** argv = split_args(strbuff);
        int argc = sizeof(argv)/sizeof(argv[0]);
        if(!strcmp(argv[0],"exit")){
            return 0;
        }
    }
}

int main(){
    control();
    return 0;
}
