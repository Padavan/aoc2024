#include "day9.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "utils.h"

struct File {
    int id;
    int size;
};

// PArt 1
long long
day9_part1(char* line, ssize_t length)
{
    long long* expanded = malloc(sizeof(long long) * 100 * length);
    for (ssize_t i = 0; i < (100 * length); i++) {
        long long fill = 0;
        expanded[i] = fill;
    }

    // expand data
    ssize_t cursor = 0;
    for (ssize_t i = 0; i < length; i++) {
        long long filling;
        if (i % 2 == 0) {
            filling = i / 2;
        } else {
            filling = -1;
        }

        char* compressed_char = get_substring(i, i + 1, line);
        ssize_t filling_size = atol(compressed_char);
        free(compressed_char);

        for (ssize_t idx = 0; idx < filling_size; idx++) {
            expanded[cursor + idx] = filling;
        }
        cursor = cursor + filling_size;
    }

    // reformat data
    int left = 0;
    int right = cursor - 1;

    while (left < right) {
        if (expanded[right] == -1) {
            right--;
            continue;
        }

        if (expanded[left] != -1) {
            left++;
            continue;
        }

        if (expanded[left] == -1) {
            expanded[left] = expanded[right];
            expanded[right] = -1;
            left++;
            right--;
        }
    }

    // count checksum
    long long checksum = 0;
    for (long long i = 0; i < cursor; i++) {
        if (expanded[i] != -1) {
            checksum = i * expanded[i] + checksum;
        }
    }

    free(expanded);

    return checksum;
}

// PART 2
long long
day9_part2(char* line, ssize_t length)
{
    int* expanded = malloc(sizeof(int) * 10 * length);
    for (ssize_t i = 0; i < 10 * length; i++) {
        int fill = -1;
        expanded[i] = fill;
    }

    // expand data
    int cursor = 0;
    for (int i = 0; i < length; i++) {
        int id;
        if (i % 2 == 0) {
            id = i / 2;
        } else {
            id = -1;
        }

        char* compressed_char = get_substring(i, i + 1, line);
        int filling_size = atol(compressed_char);
        assert(filling_size < 10);
        free(compressed_char);
        // printf("filling_size: %d, id: %d\n", filling_size, id);

        for (int idx = 0; idx < filling_size; idx++) {
            expanded[cursor + idx] = id;
        }
        cursor = cursor + filling_size;
    }

    // printf("expanded: \n");
    // for (int i = 0; i < cursor; i++) {
    //   if (i < 3000) {
    //     printf("%d ", expanded[i]);
    //   }
    // }
    // printf("\n");
    assert(cursor > 1);

    // reformat data
    int left_start = 0; // main
    int left_end = 0;
    int right_start = cursor - 1;
    int right_end = cursor - 1; // main

    while (0 < right_end) {
        // give up searching for space
        if (right_start <= left_start) {
            left_start = 0;
            left_end = 0;
            right_end = right_start;
            right_start = right_end;
            continue;
        }
        // if (right_start < 15) {
        // printf("while1 left: %d - %d\n", left_start, left_end);
        // printf("while2 right: %d - %d\n", right_start, right_end);
        // printf("\texpanded[left_start] %d, expanded[left_end]: %d\n",
        // expanded[left_start], expanded[left_end]);
        // }
        // move end of right cursor to the non -1
        if (expanded[right_end] == -1) {
            right_end--;
            right_start = right_end;
            continue;
        }

        // move start of the right cursor to next segment
        if (expanded[right_start] == expanded[right_end]) {
            // printf("\t right_left move: %d, %d , %d, %d \n", expanded[right_start],
            // expanded[right_end], right_start, right_end);
            // right_start = right_start >= 1 ? right_start - 1 : 0;
            // right_start = right_start > 0 ? right_start - 1 : 0;
            right_start--;
            continue;
        }

        // move start of left cursor to free space
        if (expanded[left_start] != -1 && expanded[left_start] < cursor - 1) {
            left_start++;
            left_end = left_start;
            continue;
        }

        // move end of left cursor to file next to free space
        if (expanded[left_end] == expanded[left_start]) {
            left_end++;
            continue;
        }

        // look for bigger space
        if (left_end - left_start < right_end - right_start) {
            // right_end = right_start - 1;
            // right_start = right_end;
            left_start = left_end;
            left_end = left_start;
            continue;
        }

        // if (expanded[left_start] == -1) {
        // printf("\t\t==== EXCHANGE left: %d,%d | right: %d,%d\n", left_start,
        // left_end, right_start, right_end); printf("\t\t\t left-id: %d, right-id:
        // %d\n", expanded[left_start], expanded[right_end]);
        for (int i = 0; i < (right_end - right_start); i++) {
            expanded[left_start + i] = expanded[right_start + i + 1];
            expanded[right_start + i + 1] = -1;
        }

        left_end = 0;
        left_start = 0;
        right_start = right_end;
        right_end = right_start;
    }

    // count checksum
    long long checksum = 0;
    for (long long i = 0; i < cursor; i++) {
        if (expanded[i] != -1) {
            long long cur = (long long)expanded[i];
            checksum = i * cur + checksum;
        }
    }

    free(expanded);

    return checksum;
}

int run_day9()
{
    int DAY = 9;
    printf("Day %d: Disk Fragmenter\n", DAY);
    // char inputpath[] = "./input/day9-test.txt";
    char inputpath[] = "./input/day9.txt";

    long long part1_result = 0;
    long long part2_result = 0;

    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    FILE* fp;
    fp = fopen(inputpath, "r");
    while ((read = getline(&line, &len, fp)) != -1) {
        assert(read > 0);
        part1_result = day9_part1(line, read);
        part2_result = day9_part2(line, read);
    }
    fclose(fp);
    free(line);

    printf("\tPart 1: %lld\n", part1_result);
    printf("\tPart 2: %lld\n", part2_result);

    return 0;
}