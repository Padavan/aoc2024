#ifndef MATRIX_UTILS_H__
#define MATRIX_UTILS_H__
#include <stdbool.h>
#include <sys/types.h>

struct Point {
  size_t row;
  size_t col;
  // size_t dir;
};

extern size_t directions[4][2];

extern struct Point directions_coord[4];


void print_char_matrix(int width, int height, char** matrix);

void print_int_matrix(size_t width, size_t height, size_t** matrix);

size_t* find_char_coord(char** matrix, size_t width, size_t height,
                        char target);

size_t* move_point(size_t first[2], size_t second[2]);

struct Point move_coord(struct Point first, struct Point second);

bool is_inbound(size_t point[2], size_t width, size_t height);

#endif /*  MATRIX_UTILS_H__  */