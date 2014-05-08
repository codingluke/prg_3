#include "console_input.h"
#include "calendar.h"

using namespace std;

/**
 * Entrypoint for the calendar application.
 * It includes three different action.
 * 1. Create a calendar for a any month of a year between 1583 and 1000000.
 * 2. Calculates days between two arbitary dates.
 * 3. End of the program.
 *
 * It uses the gregorian calendar und is aware of leap years. The user entry
 * is validated, so that it is not possible to enter a wrong date e.g. 30.02.2004
 * or 29.02.2014.
 */
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
