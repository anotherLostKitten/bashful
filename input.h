#ifndef INPUT
#define INPUT
struct doubly_ll;
/* Moves cursor forwards or backwards in a file f.
 * fback specifies whether to move the cursor backwards or forwards, while direct specifies whether to move the cursor once or to the next newline.
 */
void chline(FILE* f,char direct,char fback);
/* Moves the cursor 1 forward or 1 backward in a doubly linked list. 
 * Direct specifies whether to move forward or backwards.
 */
int horizontal(int i,struct doubly_ll* dll);
/* Moves the cursor up or down in both the doubly liked list AND the shell history, and reprints over the current terminal prompt the command acessed with arrow keys.
 * direct specifies the direction of movement, dll and f correspond to the double linked list representing user input and the shell history file, respectively.
 */
struct doubly_ll* vertical(int i,struct doubly_ll* dll);
/* Input command for processing different user key inputs, either arrow keys which are handled by above functions, delete, newline which means the argument is executed, tab which executes autocomplete functions in preparse.c, or by default just adds another character to the user typed argument.
 * Returns the string of the user's inputted command.
 */
char* input();
#endif
