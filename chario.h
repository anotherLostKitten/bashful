#ifndef CHARIO
#define CHARIO
/*This function is functionally the same as the getch() function in the ncurses library or in the windows conio library.
 *It serves the same function as getchar, however it does not echo the input to the console, and it does not cook the input provided to it.
 *This is achieved with the inclusion of the termios.h header.
*/
char getch();
#endif
