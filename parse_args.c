#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
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
		}else if(*cur=='<'){
			*cur=0;
			if(*buff)
				*carg++=buff;
			*carg=0;
			int f = open(*(carg-1),O_CREAT|O_WRONLY|O_APPEND);
			int tmp = dup(STDOUT_FILENO);
			dup2(f,STDOUT_FILENO);
			parse_args(cur+1);
			close(f);
			dup2(tmp,STDOUT_FILENO);
			return 0;
		}else if(*cur=='|'){
			*cur=0;
			if(*buff)
				*carg++=buff;
			*carg=0;
			int p[2];
			pipe(p);
			if(fork()){
				close(p[1]);
				int tmp = dup(STDIN_FILENO);
				dup2(p[0],STDIN_FILENO);
				wait(0);
				parse_args(cur+1);
				dup2(tmp,STDIN_FILENO);
				close(p[0]);
			}else{
				close(p[0]);
				int tmp = dup(STDOUT_FILENO);
				dup2(p[1],STDOUT_FILENO);
			    execute(argv);
				dup2(tmp,STDOUT_FILENO);
				close(p[1]);
				exit(0);
			}
			return 0;
		}else
			cur++;
	}
	return execute(argv);
}
