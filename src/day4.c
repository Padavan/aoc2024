
#include "day4.h"
#include "matrix_utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int increment[8][4][2] = {
    { { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 } }, // east
    { { 0, 0 }, { -1, 0 }, { -2, 0 }, { -3, 0 } }, // west
    { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 } }, // north
    { { 0, 0 }, { 0, -1 }, { 0, -2 }, { 0, -3 } }, // south
    { { 0, 0 }, { 1, 1 }, { 2, 2 }, { 3, 3 } }, // north-east
    { { 0, 0 }, { 1, -1 }, { 2, -2 }, { 3, -3 } }, // south-east
    { { 0, 0 }, { -1, 1 }, { -2, 2 }, { -3, 3 } }, // north-west
    { { 0, 0 }, { -1, -1 }, { -2, -2 }, { -3, -3 } }, // south-west
};

int check_point_x(int point[2], char** matrix, int width, int height)
{
    int finded = 0;

    int possible_word_point[4][2];
    for (int i = 0; i < 8; i++) {
        memcpy(possible_word_point, increment + i, sizeof(int[4][2]));

        // printf("cycle %d\n", i);
        // printf("pwp %d,%d\n", possible_word_point[1][0],
        // possible_word_point[1][1]);
        int* second = move_point(possible_word_point[1], point);
        int* third = move_point(possible_word_point[2], point);
        int* fourth = move_point(possible_word_point[3], point);

        _Bool is_m = is_inbound(second, width, height) && matrix[second[1]][second[0]] == 'M';
        _Bool is_a = is_inbound(third, width, height) && matrix[third[1]][third[0]] == 'A';
        _Bool is_s = is_inbound(fourth, width, height) && matrix[fourth[1]][fourth[0]] == 'S';

        if (is_m && is_a && is_s) {
            // printf("finded. start: %d,%d - end: %d,%d \n", point[0], point[1],
            // fourth[0], fourth[1]);
            finded++;
        }

        free(second);
        free(third);
        free(fourth);
    }
    // free(possible_word_point);

    return finded;
}

int run_day4_part1(char** matrix, int height, int width)
{
    int result = 0;
    int row = 0;
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            if (matrix[row][col] == 'X') {
                int target_point[2] = { col, row };
                result = result + check_point_x(target_point, matrix, width, height);
            }
        }
    }

    return result;
}

// first two coordinates for M, second two for S
int possitions_mas[4][4][2] = {
    { { -1, 1 }, { 1, 1 }, { -1, -1 }, { 1, -1 } }, // mm/ss
    { { -1, 1 }, { -1, -1 }, { 1, 1 }, { 1, -1 } }, // ms/ms
    { { -1, -1 }, { 1, -1 }, { -1, 1 }, { 1, 1 } }, // ss/mm
    { { 1, -1 }, { 1, 1 }, { -1, 1 }, { -1, -1 } }, // sm/sm
};

int check_point_a(int point[2], char** matrix, int width, int height)
{
    int found = 0;

    int possible_mas_cross[4][2];
    for (int i = 0; i < 4; i++) {
        memcpy(possible_mas_cross, possitions_mas + i, sizeof(int[4][2]));

        // printf("cycle %d\n", i);
        // printf("pwp %d,%d\n", possible_word_point[1][0],
        // possible_word_point[1][1]);

        int* first = move_point(possible_mas_cross[0], point);
        int* second = move_point(possible_mas_cross[1], point);
        int* third = move_point(possible_mas_cross[2], point);
        int* fourth = move_point(possible_mas_cross[3], point);

        _Bool is_m1 = is_inbound(first, width, height) && matrix[first[1]][first[0]] == 'M';
        _Bool is_m2 = is_inbound(second, width, height) && matrix[second[1]][second[0]] == 'M';
        _Bool is_s1 = is_inbound(third, width, height) && matrix[third[1]][third[0]] == 'S';
        _Bool is_s2 = is_inbound(fourth, width, height) && matrix[fourth[1]][fourth[0]] == 'S';

        // printf("is: %d,%d,%d,%d\n", is_m1, is_m2, is_s1, is_s2);
        // printf("points: %d,%d - %d,%d - %d,%d - %d,%d\n", first[0], first[1],
        // second[0], second[1], third[0], third[1], fourth[0], fourth[1]);

        if (is_m1 && is_m2 && is_s1 && is_s2) {
            // printf("found. start: %d,%d - end: %d,%d \n", point[0], point[1],
            // fourth[0], fourth[1]);
            found = 1;
        }

        free(first);
        free(second);
        free(third);
        free(fourth);
    }

    return found;
}

int run_day4_part2(char** matrix, int height, int width)
{
    int result = 0;
    int row = 0;
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            if (matrix[row][col] == 'A') {
                int target_point[2] = { col, row };
                // printf("TARGET: %d, %d\n", target_point[1], target_point[0]);
                result = result + check_point_a(target_point, matrix, width, height);
            }
        }
    }

    return result;
}

int run_day4()
{
    int DAY = 4;
    char inputpath[] = "./input/day4.txt";

    FILE* fp;
    fp = fopen(inputpath, "r");
    char ch;

    char content[1000000];

    int i = 0;
    int matrix_width = 0;
    int matrix_height = 1;
    do {
        ch = fgetc(fp);
        content[i] = ch;
        if (ch == '\n') {
            if (matrix_height == 1) {
                matrix_width = i;
            }
            matrix_height++;
        }
        i++;
    } while (ch != EOF);
    fclose(fp);

    char** matrix = malloc(sizeof(char*) * matrix_height);
    for (int row = 0; row < matrix_height; row++) {
        matrix[row] = malloc(sizeof(char) * matrix_width);
    }

    int col = 0;
    int row = 0;

    int index = 0;
    while (content[index] != '\0') {
        char current = content[index];

        index++;
        if (current == 'X' || current == 'M' || current == 'A' || current == 'S' || current == '.') {
            // printf("row: %d, col: %d \n", row, col);

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

    printf("Day %d\n", DAY);
    printf("\tPart 1: %d\n", run_day4_part1(matrix, matrix_height, matrix_width));
    // 2370
    printf("\tPart 2: %d\n", run_day4_part2(matrix, matrix_height, matrix_width));

    for (i = 0; i < matrix_height; ++i)
        free(matrix[i]);
    free(matrix);

    return 0;
}
