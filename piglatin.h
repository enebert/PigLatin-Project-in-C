#ifndef PIG_LATIN_H
#define PIG_LATIN_H

#include <stdbool.h>

void word_copy(char **w, const char *p);
int count_words(const char *p);
bool is_vowel(const char *s);
void cons_segment(char *buffer, const char* p);
void translate_word(char *buffer, const char* src);
char *translate(const char *phrase);

#endif

