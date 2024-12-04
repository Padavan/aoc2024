#include "day2.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* get_numbers_from_string(char* str, int number_count, int* arr)
{
    int current_number_count = 0;

    int start_index = 0;
    int end_index = 0;
    int length = strlen(str);
    for (int i = 0; i < strlen(str); i++) {

        if (str[i] == ' ' || str[i] == '\n' || i == (length - 1)) {
            int number = atoi(get_substring(start_index, end_index, str));
            arr[current_number_count] = number;
            current_number_count++;
            start_index = i + 1;
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
    if (are_numbers_safe(numbers, numbercount)) {
        return 1;
    } else {
        for (int i = 0; i < numbercount; i++) {
            int* numbers_without_one_level = malloc(sizeof(int) * (numbercount - 1));
            memcpy(numbers_without_one_level, numbers, i * sizeof(int));
            memcpy(&numbers_without_one_level[i], numbers + i + 1,
                (numbercount - 1 - i) * sizeof(int));

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

int day2part1(char inputpath[], int line_count)
{
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    int result = 0;

    FILE* fp;
    fp = fopen(inputpath, "r");
    while ((read = getline(&line, &len, fp)) != -1) {
        int number_count = count_spaces(line);
        int* numbers = malloc(sizeof(int) * number_count);
        get_numbers_from_string(line, number_count, numbers);

        int are_safe = are_numbers_safe(numbers, number_count);
        result = result + are_safe;

        free(numbers);
    }
    fclose(fp);
    free(line);

    return result;
}

int day2part2(char inputpath[], int line_count)
{
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    int result = 0;

    FILE* fp;
    fp = fopen(inputpath, "r");
    while ((read = getline(&line, &len, fp)) != -1) {
        int number_count = count_spaces(line);
        int* numbers = malloc(number_count);
        get_numbers_from_string(line, number_count, numbers);

        int are_safe = are_numbers_safe_with_dumpening(numbers, number_count);
        result = result + are_safe;

        free(numbers);
    }
    fclose(fp);
    free(line);

    return result;
}

int run_day2()
{
    int DAY = 2;
    char inputpath[] = "./input/day2.txt";

    int line_count = get_line_count(inputpath);
    if (line_count == 0) {
        perror("There is no lines in puzzle input");
        return 1;
    }

    printf("Day %d\n", DAY);
    printf("\tPart 1: %d\n", day2part1(inputpath, line_count));
    printf("\tPart 2: %d\n", day2part2(inputpath, line_count));

    return 0;
}
