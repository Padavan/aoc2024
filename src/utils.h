#ifndef ADVENT_UTILS_H__
#define ADVENT_UTILS_H__

#include <stdlib.h>

int find_character_index(char str[], char ch);

char *get_substring(size_t start, size_t end, char string[]);

int integer_comp(const void *a, const void *b);

int get_line_count(char filepath[]);
#endif /*  ADVENT_UTILS_H__  */