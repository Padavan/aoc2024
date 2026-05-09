#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/day19.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

// Dynamic programming problem

int get_cached_idx(Cache* cache, Pattern pattern)
{
    int find_index = -1;
    for (size_t i = 0; i < cache->size; i++) {
        if (cache->keys[i].size != pattern.size) {
            continue;
        }

        if (strcmp(pattern.chars, cache->keys[i].chars) == 0) {
            find_index = i;
            break;
        }
    }
    return find_index;
}

void set_cache(Cache* cache, Pattern pattern, size_t value)
{
    cache->keys[cache->size] = pattern;
    cache->values[cache->size] = value;
    cache->size = cache->size + 1;
}

bool str_start_with(Pattern longstr, Pattern shortstr)
{
    if (shortstr.size > longstr.size)
        return false;
    for (int i = 0; i < shortstr.size; i++) {
        if (longstr.chars[i] != shortstr.chars[i]) {
            return false;
        }
    }
    return true;
}

Pattern get_subpattern(Pattern pattern, int start)
{
    // printf("\t\tget_subpattern %d\n", start);
    Pattern new_pattern = {};
    for (int i = 0; i < pattern.size - start; i++) {
        new_pattern.chars[i] = pattern.chars[i + start];
        new_pattern.size = i + 1;
    }

    return new_pattern;
}

void print_cache(Cache* cache)
{
    for (size_t i = 0; i < cache->size; i++) {
        printf("cache index: %ld", i);
        printf("  cache key: %s", cache->keys[i].chars);
        printf("  cache key size: %d", cache->keys[i].size);
        printf("  cache value: %ld \n", cache->values[i]);
    }
}

void print_pattern(Pattern pattern)
{
    printf("pattern: %s size: %d\n", pattern.chars, pattern.size);
}

size_t check_design(Pattern design, List* pattern_list, Cache* cache)
{
    int cache_idx = get_cached_idx(cache, design);
    if (cache_idx == -1) {
        if (design.size == 0) {
            return 1;
        } else {
            size_t result = 0;
            for (int i = 0; i < pattern_list->size; i++) {
                Pattern target_pattern = pattern_list->items[i];
                // printf("\ttarget_pattern %s %d \n", target_pattern.chars, target_pattern.size);
                if (str_start_with(design, target_pattern)) {
                    // Pattern new_design = { design.chars[target_pattern.size], design.size - target_pattern.size };
                    Pattern new_design = get_subpattern(design, target_pattern.size);
                    // printf("\tnew_design: %s %d\n", new_design.chars, new_design.size);
                    result += check_design(new_design, pattern_list, cache);
                }
            }
            set_cache(cache, design, result);
            return result;
        }
    } else {
        return cache->values[cache_idx];
    }
}

int check_valid_patterns(List design_list, List* pattern_list)
{
    size_t count_all = 0;
    size_t count_possible = 0;

    Cache cache = {
        .keys = malloc(sizeof(Pattern) * 100000000),
        .values = malloc(sizeof(size_t) * 100000000),
        .size = 0
    };

    for (int i = 0; i < design_list.size; i++) {
        size_t count = check_design(design_list.items[i], pattern_list, &cache);
        if (count > 0) {
            count_possible++;
            count_all = count_all + count;
        }
    }

    free(cache.keys);
    free(cache.values);

    printf("\tPart 1: %ld\n", count_possible);
    // 322
    printf("\tPart 2: %ld\n", count_all);
    // 715514563508258

    return 0;
}

int run_day19()
{
    printf("Day 19: Linen Layout\n");
    char inputpath[] = "./input/day19.txt";

    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    FILE* fp;
    fp = fopen(inputpath, "r");

    int line_count = 0;

    List pattern_list = { {}, 0 };
    List designs_list = { {}, 0 };

    while ((read = getline(&line, &len, fp)) != -1) {
        if (line_count == 0) {

            Pattern new_pattern = { {}, 0 };
            for (ssize_t i = 0; i < read; i++) {
                if (line[i] == ',') {
                    new_pattern.chars[new_pattern.size] = '\0';
                    pattern_list.items[pattern_list.size] = new_pattern;
                    pattern_list.size++;
                    new_pattern.chars[0] = '\0';
                    new_pattern.size = 0;
                } else if (line[i] == '\n') {
                    new_pattern.chars[new_pattern.size] = '\0';
                    pattern_list.items[pattern_list.size] = new_pattern;
                    pattern_list.size++;
                } else if (line[i] == ' ') {
                    continue;
                } else {
                    new_pattern.chars[new_pattern.size] = line[i];
                    new_pattern.size++;
                }
            }
        }

        if (line_count > 1) {
            Pattern str = { {}, 0 };
            for (int i = 0; i < read - 1; i++) {
                str.chars[i] = line[i];
                str.size = i + 1;
            }
            designs_list.items[designs_list.size] = str;
            designs_list.size++;
        }
        line_count++;
    }

    free(line);
    fclose(fp);

    check_valid_patterns(designs_list, &pattern_list);

    return 0;
}
