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
string just_numbers(string text);
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
      cout << "Beschreibung" << endl;
  }
  else
    cout << "Beschreibung" << endl;
}

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

void solve_sudoku_from_file(string filename)
{
  cout << "Loese Sudoku" << endl;
  string file = read_file(filename);
  if (file.length() > 0)
  {
    try
    {
      string numbers = just_numbers(file);
      Square sudoku_square(9, numbers);
      Sudoku sudoku(sudoku_square);
      if (sudoku.solve())
        cout << "Sudoku:" << endl << sudoku.str() << endl
             << "Sudoku solved:" << endl << sudoku.str_solved();
      else if (sudoku.get_status() == 0)
        cout << "Sudoku nicht lösbar" << endl;
      else if (sudoku.get_status() == 2)
        cout << "Sudoku mehrfach lösbar" << endl;
    }
    catch (const invalid_argument ex)
    {
      cout << ex.what();
    }
  }
}

string just_numbers(string text)
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
