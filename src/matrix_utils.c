#include "matrix_utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

int* move_point(int first[2], int second[2])
{
    int* result = malloc(sizeof(int) * 2);
    result[0] = first[0] + second[0];
    result[1] = first[1] + second[1];
    return result;
}

_Bool is_inbound(int point[2], int width, int height)
{
    int x = point[0];
    int y = point[1];

    if (x >= 0 && x < width && y >= 0 && y < height) {
        return true;
    } else {
        return false;
    }
}