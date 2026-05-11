#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/day20.h"
#include "../include/matrix_utils.h"

#define BOOLEAN(a) ((a) ? ("true") : ("false"))

int CELL_EMPTY = 0;
int CELL_WALL = 1;
int CELL_VISITED = 2;


typedef struct {
    struct Point items[500000];
    int front;
    int rear;
} PointQueue;

typedef struct {
	Point items[10000];
	int size;
} PointList;

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

// bool is_queue_empty(PointQueue *queue)
// {
//     return (queue->front == queue->rear - 1);
// }

// void initializeQueue(PointQueue *queue)
// {
//     queue->front = -1;
//     queue->rear = 0;
// }

int bfs(Point start, Point finish, int** matrix, int matrix_size) {
	printf("bfs start, %ld, %ld\n", start.row, start.col);
	PointQueue queue = {.front = 0, .rear = 0};
	// initializeQueue(&queue);
	enqueue_point(&queue, start);

	// bool is_empty = is_queue_empty(&queue);

	// printf("queue %d, %d\n", queue.front, queue.rear);
	// printf("rear: %d,%d\n", queue.items[queue.rear].row, queue.items[queue.rear].col);
	// printf("front: %d, %d\n", queue.items[queue.front].row, queue.items[queue.front].col);

	// printf("is_empty?: %s\n", BOOLEAN(queue.rear > queue.front));

	while (queue.rear > queue.front) {
		// printf("queue rear: %d\n", queue.rear);
		Point target = dequeue_point(&queue);
		// printf("Target: %ld,%ld: %ld \n", target.row, target.col, target.rank);
		if (target.row == finish.row && target.col == finish.col) {
			printf("\tFINISHED %d \n", target.rank);
			return target.rank;
		}

		matrix[target.row][target.col] = CELL_VISITED;

		// 
		for (int i = 0; i < 4; i++) {
			Point diff_vec = directions_coord[i];
			Point next_point = {
				.col = target.col + diff_vec.col,
				.row = target.row + diff_vec.row,
				.rank = target.rank + 1,
			};

			int character = matrix[next_point.row][next_point.col];
			// printf("diff_vec: %d, %d, char; %d \n", diff_vec.row, diff_vec.col, character);
			// printf("next_point: %d, %d, char; %d \n", next_point.row, next_point.col, character);

			bool inbound = is_coord_inbound(next_point, matrix_size, matrix_size);
			// printf("inbound: %s\n", BOOLEAN(inbound));
			if (inbound && character == CELL_EMPTY) {
				// printf("enqueue!");
				enqueue_point(&queue, next_point);
			}
		}

		// printf("endloop is_empty?: %s\n", BOOLEAN(queue.rear > queue.front));
	}
	

	return 0;
}


void clean_matrix(int** matrix, int matrix_size) {
	for (int row = 0; row < matrix_size; row++) {
		for (int col = 0; col < matrix_size; col++) {
			if (matrix[row][col] == CELL_VISITED) {
				matrix[row][col] = CELL_EMPTY;
			}
		}
	}
}

void find_all_cheats(int** matrix, int matrix_size, Point start, Point finish) {
	int base_time = bfs(start, finish, matrix, matrix_size);
	printf("base_time %d\n", base_time);
	clean_matrix(matrix, matrix_size);
	int cheat_counter = 0;

	for (int row = 1; row < matrix_size - 1; row++) {
		for (int col = 1; col < matrix_size - 1; col++) {
			if (matrix[row][col] == CELL_WALL) {
				matrix[row][col] = CELL_EMPTY;
				int cheat_time = bfs(start, finish, matrix, matrix_size);
				matrix[row][col] = CELL_WALL;
				clean_matrix(matrix, matrix_size);


				if (base_time - cheat_time >= 100) {
					// printf("cheat_time: %d\n", cheat_time);
					// printf("DIFF: %d\n", base_time - cheat_time);
					cheat_counter++;
				}

			}
		}
	}

	printf("\tPart 1: %d\n", cheat_counter);
} 

// PART 2

typedef struct {
	int rank;
	int count;
} BfsResult;

