#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_character_index(char str[], char ch) {
  size_t length = strlen(str);
  for (size_t i = 0; i < length; i = i + 1) {
    if (str[i] == ch) {
      return i;
    }
  }

  return -1;
}

int find_number_index(int list[], char ch) {
  // size_t length = ;
  int index = 0;
  while (list[index] != '\0') {
    if (list[index] == ch) {
      return index;
    }
    index++;
  }

  return -1;
}

// get substring
char* get_substring(size_t start, size_t end, char string[]) {
  // printf("get_substring: %ld, %ld \n", start, end);
  assert(end > start);
  size_t length = end - start;

  char* substring = malloc(sizeof(char) * (length + 1));

  for (size_t i = 0; i < length; i++) {
    substring[i] = string[i + start];
  }
  substring[length] = '\0';

  return substring;
}

// Number comparator
int integer_comp(const void* a, const void* b) { return (*(int*)a - *(int*)b); }

// lookup file and count lines
int get_line_count(char filepath[]) {
  FILE* fp;
  fp = fopen(filepath, "r");
  int line_count = 0;

  if (!fp) {
    perror(filepath);
    return 1;
  }

  char* line = NULL;
  size_t len = 0;

  while ((getline(&line, &len, fp)) != -1) {
    line_count++;
  }
  fclose(fp);
  free(line);

  return line_count;
}

bool includes(int* list, int target) {
  int index = 0;
  while (list[index] != '\0') {
    if (list[index] == target) {
      return true;
    }
  }
  return false;
}

bool arr_includes(size_t (*list)[2], size_t lenght, size_t target_point[2]) {
  for (size_t i = 0; i < lenght; i++) {
    if (list[i][0] == target_point[0] && list[i][1] == target_point[1]) {
      return true;
    }
  }
  return false;
}

int power(int base, int exp) {
  int result = 1;
  for (;;) {
    if (exp & 1) result *= base;
    exp >>= 1;
    if (!exp) break;
    base *= base;
  }

  return result;
}

int get_digit_count(long long number) {
  if (number < 10) return 1;
  return 1 + get_digit_count(number / 10);
}
