#include <stdio.h>
#include <stdlib.h>
#include "dll.h"

int backset = 0;

void vertical(int direct){
    if(direct){
    
    }
}

void horizontal(int direct,struct doubly_ll* dll){
//    if(direct && dll->target->next){
//        dll->target = dll->target->next;
//        backset--;
//    }
//    else if(dll->target->prev->c != 0){
//        dll->target = dll->target->prev;
//        
//        backset++;
//    }
}


char* input(){
    struct doubly_ll* dll = initdll();
    setvbuf(stdin, NULL, _IONBF, 0);
    while(1){
        char c = getchar();
        switch(c){
            case 27:
                if(getchar()=='['){
                    switch(getchar()){
                        case 'A':
                            vertical(1);
                            break;
                        case 'B':
                            vertical(0);
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
                return decompose_dll(dll);
            case '\b':
                remove_prev(dll);
                break;
            default:
                add_next(dll,c);
                break;
        }
    }
    setvbuf(stdin, NULL, _IOLBF, 0);
}

