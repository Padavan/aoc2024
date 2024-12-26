#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>

#include "matrix_utils.h"
#include "utils.h"

// size_t MAX_AREA = 500;

struct Day12Result {
  size_t a;
  size_t b;
};

char CAPITAL_ALPHABET[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                             'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                             'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

size_t near_areas[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

size_t near_diagonal_areas[4][2] = {{1, 1}, {-1, 1}, {-1, -1}, {1, -1}};

void get_area_points(char **matrix, size_t width, size_t height,
                     size_t target[2], size_t area_points[500][2],
                     size_t *area_points_count, size_t *corners) {
  // printf("target: %ld, %ld", target[0], target[1]);
  area_points[*area_points_count][0] = target[0];
  area_points[*area_points_count][1] = target[1];
  *area_points_count = *area_points_count + 1;

  assert(*area_points_count < 500);
  // for (size_t i = 0; i < *area_points_count; i++) {
  //     printf("  %ld,%ld  ", area_points[i][0], area_points[i][1]);
  // }
  // printf("\n");

  int shit[4] = {0, 0, 0, 0};

  for (size_t i = 0; i < 4; i++) {
    size_t *side = move_point(target, near_areas[i]);
    if (is_inbound(side, width, height) &&
        matrix[target[0]][target[1]] == matrix[side[0]][side[1]]) {
      shit[i] = 1;
    }

    if (is_inbound(side, width, height) &&
        matrix[target[0]][target[1]] == matrix[side[0]][side[1]] &&
        !arr_includes(area_points, *area_points_count, side)) {
      get_area_points(matrix, width, height, side, area_points,
                      area_points_count, corners);
    }

    free(side);
  }

  int shit2[4] = {0, 0, 0, 0};
  for (size_t i = 0; i < 4; i++) {
    size_t *side = move_point(target, near_diagonal_areas[i]);
    if (is_inbound(side, width, height) &&
        matrix[target[0]][target[1]] == matrix[side[0]][side[1]]) {
      shit2[i] = 1;
    }

    free(side);
  }

  // if (shit[0] + shit[1] + shit[2] + shit[3] == 0) {
  //     *corners = *corners + 4;
  // }

  // printf("shits: ");
  for (int i = 0; i < 4; i++) {
    // printf("\t %d ", shit[i]);
    if (shit[i] == 0 && shit[(i + 1) % 4] == 0) {
      *corners = *corners + 1;
    }

    if (shit[i] == 1 && shit[(i + 1) % 4] == 1 && shit2[i] == 0) {
      *corners = *corners + 1;
    }
  }
  // printf("\n---\n");
}

void nullify_area(char **matrix, size_t area_points[500][2],
                  size_t *area_points_count) {
  for (size_t i = 0; i < *area_points_count; i++) {
    matrix[area_points[i][0]][area_points[i][1]] = '.';
  }
}

// super expensive
size_t get_perimeter(size_t area_points[500][2], size_t *area_points_count,
                     size_t width, size_t height) {
  size_t vertical = 0;
  for (size_t row = 0; row < height; row++) {
    size_t gap = true;
    size_t current_v = 0;

    for (size_t col = 0; col < width; col++) {
      size_t coord[2] = {row, col};
      bool area_filled = arr_includes(area_points, *area_points_count, coord);
      if (area_filled && gap) {
        current_v = current_v + 1;
        gap = false;
      } else if (area_filled) {
        // dunno
      } else if (gap == false) {
        current_v = current_v + 1;
        gap = true;
      };

      if (col == width - 1 && gap == false) {
        current_v = current_v + 1;
      }
    }

    if (current_v > 0) {
      vertical = vertical + current_v;
    }
  }

  size_t horizontal = 0;
  for (size_t col = 0; col < width; col++) {
    size_t gap = true;

    size_t current_h = 0;
    for (size_t row = 0; row < width; row++) {
      size_t coord[2] = {row, col};
      bool area_filled = arr_includes(area_points, *area_points_count, coord);
      if (area_filled && gap) {
        current_h = current_h + 1;
        gap = false;
      } else if (area_filled) {
        // dunno
      } else if (gap == false) {
        current_h = current_h + 1;
        gap = true;
      };

      if (row == height - 1 && gap == false) {
        current_h = current_h + 1;
      }
    }

    if (current_h > 0) {
      horizontal = horizontal + current_h;
    }
  }

  return vertical + horizontal;
}

struct Day12Result analyze_day12_matrix(char **matrix, size_t width,
                                        size_t height) {
  struct Day12Result result = {0, 0};

  for (size_t row = 0; row < height; row++) {
    for (size_t col = 0; col < width; col++) {
      if (find_character_index(CAPITAL_ALPHABET, matrix[row][col]) > -1) {
        size_t target[2] = {row, col};
        // size_t target[2] = { 0, 4 };
        size_t area_points[500][2];
        size_t area_points_count = 0;
        size_t corners = 0;
        get_area_points(matrix, width, height, target, area_points,
                        &area_points_count, &corners);

        size_t perimeter =
            get_perimeter(area_points, &area_points_count, width, height);
        // printf("areas: %ld, perimeter: %ld, corners: %ld \n",
        // area_points_count, perimeter, corners);
        nullify_area(matrix, area_points, &area_points_count);

        result.a = result.a + (perimeter * area_points_count);
        result.b = result.b + (corners * area_points_count);
      }
    }
  }

  return result;
}

int run_day12() {
  printf("Day 12: Garden Groups\n");
  // char inputpath[] = "./input/day12-test.txt";
  char inputpath[] = "./input/day12.txt";

  FILE *fp;
  fp = fopen(inputpath, "r");
  char ch;
  char content[50000] = {0};

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

  if (matrix_height < 2 || matrix_width < 2) {
    perror("Matrix dimensions are wrong");
    return 1;
  }

  char **matrix = (char **)malloc(sizeof(char *) * matrix_height);
  for (size_t row = 0; row < matrix_height; row++) {
    matrix[row] = (char *)malloc(sizeof(char) * matrix_width);
  }

  size_t col = 0;
  size_t row = 0;
  for (size_t i = 0; i < char_count; i++) {
    if (find_character_index(CAPITAL_ALPHABET, content[i]) >= 0) {
      matrix[row][col] = content[i];
      if (col == (matrix_width - 1)) {
        row++;
        col = 0;
      } else {
        col++;
      }
    }
  }

  struct Day12Result result =
      analyze_day12_matrix(matrix, matrix_width, matrix_height);
  printf("\tPart 1: %ld\n", result.a);
  printf("\tPart 2: %ld\n", result.b);

  for (size_t i = 0; i < matrix_height; ++i) free(matrix[i]);
  free(matrix);

  return 0;
}
