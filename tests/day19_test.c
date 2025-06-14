#include <check.h>
#include <stdbool.h>
#include "../include/day19.h"


List pattern_list = {
	{
			{{'r'}, 1},
			{{'w','r'}, 2},
			{{'b'}, 1},
			{{'g'}, 1},
			{{'b','w','u'}, 3},
			{{'r','b'}, 2},
			{{'g','b'}, 2},
			{{'b','r'}, 2},
	},
	8
};

List components = {{}, 0};

START_TEST(first_check) {
	Pattern str = { {'b','r','w','r','r'}, 5 };
	bool is_valid = check_design(str, pattern_list, -1, &components);
	ck_assert(is_valid == true);
}
END_TEST

START_TEST(second_check) {
	Pattern str = {
		{'b','g','g','r'},
		4
	};
	
	bool is_valid = check_design(str, pattern_list, -1, &components);
	ck_assert(is_valid == true);
}
END_TEST

START_TEST(third_check) {
	Pattern str = { {'g','b','b','r'}, 4 };
	bool is_valid = check_design(str, pattern_list, -1, &components);
	ck_assert(is_valid == true);
}
END_TEST

START_TEST(fourh_check) {
	Pattern str = { {'r','r','b','g','b','r'}, 6 };
	bool is_valid = check_design(str, pattern_list, -1, &components);
	ck_assert(is_valid == true);
}
END_TEST

START_TEST(fifth_check) {
	Pattern str = { {'u','b','w','u'}, 4 };
	bool is_valid = check_design(str, pattern_list, -1, &components);
	ck_assert(is_valid == false);
}
END_TEST

START_TEST(sixth_check) {
	Pattern str = { {'b','w','u','r','r','g'}, 6 };
	bool is_valid = check_design(str, pattern_list, -1, &components);
	ck_assert(is_valid == true);
}
END_TEST

START_TEST(seventh_check) {
	Pattern str = { {'b','r','g','r'}, 4 };
	bool is_valid = check_design(str, pattern_list, -1, &components);
	ck_assert(is_valid == true);
}
END_TEST

START_TEST(eigthth_check) {
	Pattern str = { {'b','b','r','g','w','b'}, 6 };
	bool is_valid = check_design(str, pattern_list, -1, &components);
	ck_assert(is_valid == false);
}
END_TEST

START_TEST(bad_color_check) {
	Pattern str = { {'b','r','w','r','r', 'z'}, 6 };
	bool is_valid = check_design(str, pattern_list, -1, &components);
	ck_assert(is_valid == false);
}
END_TEST

START_TEST(combine_patterns_test) {
	Pattern a = { {'a', 'b', 'c'}, 3};
	Pattern b = { {'d', 'e'}, 2};

	Pattern result = combine_patterns(a, b);
	ck_assert(result.lenght = 5);
	ck_assert(result.chars[0] == 'a');
	ck_assert(result.chars[1] == 'b');
	ck_assert(result.chars[2] == 'c');
	ck_assert(result.chars[3] == 'd');
	ck_assert(result.chars[4] == 'e');
}
END_TEST


START_TEST(recombination_count_first) {
	struct ComponentList mapping = {{
		{{0, 1, 2, 3}, 4},
		{{0, 1, 2}, 3},
		{{0, 1}, 2},
		{{0}, 1},
	}, 4};

	int count = count_combos(&mapping);
	ck_assert(count == 8);
}
END_TEST

START_TEST(recombination_count_second) {
	struct ComponentList mapping = {{
		{{0, 1, 2}, 3},
		{{0, 1}, 2},
		{{0}, 1},
	}, 3};

	int count = count_combos(&mapping);
	ck_assert(count == 4);
}
END_TEST

START_TEST(recombination_count_third) {
	struct ComponentList mapping = {{
		{{0, 1, 2, 3}, 4},
		{{0, 1, 2}, 3},
		{{0, 1}, 2},
		{{0}, 1},
		{{0}, 1},
		{{0}, 1},
		{{0, 1}, 2},
		{{0}, 1}
	}, 8};

	int count = count_combos(&mapping);
	ck_assert(count == 16);
}
END_TEST

START_TEST(recombination_count_fourth) {
	struct ComponentList mapping = {{
		{{0, 1, 2}, 3},
		{{0, 1, 2}, 3},
		{{0, 1}, 2},
		{{0}, 1},
	}, 4};

	int count = count_combos(&mapping);
	ck_assert(count == 7);
}
END_TEST


// brwrr can be made in two different ways: b, r, wr, r or br, wr, r.
START_TEST(recombination_count_fifth) {
	struct ComponentList mapping = {{
		{{0, 1}, 2},
		{{0}, 1},
		{{0}, 1},
		{{0}, 1},
	}, 4};

	int count = count_combos(&mapping);
	ck_assert(count == 2);
}
END_TEST

// gbbr can be made 4 different ways:
START_TEST(recombination_count_sixth) {
	struct ComponentList mapping = {{
		{{0, 1}, 2},
		{{0}, 1},
		{{0, 1}, 2},
		{{0}, 1},
	}, 4};

	int count = count_combos(&mapping);
	ck_assert(count == 4);
}
END_TEST

// rrbgbr can be made 6 different ways:
START_TEST(recombination_count_seventh) {
	struct ComponentList mapping = {{
		{{0}, 1},
		{{0, 1}, 2},
		{{0}, 1},
		{{0, 1}, 2},
		{{0, 1}, 2},
		{{0}, 1},
	}, 6};

	int count = count_combos(&mapping);
	ck_assert(count == 6);
}
END_TEST


TCase *make_day19_case (void) {
  TCase * tc = tcase_create("Day19");

  tcase_add_test(tc, first_check);
  tcase_add_test(tc, second_check);
  tcase_add_test(tc, third_check);
  tcase_add_test(tc, fourh_check);
  tcase_add_test(tc, fifth_check);
  tcase_add_test(tc, sixth_check);
  tcase_add_test(tc, seventh_check);
  tcase_add_test(tc, eigthth_check);
  tcase_add_test(tc, bad_color_check);
  tcase_add_test(tc, combine_patterns_test);
  
  tcase_add_test(tc, recombination_count_first);
  tcase_add_test(tc, recombination_count_second);
  tcase_add_test(tc, recombination_count_third);
  tcase_add_test(tc, recombination_count_fourth);
  tcase_add_test(tc, recombination_count_fifth);
  tcase_add_test(tc, recombination_count_sixth);
  tcase_add_test(tc, recombination_count_seventh);


  return tc;
}
