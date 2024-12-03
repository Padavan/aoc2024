#include "day1.h"
#include "day2.h"
#include "day3.h"

int main(int argc, char *argv[]) {
  int status = 0;

  status = run_day1() + run_day2() + run_day3();

  return status;
}
