#include "magic_square.h"
#include "magic_square_set.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cstdlib>

void run(int ordinal_number) throw(const invalid_argument);

/**
 * Entrypoint to the program "Fahrkartenautomat".
 * Creates and starts an Instance of TicketMachine with
 * Euro as currency and a list of accepted coins for
 * the paiment.
 */
int main(int argc, char *argv[])
{
  if (argc == 2)
  {
    try
    {
      run(atoi(argv[1]));
    }
    catch(const invalid_argument ex)
    {
      cout << ex.what() << endl << "Beschreibung";
    }
  }
  else
  {
    cout << "Beschreibung";
  }
}

void run(int ordinal_number) throw(const invalid_argument)
{
  if ((ordinal_number % 2) == 0)
    throw invalid_argument("Nur ungerade Zahlen sind erlaubt");
  int counter = 0;
  int num_rows_to_switch = ordinal_number / 2;
  MagicSquareSet myset;
  myset.add(MagicSquare(ordinal_number));
  do
  {
    for (int i = 1; i <= num_rows_to_switch; i++)
    {
      myset.add(myset[counter].switch_rows(i));
      myset.add(myset[counter].switch_columns(i));
    }
    myset.add(myset[counter].switch_diagonal_top_left());
    myset.add(myset[counter].switch_diagonal_top_right());
    myset.add(myset[counter].switch_diagonal_top_right());
    myset.add(myset[counter].rotate_90());
    myset.add(myset[counter].rotate_90().rotate_90());
    myset.add(myset[counter].rotate_90().rotate_90().rotate_90());
    counter++;
  } while(myset.size() > counter);
  cout << myset.str();
}
