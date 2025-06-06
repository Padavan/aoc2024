#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

struct ToiletGuard {
    int id;
    int start_x;
    int start_y;
    int velocity_x;
    int velocity_y;
    int x;
    int y;
};

void print_guard(struct ToiletGuard guard)
{
    printf("guard %d\n", guard.id);
    printf("Start position: %4d \t %4d\n", guard.start_x, guard.start_y);
    printf("Velocity:       %4d \t %4d\n", guard.velocity_x, guard.velocity_y);
    printf("             x: %4d, y: %d\n", guard.x, guard.y);
    printf("\n");
}

int day14part2(struct ToiletGuard guard_list[500], int guard_count)
{
    int width = 101;
    int height = 103;

    int seconds = 0;

    while (seconds < 100000000) {
        int** matrix = (int**)malloc(sizeof(int*) * height);
        for (int row = 0; row < height; row++) {
            matrix[row] = (int*)malloc(sizeof(int) * width);
        }

        // nullify. check if it can be deleted
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                matrix[row][col] = 0;
            }
        }

        int* distribution = malloc(sizeof(int) * width);
        for (int i = 0; i < width; i++) {
            distribution[i] = 0;
        }

        for (int i = 0; i < guard_count; i++) {
            int x = (guard_list[i].start_x + (guard_list[i].velocity_x * seconds)) % width;
            if (x < 0) {
                x = width + x;
            }
            guard_list[i].x = x;
            distribution[x] = distribution[x] + 1;

            int y = (guard_list[i].start_y + (guard_list[i].velocity_y * seconds)) % height;
            if (y < 0) {
                y = height + y;
            }
            guard_list[i].y = y;

            matrix[guard_list[i].y][guard_list[i].x] = matrix[guard_list[i].y][guard_list[i].x] + 1;
        }

        bool duplicated_positions = false;
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                if (matrix[row][col] > 1) {
                    duplicated_positions = true;
                    break;
                }
            }
        }

        for (int i = 0; i < height; ++i)
            free(matrix[i]);
        free(matrix);
        free(distribution);

        if (duplicated_positions == false) {
            // no duplicated positions;
            return seconds;
        }

        seconds++;
    }

    return 0;
}

int day14part1(struct ToiletGuard guard_list[500], int guard_count)
{
    int width = 101;
    int height = 103;
    int seconds = 100;

    int** matrix = (int**)malloc(sizeof(int*) * height);
    for (int row = 0; row < height; row++) {
        matrix[row] = (int*)malloc(sizeof(int) * width);
    }

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            matrix[row][col] = 0;
        }
    }

    for (int i = 0; i < guard_count; i++) {
        // int i = 10;
        int x = (guard_list[i].start_x + (guard_list[i].velocity_x * seconds)) % width;
        if (x < 0) {
            x = width + x;
        }
        guard_list[i].x = x;

        int y = (guard_list[i].start_y + (guard_list[i].velocity_y * seconds)) % height;
        if (y < 0) {
            y = height + y;
        }
        guard_list[i].y = y;
    }

    int info[4] = { 0 };

    int y_center = height / 2;
    int x_center = width / 2;
    // printf("x_center %d, y_center %d\n", x_center, y_center);
    for (int i = 0; i < guard_count; i++) {
        struct ToiletGuard current = guard_list[i];
        if (current.x < x_center && current.y < y_center) {
            info[0] = info[0] + 1;
        }
        if (current.x < x_center && current.y > y_center) {
            info[1] = info[1] + 1;
        }
        if (current.x > x_center && current.y < y_center) {
            info[2] = info[2] + 1;
        }
        if (current.x > x_center && current.y > y_center) {
            info[3] = info[3] + 1;
        }

        // print_guard(guard_list[i]);
        matrix[guard_list[i].y][guard_list[i].x] = matrix[guard_list[i].y][guard_list[i].x] + 1;
    }

    for (int i = 0; i < height; ++i)
        free(matrix[i]);
    free(matrix);

    return info[0] * info[1] * info[2] * info[3];
}

int run_day14()
{
    // char inputpath[] = "./input/day14-test.txt";
    char inputpath[] = "./input/day14.txt";
    printf("Day 14: Restroom Redoubt\n");

    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    FILE* fp;
    fp = fopen(inputpath, "r");

    struct ToiletGuard guard_list[500] = { 0 };
    int guard_count = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        int space_index = find_character_index(line, ' ');

        char* position = get_substring(0, space_index, line);
        int position_comma = find_character_index(position, ',');
        char* pos_x = get_substring(2, position_comma, position);
        guard_list[guard_count].start_x = atoi(pos_x);
        char* pos_y = get_substring(position_comma + 1, space_index, position);
        guard_list[guard_count].start_y = atoi(pos_y);
        free(pos_x);
        free(pos_y);
        free(position);

        char* velocity = get_substring(space_index, read, line);
        int velocity_comma = find_character_index(velocity, ',');
        char* vel_x = get_substring(3, velocity_comma, velocity);
        guard_list[guard_count].velocity_x = atoi(vel_x);

        // this line?

        // printf("velocity: '%s'\n", velocity);
        // for (int i = 0; i < read - position_comma - 1; i++) {
        // printf("  %d: %c\n", i, velocity[i]);
        // }
        // printf("---\n");
        // printf("start: %d\n", velocity_comma + 1);
        // printf("end: %ld\n", read - position_comma);

        char* vel_y = get_substring(velocity_comma + 1, read - 3 - position_comma, velocity);
        guard_list[guard_count].velocity_y = atoi(vel_y);
        // printf("vel_y: '%s' \n", vel_y);
        free(vel_x);
        free(vel_y);
        free(velocity);

        guard_count++;
    }
    fclose(fp);
    free(line);

    printf("\tPart 1: %d\n", day14part1(guard_list, guard_count));
    printf("\tPart 2: %d\n", day14part2(guard_list, guard_count));
    return 0;
}