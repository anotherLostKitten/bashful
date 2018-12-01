#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include "chario.h"
#include "dll.h"
#include "preparse.h"

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
char pwdbuff[1024];
char* command;

void chline(FILE* f,char direct,char fback){
    char c;
    if(fback && ftell(f)>1) fseek(f,-2,SEEK_CUR);
    if(direct){
        while(ftell(f) && getc(f)!='\n') fseek(f,-2,SEEK_CUR);
        if(fback && ftell(f)>1) fseek(f,-2,SEEK_CUR);
    }
    else{
        if(!fback)
            while((c=getc(f))!='\n')
                if(c==EOF)
                    break;
    }
}

struct doubly_ll* vertical(char direct, struct doubly_ll* dll,FILE* f){
    chline(f,direct,0);
    char cmd[1024];
    fgets(cmd,1024,f);
    fflush(stdout);
    chline(f,direct,1);
    struct doubly_ll* new = compose_dll(command);
    freeall(dll);
    command = decompose_dll(new);
    printf("\r"ANSI_COLOR_CYAN"%s"ANSI_COLOR_GREEN" shell$ "ANSI_COLOR_RESET"%s\033[J",pwdbuff,command);
    free(command);
    return new;
}

void horizontal(int direct,struct doubly_ll* dll){
    if(direct && dll->target->next){
        dll->target = dll->target->next;
        printf("\033[C");
    }
    else if(dll->target->prev){
        dll->target = dll->target->prev;
        printf("\033[D");
    }
}

char* input(){
    getcwd(pwdbuff,1024);
    struct doubly_ll* dll = initdll(),* q;
    char pathToShellHistory[1024];
    sprintf(pathToShellHistory,"/home/%s/.shellhistory",getenv("USER"));
    FILE* fs = fopen(pathToShellHistory,"r");
    struct stat st;
    stat(pathToShellHistory, &st);
    fseek(fs,-2,SEEK_END);
    char gone_back_flag = 0;
    while(1){
        char c = getch();
        switch(c){
            case '\033':
                if(getch()=='['){
                    switch(getch()){
                        case 'A'://up arrow
                            if(st.st_size) dll = vertical(1,dll,fs);
                            gone_back_flag = 1;
                            break;
                        case 'D'://left arrow
                            horizontal(0,dll);
                            break;
                        case 'C'://right arrow
                            horizontal(1,dll);
                            break;
                        case 'B'://down arrow
                            if(gone_back_flag)
                                dll = vertical(0,dll,fs);
                            break;
                    }
                }
                break;
            case '\n':
                putchar('\n');
                fseek(fs,0,SEEK_END);
                fclose(fs);
                command = decompose_dll(dll);
                freeall(dll);
                return command;
            case 127:
                if(dll->length==1 || !(dll->target->prev)) continue;
                remove_prev(dll);
                command = decompose_dll(dll);
                printf("\r"ANSI_COLOR_CYAN"%s"ANSI_COLOR_GREEN" shell$ "ANSI_COLOR_RESET"%s\033[J\033[%dD",pwdbuff,command,forward(dll));
                free(command);
                break;
            case '\t':
                preparse(dll);
                command = decompose_dll(dll);
                printf("\r"ANSI_COLOR_CYAN"%s"ANSI_COLOR_GREEN" shell$ "ANSI_COLOR_RESET"%s\033[%dD",pwdbuff,command,forward(dll));
                free(command);
                break;
            default:
                add_next(dll,c);
                command = decompose_dll(dll);
                printf("\r"ANSI_COLOR_CYAN"%s"ANSI_COLOR_GREEN" shell$ "ANSI_COLOR_RESET"%s\033[%dD",pwdbuff,command,forward(dll));
                free(command);                
                break;
        }
        fflush(stdout);
    }
}
