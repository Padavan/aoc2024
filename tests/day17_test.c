#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/day17.h"

// - [x] If register C contains 9, the program 2,6 would set register B to 1.
// - [x] If register A contains 10, the program 5,0,5,1,5,4 would output 0,1,2.
// - [x] If register A contains 2024, the program 0,1,5,4,3,0 would output 4,2,5,6,7,7,7,7,3,1,0 and leave 0 in register A.
// - [x] If register B contains 29, the program 1,7 would set register B to 26.
// - [x] If register B contains 2024 and register C contains 43690, the program 4,0 would set register B to 44354.


START_TEST(first_check) {
	struct Register init_state = { 0, 0, 9 };
	int cursor = 0;
	struct OutputArray output = {{0}, 0};
	struct Register next_state = run_opcode(2,6, init_state, &cursor, &output);
	ck_assert(next_state.B == 1);
}
END_TEST

START_TEST(second_check) {
	struct Register init_state = { 10, 0, 0 };
	struct OutputArray program = {{5, 0, 5, 1 ,5 , 4}, 6};
	struct OutputArray result = run_program(init_state, program);

	ck_assert(result.arr[0] == 0);
	ck_assert(result.arr[1] == 1);
	ck_assert(result.arr[2] == 2);
	ck_assert(result.size == 3);
}
END_TEST

START_TEST(third_check) {
	struct Register init_state = { 2024, 0, 0 };
	struct OutputArray program = {{0,1,5,4,3,0}, 6};
	struct OutputArray result = run_program(init_state, program);

	ck_assert(result.arr[0] == 4);
	ck_assert(result.arr[1] == 2);
	ck_assert(result.arr[2] == 5);
	ck_assert(result.arr[3] == 6);
	ck_assert(result.arr[4] == 7);
	ck_assert(result.arr[5] == 7);
	ck_assert(result.arr[6] == 7);
	ck_assert(result.arr[7] == 7);
	ck_assert(result.arr[8] == 3);
	ck_assert(result.arr[9] == 1);
	ck_assert(result.arr[10] == 0);
	ck_assert(result.size == 11);
}
END_TEST

START_TEST(fourh_check) {
	struct Register init_state = { 0, 29, 0 };
	int cursor = 0;
	struct OutputArray output = {{0}, 0};
	struct Register next_state = run_opcode(1,7, init_state, &cursor, &output);
	ck_assert(next_state.B == 26);
}
END_TEST

START_TEST(fifth_check) {
	struct Register init_state = { 0, 2024, 43690 };
	int cursor = 0;
	struct OutputArray output = {{0}, 0};
	struct Register next_state = run_opcode(4,0, init_state, &cursor, &output);
	ck_assert(next_state.B == 44354);
}
END_TEST


TCase *make_day17_case (void) {
  TCase * tc = tcase_create("Day17");

  tcase_add_test(tc, first_check);
  tcase_add_test(tc, second_check);
  tcase_add_test(tc, third_check);
  tcase_add_test(tc, fourh_check);
  tcase_add_test(tc, fifth_check);

  return tc;
}
