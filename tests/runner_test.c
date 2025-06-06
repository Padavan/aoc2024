#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/runner_test.h"


int main(void) {
	Suite *s1 = suite_create("Core");
	SRunner *sr = srunner_create(s1);
	int number_of_failed;

	suite_add_tcase(s1, make_day17_case());
	suite_add_tcase(s1, make_utils_case());

	srunner_run_all(sr, CK_ENV);
	number_of_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return number_of_failed == 0 ? 0 : 1;
}
