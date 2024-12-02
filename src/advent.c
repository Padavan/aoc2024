#include "day1.h"
#include "day2.h"

int main(int argc, char *argv[]) {
  int status = 0;

  status = run_day1() + run_day2();

  return status;
}
