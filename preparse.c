#include <stdlib.h>
#include <stdio.h>
//#include <std
#include "dll.h"

char* preparse(struct doubly_ll* dll){
    struct node* nptr = dll->target;
    while(nptr->prev && nptr->prev->c!=' ') nptr = nptr->prev;
    struct node* store = nptr;
    int i = 0;
    while(nptr->next && nptr->next->c!=' ',i++)
        nptr = nptr->next;
    char* word = malloc(i+1);
    word[i+1] = 0;
    for(;store!=nptr;nptr=nptr->prev,i--)
        word[i] = nptr->c;
    return word;
    //returns the word that the cursor is currently on in the dll
    //o wait maybe it doesn't work properly if it is at the beginning of the string?
}

char* autocomplete(char first_word_flag){//flag for whether it is the first word argument, could be calculated in preparse maybe?
    if(first_word_flag){
        //match with stuff in /bin
    }
    else{
        //match with current directory
    }
}

void insert_into_dll(struct doubly_ll* dll){
    //insert the autocompleted string into the dll, replacing the word with the autocompleted word
}
