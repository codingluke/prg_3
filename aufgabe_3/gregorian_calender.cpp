#include <iostream>
#include "console_input.h"
#include "console_output.h"

/**
 * Checks if a year is a leap year.
 *
 * @param year    the year to investigate.
 *
 * @return true   if the year is a leap year.
 *         false  if the year is not a leap year.
 */
bool is_leap_year(int year)
{
  bool leap_year = false;
  if ((year % 4) == 0)
  {
    if ((year % 400) == 0)
      leap_year = true;
    else
      if (year % 100 > 0)
        leap_year = true;
  }
  return leap_year;
}


/**
 * Calculates the amount of days for the given month and year.
 *
 * @param month   the month.
 * @param year    the year.
 *
 * @return amounth the amounth of days of the month.
 */
int calculate_days_of_month(int month, int year)
{
  int amouth = 31;
  if (month == 4 || month == 6 || month == 9 || month == 11)
    amouth = 30;
  else
  {
    if (month == 2)
    {
      if (is_leap_year(year))
        amouth = 29;
      else
        amouth = 28;
    }
  }
  return amouth;
}

/**
 * Calculate with a given date how many days are past since
 * the 1.1.1583.
 *
 * @param day     the day of the date.
 * @param month   the month of the date.
 * @param year    the year of the date.
 *
 * @return amouth the amouth days past since 1.1.1583.
 */
int calculate_days_from_the_beginning(int day, int month, int year)
{
  int amouth = 0;
  for (int i = 1583; i < year; i++)
  {
    amouth += 365;
    if (is_leap_year(i))
      amouth++;
  }
  if (month != 1)
    for (int j = 1; j < month; j++)
      amouth += calculate_days_of_month(j, year);
  return (amouth + (day - 1));
}

/**
 * Calculates for a given month and year the start column of
 * a calendar for the first day of the month. The calendar starts
 * with Sunday.
 *
 * So | Mo | Di | Mi | Do | Fr | Sa
 *  0 |  1 |  2 |  3 |  4 |  5 |  6
 *
 * @param month the given month.
 * @param year  the given year.
 *
 * @return the column in which the first year lies.
 */
int calculate_start_column(int month, int year)
{
  int days = calculate_days_from_the_beginning(1, month, year);
  return ((days % 7) + 6) % 7;
}

//void print_calender(int start_column, int num_days, int month, int year)
//{

//}
