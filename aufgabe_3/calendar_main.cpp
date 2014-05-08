#include "console_input.h"
#include "calendar.h"

using namespace std;

int main()
{
  int action = 0;
  do
  {
    print_actions();
    action = read_int("Bitte waehlen:\t", 1, 3);
    if (action == 1)
      generate_and_print_calendar();
    else if (action == 2)
      calc_and_print_days_between_dates();
  } while (action != 3);
  print_goodbye();
}
