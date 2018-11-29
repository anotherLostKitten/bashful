#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
int getch()
{
   struct termios old, new;
   char ch;
   tcgetattr(STDIN_FILENO, &old);
   new=old;
   new.c_lflag &= ~( ICANON | ECHO );
   new.c_oflag &= ~(OPOST);
   tcsetattr(STDIN_FILENO, TCSANOW, &new);
   ch=getchar();
   tcsetattr(STDIN_FILENO, TCSANOW, &old);
   return ch;
}

void putstr(char* c)
{
   struct termios old, new;
   tcgetattr(0, &old);
   new=old;
   new.c_lflag &= ~( ICANON | ECHO );
   new.c_oflag &= ~(OPOST);
   tcsetattr(0, TCSANOW, &new);
   printf("%s",c);
   tcsetattr(0, TCSANOW, &old);
}
