#ifndef PREPARSE
#define PREPARSE
struct doubly_ll;
char* preparse(struct doubly_ll* dll);
char* autocomplete(char first_word_flag);
void insert_into_dll(struct doubly_ll* dll);
#endif
