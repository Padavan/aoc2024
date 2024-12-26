#include "day10.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix_utils.h"
#include "utils.h"

char allowed_characters[10] = {'0', '1', '2', '3', '4',
                               '5', '6', '7', '8', '9'};

size_t sides[4][2] = {{-1, 0}, {0, 1}, {0, -1}, {1, 0}};

void get_summit_count_rec(size_t point[2], size_t** matrix, size_t size,
                          size_t tops[][2], size_t* tops_count) {
  // int collect_result = result;
  // printf("get_summit_count_rec: result %d\n", result);
  for (int i = 0; i < 4; i++) {
    size_t* side = move_point(point, sides[i]);

    if (is_inbound(side, size, size) &&
        matrix[side[0]][side[1]] - matrix[point[0]][point[1]] == 1) {
      // printf("\tside %d, %d, value: %d\n", side[0], side[1],
      // matrix[side[0]][side[1]]);
      if (matrix[side[0]][side[1]] == 9) {
        // printf("\t\tfound top %d,%d, value: %d \n", side[0], side[1],
        // matrix[side[0]][side[1]]);
        if (!arr_includes(tops, *tops_count, side)) {
          // printf("inside condition\n");
          tops[*tops_count][0] = side[0];
          tops[*tops_count][1] = side[1];
          *tops_count = *tops_count + 1;
        }

        // collect_result++;
      } else {
        get_summit_count_rec(side, matrix, size, tops, tops_count);
      }
    }

    free(side);
  }

  return;
}

int day10_part1(size_t** matrix, size_t width, size_t height) {
  int result = 0;
  for (size_t row = 0; row < width; row++) {
    for (size_t col = 0; col < height; col++) {
      if (matrix[row][col] == 0) {
        size_t start[2] = {row, col};
        size_t(*tops)[2] = malloc(height * width * sizeof(size_t[2]));
        size_t tops_count = 0;
        get_summit_count_rec(start, matrix, width, tops, &tops_count);

        free(tops);
        result = result + tops_count;
      }
    }
  }

  return result;
}

// PART 2
void get_summit_distinct_count_rec(size_t point[2], size_t** matrix,
                                   size_t size, size_t* trails_count) {
  for (int i = 0; i < 4; i++) {
    size_t* side = move_point(point, sides[i]);

    if (is_inbound(side, size, size) &&
        matrix[side[0]][side[1]] - matrix[point[0]][point[1]] == 1) {
      if (matrix[side[0]][side[1]] == 9) {
        *trails_count = *trails_count + 1;
      } else {
        get_summit_distinct_count_rec(side, matrix, size, trails_count);
      }
    }

    free(side);
  }

  return;
}

int day10_part2(size_t** matrix, size_t width, size_t height) {
  int result = 0;
  for (size_t row = 0; row < width; row++) {
    for (size_t col = 0; col < height; col++) {
      if (matrix[row][col] == 0) {
        size_t start[2] = {row, col};
        size_t trails_count = 0;
        get_summit_distinct_count_rec(start, matrix, width, &trails_count);

        result = result + trails_count;
      }
    }
  }

  return result;
}

int run_day10() {
  // char inputpath[] = "./input/day10-test.txt";
  char inputpath[] = "./input/day10.txt";
  printf("Day 10: Hoof It\n");

  FILE* fp;
  fp = fopen(inputpath, "r");
  char ch;

  char content[10000] = {0};

  size_t char_count = 0;
  size_t matrix_width = 0;
  size_t matrix_height = 1;
  do {
    ch = fgetc(fp);
    if (ch == '\n') {
      if (matrix_height == 1) {
        matrix_width = char_count;
      }
      matrix_height++;
    } else {
      content[char_count] = ch;
    }
    char_count++;
  } while (ch != EOF);
  fclose(fp);

  if (matrix_width < 2) {
    perror("Matrix dimensions are wrong");
    return 1;
  }

  size_t** matrix = malloc(sizeof(size_t*) * matrix_height);
  for (size_t row = 0; row < matrix_height; row++) {
    matrix[row] = malloc(sizeof(size_t) * matrix_width);
  }

  for (size_t row = 0; row < matrix_height; row++) {
    for (size_t col = 0; col < matrix_width; col++) {
      matrix[row][col] = '0';
    }
  }

  size_t col = 0;
  size_t row = 0;
  for (size_t i = 0; i < char_count; i++) {
    char current = content[i];
    if (find_character_index(allowed_characters, current) >= 0) {
      char* number = get_substring(i, i + 1, content);
      matrix[row][col] = atoi(number);
      if (col == (matrix_width - 1)) {
        row++;
        col = 0;
      } else {
        col++;
      }
      free(number);
    }
  }

  printf("\tPart 1: %d\n", day10_part1(matrix, matrix_width, matrix_height));
  printf("\tPart 2: %d\n", day10_part2(matrix, matrix_width, matrix_height));

  for (size_t i = 0; i < matrix_height; ++i) free(matrix[i]);
  free(matrix);

  return 0;
}
