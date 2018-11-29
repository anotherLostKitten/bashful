#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST
struct node{
    char c;
    struct node* next;
    struct node* prev;
};

struct doubly_ll{
    int length;
    struct node* target;
};
struct node* char2node(char c);
void add_next(struct doubly_ll* self, char toinsert);
void remove_prev(struct doubly_ll* self);
struct doubly_ll* initdll();
char* decompose_dll(struct doubly_ll* rotting);
struct doubly_ll* compose_dll(char* source);
struct doubly_ll* forward_str(struct doubly_ll* self);
void freeall(struct doubly_ll* self);
#endif
