#include <iostream>
#include "console_input.h"
#include "date.h"
#include "gregorian_calender.h"

using namespace std;

void print_actions()
{
  cout << "Waehle eine option:\n" << "1) Kalender erstellen:" << endl
       << "2) Anzahl Tage zwischen zwei Datumsangaben berechnen:" << endl
       << "3) Programm beenden\n";
}

void generate_and_print_calendar()
{
  cout << endl;
  int year = read_int("Jahr angeben:\t", 1583, 1000000);
  int month = read_int("Monat angeben:\t", 1, 12);
  cout << endl;
  print_calendar(month, year);
  cout << endl;
}

void calc_and_print_days_between_dates()
{
  cout << endl;
  Date date1 = read_date("Erstes Datum eingeben:");
  Date date2 = read_date("Zweites Datum eingeben:");
  int days_bewteen = calc_days_between_dates(date1, date2);
  cout << "Tage zwischen den Daten: " << days_bewteen << endl << endl;
}

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
  cout << "Byebye";
}

