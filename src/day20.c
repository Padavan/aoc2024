#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/day20.h"
#include "../include/matrix_utils.h"

#define BOOLEAN(a) ((a) ? ("true") : ("false"))

int CELL_EMPTY = -1;
int CELL_WALL = -2;
int CELL_VISITED = 2;

// GETTING PATH STRUCTS
typedef struct {
    Point items[20000];
    int size;
} PointList;

typedef struct {
    PointList* items;
    int front;
    int rear;
} PointPathQueue;

PointList dequeue_path(PointPathQueue* queue)
{
    PointList target = queue->items[queue->front];
    queue->front++;
    return target;
}

void enqueue_path(PointPathQueue* queue, PointList target)
{
    queue->items[queue->rear] = target;
    queue->rear++;
    return;
}

// MAPPING STRUCTS
typedef struct {
    Point items[100000];
    int front;
    int rear;
} PointQueue;

Point dequeue_point(PointQueue* queue)
{
    Point target = queue->items[queue->front];
    queue->front++;
    return target;
}

void enqueue_point(PointQueue* queue, Point target)
{
    queue->items[queue->rear] = target;
    queue->rear++;
    return;
}

PointList bfs(Point start, Point finish, int** matrix, int matrix_size)
{

    PointList initial_path = {};
    initial_path.items[0] = start;
    initial_path.size = 1;

    PointPathQueue queue = {
        .items = malloc(sizeof(PointList) * 10000),
        .front = 0,
        .rear = 0
    };
    enqueue_path(&queue, initial_path);

    while (queue.rear > queue.front) {
        PointList target = dequeue_path(&queue);
        Point target_node = target.items[target.size - 1];

        if (target_node.row == finish.row && target_node.col == finish.col) {
            return target;
        }

        matrix[target_node.row][target_node.col] = CELL_VISITED;

        for (int i = 0; i < 4; i++) {
            Point diff_vec = directions_coord[i];
            Point next_point = {
                .col = target_node.col + diff_vec.col,
                .row = target_node.row + diff_vec.row,
            };

            int character = matrix[next_point.row][next_point.col];
            bool inbound = is_coord_inbound(next_point, matrix_size, matrix_size);
            if (inbound && character == CELL_EMPTY) {
                PointList newPath = target;
                newPath.items[target.size] = next_point;
                newPath.size++;
                enqueue_path(&queue, newPath);
            }
        }

        // printf("endloop is_empty?: %s\n", BOOLEAN(queue.rear > queue.front));
    }

    free(queue.items);

    return initial_path;
}

void clean_matrix(int** matrix, int matrix_size)
{
    for (int row = 0; row < matrix_size; row++) {
        for (int col = 0; col < matrix_size; col++) {
            if (matrix[row][col] == CELL_VISITED) {
                matrix[row][col] = CELL_EMPTY;
            }
        }
    }
}

void map_matrix(int** matrix, int matrix_size, Point finish)
{
    PointQueue queue = { .front = 0, .rear = 0 };
    finish.rank = 0;
    enqueue_point(&queue, finish);

    while (queue.rear > queue.front) {
        Point target = dequeue_point(&queue);
        // printf("Target: %d,%d \n", target.row, target.col);
        matrix[target.row][target.col] = target.rank;
        for (int i = 0; i < 4; i++) {
            Point diff_vec = directions_coord[i];
            Point next_point = {
                .col = target.col + diff_vec.col,
                .row = target.row + diff_vec.row,
                .rank = target.rank + 1,
            };

            int character = matrix[next_point.row][next_point.col];
            // printf("Target: %d,%d \n", next_point.row, next_point.col);
            bool inbound = is_coord_inbound(next_point, matrix_size, matrix_size);
            // printf("inbound: %s\n", BOOLEAN(inbound));
            if (inbound && character == CELL_EMPTY) {
                enqueue_point(&queue, next_point);
            }
        }
    }
}

