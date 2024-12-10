#include "day1.h"
#include "day2.h"
#include "day3.h"
#include "day4.h"
#include "day5.h"
#include "day6.h"
#include "day7.h"
#include "day8.h"
#include "day9.h"

int main(int argc, char* argv[]) {
  int status = 0;

  status = run_day1()
           // + run_day2()
           // + run_day3()
           // + run_day4()
           // + run_day5()
           // + run_day6()
           // + run_day7()
           // + run_day8()
           + run_day9();

  return status;
}
