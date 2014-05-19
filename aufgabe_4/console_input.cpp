#include <iostream>
#include <limits>
#include <string>
#include "console_input.h"

using namespace std;

static const double DBL_MAX = numeric_limits<double>::max();
static const double DBL_MIN = -1 * numeric_limit<double>::max();
static const long LONG_MAX = numeric_limits<long>::max();
static const long LONG_MIN = numeric_limits<long>::min();
static const int INT_MAX = numeric_limits<int>::max();
static const int INT_MIN = numeric_limits<int>::min();

/**
 * Reads a double value in between a given interval from the console.
 * When the entered value is not valid to the interval, the user
 * gets prompted to reenter a valid.
 *
 * @param min   lower bound of the interval.
 * @param max   top bound of the interval
 *
 * @return a double value in between min and max.
 */
double read_double(double min, double max)
{
  if (max < min)
    swap(min, max);
  double entry = 0;
  bool entry_ok = false;
  cin.clear();
  cin.unsetf(cin.skipws);
  do
  {
    cin >> entry;
    entry_ok = cin.good() && min <= entry && entry <= max;
    cin.clear();
    cin.ignore(static_cast<streamsize>(LONG_MAX), '\n');
    if (!entry_ok)
    {
      cout << "Bitte eine Zahl eingeben [";
      cout << min << " - " << max << "]: ";
    }
  } while (!entry_ok);
  cin.setf(cin.skipws);
  return entry;
}

/**
 * Reads a double value from the console in between the whole range of double.
 *
 * @return a valid double value.
 */
double read_double()
{
  return read_double(DBL_MIN, DBL_MAX);
}


/**
 * Prints a text to the console and reads a double value from the console
 * in between the whole range of double.
 *
 * @param text text to print to the console.
 *
 * @return a valid double value.
 */
double read_double(string text)
{
  cout << text;
  return read_double();
}

double read_double(string text, double min, double max)
{
  cout << text;
  return read_double(min, max);
}

/**
 * Reads a long value in between a given interval from the console.
 * When the entered value is not valid to the interval, the user
 * gets prompted to reenter a valid.
 *
 * @param min   lower bound of the interval.
 * @param max   top bound of the interval
 *
 * @return a long value in between min and max.
 */
long read_long(long min, long max)
{
  return static_cast<long>(read_double(min, max));
}

/**
 * Reads a long value from the terminal in between the whole range of long.
 *
 * @return a valid long value.
 */
long read_long()
{
  return read_long(LONG_MIN, LONG_MAX);
}

/**
 * Prints a text to the console and reads a long value from the console
 * in between the whole range of long.
 *
 * @param text text to print to the console.
 *
 * @return a valid long value.
 */
long read_long(string text)
{
  cout << text;
  return read_long();
}

/**
 * Prints a text to the console and reads a long value in between
 * a given interval from the console. When the value is not in between
 * the interval, the user gets prompted to reeinter a valid value.
 *
 * @param text  text to print to the console.
 * @param min   lower bound of the interval.
 * @param max   top bound of the interval.
 *
 * @return a long value in between min and max.
 */
long read_long(string text, long min, long max)
{
  cout << text;
  return read_long(min, max);
}

/**
 * Reads a integer value in between a given interval from the console.
 * When the entered value is not valid to the interval, the user
 * gets prompted to reenter a valid.
 *
 * @param min   lower bound of the interval.
 * @param max   top bound of the interval
 *
 * @return a int value in between min and max.
 */
int read_int(int min, int max)
{
  return static_cast<int>(read_long(min, max));
}

/**
 * Reads an integer value from the terminal in between the whole range of long.
 *
 * @return a valid integer value.
 */
int read_int()
{
  return static_cast<int>(read_long(INT_MIN, INT_MAX));
}

/**
 * Prints a text to the console and reads a integer value from the console
 * in between the whole range of integer.
 *
 * @param text text to print to the console.
 *
 * @return a valid integer value.
 */
int read_int(string text)
{
  cout << text;
  return read_int();
}

/**
 * Prints a text to the console and reads a integer value in between
 * a given interval from the console. When the value is not in between
 * the interval, the user gets prompted to reeinter a valid value.
 *
 * @param text  text to print to the console.
 * @param min   lower bound of the interval.
 * @param max   top bound of the interval.
 *
 * @return a integer value in between min and max.
 */
int read_int(string text, int min, int max)
{
  cout << text;
  return read_int(min, max);
}


bool read_yes_no(string text)
{
  string input;
  bool yes = false;
  do
  {
    cout << text << " (j/n): ";
    getline(cin, input);
  }
  while (!cin.fail() && input != "j" && input != "n");
  if (input == "j")
    yes = true;
  return yes;
}

string read_text(string text)
{
  string input;
  cout << text;
  getline(cin, input);
  return input;
}
