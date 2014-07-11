#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cstdlib>
#include <sstream>
#include <string>
#include "magic_square.h"
#include "magic_square_set.h"
#include "file_controller.h"

using namespace std;

void run(int ordinal_number);
void print_description();

/**
 * Entrypoint to the program "MagicSquare".
 * It checks if the given arguments are valid and runs the square generation.
 * Out of a basic MagicSquare with a given ordinal, the program generates
 * several different combination by mutating the Square with four rules.
 *
 * 1. Switch two rows which have from their bottom/top border a same distance.
 * 2. Switch two cols wich have from their left/right broder the same distance
 * 3. Mirror the Square by their two diagonal lines.
 * 4. Rotate the Square 90, 180 and 270 degrees clockwise.
 *
 * The Program needs one extra parameter "n" which defines the ordinal
 * number for the basic Magic Square. The number must be a odd number other
 * wise the algorighm by de la Loubère is not working properly.
 *
 * @param argc    Number of arguments given.
 * @param argv[]  Array of the given arguments.
 */
int main(int argc, char *argv[])
{
  if (argc == 2)
    run(atoi(argv[1]));
  else
    print_description();
}

/**
 * Prints out the description to use the program to the console.
 */
void print_description()
{
  cout << "Das Program kann wie folgt gestartet werden." << endl << endl
       << "  ./Magic n" << endl << endl
       << "wobei:" << endl
       << "  n\t\tOrdnung des Magic Squares (nur Ungerade Zahlen)" << endl;
}

/**
 * Generates a basic MagicSquare out of a given ordinal number. Adds
 * this number to a list of unique magic squares. Generates and adds
 * also all the possible combinations to the list.
 * Iterates over the list and generates and repeates the process for
 * the new added magic squares until no new combination is found.
 * Then it gives out all the MagicSquares to the console and writes
 * them to a filed named "Magisch_<ordinal_number>.txt".
 *
 * @param ordinal_number  The ordinal number of the basic MagicSquare.
 */
void run(int ordinal_number)
{
  try
  {
    int counter = 0;
    int num_rows_to_switch = ordinal_number / 2;
    MagicSquareSet myset;
    myset.add(new MagicSquare(ordinal_number));
    do
    {
      MagicSquare square = myset[counter];
      for (int i = 1; i <= num_rows_to_switch; i++)
      {
        myset.add(new MagicSquare(square.switch_rows(i)));
        myset.add(new MagicSquare(square.switch_columns(i)));
      }
      myset.add(new MagicSquare(square.switch_diagonal_top_left()));
      myset.add(new MagicSquare(square.switch_diagonal_top_right()));
      myset.add(new MagicSquare(square.rotate_90()));
      myset.add(new MagicSquare(square.rotate_90().rotate_90()));
      myset.add(new MagicSquare(square.rotate_90().rotate_90().rotate_90()));
      counter++;
    } while(myset.size() > counter);
    string output = myset.str();
    cout << output << endl;
    ostringstream filename;
    filename << "magisch_" << ordinal_number << ".txt";
    write_to_file(filename.str(), output, false);
  }
  catch (const invalid_argument ex)
  {
    cout << ex.what() << endl;
  }
}