BfsResult bfs_with_cheat(Point start, Point finish, int** matrix, int matrix_size, int cheat_start_rank) {
	// printf("start: %d, %d\n", start.row, start.col);
	// printf("finish: %d, %d\n", finish.row, finish.col);
	// printf("bfs start, %ld, %ld\n", start.row, start.col);
	// printf("cheat_start_rank: %d\n", cheat_start_rank);
	PointList path = {};

	PointQueue queue = {.front = 0, .rear = 0};
	// initializeQueue(&queue);
	enqueue_point(&queue, start);

	// bool is_empty = is_queue_empty(&queue);

	// printf("queue %d, %d\n", queue.front, queue.rear);
	// printf("rear: %d,%d\n", queue.items[queue.rear].row, queue.items[queue.rear].col);
	// printf("front: %d, %d\n", queue.items[queue.front].row, queue.items[queue.front].col);

	// printf("is_empty?: %s\n", BOOLEAN(queue.rear > queue.front));

	while (queue.rear > queue.front) {
		// printf("queue rear: %d\n", queue.rear);
		Point target = dequeue_point(&queue);
		// printf("Target: %ld,%ld: %ld \n", target.row, target.col, target.rank);
		if (target.row == finish.row && target.col == finish.col) {
			// printf("\tFINISHED %d \n", target.rank);
			return (BfsResult){ .rank = target.rank, .count = target.count };
		}

		matrix[target.row][target.col] = CELL_VISITED;

		bool cheat_enabled = target.rank >= cheat_start_rank && target.rank <= cheat_start_rank + 20;
		// 
		for (int i = 0; i < 4; i++) {
			Point diff_vec = directions_coord[i];
			Point next_point = {
				.col = target.col + diff_vec.col,
				.row = target.row + diff_vec.row,
				.rank = target.rank + 1,
			};

			// printf("before\n");
			// printf("after\n");
			// printf("diff_vec: %d, %d, char; %d \n", diff_vec.row, diff_vec.col, character);
			// printf("next_point: %d, %d, char; %d \n", next_point.row, next_point.col, character);

			bool inbound = is_coord_inbound(next_point, matrix_size, matrix_size);
			// printf("inbound: %s\n", BOOLEAN(inbound));
			if (inbound) {
				int character = matrix[next_point.row][next_point.col];

				if (character == CELL_EMPTY) {
					next_point.count = target.count;
					enqueue_point(&queue, next_point);
				}	
				if (character == CELL_WALL && cheat_enabled) {
					next_point.count = target.count + 1;
					enqueue_point(&queue, next_point);
				}
				// if (character == CELL_VISITED && cheat_enabled) {
				// 	next_point.count = target.count;
				// 	enqueue_point(&queue, next_point);
				// }
			}
		}

		// printf("endloop is_empty?: %s\n", BOOLEAN(queue.rear > queue.front));
	}
	

	return (BfsResult){};
}


void find_longer_cheats(int** matrix, int matrix_size, Point start, Point finish) {
	int base_time = bfs(start, finish, matrix, matrix_size);
	printf("base_time %d\n", base_time);
	clean_matrix(matrix, matrix_size);
	int cheat_counter = 0;

	for (int cheat_start_rank = 0; cheat_start_rank < base_time - 1; cheat_start_rank++) {
		// for (int col = 1; col < matrix_size - 1; col++) {
			// if (matrix[row][col] == CELL_WALL) {
				// matrix[row][col] = CELL_EMPTY;
		// printf("CHEAT_START_RANK: %d\n", cheat_start_rank);

		int** copy_matrix = malloc(sizeof(int*) * matrix_size);
	    for (int row = 0; row < matrix_size; row++) {
	        copy_matrix[row] = malloc(sizeof(int) * matrix_size);
	    }

	    for (int row = 0; row < matrix_size; row++) {
			for (int col = 0; col < matrix_size; col++) {
				copy_matrix[row][col] = matrix[row][col];
			}
		}


		BfsResult result = bfs_with_cheat(start, finish, copy_matrix, matrix_size, cheat_start_rank);
		// matrix[row][col] = CELL_WALL;
		// clean_matrix(matrix, matrix_size);
		for (size_t i = 0; i < matrix_size; ++i)
	        free(copy_matrix[i]);
	    free(copy_matrix);


		printf("RESULT: rank: %d - count: %d\n", result.rank, result.count);
		if (base_time - result.rank >= 50) {
			// printf("DIFF: %d\n", base_time - result.rank);
			// printf("cheat_time: %d\n", cheat_time);
			cheat_counter = cheat_counter + 1;
		}
	}

	printf("\tPart 2: %d\n", cheat_counter);
	// should be 285 in test
	// 9335 too low
	// 10455
	// 9226
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
    		printf("matrix_size  %d\n", matrix_size);

    		matrix = malloc(sizeof(int*) * matrix_size);
		    for (int row = 0; row < matrix_size; row++) {
		        matrix[row] = malloc(sizeof(int) * matrix_size);
		    }
    	}

    	for (int i = 0; i<matrix_size; i++) {
            if (line[i] == '.') {
            	matrix[line_count][i] = CELL_EMPTY; 
            } else if (line[i] == '#') {
            	matrix[line_count][i] = CELL_WALL; 
            } else if (line[i] == 'S') {
            	matrix[line_count][i] = CELL_EMPTY; 
                start = (Point){
                	.row = line_count,
                	.col = i,
                	.rank = 0,
                	.count = 0
                };
            } else if (line[i] == 'E') {
            	matrix[line_count][i] = CELL_EMPTY; 
            	finish = (Point){.row = line_count, .col = i};
            }
    	}

    	printf("line_count %d\n", line_count);
        line_count++;
    }


    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
        	printf(" %2d ", matrix[i][j]);
        }
        printf("\n");
    }

    // find_all_cheats(matrix, matrix_size, start, finish);
    find_longer_cheats(matrix, matrix_size, start, finish);

    for (size_t i = 0; i < matrix_size; ++i)
        free(matrix[i]);
    free(matrix);

    free(line);
    fclose(fp);

    return 0;
}
