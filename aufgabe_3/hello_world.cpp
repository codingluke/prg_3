#include <iostream>
#include "console_input.h"
#include "console_output.h"
#include "gregorian_calender.h"

using namespace std;

int main()
{
  //typedef ios_base::fmtflags Formattype;
  //Formattype fixed_rechts[] = {cout.right, cout.fixed, cout.showpoint};

  //int i = calculate_days_of_month(1, 2014);
  //int i = calculate_days_from_the_beginning(1, 2, 1905);

  //char text1[] = "Dies ist der erste Text.\n";
  //for (int breite = 33; breite >= 25; breite--)
    //write_text(text1, breite, cout.right);
  //string text2 = "Dies ist der zweite Text.\n";
  //for (int breite = 25; breite <= 33; breite++)
    //write_text(text2, breite, cout.right);

  print_calender(2, 1583);
  //write_number((long)i, fixed_rechts, 3);
}
