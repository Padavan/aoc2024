#include <assert.h>
#include <bits/getopt_core.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// #include "day1.h"
// #include "day10.h"
// #include "day11.h"
// #include "day12.h"
// #include "day13.h"
// #include "day14.h"
// #include "day15.h"
#include "day16.h"
// #include "day2.h"
// #include "day3.h"
// #include "day4.h"
// #include "day5.h"
// #include "day6.h"
// #include "day7.h"
// #include "day8.h"
// #include "day9.h"

void usage() {
  printf("usage: advent [options] \n");
  printf("\t-d DAY \t\t Run specific day \n");
  printf("\t-h \t\t Display this help and exit \n");
}

int main(int argc, char* argv[]) {
  char opt;
  int day = -1;
  while ((opt = getopt(argc, argv, "dh")) != -1) {
    printf("opt: %c\n", opt);
    switch (opt) {
      case 'd':
        printf("option: %s\n", optarg);
        assert(optarg != NULL);
        day = atoi(optarg);
        break;
      case 'h':
        usage();
        return 0;
        // break;
    }
  }

  switch (day) {
    case -1:
      // run_day1();
      // run_day2();
      // run_day3();
      // run_day4();
      // run_day5();
      // run_day6();
      // run_day7();
      // run_day8();
      // run_day9();
      // run_day10();
      // run_day11();
      // run_day12();
      // run_day13();
      // run_day14();
      // run_day15();
      run_day16();
      break;
    // case 1:
    //   run_day1();
    //   break;
    // case 2:
    //   // run_day2();
    //   break;
    // case 12:
    //   run_day12();
    //   break;
    // case 13:
    //   run_day13();
    //   break;
  }

  return 0;
}