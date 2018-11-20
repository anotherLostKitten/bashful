#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "execute.h"

int parse_args(char* buff){
  int spaces = 0;
  for(int i=0;buff[i];i++){
    if(buff[i]==' ')
      spaces++;
  }
  char** args = malloc((spaces+1)*sizeof(char*));
  int fewerspaces = 0;
  char* ptr = buff;
  args[0]=ptr;
  for(int c = 1; c<=spaces-fewerspaces;c++){
    while(*(ptr++)!=' ') ;
    *(ptr-1)=0;
    args[c]=ptr;
    if(*(ptr)=='"'){
      ptr++;
      char indicator = 1;
      args[c]++;
      while(*(ptr++)&&indicator){
	switch(*ptr){
	case ' ':
	  fewerspaces++;
	  break;
	case '"':
	  ptr[0]=0;
	  if(c<spaces-fewerspaces)
	    ptr=&ptr[2];
	  indicator = 0;
	  break;
	}
      }
    }
  }
  char** temp = malloc((spaces+1-fewerspaces)*sizeof(char*));
  for(int i = 0;i<=spaces+fewerspaces;i++)
    temp[i]=args[i];
  free(args);
  args=temp;
  if(execute(spaces+1,args))
    return -1;
  return 0;
}
