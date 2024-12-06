#include "day5.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RULE_LEGNTH = 500;

typedef struct {
    int arr[500];
    int top;
} Stack;

enum INPUT_PARTS {
    CONDITIONS,
    UPDATES
};

int run_day5_part2(char* line, int rule_list[2000][2], int rule_count, int updates[500], int updates_count)
{
    for (int i = 0; i < updates_count; i++) {
        int target = updates[i];

        for (int rule_number = 0; rule_number < rule_count; rule_number++) {
            if (target == rule_list[rule_number][0]) {
                int follow = rule_list[rule_number][1];

                int follow_index = find_number_index(updates, follow);
                if (follow_index >= 0 && follow_index < i) {
                    updates[i] = follow;
                    updates[follow_index] = target;
                    i = 0;
                }
            }
        }
    }

    int middle = (updates_count - 1) / 2;
    return updates[middle];
}

int run_day5_part1(char* line, int rule_list[2000][2], int rule_count, int updates[500], int updates_count)
{
    bool is_update_line_valid = true;
    for (int i = 0; i < updates_count; i++) {
        int target = updates[i];

        for (int rule_number = 0; rule_number < rule_count; rule_number++) {
            if (target == rule_list[rule_number][0]) {
                int follow = rule_list[rule_number][1];

                int follow_index = find_number_index(updates, follow);
                if (follow_index >= 0 && follow_index < i) {
                    is_update_line_valid = false;
                }
            }
        }
    }

    if (is_update_line_valid) {
        int middle = (updates_count - 1) / 2;
        return updates[middle];
    }

    return 0;
}

int run_day5()
{
    int DAY = 5;
    // char inputpath[] = "./input/day5-test.txt";
    char inputpath[] = "./input/day5.txt";
    printf("Day %d\n", DAY);

    // int result = 0;
    // int mul_count = 0;

    size_t line_num = 0;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    FILE* fp;
    fp = fopen(inputpath, "r");
    enum INPUT_PARTS input_part = CONDITIONS;

    int result_part_1 = 0;
    int result_part_2 = 0;
    // todo remove hardcoded lenght
    int rule_list[2000][2] = { 0 };
    int rule_count = 0;
    int condition_count = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        if (line[0] == '\n') {
            input_part = UPDATES;
            continue;
        }

        if (input_part == CONDITIONS) {
            char* first_part = get_substring(0, 2, line);
            char* second_part = get_substring(3, 5, line);

            int first = atoi(first_part);
            int second = atoi(second_part);
            // int rule[2] = { first, second };
            rule_list[rule_count][0] = first;
            rule_list[rule_count][1] = second;
            rule_count++;

            free(first_part);
            free(second_part);
        }

        if (input_part == UPDATES) {
            int index = 0;

            char number_char[4] = { 0 };
            int number_char_index = 0;
            int updates_count = 0;
            int updates[500];
            while (line[index] != 0) {

                if (line[index] == ',' || line[index] == '\n') {
                    updates[updates_count] = atoi(number_char);
                    int number_char[4] = { 0 };
                    number_char_index = 0;
                    updates_count++;

                } else {
                    number_char[number_char_index] = line[index];
                    number_char_index++;
                }

                index++;
            }

            int line_result_part1 = run_day5_part1(line, rule_list, rule_count, updates, updates_count);
            result_part_1 = result_part_1 + line_result_part1;
            if (line_result_part1 == 0) {
                int line_result_part2 = run_day5_part2(line, rule_list, rule_count, updates, updates_count);
                result_part_2 = result_part_2 + line_result_part2;
            }
            condition_count++;
        }
    }

    free(line);
    fclose(fp);

    printf("\tPart 1: %d\n", result_part_1);
    printf("\tPart 2: %d\n", result_part_2);

    return 0;
}
