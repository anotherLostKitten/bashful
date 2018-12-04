# BASHFUL

a shell except it's shelldon from big bang theory (bazinga)

# FEATURES

Arbitrary command execution, plus cd and exit.

Semicolons to sequentially execute a number of commands from a single input line.

Redirection (>,<) and piping (|). Also added: >> to redirect stdout to append to a file, and 2> or 2>> to redirect stderr.

Ampersands at the end of a line will allow the command to run in the background.

Double quotes allow you to treat the enclosed text as one argument, including spaces.

Left and right arrow allow you to navigate backwards and forwards within the text that you have in order to insert text in the middle of what you've already typed.

Up and down arrow allow you to navigate backwards and forwards through the command history, stored in /home/USER/.shellhistory

Tab autocompletes commands for the first argument, and file/directory for all subsequent arguments.

# ALMOST FEATURES

We tried to add better tab autocompletion.

We were going to add ampersand redirects but we decided against it.

# WE PRETEND THESE ARE FEATURES

Holding the horizontal arrow keys for long enough can mess up the position in which the cursor appears (although this has no effect on the way text is inserted). The visual bug should go away after a backspace is pressed.

When the input reaches at least 2 lines long, on any new keyboard input, all but the last line of the input will stay and a new copy of the prompt and the whole input will be printed starting from the bottom line. 

Various other visual glitches (that also glitch bash so we feel no need to list them here).

All of the bugs that we listed above are simply aesthetic bugs, and don't modify at all the actual input.

# CONJUNCTION JUNCTION?

## chario.h

```c
char getch();
```

This function is functionally the same as the getch() function in the ncurses library or in the windows conio library.
It serves the same function as getchar, however it does not echo the input to the console, and it does not cook the input provided to it.
This is achieved with the inclusion of the termios.h header.

## control.h

```c
int control();
```

Main control loop for running terminal.
Runs a loop until exit is called, in which case returns zero.

## dll.h
This doubly linked list represents the text that is input into the terminal until enter is pressed. This was a necessary way to represent the text in order to properly implement arrow key support, insertion in the middle of the string, and tab autocompletion. 

```c
struct node{
    char c;
    struct node* next;
    struct node* prev;
};
```

Represents a node in a doubly linked list.

```c
struct doubly_ll{
    int length;
    struct node* target;
};
```

Represents a doubly linked list, where target is the current position of the cursor

```c
struct node* char2node(char c);
```

Turns an input character into a node with null prev and next pointers but with the proper c field
Primarily for the use of the add_next and compose_dll functions. 

```c
void add_next(struct doubly_ll* self, char toinsert);
```

Inserts a node containing the character toinsert after the position of the cursor in the doubly linked list.
Moves the cursor to point to the newly inserted node.
Called on the insertion of a text character into stdin.

```c
void remove_prev(struct doubly_ll* self);
```

Removes the node at the position of the cursor in the doubly linked list.
Moves the cursor to the node before the recently deleted node.
Called when backspace is written into stdin.

```c
struct doubly_ll* initdll();
```

Allocates memory for and creates a minimal case doubly linked list with a dummy anchor cursor node.

```c
char* decompose_dll(struct doubly_ll* rotting);
```

Creates a string from the doubly linked list rotting (get it decompose, rotting haha) without modifying it.

```c
struct doubly_ll* compose_dll(char* source);
```

Creates a doubly linked list from string 'source'.

```c
int forward(struct doubly_ll* self);
```

Counts how many nodes are in front of the cursor in a doubly linked list.
Used in calculating the cursor position after an arrow key press or character input.

```c
void freeall(struct doubly_ll* self);
```

Frees all the nodes in a doubly linked list, then the doubly linked list itself.

## execute.h

```c
int execute(char** argv);
```

Takes in a null-terminated array of strings, argv, and executes them as if they were command line arguments.
Returns -1 if the program should exit, otherwise returns the return value of the command execute.

## input.h

```c
void chline(FILE* f,char direct,char fback);
```

Moves cursor forwards or backwards in a file f.
fback specifies whether to move the cursor past an encountered newline or not, while direct specifies whether to move the cursor to the next or previous newline.

```c
int horizontal(int i,struct doubly_ll* dll);
```

Moves the cursor 1 forward or 1 backward in a doubly linked list. 
Direct specifies whether to move forward or backwards.
Also moves the text cursor forward or backwards

```c
struct doubly_ll* vertical(int i,struct doubly_ll* dll);
```

Moves the cursor up or down in the the shell history, sets the doubly linked list to the desired previously input command, and reprints over the current terminal prompt the command acessed with arrow keys.
direct specifies the direction of movement, dll and f correspond to the double linked list representing user input and the shell history file, respectively.

```c
char* input();
```

Input command for processing different user key inputs, either arrow keys which are handled by above functions, backspace, and enter/return which means the argument is executed, tab which executes autocompletion functions in preparse.c, or anythng else which just adds another character to the user typed argument. All of these except enter (which frees the doubly linked list), and the horizontal arrow keys, update the doubly linked list.
Returns the string of the user's inputted command.

## parse_args.h

```c
int parse_args(char* buff);
```

Parses a string buff into arguments which it then executes.
Returns -1 if the program should exit, otherwise returns the return value of the rightmost argument in a sequence.

## preparse.h

```c
int preparse(struct doubly_ll* dll);
```

Simple parsing of terminal argument to determine what the currently being typed word is so as to facilitate tab autocompletion.
dll is the doubly linked list that corresponds to the command the user has entered so far.

```c
int autocomplete(struct doubly_ll* dll,char first_word_flag,char* word);
```

Adds to the doubly linked list the value of the first entry in the current directory (/ for first argumend or cwd otherwise) whose beginning matches word.
dll is the doubly linked list of the current terminal entry, first_word_flag denotes whether direcory used should be / or cwd, and word is the word that would be autocompleted.
