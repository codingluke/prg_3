#include <iostream>
#include "console_input.h"
#include "gregorian_calender.h"
#include "date.h"

using namespace std;

/**
 * Prints a description of the available actions to the console.
 */
void print_actions()
{
  cout << "Waehle eine option:" << endl
       << "  1) Kalender erstellen:" << endl
       << "  2) Anzahl Tage zwischen zwei Datumsangaben berechnen:" << endl
       << "  3) Programm beenden" << endl;
}

void print_goodbye()
{
  cout << "Byebye";
}

/**
 * Promts the user to enter a month of a year, and prints the according
 * gregorian calender to the console.
 */
void generate_and_print_calendar()
{
  cout << endl;
  int year = read_int("Jahr angeben:\t", 1583, 1000000);
  int month = read_int("Monat angeben:\t", 1, 12);
  cout << endl;
  print_calendar(month, year);
  cout << endl;
}

/**
 * Promts the user to enter two dates, calculates the days between them
 * and prints the result to the console.
 */
void calc_and_print_days_between_dates()
{
  cout << endl;
  Date date1 = read_date("Erstes Datum eingeben:");
  Date date2 = read_date("Zweites Datum eingeben:");
  int days_bewteen = calc_days_between_dates(date1, date2);
  cout << "Zwischen dem " << date1.day << "." << date1.month << "." << date1.year
       << " und dem " << date2.day << "." << date2.month << "." << date2.year
       << " liegen " << days_bewteen << " Tage." << endl << endl;
}
