#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/utils.h"


START_TEST(convert_to_string_simple_number) {
	int a = 42;
	char* string = convert_to_string(a);	
	ck_assert(string[0] == '4');
	ck_assert(string[1] == '2');
	free(string);
}
END_TEST

START_TEST(convert_to_string_long_number) {
	int a = 1234567;
	char* string = convert_to_string(a);	
	ck_assert(string[0] == '1');
	ck_assert(string[1] == '2');
	ck_assert(string[2] == '3');
	ck_assert(string[3] == '4');
	ck_assert(string[4] == '5');
	ck_assert(string[5] == '6');
	ck_assert(string[6] == '7');
	free(string);
}
END_TEST

START_TEST(convert_to_string_one_digit_number) {
	int a = 0;
	char* string = convert_to_string(a);	
	ck_assert(string[0] == '0');
	free(string);
}
END_TEST


TCase *make_utils_case(void) {
  TCase * tc = tcase_create("Day17");

  tcase_add_test (tc, convert_to_string_simple_number);
  tcase_add_test (tc, convert_to_string_long_number);
  tcase_add_test (tc, convert_to_string_one_digit_number);

  return tc;
}
