#include "day6.h"
#include "matrix_utils.h";
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum DIRECTION {
    UP,
    RIGHT,
    DOWN,
    LEFT,
};

// row, col
int increments[4][2] = {
    {-1, 0},
    { 0, 1},
    { 1, 0},
    { 0,-1},
};

int does_it_loop(char** matrix, int height, int width, int start[2], int test_barrier[2]) {
    // printf("new barrier: %d,%d\n", test_barrier[0], test_barrier[1]);
    matrix[test_barrier[0]][test_barrier[1]] = '#';

    int marked_points[8000][2];
    int marked_points_count = 0;
    int steps = 0;

    enum DIRECTION direction = UP;
    int current[2] = { start[0], start[1] };
    int* next = move_point(current, increments[direction]);


    bool is_loop = false;

    while(is_inbound(next, height, width) && steps < 8000) {
        if (matrix[next[0]][next[1]] == '#') {
            direction = (direction + 1) % 4;
            next = move_point(current, increments[direction]);
        } else {
            current[0] = next[0];
            current[1] = next[1];
            matrix[current[0]][current[1]] = 'X';
            steps++;

            // bool point_already_marked = false;
            // for (int i=0; i < marked_points_count; i++) {
            //     if (marked_points[i][0] == current[0] && marked_points[i][1] == current[1]) {
            //         point_already_marked = true;
            //     }
            // }

            // if (point_already_marked == false) {
            //     marked_points[marked_points_count][0] = current[0];
            //     marked_points[marked_points_count][1] = current[1];
            //     marked_points_count++;
            // }

            next = move_point(next, increments[direction]);
        }
    }
    free(next);

    matrix[test_barrier[0]][test_barrier[1]] = '.';

    if (steps == 8000) {
        return true;
    } else {
        return false;
    }
}

int run_day6_part2(char** matrix, int height, int width, int start[2]) {
    int marked_points[50000][2];
    int marked_points_count = 1;
    marked_points[0][0]  = start[0];
    marked_points[0][0]  = start[1];
    enum DIRECTION direction = UP;
    int current[2] = { start[0], start[1] };
    int* next = move_point(current, increments[direction]);

    while(is_inbound(next, height, width)) {
        if (matrix[next[0]][next[1]] == '#') {
            direction = (direction + 1) % 4;
            next = move_point(current, increments[direction]);
        } else {
            current[0] = next[0];
            current[1] = next[1];
            matrix[current[0]][current[1]] = 'X';
            bool point_already_marked = false;
            for (int i=0; i < marked_points_count; i++) {
                if (marked_points[i][0] == current[0] && marked_points[i][1] == current[1]) {
                    point_already_marked = true;
                }
            }
            if (point_already_marked == false) {
                marked_points[marked_points_count][0] = current[0];
                marked_points[marked_points_count][1] = current[1];
                marked_points_count++;
            }

            next = move_point(next, increments[direction]);
        }
    }
    free(next);

    int barrier_count = 0;
    for (int i = 1; i < marked_points_count; i++) {
        if (does_it_loop(matrix, height, width, start, marked_points[i])) {
            barrier_count++;
        }
    }

    return barrier_count;
}

int run_day6_part1(char** matrix, int height, int width, int start[2]) {
    // int *marked_points[2] = malloc(sizeof(int[2])*width*height);
    int marked_points[50000][2];
    // int* marked_points[width*height];
    // for (int i = 0; i < width*height; i++)
    //     marked_points[2] = (int*)malloc(2 * sizeof(int));
    int marked_points_count = 1;
    marked_points[0][0]  = start[0];
    marked_points[0][0]  = start[1];

    enum DIRECTION direction = UP;
    int current[2] = { start[0], start[1] };
    int* next = move_point(current, increments[direction]);

    int move_count = 0;
    while(is_inbound(next, height, width)) {
        if (matrix[next[0]][next[1]] == '#') {
            // printf("barrier found: %d,%d\n", next[0], next[1]);
            direction = (direction + 1) % 4;
            next = move_point(current, increments[direction]);
        } else {
            current[0] = next[0];
            current[1] = next[1];
            // printf("next step: %d,%d\n", current[0], current[1]);

            matrix[current[0]][current[1]] = 'X';

            bool point_already_marked = false;
            for (int i=0; i < marked_points_count; i++) {
                if (marked_points[i][0] == current[0] && marked_points[i][1] == current[1]) {
                    point_already_marked = true;
                }
            }

            if (point_already_marked == false) {
                marked_points[marked_points_count][0] = current[0];
                marked_points[marked_points_count][1] = current[1];
                marked_points_count++;
            }


            next = move_point(next, increments[direction]);
            move_count++;
        }
    }
    free(next);

    return marked_points_count;
}

int run_day6()
{
    int DAY = 5;
    // char inputpath[] = "./input/day6.txt";
    char inputpath[] = "./input/day6.txt";
    printf("Day %d\n", DAY);

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

    int start[2]; 

    int index = 0;
    while (content[index] != '\0') {
        char current = content[index];

        index++;
        if (current == '#' || current == '.' || current == '^') {
            if (current == '^') {
                start[0] = row;
                start[1] = col;
            }
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

    printf("\tPart 1: %d\n", run_day6_part1(matrix, matrix_height, matrix_width, start));
    printf("\tPart 2: %d\n", run_day6_part2(matrix, matrix_height, matrix_width, start));

    for (i = 0; i < matrix_height; ++i)
        free(matrix[i]);
    free(matrix);



    return 0;
}
