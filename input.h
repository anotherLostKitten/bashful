#ifndef INPUT
#define INPUT
struct doubly_ll;
/* Moves cursor forwards or backwards in a file f.
 * fback specifies whether to move the cursor past an encountered newline or not, while direct specifies whether to move the cursor to the next or previous newline.
 */
void chline(FILE* f,char direct,char fback);
/* Moves the cursor 1 forward or 1 backward in a doubly linked list. 
 * Direct specifies whether to move forward or backwards.
 * Also moves the text cursor forward or backwards
 */
int horizontal(int i,struct doubly_ll* dll);
/* Moves the cursor up or down in the the shell history, sets the doubly linked list to the desired previously input command, and reprints over the current terminal prompt the command acessed with arrow keys.
 * direct specifies the direction of movement, dll and f correspond to the double linked list representing user input and the shell history file, respectively.
 */
struct doubly_ll* vertical(int i,struct doubly_ll* dll);
/* Input command for processing different user key inputs, either arrow keys which are handled by above functions, backspace, and enter/return which means the argument is executed, tab which executes autocompletion functions in preparse.c, or anythng else which just adds another character to the user typed argument. All of these except enter (which frees the doubly linked list), and the horizontal arrow keys, update the doubly linked list.
 * Returns the string of the user's inputted command.
 */
char* input();
#endif
