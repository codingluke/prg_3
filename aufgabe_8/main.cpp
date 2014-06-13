#include <iostream>
#include <iomanip>
#include <string>
#include "maumau.h"

using namespace std;

void print_manual();

/**
 * Entrypoint to the program "Maumau".
 * Checks the arguments given by the user and starts a new
 * game for four players. When the option -a is set the game
 * gets completely simulated. When the option -m is set the
 * User will play the Player 1. If the program gets started with
 * invalid parameters, there is a manual shown.
 *
 */
int main(int argc, char *argv[])
{
  if (argc == 2)
  {
    string option = argv[1];
    Maumau game(4);
    if (option == "-a")
      game.start();
    else if (option == "-m")
      game.start(true);
    else
      print_manual();
  }
  else
    print_manual();
}

void print_manual()
{
  cout << "Benutzung des Programms: ./Maumau option" << endl
       << "wobei option" << endl << "  -m :   Spiele Spieler 1 manuell"
       << endl << "  -a :   Spiele alle Spieler automatisch";
}
