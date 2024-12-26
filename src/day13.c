#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

struct Machine {
  long long a_x;
  long long a_y;
  long long b_x;
  long long b_y;
  long long x_loc;
  long long y_loc;
};

void print_machine_data(struct Machine machine) {
  printf("A: x+%lld, y+%lld\n", machine.a_x, machine.a_y);
  printf("B: x+%lld, y+%lld\n", machine.b_x, machine.b_y);
  printf("Prize: X=%lld, Y=%lld\n", machine.x_loc, machine.y_loc);
  printf("\n");
}

long long get_b(long long a, struct Machine machine) {
  assert(machine.a_x > 0 && machine.b_y > 0 && machine.a_y > 0 &&
         machine.b_x > 0);
  return (machine.x_loc - (a * machine.a_x)) / machine.b_x;
}

long long get_a(struct Machine machine) {
  assert(machine.a_x > 0 && machine.b_y > 0 && machine.a_y > 0 &&
         machine.b_x > 0);
  return (machine.x_loc * machine.b_y - machine.y_loc * machine.b_x) /
         ((machine.a_x * machine.b_y) - (machine.a_y * machine.b_x));
};

bool check_machine(struct Machine machine, long long a, long long b) {
  if (a * machine.a_x + b * machine.b_x == machine.x_loc &&
      a * machine.a_y + b * machine.b_y == machine.y_loc) {
    return true;
  } else {
    return false;
  }
}

long long day13part1(struct Machine list[500], int machine_count) {
  long long token_sum = 0;

  for (int i = 0; i < machine_count; i++) {
    long long a = get_a(list[i]);
    long long b = get_b(a, list[i]);

    if (check_machine(list[i], a, b)) {
      token_sum = token_sum + a * 3 + b;
    }
  }

  return token_sum;
}

long long day13part2(struct Machine list[500], int machine_count) {
  long long token_sum = 0;
  long long bullshit = 10000000000000;

  for (int i = 0; i < machine_count; i++) {
    struct Machine corrected_machine = list[i];
    corrected_machine.x_loc = list[i].x_loc + bullshit;
    corrected_machine.y_loc = list[i].y_loc + bullshit;

    long long a = get_a(corrected_machine);
    long long b = get_b(a, corrected_machine);

    if (check_machine(corrected_machine, a, b)) {
      token_sum = token_sum + a * 3 + b;
    }
  }
  return token_sum;
}

int run_day13() {
  // char inputpath[] = "./input/day13-test.txt";
  char inputpath[] = "./input/day13.txt";
  printf("Day 13: Claw Contraption\n");

  char* line = NULL;
  size_t len = 0;
  ssize_t read;

  struct Machine list[500] = {0};
  int machine_count = 0;

  FILE* fp;
  fp = fopen(inputpath, "r");

  while ((read = getline(&line, &len, fp)) != -1) {
    if (find_character_index(line, 'A') > -1) {
      // parse Button A string
      size_t x_index = find_character_index(line, 'X');
      size_t comma_index = find_character_index(line, ',');
      size_t y_index = find_character_index(line, 'Y');

      assert(x_index > 0 && y_index > 0 && comma_index > 0);

      char* x_number = get_substring(x_index + 2, comma_index, line);
      list[machine_count].a_x = atol(x_number);
      free(x_number);

      char* y_number = get_substring(y_index + 2, read - 1, line);
      list[machine_count].a_y = atol(y_number);
      free(y_number);
    }

    if (find_character_index(line, 'B') > -1) {
      // parse Button B string
      size_t x_index = find_character_index(line, 'X');
      size_t comma_index = find_character_index(line, ',');
      size_t y_index = find_character_index(line, 'Y');

      assert(x_index > 0 && y_index > 0 && comma_index > 0);

      char* x_number = get_substring(x_index + 2, comma_index, line);
      list[machine_count].b_x = atol(x_number);
      ;
      free(x_number);

      char* y_number = get_substring(y_index + 2, read - 1, line);
      list[machine_count].b_y = atol(y_number);
      free(y_number);
    }

    if (find_character_index(line, 'z') > -1) {
      // parse Prize string
      size_t x_index = find_character_index(line, 'X');
      size_t comma_index = find_character_index(line, ',');
      size_t y_index = find_character_index(line, 'Y');

      assert(x_index > 0 && y_index > 0 && comma_index > 0);

      char* x_number = get_substring(x_index + 2, comma_index, line);
      list[machine_count].x_loc = atol(x_number);
      free(x_number);

      char* y_number = get_substring(y_index + 2, read - 1, line);
      list[machine_count].y_loc = atol(y_number);
      free(y_number);

      machine_count++;
    }
  }
  fclose(fp);
  free(line);

  // for (int i = 0; i<machine_count; i++) {
  //   print_machine_data(list[i]);
  // }

  // struct Day12Result result = analyze_day12_matrix(matrix, matrix_width,
  // matrix_height);
  printf("\tPart 1: %lld\n", day13part1(list, machine_count));
  printf("\tPart 2: %lld\n", day13part2(list, machine_count));

  return 0;
}