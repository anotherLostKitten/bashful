#ifndef PREPARSE
#define PREPARSE
struct doubly_ll;
int preparse(struct doubly_ll* dll);
DIR* autocomplete(struct doubly_ll* dll,char first_word_flag,char* word);
#endif
