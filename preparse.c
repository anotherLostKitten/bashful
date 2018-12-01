#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include "dll.h"

int autocomplete(struct doubly_ll* dll,char first_word_flag,char* word);

int preparse(struct doubly_ll* dll){
    struct node* nptr = dll->target;
    struct node* store = nptr;
    int i = 0;
    char first_word_flag;
    for(nptr = nptr->prev;;nptr = nptr->prev,i++){
        if(nptr->c==' '){
            first_word_flag = 0;
            break;
        }
        else if(!nptr->prev){
            first_word_flag = 1;
            break;
        }
    }
    nptr = nptr->next;
    char* word = malloc(i+1);
    word[i+1] = 0;
    for(i=0;nptr!=store;nptr=nptr->next,i++)
        word[i] = nptr->c;
    word[i] = store->c;
    autocomplete(dll,first_word_flag,word);
    return 0;
}

int autocomplete(struct doubly_ll* dll,char first_word_flag,char* word){//flag for whether it is the first word argument, could be calculated in preparse maybe?
    DIR* dir;
    struct dirent* dirdata;
    struct stat statdata;
    if(first_word_flag){
        dir = opendir("/bin");
    }
    else{
        char* i;
        if(i = strrchr(word,'/')){
            int lom = (int) (i-word);
            char dir2[lom+3];
            memcpy(dir2+2,word,lom);
            dir2[0] = '.',dir2[1] = '/',dir2[lom+2] = 0;
            if(stat(dir2,&statdata)<0)
                return 0;
            dir = opendir(dir2);
            word = i + 1;
        }
        else
            dir = opendir(".");
    }
    int len = strlen(word);
    while(dirdata = readdir(dir)){
        if(!strncmp(dirdata->d_name,word,len)){
            char* strtoins = dirdata->d_name+len;
            for(int i = 0;strtoins[i];i++){
                add_next(dll,strtoins[i]);
            }
            break;
        }
    }
    return 0;
}
