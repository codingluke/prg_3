#include <iostream>
#include <iomanip>
#include "lottery.h"
#include "console_input.h"

void print_actions();

/**
 * Entrypoint to the program "Fahrkartenautomat".
 * Creates and starts an Instance of TicketMachine with
 * Euro as currency and a list of accepted coins for
 * the paiment.
 */
int main()
{
  Lottery the_lottery(1000);
  cout << "1000 Ziehungen geladen";
  int action = 0;
  do
  {
    print_actions();
    action = read_int("Ihre Wahl: ", 1, 15);
    if (action == 1)
      cout << endl << the_lottery.str_years_to_play();
    else if (action == 2)
      cout << endl << the_lottery.str_frequency_scale();
    else if (action == 3)
      cout << endl << the_lottery.str_minimum();
    else if (action == 4)
      cout << endl << the_lottery.str_maximum();
    else if (action == 5)
      cout << endl << the_lottery.str_length();
    else if (action == 6)
      cout << endl << the_lottery.str_count_length_in_win();
    else if (action == 7)
      cout << endl << the_lottery.str_count_even();
    else if (action == 8)
      cout << endl << the_lottery.str_count_odd();
    else if (action == 9)
      cout << endl << the_lottery.str_count_prim();
    else if (action == 10)
      cout << endl << the_lottery.str_count_not_prim();
    else if (action == 11)
      cout << endl << the_lottery.str_count_street_types();
    else if (action == 12)
      cout << endl << the_lottery.tip();
    else if (action == 13)
      cout << endl << the_lottery.autotip();
    else if (action == 14)
    {
      int n = read_int("Anzahl der Ziehungen: ", 1, 60000000);
      cout << endl << "Lade " << n << " Ziehungen" << endl;
      the_lottery = Lottery(n);
      cout << n << " Ziehungen geladen!" << endl;
    }
  } while(action != 15);
  cout << "byebye!";
}

void print_actions()
{
  cout << endl << "Bitte waehlen:" << endl
       << "(1) Information" << endl
       << "(2) Haeufigkeitsverteilung" << endl
       << "(3) Verteilung der Minima" << endl
       << "(4) Verteilung der Maxima" << endl
       << "(5) Verteilung der Ziehungslaengen" << endl
       << "(6) Anzahl Ziehungen, die ihre Laenge enthalten" << endl
       << "(7) Anzahl gerade Ziehungen" << endl
       << "(8) Anzahl ungerade Ziehungen" << endl
       << "(9) Anzahl Primziehungen" << endl
       << "(10) Anzahl Nichtprimziehungen" << endl
       << "(11) Verteilung der k-Ziehungen" << endl
       << "(12) Tippen" << endl
       << "(13) Automatisch Tippen" << endl
       << "(14) Neue Ziehungen" << endl
       << "(15) Beenden" << endl;
}
