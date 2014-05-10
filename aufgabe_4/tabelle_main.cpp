#include <iostream>
#include "console_input.h"

using namespace std;

/**
 * Entrypoint for the calendar application. It includes three different actions:
 * 1. Create a calendar for a any month of a year between 1583 and 1000000.
 * 2. Calculates days between two arbitary dates.
 * 3. Exit the program.
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
    action = read_int("Bitte waehlen:\t", 1, 3);
    cout << "hallo welt";
  } while (action != 3);
}
