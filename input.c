#include <stdio.h>
#include <stdlib.h>
#include "chario.h"
#include "dll.h"
void seeklines(int direct,FILE* f){
    if(direct)
        while(getc(f)!='\n') fseek(f,-2,SEEK_CUR);
    else
        while(getc(f)!='\n') ;
}
void vertical(int direct, struct doubly_ll* dll){
    if(direct){
        
    }
}

void horizontal(int direct,struct doubly_ll* dll){
    if(direct && dll->target->next){
        dll->target = dll->target->next;
        printf("\033[1C");
        fflush(stdout);
    }
    else if(dll->target->prev){
        dll->target = dll->target->prev;
        printf("\033[1D");
        fflush(stdout);
    }
}

char* input(){
    struct doubly_ll* dll = initdll();
    while(1){
        char c = getch();
        switch(c){
            case 27:
                if(getch()=='['){
                    switch(getch()){
                        case 'A':
                            vertical(1,dll);
                            break;
                        case 'B':
                            vertical(0,dll);
                            break;
                        case 'C':
                            horizontal(1,dll);
                            break;
                        case 'D':
                            horizontal(0,dll);
                            break;
                    }
                }
                break;
            case '\n':
                putch('\r');
                putch('\n');
                return decompose_dll(dll);
            case 127:
                if(dll->length==1) continue;
                remove_prev(dll);
                struct doubly_ll* q = forward_str(dll);
                printf("\033[0J\b \b");
                fflush(stdout);
                putstr(decompose_dll(q));
                printf("\033[%dD",q->length-1);
                if(!q->target->next) printf("\033[1C");
                fflush(stdout);
                freeall(q);
                break;
            default:
                putch(c);
                for(int i = 0;i<dll->length;i++)
                   putstr("\b \b");
                add_next(dll,c);
                putstr(decompose_dll(dll));
                break;
        }
    }
}

