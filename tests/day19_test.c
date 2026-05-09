#include <check.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/day19.h"


START_TEST(cache_check) {
	Cache cache = {
		.keys = malloc(sizeof(Pattern) * 100000000),
		.values = malloc(sizeof(size_t) * 100000000),
		.size = 0
	};

	Pattern pattern = {
		.chars = "abc",
		.size = 3
	};

	Pattern pattern2 = {
		.chars = "def",
		.size = 3
	};

	Pattern pattern3 = {
		.chars = "xyz",
		.size = 3
	};

	Pattern pattern4 = {
		.chars = "notfound",
		.size = 8
	};

	set_cache(&cache, pattern, 5);
	set_cache(&cache, pattern2, 3);
	set_cache(&cache, pattern3, 1);

	int first = get_cached_idx(&cache, pattern);
	int second = get_cached_idx(&cache, pattern2);
	int third = get_cached_idx(&cache, pattern3);
	int fourth = get_cached_idx(&cache, pattern4);
	printf("second %d\n", second);

	print_cache(&cache);

	ck_assert(first == 0);
	ck_assert(second == 1);
	ck_assert(third == 2);
	ck_assert(fourth == -1);
}
END_TEST



TCase *make_day19_case (void) {
  TCase * tc = tcase_create("Day19");

  tcase_add_test(tc, cache_check);

  return tc;
}
