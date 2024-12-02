#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "day1.h"

int part1(char inputpath[], int line_count) {
  int *first_col = malloc(line_count * sizeof(int));
  int *second_col = malloc(line_count * sizeof(int));

  size_t line_num = 0;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  FILE *fp;
  fp = fopen(inputpath, "r");
  while ((read = getline(&line, &len, fp)) != -1) {
    size_t whitespace_index = find_character_index(line, ' ');
    char *first_part = get_substring(0, whitespace_index, line);
    int first_number = atoi(first_part);
    free(first_part);
    char *second_part = get_substring(whitespace_index + 1, strlen(line), line);
    int second_number = atoi(second_part);
    free(second_part);

    first_col[line_num] = first_number;
    second_col[line_num] = second_number;
    line_num++;
  }
  fclose(fp);
  free(line);

  qsort(first_col, line_count, sizeof(int), integer_comp);
  qsort(second_col, line_count, sizeof(int), integer_comp);

  int result = 0;
  for (int i = 0; i < line_count; i++) {
    result = result + abs(first_col[i] - second_col[i]);
  }

  return result;
}

int get_number_occurance(int *sorted_arr, int line_count, int target) {
  int occurance = 0;
  for (int i = 0; i < line_count; i++) {
    if (sorted_arr[i] == target) {
      occurance = occurance + 1;
    }
    if (target < sorted_arr[i]) {
      break;
    }
  }

  return occurance;
}

int part2(char inputpath[], int line_count) {
  int *first_col = malloc(line_count * sizeof(int));
  int *second_col = malloc(line_count * sizeof(int));

  size_t line_num = 0;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  FILE *fp;
  fp = fopen(inputpath, "r");
  while ((read = getline(&line, &len, fp)) != -1) {
    size_t whitespace_index = find_character_index(line, ' ');
    char *first_part = get_substring(0, whitespace_index, line);
    int first_number = atoi(first_part);
    free(first_part);
    char *second_part = get_substring(whitespace_index + 1, strlen(line), line);
    int second_number = atoi(second_part);
    free(second_part);

    first_col[line_num] = first_number;
    second_col[line_num] = second_number;
    line_num++;
  }
  fclose(fp);
  free(line);

  qsort(second_col, line_count, sizeof(int), integer_comp);

  int result = 0;
  for (int i = 0; i < line_count; i++) {
    int target_number = first_col[i];
    int current_occurance =
        get_number_occurance(second_col, line_count, target_number);
    result = (current_occurance * target_number) + result;
  }

  return result;
}

int run_day1() {
  int DAY = 1;
  char inputpath[] = "./input/day1.txt";

  int line_count = get_line_count(inputpath);
  if (line_count == 0) {
    perror("There is no lines in puzzle input");
    return 1;
  }

  printf("Day %d\n", DAY);
  printf("\tPart 1: %d\n", part1(inputpath, line_count));
  printf("\tPart 2: %d\n", part2(inputpath, line_count));

  return 0;
}
