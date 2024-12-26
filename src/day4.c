#include "day4.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix_utils.h"

size_t position_xmas[8][4][2] = {
    {{0, 0}, {1, 0}, {2, 0}, {3, 0}},        // east
    {{0, 0}, {-1, 0}, {-2, 0}, {-3, 0}},     // west
    {{0, 0}, {0, 1}, {0, 2}, {0, 3}},        // north
    {{0, 0}, {0, -1}, {0, -2}, {0, -3}},     // south
    {{0, 0}, {1, 1}, {2, 2}, {3, 3}},        // north-east
    {{0, 0}, {1, -1}, {2, -2}, {3, -3}},     // south-east
    {{0, 0}, {-1, 1}, {-2, 2}, {-3, 3}},     // north-west
    {{0, 0}, {-1, -1}, {-2, -2}, {-3, -3}},  // south-west
};

int check_point_x(size_t point[2], char** matrix, size_t width, size_t height) {
  int finded = 0;

  for (size_t i = 0; i < 8; i++) {
    size_t* second = move_point(position_xmas[i][1], point);
    size_t* third = move_point(position_xmas[i][2], point);
    size_t* fourth = move_point(position_xmas[i][3], point);

    bool is_m = is_inbound(second, width, height) &&
                matrix[second[1]][second[0]] == 'M';
    bool is_a =
        is_inbound(third, width, height) && matrix[third[1]][third[0]] == 'A';
    bool is_s = is_inbound(fourth, width, height) &&
                matrix[fourth[1]][fourth[0]] == 'S';

    if (is_m && is_a && is_s) {
      finded++;
    }

    free(second);
    free(third);
    free(fourth);
  }

  return finded;
}

int run_day4_part1(char** matrix, size_t height, size_t width) {
  int result = 0;
  for (size_t row = 0; row < height; row++) {
    for (size_t col = 0; col < width; col++) {
      if (matrix[row][col] == 'X') {
        size_t target_point[2] = {col, row};
        result = result + check_point_x(target_point, matrix, width, height);
      }
    }
  }

  return result;
}

// first two coordinates for M, second two for S
size_t possitions_mas[4][4][2] = {
    {{-1, 1}, {1, 1}, {-1, -1}, {1, -1}},  // mm/a/ss
    {{-1, 1}, {-1, -1}, {1, 1}, {1, -1}},  // ms/a/ms
    {{-1, -1}, {1, -1}, {-1, 1}, {1, 1}},  // ss/a/mm
    {{1, -1}, {1, 1}, {-1, 1}, {-1, -1}},  // sm/a/sm
};

int check_point_a(size_t point[2], char** matrix, size_t width, size_t height) {
  int found = 0;

  for (int i = 0; i < 4; i++) {
    size_t* first = move_point(possitions_mas[i][0], point);
    size_t* second = move_point(possitions_mas[i][1], point);
    size_t* third = move_point(possitions_mas[i][2], point);
    size_t* fourth = move_point(possitions_mas[i][3], point);

    bool is_m1 =
        is_inbound(first, width, height) && matrix[first[1]][first[0]] == 'M';
    bool is_m2 = is_inbound(second, width, height) &&
                 matrix[second[1]][second[0]] == 'M';
    bool is_s1 =
        is_inbound(third, width, height) && matrix[third[1]][third[0]] == 'S';
    bool is_s2 = is_inbound(fourth, width, height) &&
                 matrix[fourth[1]][fourth[0]] == 'S';

    if (is_m1 && is_m2 && is_s1 && is_s2) {
      found = 1;
    }

    free(first);
    free(second);
    free(third);
    free(fourth);
  }

  return found;
}

int run_day4_part2(char** matrix, size_t height, size_t width) {
  int result = 0;
  for (size_t row = 0; row < height; row++) {
    for (size_t col = 0; col < width; col++) {
      if (matrix[row][col] == 'A') {
        size_t target_point[2] = {col, row};
        result = result + check_point_a(target_point, matrix, width, height);
      }
    }
  }

  return result;
}

int run_day4() {
  printf("Day 4: Ceres Search\n");
  char inputpath[] = "./input/day4.txt";

  FILE* fp;
  fp = fopen(inputpath, "r");

  char ch;
  char content[1000000];

  size_t content_size = 0;
  size_t matrix_width = 0;
  size_t matrix_height = 1;
  do {
    ch = fgetc(fp);
    content[content_size] = ch;
    if (ch == '\n') {
      if (matrix_height == 1) {
        matrix_width = content_size;
      }
      matrix_height++;
    }
    content_size++;
  } while (ch != EOF);
  fclose(fp);

  assert(matrix_height > 1 && matrix_width > 1);

  char** matrix = malloc(sizeof(char*) * matrix_height);
  for (size_t row = 0; row < matrix_height; row++) {
    matrix[row] = malloc(sizeof(char) * matrix_width);
  }

  // fill matrix
  for (size_t row = 0; row < matrix_height; row++) {
    for (size_t col = 0; col < matrix_width; col++) {
      matrix[row][col] = '.';
    }
  }

  size_t col = 0;
  size_t row = 0;

  size_t index = 0;
  while (index < content_size) {
    char current = content[index];

    index++;
    if (current == 'X' || current == 'M' || current == 'A' || current == 'S' ||
        current == '.') {
      matrix[row][col] = current;
      if (col == (matrix_width - 1)) {
        row++;
        col = 0;
      } else {
        col++;
      }
    }
  }

  // print_char_matrix(matrix_width, matrix_height, matrix);

  printf("\tPart 1: %d\n", run_day4_part1(matrix, matrix_height, matrix_width));
  printf("\tPart 2: %d\n", run_day4_part2(matrix, matrix_height, matrix_width));

  for (size_t i = 0; i < matrix_height; ++i) free(matrix[i]);
  free(matrix);

  return 0;
}
