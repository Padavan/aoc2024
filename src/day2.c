#include "day2.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

void* get_numbers_from_string(char* str, int* arr)
{
    int current_number_count = 0;

    int start_index = 0;
    int end_index = 0;
    size_t length = strlen(str);
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == ' ' || str[i] == '\n' || i == (length - 1)) {
            char* numberstr = get_substring(start_index, end_index, str);
            int number = atoi(numberstr);
            arr[current_number_count] = number;
            current_number_count++;
            start_index = i + 1;
            free(numberstr);
        } else {
            end_index = i + 1;
        }
    }

    return arr;
}

int count_spaces(const char* str)
{
    int count = 0;
    while (*str != '\0') {
        if (*str == ' ') {
            count++;
        }
        str++;
    }
    return count + 1;
}

int are_numbers_safe(int* numbers, int numbercount)
{
    int status = -1;

    int previous = -1;
    for (int i = 0; i < numbercount; i++) {
        int current = numbers[i];

        if (previous == -1) {
            previous = current;
            continue;
        };

        int diff = abs(current - previous);
        if (diff > 3 || diff < 1) {
            return 0;
        }

        if (current > previous && status == 1) {
            return 0;
        }

        if (current < previous && status == 0) {
            return 0;
        }

        if (current > previous) {
            status = 0;
        } else {
            status = 1;
        }
        previous = current;
    }

    return 1;
}

int are_numbers_safe_with_dumpening(int* numbers, int numbercount)
{
    assert(numbercount > 1);
    if (are_numbers_safe(numbers, numbercount)) {
        return 1;
    } else {
        for (int i = 0; i < numbercount; i++) {
            int* numbers_without_one_level = malloc(sizeof(int) * (numbercount - 1));

            int index = 0;
            for (int j = 0; j < numbercount; j++) {
                if (j == i) {
                    continue;
                }
                numbers_without_one_level[index] = numbers[j];
                index++;
            }

            if (are_numbers_safe(numbers_without_one_level, numbercount - 1)) {
                free(numbers_without_one_level);
                return 1;
            } else {
                free(numbers_without_one_level);
            }
        }
    }

    return 0;
}

int day2part1(char inputpath[])
{
    char* line = NULL;
    size_t len = 0;

    int result = 0;

    FILE* fp;
    fp = fopen(inputpath, "r");
    while ((getline(&line, &len, fp)) != -1) {
        int number_count = count_spaces(line);
        int numbers[10] = { 0 };
        get_numbers_from_string(line, numbers);

        int are_safe = are_numbers_safe(numbers, number_count);
        result = result + are_safe;
    }
    fclose(fp);
    free(line);

    return result;
}

int day2part2(char inputpath[])
{
    char* line = NULL;
    size_t len = 0;

    int result = 0;

    FILE* fp;
    fp = fopen(inputpath, "r");
    while ((getline(&line, &len, fp)) != -1) {
        int number_count = count_spaces(line);
        int numbers[10] = { 0 };
        get_numbers_from_string(line, numbers);

        int are_safe = are_numbers_safe_with_dumpening(numbers, number_count);
        result = result + are_safe;
    }
    fclose(fp);
    free(line);

    return result;
}

int run_day2()
{
    char inputpath[] = "./input/day2.txt";

    printf("Day 2: Red-Nosed Reports\n");
    printf("\tPart 1: %d\n", day2part1(inputpath));
    printf("\tPart 2: %d\n", day2part2(inputpath));

    return 0;
}
