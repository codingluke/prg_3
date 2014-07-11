#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cstdlib>
#include <sstream>
#include <string>
#include "file_controller.h"
#include "sudoku.h"
#include "square.h"

using namespace std;

void generate_sudoku(int ordinal);
void solve_sudoku_from_file(string filename);
void print_description();
string extract_numbers(string text);
bool isi(string text);

/**
 * Entrypoint to the program "Sudoku".
 *
 * @param argc    Number of arguments given.
 * @param argv[]  Array of the given arguments.
 */
int main(int argc, char *argv[])
{
  if (argc == 3)
  {
    string option = argv[1];
    if (option == "-g")
      generate_sudoku(atoi(argv[2]));
    else if (option == "-s")
    {
      string filename = argv[2];
      solve_sudoku_from_file(filename);
    }
    else
      print_description();
  }
  else
    print_description();
}

/**
 * Prints out the description to use the program to the console.
 */
void print_description()
{
  cout << "Das Program kann wie folgt gestartet werden." << endl << endl
       << "  ./Sudoku -g n" << endl
       << "  ./Sudoku -s dateiname" << endl << endl
       << "wobei:" << endl
       << "  n\t\tOrdnung des Sudokus" << endl
       << "  dateiname\tName der datei mit einem Sudoku" << endl << endl
       << "Das Sudoku muss in der Datei in folgendem Format sein:"
       << endl << endl
       << "  3 5 0  0 0 0  0 0 0" << endl
       << "  0 0 0  0 1 7  0 0 0" << endl
       << "  8 0 0  0 3 0  0 0 0" << endl << endl
       << "  4 0 9  6 0 3  0 0 5" << endl
       << "  0 0 1  4 0 0  6 9 8" << endl
       << "  0 8 0  0 0 0  0 0 4" << endl << endl
       << "  0 0 0  0 0 0  7 0 0" << endl
       << "  0 0 0  0 4 0  9 0 3" << endl
       << "  0 0 5  0 0 0  0 6 2" << endl;
}

/**
 * Generates a Sudoku of a given ordinal number, solves it and
 * prints the result out to the console.
 *
 * @param ordinal  The ordnial number of the Sudoku to generate.
 */
void generate_sudoku(int ordinal)
{
  cout << "Ich erzeuge ein Sudoku. Bitte warten ..." << endl << endl;
  try
  {
    Sudoku sudoku(ordinal);
    sudoku.solve();
    cout << "Sudoku der Ordnung " << ordinal << ":" << endl << endl
         << sudoku.str() << endl
         << "Loesung:" << endl << endl << sudoku.str_solved();
  }
  catch (const invalid_argument ex)
  {
    cout << ex.what();
  }
}

/**
 * Reads a file by its filename. When the file contains Numbers
 * in form of a Sudoku, it tries to solve the Sudoku.
 * When the Sudoku is solvable and unique it gives out the solved
 * sudoku. Otherwise, it gives out whether the Sudoku is not solvable or not
 * unique.
 *
 * @param filename  Name of the File containing the Sudoku.
 */
void solve_sudoku_from_file(string filename)
{
  cout << "Loese Sudoku" << endl;
  string file = read_file(filename);
  if (file.length() > 0)
  {
    try
    {
      string numbers = extract_numbers(file);
      Square sudoku_square(9, numbers);
      Sudoku sudoku(sudoku_square);
      sudoku.solve();
      cout << "Sudoku:" << endl << sudoku.str() << endl
           << "Sudoku solved:" << endl << sudoku.str_solved();
    }
    catch (const invalid_argument ex)
    {
      cout << ex.what();
    }
  }
}

/**
 * Extracts numbers out of a string and returns them as a new string.
 *
 * @param text  The string with numbers in it.
 *
 * @return new string just with numbers.
 */
string extract_numbers(string text)
{
  string result = "";
  for(unsigned int i = 0; i < text.length(); i++)
  {
    string single_char = text.substr(i, 1);
    if (isi(single_char))
      result += single_char;
  }
  return result;
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
bool isi(string text)
{
  int i;
  std::istringstream in(text);
  return in >> i && in.eof();
}
