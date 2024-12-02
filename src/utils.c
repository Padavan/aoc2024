#include <assert.h>
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

// get substring
char *get_substring(size_t start, size_t end, char string[]) {
  assert(end > start);
  size_t length = end - start;

  char *substring = malloc(length);

  for (size_t i = 0; i < length; i++) {
    substring[i] = string[i + start];
  }

  return substring;
}

// Number comparator
int integer_comp(const void *a, const void *b) {
  return (*(int *)a - *(int *)b);
}

// lookup file and count lines
int get_line_count(char filepath[]) {
  FILE *fp;
  fp = fopen(filepath, "r");
  int line_count = 0;

  if (!fp) {
    perror(filepath);
    return 1;
  }

  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  while ((read = getline(&line, &len, fp)) != -1) {
    line_count++;
  }
  fclose(fp);
  free(line);

  return line_count;
}