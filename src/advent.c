#include "day1.h"
#include "day2.h"
#include "day3.h"
#include "day4.h"
#include "day5.h"
#include "day6.h"

int main(int argc, char* argv[])
{
    int status = 0;

    status = run_day1() + run_day2() + run_day3() + run_day4() + run_day5() + run_day6();

    return status;
}
