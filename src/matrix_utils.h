#ifndef MATRIX_UTILS_H__
#define MATRIX_UTILS_H__
#include <stdbool.h>
#include <sys/types.h>

void print_char_matrix(int width, int height, char** matrix);

void print_int_matrix(int width, int height, int** matrix);

size_t* find_char_coord(char** matrix, size_t width, size_t height,
                        char target);

size_t* move_point(size_t first[2], size_t second[2]);

bool is_inbound(size_t point[2], size_t width, size_t height);

#endif /*  MATRIX_UTILS_H__  */
