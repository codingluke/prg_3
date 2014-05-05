#include <iostream>
#include <climits>
#include <string>
#include "io_util.h"
#include "date.h"
#include "gregorian_calender.h"

using namespace std;

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
  if (max < min)
    swap(min, max);
  long entry = 0;
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
     cout << "Bitte eine ganze Zahl eingeben [";
     cout << min << " - " << max << "]: ";
   }
  } while (!entry_ok);
  cin.setf(cin.skipws);
  return entry;
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

/**
 * Prints a text to the console and reads a valid date from the console.
 * It is not possible to read a invalid date like 29.2.2014.
 *
 * @param text  text to print to the console.
 *
 * @return the readed valid date.
 */
Date read_date(string text)
{
  cout << text << "\n";
  Date date;
  date.year = read_int("Jahr:\t", 1583, 1000000);
  date.month = read_int("Monat:\t", 1, 12);
  date.day = read_int("Tag:\t", 1, calc_days_of_month(date.month, date.year));
  return date;
}
