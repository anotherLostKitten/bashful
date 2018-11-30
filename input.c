#include <stdio.h>
#include <stdlib.h>
#include "chario.h"
#include "dll.h"

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
    char command[1024];
    fgets(command,1024,f);
    fflush(stdout);
    chline(f,direct,1);
    struct doubly_ll* new = compose_dll(command);
    while(dll->target->prev && (dll->target = dll->target->prev))
        printf("\033[D");
    freeall(dll);
    printf("\033[J%s",decompose_dll(new));
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
    struct doubly_ll* dll = initdll();
    struct doubly_ll* q;
    FILE* fs = fopen(".shellhistory","r");
    fseek(fs,-2,SEEK_END);
    char gone_back_flag = 0;
    while(1){
        char c = getch();
        switch(c){
            case '\033':
                if(getch()=='['){
                    switch(getch()){
                        case 'A'://up arrow
                            dll = vertical(1,dll,fs);
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
                return decompose_dll(dll);
            case 127:
                if(dll->length==1 || !(dll->target->prev)) continue;
                remove_prev(dll);
                q = forward_str(dll);
                printf("\033[D\033[J%s\033[%dD\033[1C",decompose_dll(q),q->length);
                freeall(q);
                break;
            default:
                add_next(dll,c);
                q = forward_str(dll);
                putchar(c);
                printf("\033[J%s",decompose_dll(q));
                if(q->target->next)
                    printf("\033[%dD",q->length);
                freeall(q);
                break;
        }
        fflush(stdout);
    }
}
