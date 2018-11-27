#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "execute.h"

int parse_args(char*buff){
	char**carg=malloc(256),**argv=carg,*cur=buff;
	while(*buff){
		if(!*cur){
			if(*buff)
				*carg++=buff;
			*carg=0;
			break;
		}else if(*cur=='"'){
			char*qt=cur+1;
			strcpy(cur,strsep(&qt,"\""));
			*carg++=buff;
			cur=buff=qt;
		}else if(*cur==';'){
			*cur=0;
			if(*buff)
				*carg++=buff;
			*carg=0;
			if(execute(argv)==-1)
				return -1;
			else
				return parse_args(cur+1);
		}else if(*cur==' '){
			for(;*cur==' ';*cur++=0);
			if(*buff)
				*carg++=buff;
			buff=cur;
		}else if(*cur=='|'||*cur=='<'){
			char t=*cur;
			*cur=0;
			if(*buff)
				*carg++=buff;
			*carg++=t=='|'?"|":"<";
			buff=cur+1;
		}else
			cur++;
	}
	return execute(argv);
}
