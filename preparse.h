#ifndef PREPARSE
#define PREPARSE
struct doubly_ll;
/* Simple parsing of terminal argument to determine what the currently being typed word is so as to facilitate tab autocompletion.
 * dll is the doubly linked list that corresponds to the command the user has entered so far.
 */
int preparse(struct doubly_ll* dll);
/* Adds to the doubly linked list the value of the first entry in the current directory (/ for first argumend or cwd otherwise) whose beginning matches word.
 * dll is the doubly linked list of the current terminal entry, first_word_flag denotes whether direcory used should be / or cwd, and word is the word that would be autocompleted.
 */
int autocomplete(struct doubly_ll* dll,char first_word_flag,char* word);
#endif
