#ifndef EXECUTE
#define EXECUTE
/* Takes in a null-terminated array of strings, argv, and executes them as if they were command line arguments.
 * Returns -1 if the program should exit, otherwise returns the return value of the command execute.
 */
int execute(char** argv);
#endif
