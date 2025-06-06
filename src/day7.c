#include "day7.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "utils.h"

enum OPERATION {
    ADD = '+',
    MULTIPLY = '*',
    CONCAT = '@'
};

long long
apply_combination(char* combination, long long numbers[], int operation_count)
{
    long long result = numbers[0];
    for (int i = 0; i < operation_count; i++) {
        // printf("\t\t %lld\n", result);
        if (combination[i] == '+') {
            result = result + numbers[i + 1];
        } else if (combination[i] == '*') {
            result = result * numbers[i + 1];
        } else if (combination[i] == '@') {
            int digit_count = get_digit_count(numbers[i + 1]);
            long long change_digita_position = power(10, digit_count);
            result = (result * change_digita_position) + numbers[i + 1];
        }
    }
    return result;
};

bool run_day7_part1(long long result, long long numbers[], int number_count)
{
    int operation_count = number_count - 1;
    int total_combinations = power(2, operation_count);

    for (int i = 0; i < total_combinations; i++) {
        char* combination = malloc(sizeof(char) * operation_count);
        for (int j = 0; j < operation_count; j++) {
            // todo I don't get this line
            if ((i >> j) & 1) {
                combination[j] = '+';
            } else {
                combination[j] = '*';
            }
        }
        long long combo_result = apply_combination(combination, numbers, operation_count);
        // printf("\tcombo_result %20lld \t\twith combo: %s\n", combo_result,
        // combination); free(combination);
        if (combo_result == result) {
            // printf("VALID %lld, with combo %s\n", result, combination);
            free(combination);
            return true;
        }
        free(combination);
    }

    return false;
};

// PART 2
bool run_day7_part2(long long result, long long numbers[], int number_count)
{
    int operation_count = number_count - 1;
    int total_combinations = power(3, operation_count);

    for (int i = 0; i < total_combinations; i++) {
        int current = i;
        char* combination = malloc(sizeof(char) * operation_count);
        for (int j = 0; j < operation_count; j++) {
            if (current % 3 == 0) {
                combination[j] = '+';
            } else if (current % 3 == 1) {
                combination[j] = '*';
            } else if (current % 3 == 2) {
                combination[j] = '@';
            } else {
                printf("unkown shit %d\n", current % 3);
            }
            current = current / 3;
        }
        long long combo_result = apply_combination(combination, numbers, operation_count);
        // printf("\tcombo_result %20lld \t\twith combo: %s\n", combo_result,
        // combination); free(combination);
        if (combo_result == result) {
            // printf("VALID %lld, with combo %s\n", result, combination);
            free(combination);
            return true;
        }
        free(combination);
    }

    return false;
};

int run_day7()
{
    printf("Day 7: Bridge Repair\n");
    // char inputpath[] = "./input/day7-test.txt";
    char inputpath[] = "./input/day7.txt";

    long long part1_result = 0;
    long long part2_result = 0;

    char* line = NULL;
    size_t len = 0;

    FILE* fp;
    fp = fopen(inputpath, "r");
    while ((getline(&line, &len, fp)) != -1) {
        // size_t colon_index = find_character_index(line, ':');
        char result_str[20] = { 0 };
        size_t colon_index = 0;
        while (line[colon_index] != ':') {
            result_str[colon_index] = line[colon_index];
            colon_index++;
        }

        long long result = atol(result_str);
        char* rest = get_substring(colon_index + 2, strlen(line), line);

        int index = colon_index + 2;
        while (line[index] != '\0') {
            index++;
        }

        long long numbers[20] = { 0 };
        int number_count = 0;

        char* pch;
        pch = strtok(rest, " ");
        while (pch != NULL) {
            numbers[number_count] = atol(pch);
            number_count++;
            pch = strtok(NULL, " ");
        }

        assert(number_count > 1);

        if (run_day7_part1(result, numbers, number_count)) {
            part1_result = part1_result + result;
        }

        if (run_day7_part2(result, numbers, number_count)) {
            part2_result = part2_result + result;
        }

        free(pch);
        free(rest);
    }
    fclose(fp);
    free(line);

    printf("\tPart 1: %lld\n", part1_result);
    printf("\tPart 2: %lld\n", part2_result);

    return 0;
}
