#ifndef PARSEARGS
#define PARSEARGS
/* Parses a string buff into arguments which it then executes.
 * Returns -1 if the program should exit, otherwise returns the return value of the rightmost argument in a sequence.
 */
int parse_args(char* buff);
#endif