void find_all_cheats(int** matrix, int matrix_size, Point start, Point finish)
{
    PointList base_path = bfs(start, finish, matrix, matrix_size);
    clean_matrix(matrix, matrix_size);
    map_matrix(matrix, matrix_size, finish);

    // PART 1
    int DISTANCE = 2;
    int cheat_counter_1 = 0;

    for (int step = 0; step < base_path.size - 1; step++) {
        Point start_jump = base_path.items[step];
        int start_jump_value = matrix[start_jump.row][start_jump.col];

        for (int row = -DISTANCE; row <= DISTANCE; row++) {
            int used = DISTANCE - abs(row);
            for (int col = -used; col <= used; col++) {
                // printf("col: %d, row: %d\n", row, col);
                Point end_jump = {
                    .row = start_jump.row + row,
                    .col = start_jump.col + col,
                };
                if (is_coord_inbound(end_jump, matrix_size, matrix_size) && matrix[end_jump.row][end_jump.col] != CELL_WALL) {
                    int end_jump_value = matrix[end_jump.row][end_jump.col];

                    int manhattan_distance = abs(row) + abs(col);
                    int diff = start_jump_value - manhattan_distance - end_jump_value;
                    if (diff >= 100) {
                        cheat_counter_1++;
                    }
                }
            }
        }
    }

    printf("\tPart 1: %d\n", cheat_counter_1);

    DISTANCE = 20;
    int cheat_counter_2 = 0;

    for (int step = 0; step < base_path.size - 1; step++) {
        Point start_jump = base_path.items[step];
        int start_jump_value = matrix[start_jump.row][start_jump.col];

        for (int row = -DISTANCE; row <= DISTANCE; row++) {
            int used = DISTANCE - abs(row);
            for (int col = -used; col <= used; col++) {
                // printf("col: %d, row: %d\n", row, col);
                Point end_jump = {
                    .row = start_jump.row + row,
                    .col = start_jump.col + col,
                };
                if (is_coord_inbound(end_jump, matrix_size, matrix_size) && matrix[end_jump.row][end_jump.col] != CELL_WALL) {
                    int end_jump_value = matrix[end_jump.row][end_jump.col];

                    int manhattan_distance = abs(row) + abs(col);
                    int diff = start_jump_value - manhattan_distance - end_jump_value;
                    if (diff >= 100) {
                        cheat_counter_2++;
                    }
                }
            }
        }
    }

    printf("\tPart 2: %d\n", cheat_counter_2);
    // 44 in test
}

int run_day20()
{
    printf("Day 20: Race Condition\n");
    char inputpath[] = "./input/day20.txt";

    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    FILE* fp;
    fp = fopen(inputpath, "r");

    int** matrix;
    int matrix_size = 0;
    Point start;
    Point finish;

    int line_count = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        if (line_count == 0) {
            matrix_size = strlen(line) - 1;

            matrix = malloc(sizeof(int*) * matrix_size);
            for (int row = 0; row < matrix_size; row++) {
                matrix[row] = malloc(sizeof(int) * matrix_size);
            }
        }

        for (int i = 0; i < matrix_size; i++) {
            if (line[i] == '.') {
                matrix[line_count][i] = CELL_EMPTY;
            } else if (line[i] == '#') {
                matrix[line_count][i] = CELL_WALL;
            } else if (line[i] == 'S') {
                matrix[line_count][i] = CELL_EMPTY;
                start = (Point) {
                    .row = line_count,
                    .col = i
                };
            } else if (line[i] == 'E') {
                matrix[line_count][i] = CELL_EMPTY;
                finish = (Point) { .row = line_count, .col = i };
            }
        }

        // printf("line_count %d\n", line_count);
        line_count++;
    }

    find_all_cheats(matrix, matrix_size, start, finish);

    for (int i = 0; i < matrix_size; ++i)
        free(matrix[i]);
    free(matrix);

    free(line);
    fclose(fp);

    return 0;
}
