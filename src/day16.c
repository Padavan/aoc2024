#include "matrix_utils.h"
#include "utils.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

const size_t NOT_VISITED = 99999;
const size_t WALL = -1;
const size_t SUCCESSFULL_CELL = 55555555;
const int PARTANSWER = 11048;

enum DIRECTION { UP, DOWN, LEFT, RIGHT };

struct DAY16Result {
  size_t part1;
  size_t part2;
};


typedef struct {
  struct Point arr[100];
  int top;
} Stack;

void initialize(Stack *stack) {
    stack->top = -1;  
}

bool isempty(Stack *stack){
   return stack->top == -1;
}

bool isfull(Stack *stack) {
  return stack->top == 100;
}

void push(Stack *stack, struct Point value) {
    if (isfull(stack)) {
        printf("Stack Overflow\n");
        return;
    }
    stack->arr[++stack->top] = value;
}

struct Point pop(Stack *stack) {
    struct Point popped = stack->arr[stack->top];
    stack->top--;
    return popped;
}



bool flood(size_t** matrix, size_t size, struct Point target, struct Point end, enum DIRECTION direction, size_t tiles[1000][2], int turns) {
  bool is_best = false;
  if (target.row == end.row && target.col == end.col) {
    printf("BBB: %ld\n", matrix[target.row][target.col]);
    printf("CCC: %d\n", turns);
    // printf()
    long int result = matrix[target.row][target.col] + (turns * 1000);
    printf("DDD: %ld\n", result);
    printf("   \n");
    // *count = 0;
    // matrix[target.row][target.col] = SUCCESSFULL_CELL;
    return true;
  }

  size_t current_score = matrix[target.row][target.col];
  // printf("flood current_score: %ld, target: %ld, %ld \n", current_score, target.row, target.col);
  // printf("flood direction: %d\n", direction);

  // --- same direction
  struct Point s_next = move_coord(target, directions_coord[direction]);
  bool is_snext_wall = matrix[s_next.row][s_next.col] == (unsigned long) -1;
  bool is_snext_best = false;
  bool is_snext_points_higher = matrix[s_next.row][s_next.col] > current_score;

  if (!is_snext_wall && is_snext_points_higher) {
    matrix[s_next.row][s_next.col] = current_score + 1;
    is_snext_best = flood(matrix, size, s_next, end, direction, tiles, turns);
    // if (!is_snext_best) {
    //   matrix[s_next.row][s_next.col] = NOT_VISITED;
    // };
  }

  // --- check clock-wise direction
  int cw_direction = (direction - 1) % 4;
  struct Point cw_next = move_coord(target, directions_coord[cw_direction]);
  bool is_next_cwcell_wall = matrix[cw_next.row][cw_next.col] == (unsigned long) -1;
  bool is_next_cw_points_highter = matrix[cw_next.row][cw_next.col] > current_score;
  bool is_next_cwcell_best = false;
  if (!is_next_cwcell_wall && is_next_cw_points_highter) {
    matrix[cw_next.row][cw_next.col] = current_score + 1;
    is_next_cwcell_wall = flood(matrix, size, cw_next, end, cw_direction, tiles, turns + 1);
    // if (!is_next_cwcell_best) {
    //   matrix[cw_next.row][cw_next.col] = NOT_VISITED;
    // }
  }

  // -- check counter-clock-wise direcion
  int ccw_direction = (direction + 1) % 4;
  struct Point ccw_next = move_coord(target, directions_coord[ccw_direction]);
  bool is_ccwcell_wall = matrix[ccw_next.row][ccw_next.col] == (unsigned long) -1; 
  bool is_ccwcell_best = false;
  bool is_ccwcell_higher_points = matrix[ccw_next.row][ccw_next.col] > current_score;
  // bool is_ccwcell_is_best = matrix[ccw_next.row][ccw_next.col] == SUCCESSFULL_CELL;
  // printf("is_ccwcell_higher_points %s \n", is_ccwcell_higher_points ? "true" : "false");
  // printf("is_ccwcell_wall: %s \n", is_ccwcell_wall ? "true": "false");
  // printf("ccw_score: %ld \n", matrix[ccw_next.row][ccw_next.col]);
  // printf("ccw_direction: %d \n", ccw_direction);
  if (!is_ccwcell_wall && is_ccwcell_higher_points) {
    // matrix[target.row][target.col] = matrix[target.row][target.col] + 1;
    matrix[ccw_next.row][ccw_next.col] = current_score + 1;
    // printf("check ccw\n");
    // step = step + 1;
    is_ccwcell_best = flood(matrix, size, ccw_next, end, ccw_direction, tiles, turns + 1);

    // if (!is_ccwcell_best) {
    //   matrix[ccw_next.row][ccw_next.col] = NOT_VISITED;
    // };
  }

  // if (is_best) {
  //   // tiles[*count].row = target[0];
  //   // tiles[*count].col = target.col;
  //   *count = *count + 1;
  //   // matrix[target[0]][target[1]] = SUCCESSFULL_CELL; // mark successful cell
  // }

  // return is_ccwcell_best || is_next_cwcell_best || is_snext_best;
  return false;
}



