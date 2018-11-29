#include <stdio.h>
#include <stdlib.h>
#include "chario.h"
#include "dll.h"

struct doubly_ll* vertical(int direct, struct doubly_ll* dll){
    FILE* f = fopen(".shellhistory","r");
    rewind(f);
    char c;
    if(direct)
        while(ftell(f)!=0 && (c=getc(f))!='\n') fseek(f,-2,SEEK_CUR);
    else
        while((c=getc(f))!='\n') 
            if(c!=EOF) return NULL;
    char command[1024];
    fgets(command,1024,f);
    fclose(f);
    struct doubly_ll* new = compose_dll(command);
    while(dll->target->prev){
        dll->target = dll->target->prev;
        printf("\033[D");
    }
    freeall(dll);
    printf("\033[J");
    printf("%s",decompose_dll(new));
    fflush(stdout);
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
    fflush(stdout);
}

char* input(){
    struct doubly_ll* dll = initdll();
    struct doubly_ll* q;
    while(1){
        q = NULL;
        char c = getch();
        switch(c){
            case '\033':
                if(getch()=='['){
                    switch(getch()){
                        case 'A'://up arrow
                            q = vertical(1,dll);
                            break;
                        case 'D'://left arrow
                            horizontal(0,dll);
                            break;
                        case 'C'://right arrow
                            horizontal(1,dll);
                            break;
                        case 'B'://down arrow
                            q = vertical(0,dll);
                            break;
                    }
                    if(q) dll = q;
                }
                break;
            case '\n':
                printf("\r\n");
                return decompose_dll(dll);
            case 127:
                if(dll->length==1 || !(dll->target->prev)) continue;
                remove_prev(dll);
                q = forward_str(dll);
                printf("\033[D\033[J");
                printf("%s",decompose_dll(q));
                printf("\033[%dD",q->length); 
                printf("\033[1C");
                fflush(stdout);
                freeall(q);
                break;
            default:
                add_next(dll,c);
                q = forward_str(dll);
                putchar(c);
                printf("\033[J");
                printf("%s",decompose_dll(q));
                if(q->target->next)
                    printf("\033[%dD",q->length);
                fflush(stdout);
                freeall(q);
                break;
        }
    }
    FILE* f = fopen(".shellhistory","r");
    fseek(f,0,SEEK_END);
    fclose(f);
}
