#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/matrix_utils.h"
#include "../include/utils.h"

const size_t CELL = 0;
const size_t CORRUPTED = -1;
// const size_t VISITED = 2;
const size_t HARD_CUTOFF = 1024;
// const size_t HARD_CUTOFF = 12;

struct DynArray {
    struct Point items[5000];
    int front;
    int rear;
};

struct Point dequeue(struct DynArray* dyn_array)
{
    struct Point target = dyn_array->items[dyn_array->front];
    dyn_array->front++;
    return target;
}

void enqueue(struct DynArray* dyn_array, struct Point target)
{
    dyn_array->items[dyn_array->rear] = target;
    dyn_array->rear++;
    return;
}

//////// PART1 /////////

int get_minimum_steps(struct Point list[5000], size_t grid_size, size_t cutoff)
{

    size_t** matrix = malloc(sizeof(size_t*) * grid_size);
    for (size_t row = 0; row < grid_size; row++) {
        matrix[row] = malloc(sizeof(size_t) * grid_size);
    }

    for (size_t row = 0; row < grid_size; row++) {
        for (size_t col = 0; col < grid_size; col++) {
            matrix[row][col] = 0;
        }
    }

    for (size_t i = 0; i < cutoff; i++) {
        matrix[list[i].row][list[i].col] = CORRUPTED;
    }

    struct Point start = { 0, 0 };
    struct Point end = { grid_size - 1, grid_size - 1 };

    struct DynArray queue = { { start }, 0, 1 };

    int minimum_steps = -1;
    while (queue.rear > queue.front && minimum_steps == -1) {
        struct Point target = dequeue(&queue);
        int target_steps = matrix[target.row][target.col];

        if (target.row == end.row && target.col == end.col) {
            minimum_steps = target_steps;
            continue;
        }

        for (int i = 0; i < 4; i++) {
            struct Point next_target = move_coord(target, directions_coord[i]);

            if (is_coord_inbound(next_target, grid_size, grid_size) && matrix[next_target.row][next_target.col] == CELL) {
                matrix[next_target.row][next_target.col] = target_steps + 1;
                enqueue(&queue, next_target);
            }
        }
    }

    for (size_t i = 0; i < grid_size; ++i) {
        free(matrix[i]);
    }
    free(matrix);

    return minimum_steps;
}

///////// PART 2

struct Point find_first_prevntable_byte(struct Point list[5000], size_t grid_size)
{

    size_t cutoff_candidate = HARD_CUTOFF;

    int steps = get_minimum_steps(list, grid_size, cutoff_candidate);

    while (steps != -1) {
        cutoff_candidate++;
        steps = get_minimum_steps(list, grid_size, cutoff_candidate);
    }

    return list[cutoff_candidate - 1];
}

int run_day18()
{
    printf("Day 18: RAM Run\n");
    // char inputpath[] = "./input/day18-test.txt";
    char inputpath[] = "./input/day18.txt";

    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    FILE* fp;
    fp = fopen(inputpath, "r");

    struct Point byte_position_list[5000] = {};
    int count = 0;

    while ((read = getline(&line, &len, fp)) != -1) {
        int comma_index = find_character_index(line, ',');

        if (comma_index > 0) {
            char* s_col = get_substring(0, comma_index, line);
            char* s_row = get_substring(comma_index + 1, read, line);

            struct Point new_point = { atoi(s_row), atoi(s_col) };
            free(s_col);
            free(s_row);
            byte_position_list[count] = new_point;
            count++;
        }
    }

    free(line);
    fclose(fp);

    int result1 = get_minimum_steps(byte_position_list, 71, HARD_CUTOFF);
    struct Point result2 = find_first_prevntable_byte(byte_position_list, 71);

    printf("\tPart 1: %d\n", result1);
    // 344
    printf("\tPart 2: %ld,%ld\n", result2.col, result2.row);

    return 0;
}
