#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dll.h"

#define ANSI_BACKGROUND_CYAN     "\x1b[46m"
#define ANSI_COLOR_RESET         "\x1b[0m"

struct doubly_ll* initdll(){
    struct doubly_ll* dll = malloc(sizeof(struct doubly_ll));
    dll->length = 1;
    dll->target = char2node(0);
    dll->flag = 0;
}

void add_next(struct doubly_ll* self, char toinsert){
    struct node* t = self->target;
    struct node* n = self->target->next;

    struct node* i = char2node(toinsert);

    t->next = i;
    i->prev = t;
    i->next = n;
    if(n)
        n->prev = i;
    self->target = i;
    (self->length)++;
}

void remove_prev(struct doubly_ll* self){
    struct node* p = self->target->prev;
    struct node* n = self->target->next;

    p->next = n;
    if(n)
        n->prev = p;
    free(self->target);
    self->target = p;
    (self->length)--;
}


struct node* char2node(char c){
    struct node* n = malloc(sizeof(struct node));
    n->c = c;
    n->next = NULL;
    n->prev = NULL;
}

char* decompose_dll(struct doubly_ll* rotting){
    struct node* nptr = rotting->target;
    while(nptr->prev->c != 0)
        nptr = nptr->prev;
    char* remains = calloc(rotting->length,sizeof(char));
    int i = 0;
    for(;nptr;i++,nptr=nptr->next) 
        remains[i] = nptr->c;
    return remains;
}
