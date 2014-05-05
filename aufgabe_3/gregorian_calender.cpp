#include <iostream>
#include "console_output.h"
#include "io_util.h"
#include "date.h"

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
 * calcs the amount of days for the given month and year.
 *
 * @param month   the month.
 * @param year    the year.
 *
 * @return amounth the amounth of days of the month.
 */
int calc_days_of_month(int month, int year)
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
 * calc with a given date how many days are past since
 * the 1.1.1583.
 *
 * @param day     the day of the date.
 * @param month   the month of the date.
 * @param year    the year of the date.
 *
 * @return amouth the amouth days past since 1.1.1583.
 */
int calc_days_since_the_beginning(int day, int month, int year)
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
      amouth += calc_days_of_month(j, year);
  return (amouth + (day - 1));
}

/**
 * Calculates the days in between two dates. The order of the dates
 * is not important.
 *
 * @param date1   first date to calculate days in between.
 * @param date2   second date to calculate days in between.
 *
 * @return days in between the given dates.
 */
int calc_days_between_dates(Date date1, Date date2)
{
  int days1 = calc_days_since_the_beginning(date1.day, date1.month, date1.year);
  int days2 = calc_days_since_the_beginning(date2.day, date2.month, date2.year);
  if (days1 < days2)
    swap(days1, days2);
  return days1 - days2;
}

/**
 * calcs for a given month and year the start column of
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
int calc_start_column(int month, int year)
{
  int days = calc_days_since_the_beginning(1, month, year);
  return ((days % 7) + 6) % 7;
}

/**
 * Prints a line of a given sign for a given length to the console.
 *
 * @param sign    sign to print the line with.
 * @param length  length of the line.
 */
void print_line(char* sign, int length)
{
  cout << "\n";
  for (int i = 0; i < length; i++)
    cout << sign;
  cout << "\n";
}

/**
 * Prints days in the format of a Calendar to the console. Days before
 * the start_column are filled empty.
 *
 *       1     2    3     4     5     6
 * 7     8     9    10    11    12    13
 * 14    15    16   17    18    19    20
 * 21    22    23   24    25    26    27
 * 28    29    30
 *
 * @param start_column  column of the first day.
 * @param num_days      amouth of days to print.
 */
void print_days(int start_column, int num_days)
{
  int column = 0;
  while (column < start_column)
  {
    string empty_day = "      ";
    write_text(empty_day, 6, cout.left);
    column++;
  }
  for (int day = 1; day <= num_days; day++)
  {
    streamsize fieldwith = 6;
    write_number((long)day, fieldwith, cout.left);
    column++;
    if (column == 7)
    {
      column = 0;
      if (day != num_days)
        cout << "\n";
    }
  }
}

/**
 * Prints the calendar of a given month and year to the console.
 *
 * @param month         month of the calendar.
 * @param year          year of the calendar.
 */
void print_calendar(int month, int year)
{
  int start_column = calc_start_column(month, year);
  int num_days = calc_days_of_month(month, year);
  string month_names[] = {
    "Januar", "Februar", "Maerz", "April", "Mai", "Juni",
    "Juli", "August", "September", "Oktober", "November",
    "Dezember"
  };
  string day_names[] = {"So", "Mo", "Di", "Mi", "Do", "Fr", "Sa"};
  write_text(month_names[month - 1], 10, cout.left);
  write_number((long)year, cout.left);
  cout << "\n\n";
  for (int i = 0; i < 7; i++)
    write_text(day_names[i], 6, cout.left);
  char sign[] = "=";
  print_line(sign, 40);
  print_days(start_column, num_days);
  print_line(sign, 40);
}
