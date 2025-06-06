#include "day6.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix_utils.h"

enum DIRECTION {
    UP,
    RIGHT,
    DOWN,
    LEFT,
};

// row, col
size_t patrol_inc[4][2] = {
    { -1, 0 },
    { 0, 1 },
    { 1, 0 },
    { 0, -1 },
};

bool does_it_loop(char** matrix,
    size_t height,
    size_t width,
    size_t start[2],
    size_t* test_barrier)
{
    matrix[test_barrier[0]][test_barrier[1]] = '#';
    // free(test_barrier);

    size_t marked_points[50000][2] = { 0 };
    size_t marked_points_count = 1;
    size_t twice_visited_points = 0;

    enum DIRECTION direction = UP;
    size_t current[2] = { start[0], start[1] };
    size_t* next = move_point(current, patrol_inc[direction]);

    while (is_inbound(next, height, width) && twice_visited_points < marked_points_count) {
        if (matrix[next[0]][next[1]] == '#') {
            direction = (direction + 1) % 4;
            size_t* nextnext = move_point(current, patrol_inc[direction]);
            next[0] = nextnext[0];
            next[1] = nextnext[1];
            free(nextnext);
        } else {
            current[0] = next[0];
            current[1] = next[1];
            if (matrix[current[0]][current[1]] == 'X') {
                twice_visited_points++;
            } else {
                twice_visited_points = 0;
                matrix[current[0]][current[1]] = 'X';
                marked_points[marked_points_count][0] = current[0];
                marked_points[marked_points_count][1] = current[1];
                marked_points_count++;
            }

            size_t* nextnext = move_point(next, patrol_inc[direction]);
            next[0] = nextnext[0];
            next[1] = nextnext[1];
            free(nextnext);
        }
    }
    free(next);

    // clear
    for (size_t i = 0; i < marked_points_count; i++) {
        matrix[marked_points[i][0]][marked_points[i][1]] = '.';
    }
    matrix[test_barrier[0]][test_barrier[1]] = '.';

    // printf("twice_visited_points: %ld / %ld \n", twice_visited_points,
    // marked_points_count);
    if (twice_visited_points == marked_points_count) {
        return true;
    } else {
        return false;
    }
}

int run_day6_part2(char** matrix, size_t height, size_t width, size_t start[2])
{
    size_t marked_points[50000][2] = { 0 };
    size_t marked_points_count = 1;
    marked_points[0][0] = start[0];
    marked_points[0][0] = start[1];
    enum DIRECTION direction = UP;
    size_t current[2] = { start[0], start[1] };
    size_t* next = move_point(current, patrol_inc[direction]);

    while (is_inbound(next, height, width)) {
        if (matrix[next[0]][next[1]] == '#') {
            // printf("barrier found: %d,%d\n", next[0], next[1]);
            direction = (direction + 1) % 4;
            size_t* nextnext = move_point(current, patrol_inc[direction]);
            next[0] = nextnext[0];
            next[1] = nextnext[1];
            free(nextnext);
        } else {
            current[0] = next[0];
            current[1] = next[1];
            // printf("next step: %d,%d\n", current[0], current[1]);

            // matrix[current[0]][current[1]] = 'X';

            bool point_already_marked = false;
            for (size_t i = 0; i < marked_points_count; i++) {
                if (marked_points[i][0] == current[0] && marked_points[i][1] == current[1]) {
                    point_already_marked = true;
                }
            }

            if (point_already_marked == false) {
                marked_points[marked_points_count][0] = current[0];
                marked_points[marked_points_count][1] = current[1];
                marked_points_count++;
            }

            size_t* nextnext = move_point(next, patrol_inc[direction]);
            next[0] = nextnext[0];
            next[1] = nextnext[1];
            free(nextnext);
        }
    }
    free(next);

    int barrier_count = 0;
    for (size_t i = 1; i < marked_points_count; i++) {
        if (does_it_loop(matrix, height, width, start, marked_points[i])) {
            barrier_count++;
        }
    }

    return barrier_count;
}

int run_day6_part1(char** matrix, size_t height, size_t width, size_t start[2])
{
    size_t marked_points[50000][2] = { 0 };
    size_t marked_points_count = 1;
    marked_points[0][0] = start[0];
    marked_points[0][0] = start[1];

    enum DIRECTION direction = UP;
    size_t current[2] = { start[0], start[1] };
    size_t* next = move_point(current, patrol_inc[direction]);

    while (is_inbound(next, height, width)) {
        if (matrix[next[0]][next[1]] == '#') {
            // printf("barrier found: %d,%d\n", next[0], next[1]);
            direction = (direction + 1) % 4;
            size_t* nextnext = move_point(current, patrol_inc[direction]);
            next[0] = nextnext[0];
            next[1] = nextnext[1];
            free(nextnext);
        } else {
            current[0] = next[0];
            current[1] = next[1];
            // printf("next step: %d,%d\n", current[0], current[1]);

            // matrix[current[0]][current[1]] = 'X';

            bool point_already_marked = false;
            for (size_t i = 0; i < marked_points_count; i++) {
                if (marked_points[i][0] == current[0] && marked_points[i][1] == current[1]) {
                    point_already_marked = true;
                }
            }

            if (point_already_marked == false) {
                marked_points[marked_points_count][0] = current[0];
                marked_points[marked_points_count][1] = current[1];
                marked_points_count++;
            }

            size_t* nextnext = move_point(next, patrol_inc[direction]);
            next[0] = nextnext[0];
            next[1] = nextnext[1];
            free(nextnext);
        }
    }
    free(next);

    return marked_points_count;
}

int run_day6()
{
    printf("Day 6: Guard Gallivant\n");
    // char inputpath[] = "./input/day6.txt";
    char inputpath[] = "./input/day6.txt";

    FILE* fp;
    fp = fopen(inputpath, "r");
    char ch;

    char content[1000000] = { 0 };

    size_t i = 0;
    size_t matrix_size = 0;
    size_t line = 1;
    do {
        ch = fgetc(fp);
        content[i] = ch;
        if (ch == '\n') {
            if (line == 1) {
                matrix_size = i;
            }
            line++;
        }
        i++;
    } while (ch != EOF);
    fclose(fp);

    assert(matrix_size > 1);

    char** matrix = malloc(sizeof(char*) * matrix_size);
    for (size_t row = 0; row < matrix_size; row++) {
        matrix[row] = malloc(sizeof(char) * matrix_size);
    }

    for (size_t row = 0; row < matrix_size; row++) {
        for (size_t col = 0; col < matrix_size; col++) {
            matrix[row][col] = '.';
        }
    }

    size_t col = 0;
    size_t row = 0;

    size_t start[2];

    size_t index = 0;
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
            if (col == (matrix_size - 1)) {
                row++;
                col = 0;
            } else {
                col++;
            }
        }
    }

    printf("\tPart 1: %d\n",
        run_day6_part1(matrix, matrix_size, matrix_size, start));
    printf("\tPart 2: %d\n",
        run_day6_part2(matrix, matrix_size, matrix_size, start));

    for (size_t i = 0; i < matrix_size; ++i)
        free(matrix[i]);
    free(matrix);

    return 0;
}
