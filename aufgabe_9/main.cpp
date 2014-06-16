#include "magic_square.h"
#include "magic_square_set.h"
#include <iostream>
#include <iomanip>

/**
 * Entrypoint to the program "Fahrkartenautomat".
 * Creates and starts an Instance of TicketMachine with
 * Euro as currency and a list of accepted coins for
 * the paiment.
 */
int main()
{
  int counter = 0;
  int ordinal_number = 7;
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

  for (int i = 0; i < myset.size(); i++)
    cout << myset[i].str() << endl << endl;

  cout << "Size: " << myset.size() << endl;
}
