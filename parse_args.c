#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "execute.h"

int parse_args(char* buff){
  for(char*i;i=strsep(&buff,";");){
    int spaces = 0;
    for(int j=0;i[j];j++)
      if(i[j]==' '||i[j]==';'){
	spaces++;
	for(;i[j]==' '&&i[j+1];j++);
      }
    char**args = malloc((spaces+1)*sizeof(char*)),**curarg = args;
    for(char*j=i;j;){
      for(;*j==' ';j++);
      if(!*j)
	break;
      if(*j=='"'){
	j++;
	*curarg++=strsep(&j,"\"");
      }else
	*curarg++=strsep(&j," ");
      //printf("[%s]\n",*(curarg-1));
    }
    if(execute(args)==-1)
      return -1;
  }
  return 0;
}
