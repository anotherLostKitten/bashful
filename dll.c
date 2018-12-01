#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dll.h"

struct doubly_ll* initdll(){
    struct doubly_ll* dll = malloc(sizeof(struct doubly_ll));
    dll->length = 1;
    dll->target = char2node(0);
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
    while(nptr->prev)
        nptr = nptr->prev;
    nptr = nptr->next;
    char* remains = calloc(rotting->length,sizeof(char));
    if(!nptr) return remains;
    for(int i = 0;nptr;i++,nptr=nptr->next) 
        remains[i] = nptr->c;
    return remains;
}

struct doubly_ll* compose_dll(char* source){
    struct doubly_ll* dll = initdll();
    for(int i = 0;source[i+1];i++)
        add_next(dll,source[i]);
    return dll;
}

int forward(struct doubly_ll* self){
    struct node* targ = self->target;
    int i = 0;
    for(;targ->next;targ = targ->next) i++;
    return i-1;
}

void freeall(struct doubly_ll* self){
    while(self->target->next) self->target = self->target->next;
    while(self->target->prev){
        struct node* slef = self->target;
        self->target = self->target->prev;
        free(slef);
    }
    free(self->target);
    free(self);
}
