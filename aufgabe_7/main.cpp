#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include "lottery.h"
#include "console_input.h"

using namespace std;

bool isi(char text[]);
void start(int number_of_winnings);
void print_actions();

/**
 * Entrypoint to the program "Lottery". Lottery is a Program to simulate
 * and analyze lotto winnings. There are following possibilities to choose
 * from.
 *
 * frequency scale, arrangement of the minima, arrangement of the maxima,
 * arrangement of the lengths, number of winning which has their lengths
 * also as number, number of odd winnings, number of even winnings,
 * number of prim winnings, number of non prim winnings, arrangement of
 * k-street winnings, tip a LotteryWin, automated tipping and generate a
 * neu number of winnings.
 *
 * The program has to be started with one extra parameter including the
 * number of winnings to generate.
 *
 * ./Lottery 5000000
 *
 * @param argc        Length of the arguments array.
 * @param *argv[]     Arguments array form the program execution.
 */
int main(int argc, char *argv[])
{
  if (argc == 2 && isi(argv[1]))
    start(atoi(argv[1]));
  else
    cout << "Benutzung des Programms: ./Lottery n" << endl
         << "wobei n die Anzahl Ziehungen als Nummer angegeben wird."
         << endl;
}

/**
 * Starts the Lottery with a given number of LotteryWins to generate.
 * It then prints out the menu to the console and handles the chosen
 * action by the user.
 *
 * @param number_of_winnings  Number of LotteryWin to generate.
 */
void start(int number_of_winnings)
{
  Lottery the_lottery(number_of_winnings);
  cout << number_of_winnings << " Ziehungen geladen";
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
      int n = read_int("Anzahl der Ziehungen: ", 1, 30000000);
      cout << endl << "Lade " << n << " Ziehungen" << endl;
      the_lottery = Lottery(n);
      cout << n << " Ziehungen geladen!" << endl;
    }
  } while(action != 15);
}

/**
 * Prints the menu with the possible actions to the console.
 */
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

/**
 * Checks whether an array of chars represents an integer or not.
 * Solfs atoi problem that returns a 0 for a char which is not a number.
 *
 * @param text[] Array of chars.
 *
 * @return true when text[] represents a number.
 *         false when text[] doesn't represent a number.
 */
bool isi(char text[])
{
  int i;
  std::istringstream in(text);
  return in >> i && in.eof();
}
