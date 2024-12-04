#ifndef MATRIX_UTILS_H__
#define MATRIX_UTILS_H__
#include <stdbool.h>

void print_char_matrix(int width, int height, char** matrix);

int* move_point(int first[2], int second[2]);

_Bool is_inbound(int point[2], int width, int height);

#endif /*  MATRIX_UTILS_H__  */
