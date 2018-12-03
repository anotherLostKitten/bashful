#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST
//Note: This doubly linked list represents the text that is input into the terminal until enter is pressed. This was a necessary way to represent the text in order to properly implement arrow key support, insertion in the middle of the string, and tab autocompletion. 

//Represents a node in a doubly linked list.
struct node{
    char c;
    struct node* next;
    struct node* prev;
};

//Represents a doubly linked list, where target is the current position of the cursor
struct doubly_ll{
    int length;
    struct node* target;
};

/*Turns an input character into a node with null prev and next pointers but with the proper c field
 *Primarily for the use of the add_next and compose_dll functions.
 */ 
struct node* char2node(char c);

/*Inserts a node containing the character toinsert after the position of the cursor in the doubly linked list.
 *Moves the cursor to point to the newly inserted node.
 *Called on the insertion of a text character into stdin.
 */
void add_next(struct doubly_ll* self, char toinsert);

/*Removes the node at the position of the cursor in the doubly linked list.
 *Moves the cursor to the node before the recently deleted node.
 *Called when backspace is written into stdin.
 */
void remove_prev(struct doubly_ll* self);

//Allocates memory for and creates a minimal case doubly linked list with a dummy anchor cursor node.
struct doubly_ll* initdll();

//Creates a string from the doubly linked list rotting (get it decompose, rotting haha) without modifying it.
char* decompose_dll(struct doubly_ll* rotting);

//Creates a doubly linked list from string 'source'.
struct doubly_ll* compose_dll(char* source);

/*Counts how many nodes are in front of the cursor in a doubly linked list.
 *Used in calculating the cursor position after an arrow key press or character input.
 */
int forward(struct doubly_ll* self);

//Frees all the nodes in a doubly linked list, then the doubly linked list itself.
void freeall(struct doubly_ll* self);
#endif
