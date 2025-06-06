#include "../include/day11.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/utils.h"

struct Stone {
    long long value;
    long long multipier;
};

long long
blinking_loop(struct Stone* stones, int stone_count, int cycle, int cycle_limit)
{
    if (stone_count <= 0) {
        free(stones);
        return 0;
    }

    struct Stone* new_stones = malloc(sizeof(struct Stone) * 2 * stone_count);
    int index = 0;

    // condition phase
    for (int i = 0; i < stone_count; i++) {
        int digits_count = get_digit_count(stones[i].value);

        if (stones[i].value == -1) {
            continue;
        } else if (stones[i].value == 0) {
            struct Stone new_stone = { 1, stones[i].multipier };
            new_stones[index] = new_stone;
        } else if (digits_count % 2 == 0) {
            long long base = power(10, digits_count / 2);

            long long first_value = stones[i].value / base;
            long long second_value = stones[i].value % base;

            struct Stone first_stone = { first_value, stones[i].multipier };
            struct Stone second_stone = { second_value, stones[i].multipier };
            new_stones[index] = first_stone;
            index++;
            new_stones[index] = second_stone;
        } else {
            struct Stone new_stone = { stones[i].value * 2024, stones[i].multipier };
            new_stones[index] = new_stone;
        }
        index++;
    }

    // compress phase
    for (int i = 0; i < index; i++) {
        if (new_stones[i].value != -1) {
            long long multipier = new_stones[i].multipier;
            for (int j = 0; j < index; j++) {
                if (new_stones[i].value == new_stones[j].value && i != j) {
                    multipier = new_stones[j].multipier + multipier;
                    new_stones[j].value = -1;
                }
            }
            new_stones[i].multipier = multipier;
        }
    }

    free(stones);

    if (cycle == cycle_limit) {
        long long result = 0;
        for (int i = 0; i < index; i++) {
            if (new_stones[i].value != -1) {
                result = result + new_stones[i].multipier;
            }
        }
        free(new_stones);
        return result;
    } else {
        // free(new_stones);
        return blinking_loop(new_stones, index, cycle + 1, cycle_limit);
    }
}

int run_day11()
{
    printf("Day 11: Plutonian Pebbles\n");

    // char inputpath[] = "./input/day11-test.txt";
    char inputpath[] = "./input/day11.txt";

    char* line = NULL;
    size_t len = 0;

    long long part1_result = 0;
    long long part2_result = 0;

    FILE* fp;
    fp = fopen(inputpath, "r");
    while ((getline(&line, &len, fp)) != -1) {
        struct Stone* numbers = malloc(sizeof(struct Stone) * 20);
        struct Stone* numbers2 = malloc(sizeof(struct Stone) * 20);
        int number_count = 0;

        char* pch;
        pch = strtok(line, " ");
        while (pch != NULL) {
            long long value = atol(pch);
            struct Stone new_stone = { value, 1 };
            numbers[number_count] = new_stone;
            numbers2[number_count] = new_stone;
            number_count++;
            pch = strtok(NULL, " ");
        }

        assert(number_count > 1);

        part1_result = blinking_loop(numbers, number_count, 1, 25);
        part2_result = blinking_loop(numbers2, number_count, 1, 75);

        free(pch);
    }

    fclose(fp);
    free(line);

    printf("\tPart 1: %lld\n", part1_result);
    printf("\tPart 2: %lld\n", part2_result);

    return 0;
}