struct DAY16Result get_lowest_labyrint_score(size_t** matrix, size_t size, size_t start[2], size_t end[2]) {
  print_int_matrix(size, size, matrix);
  enum DIRECTION start_direction = RIGHT;
  struct Point start_point = {start[0], start[1]};
  struct Point end_point = {end[0], end[1]};

  matrix[start[0]][start[1]] = 0;
  size_t best_tiles[1000][2] = { 0 };
  size_t best_tiles_count = 0;


  Stack stack;
  initialize(&stack);  
  push(&stack, start_point);
  flood(matrix, size, start_point, end_point, start_direction, best_tiles, 0);
  print_int_matrix(size, size, matrix);

  printf("best_tiles_count: %ld\n", best_tiles_count);
  // traverse_best_tiles(matrix, size, end, best_tiles, &best_tiles_count);

  // printf("best_tiles_count %ld\n", best_tiles_count);

  // for (size_t i = 0; i < best_tiles_count; i++) {
  //   matrix[best_tiles[i][0]][best_tiles[i][1]] = 99999999;
  // }
  int counter = 0;
  for (size_t row = 0; row < size; row++) {
    for (size_t col = 0; col < size; col++) {
      // printf("shit : %ld, \n", matrix[row][col]);
      if (matrix[row][col] == SUCCESSFULL_CELL) {
        counter++;
      }
    }
  }

  printf("counter %d \n", counter);

  print_int_matrix(size, size, matrix);

  // printf("end score: %ld \n", matrix[end[0]][end[1]]);
  struct DAY16Result result = {matrix[end[0]][end[1]], best_tiles_count};
  return result;
}

int run_day16() {
  printf("Day 16: Reindeer Maze\n");
  // char inputpath[] = "./input/day16.txt";
  char inputpath[] = "./input/day16-test.txt";

  FILE* fp;
  fp = fopen(inputpath, "r");
  char ch;

  char content[30000] = {0};

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

  size_t** matrix = malloc(sizeof(size_t*) * matrix_width);
  for (size_t row = 0; row < matrix_width; row++) {
    matrix[row] = malloc(sizeof(size_t) * matrix_width);
  }

  // int moves[30000] = {0};
  // size_t moves_count = 0;

  size_t col = 0;
  size_t row = 0;
  size_t index = 0;
  size_t start[2] = {0};
  size_t end[2] = {0};
  while (index <= char_count) {
    char current = content[index];

    index++;
    if (current == '.' || current == '#') {
      matrix[row][col] = current == '.' ? NOT_VISITED : WALL;
      if (col == (matrix_width - 1)) {
        row++;
        col = 0;
      } else {
        col++;
      }
    }
    if (current == 'S' || current == 'E') {
      if (current == 'S') {
        start[0] = row;
        start[1] = col;
        matrix[row][col] = 0;
      }

      if (current == 'E') {
        end[0] = row;
        end[1] = col;
        matrix[row][col] = NOT_VISITED;
      }

      if (col == (matrix_width - 1)) {
        row++;
        col = 0;
      } else {
        col++;
      }
    }
  }

  struct DAY16Result result = get_lowest_labyrint_score(matrix, matrix_width, start, end);
  printf("\tPart 1: %ld\n", result.part1);
  printf("\tPart 2: %ld\n", result.part2);
  // 540 to low
  // 631 to high

  for (size_t i = 0; i < matrix_width; ++i) free(matrix[i]);
  free(matrix);

  return 0;
}