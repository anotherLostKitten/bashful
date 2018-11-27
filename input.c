#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <ctype.h>
#include <string.h>
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
    }
    else if(dll->target->prev->c != 0){
        dll->target = dll->target->prev;
    }
}

int getch()
{
   struct termios old, new;
   char ch;
   tcgetattr(0, &old);
   new=old;
   new.c_lflag &= ~( ICANON | ECHO );
   tcsetattr(0, TCSANOW, &new);
   ch=getchar();
   tcsetattr(0, TCSANOW, &old);
   return ch;
}

void putch(char c)
{
   struct termios old, new;
   tcgetattr(0, &old);
   new=old;
   new.c_lflag &= ~( ICANON | ECHO );
   tcsetattr(0, TCSANOW, &new);
   putchar(c);
   tcsetattr(0, TCSANOW, &old);
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
                putch('\n');
                return decompose_dll(dll);
            case 127:
                if(dll->length!=1) break;
                putch(127);
                remove_prev(dll);
                break;
            default:
                putch(c);
                add_next(dll,c);
                break;
        }
    }
}

