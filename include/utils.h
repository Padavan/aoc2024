#ifndef ADVENT_UTILS_H__
#define ADVENT_UTILS_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef int32_t i32;
typedef uint8_t u8;
typedef uint64_t u64;

typedef struct {
	u8* str;
	u64 size;
} string8;

#define STR8_LIT(s) (string8){ (u8*)(s), sizeof((s)) - 1}
#define STR8_FMT(s8) (int)(s8).size, (s8).str
#define MIN(a, b) ((a) < (b) ? (a) : (b))


string8 str8_substr(string8 str, u64 start, u64 end);

// string8 str8_substr(string8 str, u64 start, u64 end) {
// 	end = MIN(end, str.size);
// 	start = MIN(start, end);
// 	return (string8){ str.str + start, end - start };
// }


int find_character_index(char str[], char ch);

int find_number_index(int list[], char ch);

char* get_substring(size_t start, size_t end, char string[]);

int integer_comp(const void* a, const void* b);

int get_line_count(char filepath[]);

bool includes(int* list, int target);

bool arr_includes(size_t list[][2], size_t lenght, size_t target_point[2]);

int power(int base, int exp);

long long llpower(long long base, long exp);

int get_digit_count(long long number);

char* convert_to_string(int number);

char get_digit_char(int digit);

#endif /*  ADVENT_UTILS_H__  */
