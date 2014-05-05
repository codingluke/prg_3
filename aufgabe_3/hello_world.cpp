#include <iostream>
#include "console_input.h"
#include "console_output.h"
#include "gregorian_calender.h"

using namespace std;

int main()
{
  typedef ios_base::fmtflags Formattype;
  Formattype fixed_rechts[] = {cout.right, cout.fixed, cout.showpoint};

  int i = calculate_start_column(5, 2014);
  //int i = calculate_days_of_month(1, 2014);
  //int i = calculate_days_from_the_beginning(1, 2, 1905);
  write_number((long)i, fixed_rechts, 3);
}
