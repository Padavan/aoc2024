#include "matrix_utils.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

size_t directions[4][2] = {
    { -1, 0 }, // up
    { 0, -1 }, // left
    { 1, 0 }, // down
    { 0, 1 } // right
};

struct Point directions_coord[4] = {
    { -1, 0 }, // up
    { 0, -1 }, // left
    { 1, 0 }, // down
    { 0, 1 } // right
};

void print_char_matrix(int width, int height, char** matrix)
{
    printf("printing matrix...\n");
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            printf(" %c ", matrix[row][col]);
        }
        printf("\n");
    }

    return;
}

void print_int_matrix(size_t width, size_t height, size_t** matrix)
{
    printf("printing matrix...\n");
    for (size_t row = 0; row < height; row++) {
        for (size_t col = 0; col < width; col++) {
            printf(" %5ld ", matrix[row][col]);
        }
        printf("\n");
    }

    return;
}

size_t*
find_char_coord(char** matrix, size_t width, size_t height, char target)
{
    size_t* result = malloc(sizeof(size_t) * 2);
    for (size_t row = 0; row < height; row++) {
        for (size_t col = 0; col < width; col++) {
            if (matrix[row][col] == target) {
                result[0] = row;
                result[1] = col;
            }
        }
    }

    return result;
}

size_t*
move_point(size_t first[2], size_t second[2])
{
    size_t* result = malloc(sizeof(size_t) * 2);
    result[0] = first[0] + second[0];
    result[1] = first[1] + second[1];
    return result;
}

struct Point
move_coord(struct Point first, struct Point second)
{
    struct Point result = { first.row + second.row, first.col + second.col };
    return result;
}

bool is_inbound(size_t point[2], size_t width, size_t height)
{
    size_t x = point[0];
    size_t y = point[1];

    if (x >= 0 && x < width && y >= 0 && y < height) {
        return true;
    } else {
        return false;
    }
}