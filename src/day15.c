#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix_utils.h"
#include "utils.h"

enum DIRECTION {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

size_t dir_increment[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

bool move_robot_rec(char** matrix, size_t position[2], int direction)
{
    size_t* next = move_point(position, dir_increment[direction]);
    bool can_swap_places = false;

    if (matrix[next[0]][next[1]] == '#') {
        can_swap_places = false;
    }

    if (matrix[next[0]][next[1]] == '.') {
        can_swap_places = true;
    }

    if (matrix[next[0]][next[1]] == 'O' || matrix[next[0]][next[1]] == '[' || matrix[next[0]][next[1]] == ']') {
        can_swap_places = move_robot_rec(matrix, next, direction);
    }

    if (can_swap_places) {
        matrix[next[0]][next[1]] = matrix[position[0]][position[1]];
        matrix[position[0]][position[1]] = '.';
    }

    free(next);
    return can_swap_places;
}

size_t
get_gps_sum(char** matrix, size_t height, size_t width)
{
    size_t result = 0;
    for (size_t row = 0; row < height; row++) {
        for (size_t col = 0; col < width; col++) {
            if (matrix[row][col] == 'O' || matrix[row][col] == '[') {
                result = result + (row * 100 + col);
            }
        }
    }

    return result;
}

size_t
day15part1(char** matrix, size_t size, int moves[30000], size_t moves_count)
{
    // print_char_matrix(size, size, matrix);
    for (size_t i = 0; i < moves_count; i++) {
        size_t* robot_pos = find_char_coord(matrix, size, size, '@');

        int direction = moves[i];
        move_robot_rec(matrix, robot_pos, direction);
        free(robot_pos);
    }

    size_t gps_sum = get_gps_sum(matrix, size, size);

    return gps_sum;
}

// PART 2

void fat_matrix_flood(char** matrix,
    size_t position[2],
    enum DIRECTION direction,
    size_t points[][2],
    size_t* points_count,
    bool* can_move)
{
    // if (matrix[position[0]][position[1]] != '#' &&
    // matrix[position[0]][position[1]] != '.') {
    if (!arr_includes(points, *points_count, position)) {
        points[*points_count][0] = position[0];
        points[*points_count][1] = position[1];
        *points_count = *points_count + 1;
    }

    size_t* next = move_point(position, dir_increment[direction]);
    size_t next_adj[2] = { 0 };
    next_adj[0] = next[0];
    if (matrix[next[0]][next[1]] == '[') {
        next_adj[1] = next[1] + 1;
        assert(matrix[next_adj[0]][next_adj[1]] == ']');
        fat_matrix_flood(matrix, next, direction, points, points_count, can_move);
        fat_matrix_flood(
            matrix, next_adj, direction, points, points_count, can_move);
    } else if (matrix[next[0]][next[1]] == ']') {
        next_adj[1] = next[1] - 1;
        assert(matrix[next_adj[0]][next_adj[1]] == '[');
        fat_matrix_flood(matrix, next, direction, points, points_count, can_move);
        fat_matrix_flood(
            matrix, next_adj, direction, points, points_count, can_move);
    } else if (matrix[next[0]][next[1]] == '#') {
        *can_move = false;
    }
    free(next);
}

void move_fat_flood(char** matrix,
    size_t points[][2],
    size_t index,
    size_t length,
    enum DIRECTION direction)
{
    char current = matrix[points[index][0]][points[index][1]];

    matrix[points[index][0]][points[index][1]] = '.';
    if (index < length - 1) {
        move_fat_flood(matrix, points, index + 1, length, direction);
    }

    size_t* next = move_point(points[index], dir_increment[direction]);

    matrix[next[0]][next[1]] = current;

    free(next);
}

size_t
day15part2(char** matrix,
    size_t height,
    size_t width,
    int moves[30000],
    size_t moves_count)
{
    // print_char_matrix(width, height, matrix);

    for (size_t i = 0; i < moves_count; i++) {
        size_t* robot_pos = find_char_coord(matrix, width, height, '@');

        enum DIRECTION direction = moves[i];
        if (direction == LEFT || direction == RIGHT) {
            move_robot_rec(matrix, robot_pos, direction);
        } else {
            size_t(*points)[2] = malloc(100 * sizeof(size_t[2]));
            size_t points_count = 0;
            bool can_move = true;
            fat_matrix_flood(
                matrix, robot_pos, direction, points, &points_count, &can_move);

            if (can_move) {
                move_fat_flood(matrix, points, 0, points_count, direction);
            }

            free(points);
        }

        // print_char_matrix(width, height, matrix);
        free(robot_pos);
    }

    size_t gps_sum = get_gps_sum(matrix, height, width);

    return gps_sum;
}

int run_day15()
{
    printf("Day 15: Warehouse Woes\n");
    char inputpath[] = "./input/day15.txt";
    // char inputpath[] = "./input/day15-test.txt";

    FILE* fp;
    fp = fopen(inputpath, "r");
    char ch;

    char content[30000] = { 0 };

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

    char** matrix = malloc(sizeof(char*) * matrix_width);
    for (size_t row = 0; row < matrix_width; row++) {
        matrix[row] = malloc(sizeof(char) * matrix_width);
    }

    int moves[30000] = { 0 };
    size_t moves_count = 0;

    size_t col = 0;
    size_t row = 0;
    size_t index = 0;
    size_t start[2] = { 0 };
    while (index <= char_count) {
        char current = content[index];

        index++;
        if (current == '.' || current == '#' || current == 'O' || current == '@') {
            if (current == '@') {
                start[0] = row;
                start[1] = col;
            }

            matrix[row][col] = current;
            if (col == (matrix_width - 1)) {
                row++;
                col = 0;
            } else {
                col++;
            }
        }

        if (current == 'v') {
            moves[moves_count] = DOWN;
            moves_count++;
        }
        if (current == '^') {
            moves[moves_count] = UP;
            moves_count++;
        }
        if (current == '<') {
            moves[moves_count] = LEFT;
            moves_count++;
        }
        if (current == '>') {
            moves[moves_count] = RIGHT;
            moves_count++;
        }
    }

    char** fat_matrix = malloc(sizeof(char*) * matrix_width);
    for (size_t row = 0; row < matrix_width; row++) {
        fat_matrix[row] = malloc(sizeof(char) * matrix_width * 2);
    }

    for (size_t row = 0; row < matrix_width; row++) {
        for (size_t col = 0; col < matrix_width; col++) {
            if (matrix[row][col] == '#') {
                fat_matrix[row][col * 2] = '#';
                fat_matrix[row][col * 2 + 1] = '#';
            } else if (matrix[row][col] == '.') {
                fat_matrix[row][col * 2] = '.';
                fat_matrix[row][col * 2 + 1] = '.';
            } else if (matrix[row][col] == 'O') {
                fat_matrix[row][col * 2] = '[';
                fat_matrix[row][col * 2 + 1] = ']';
            }
            if (matrix[row][col] == '@') {
                fat_matrix[row][col * 2] = '@';
                fat_matrix[row][col * 2 + 1] = '.';
            }
        }
    }

    printf("\tPart 1: %ld\n",
        day15part1(matrix, matrix_width, moves, moves_count));
    printf(
        "\tPart 2: %ld\n",
        day15part2(fat_matrix, matrix_width, matrix_width * 2, moves, moves_count));

    for (size_t i = 0; i < matrix_width; ++i)
        free(matrix[i]);
    free(matrix);

    for (size_t i = 0; i < matrix_width; ++i)
        free(fat_matrix[i]);
    free(fat_matrix);

    return 0;
}
