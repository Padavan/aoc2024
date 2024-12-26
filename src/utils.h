#ifndef ADVENT_UTILS_H__
#define ADVENT_UTILS_H__

#include <stdbool.h>
#include <stdlib.h>

int find_character_index(char str[], char ch);

int find_number_index(int list[], char ch);

char* get_substring(size_t start, size_t end, char string[]);

int integer_comp(const void* a, const void* b);

int get_line_count(char filepath[]);

bool includes(int* list, int target);

bool arr_includes(size_t list[][2], size_t lenght, size_t target_point[2]);

int power(int base, int exp);

int get_digit_count(long long number);

#endif /*  ADVENT_UTILS_H__  */