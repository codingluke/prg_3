#include <iostream>
#include "console_input.h"
#include "console_output.h"
#include "date.h"
#include "gregorian_calender.h"

using namespace std;

void print_actions()
{
  cout << "Waehle eine option:\n";
  cout << "1) Kalender erstellen:\n";
  cout << "2) Anzahl Tage zwischen zwei Datumsangaben berechnen:\n";
  cout << "3) Programm beenden\n";
}

void generate_and_print_calendar()
{
  cout << "\n";
  int year = read_int("Jahr angeben:\t", 1583, 1000000);
  int month = read_int("Monat angeben:\t", 1, 12);
  cout << "\n";
  print_calendar(month, year);
  cout << "\n";
}

void calc_and_print_days_between_dates()
{
  cout << "\n";
  Date date1 = read_date("Erstes Datum eingeben:");
  Date date2 = read_date("Zweites Datum eingeben:");
  int days_bewteen = calc_days_between_dates(date1, date2);
  cout << "Tage zwischen den daten: " << days_bewteen << "\n\n";
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

