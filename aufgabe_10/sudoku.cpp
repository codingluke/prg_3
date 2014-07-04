#include <iostream>
#include <iomanip>
#include "sudoku.h"
#include <sstream>
#include <string>
#include "time.h"
#include <cstdlib>
#include <stdexcept>

using namespace std;

/**
 * Static parameter to flag if random seed is already set.
 */
bool Sudoku::rand_seeded = false;

/**
 * Default constructor. Initializes a unique sudoku with 26 presetted numbers.
 */
Sudoku::Sudoku() : unsolved(9), solved(9)
{
  seed_rand();
  generate_unique(26);
}

/**
 * Initializes a unique Sudoku with a given ordinal number.
 *
 * @param ordinal   Number of presetted numbers in the Sudoku.
 *
 * @throw const invalid_argument when ordinal number is not between 24 and 34.
 */
Sudoku::Sudoku(int ordinal) throw(const invalid_argument)
  : unsolved(9), solved(9)
{
  if (ordinal <= 24 || ordinal >= 34)
    throw invalid_argument("Ungueltige Ordnung! Nur Ordnungen zwischen 24 - 34 erlaupt!");
  seed_rand();
  generate_unique(ordinal);
}

/**
 * Initializes a Sudoku out of a given Square.
 *
 * @param the_unsolved  The Square of the Sudoku.
 *
 * @throw const invalid_argument when square can not be devided by 3.
 */
Sudoku::Sudoku(const Square& the_unsolved) throw(const invalid_argument)
  : unsolved(the_unsolved), solved(the_unsolved)
{
  if (the_unsolved.get_ordinal() % 3 != 0)
  {
    unsolved = Square(9);
    solved = unsolved;
    throw invalid_argument("Ungueltige Quadratgroesse!");
  }
}

/**
 * Solves the sudoku. Gives back true when the sudoku is solved and is
 * unique. Gives back false when the Sudoku can not be solved or is not
 * unique.
 *
 * @return true when the Sudoku is unique and can be solved.
 *         false when the Sudoku is not unique or can not be solved.
 */
bool Sudoku::solve()
{
  bool valid = true;
  int round = 0;
  int tmp_col = 0;
  int first_col = first_empty_col();
  int last_col = last_empty_col();
  int ordinal = unsolved.get_ordinal();
  Square tmp_solved(ordinal);
  for (int row = 0; valid && row < ordinal; row++)
    for (int col = 0; valid && col < ordinal; col++)
      if (is_empty(row, col))
      {
        if (!auto_set_field(row, col, first_col))
        {
          if (solved[row][col] == -1)
            valid = false;
          tmp_col = prev_empty_col(row, col);
          if (tmp_col > col)
            row--;
          col = tmp_col - 1;
        }
        else
        {
          if (row == (ordinal - 1) && col == last_col)
          {
            round++;
            if (round < 2)
              col -= 2;
            if (round == 1)
              tmp_solved = solved;
          }
        }
      }
  if (round == 1)
    valid = true;
  else if (round == 2)
    valid = solved == tmp_solved;
  solved = tmp_solved;
  return valid;
}

/**
 * Gives out the previous empty column of a given field.
 *
 * @param row  The row of the field.
 * @param col  The column of the field.
 *
 * @return previous column.
 */
int Sudoku::prev_empty_col(int row, int col) const
{
  do
  {
    if (col == 0 && row > 0)
    {
      row--;
      col = 8;
    }
    else if (col > 0)
      col--;
  } while (!is_empty(row, col) && !(row == 0 && col == 0));
  return col;
}

/**
 * Checks whether a number is valid and sets the number to a given field.
 *
 * @param row     Row of the field.
 * @param col     Column of the field.
 * @param number  Number to set.
 *
 * @return true when number is valid and added.
 *         false when number is not valid.
 */
bool Sudoku::set_field(int row, int col, int number)
{
  return set_field(row, col, number, unsolved);
}

/**
 * Check whether a number is valid an adds the number to a given field
 * in a given Square.
 *
 * @param row     Row of the field.
 * @param col     Column of the field.
 * @param number  Number to set.
 * @param square  Square to add the number.
 *
 * @return true when number is valid and added.
 *         false when number is not valid.
 */
bool Sudoku::set_field(int row, int col, int number, Square& square)
{
  bool valid = true;
  int tmp = square[row][col];
  square[row][col] = number;
  if (!validate_square_by_field(row, col, square) ||
      !validate_col(col, square) || !validate_row(row, square))
  {
    square[row][col] = tmp;
    valid = false;
  }
  return valid;
}

/**
 * Returns the first empty column of the Sudoku.
 *
 * @return first empty column of the Sudoku.
 */
int Sudoku::first_empty_col() const
{
  int empty = -1;
  for (int col = 0; empty == -1 && col < unsolved.get_ordinal(); col++)
    if (is_empty(0, col))
      empty = col;
  return empty;
}

/**
 * Returns the last empty column of the Sudoku.
 *
 * @return  last empty column of the Sudoku.
 */
int Sudoku::last_empty_col() const
{
  int empty = -1;
    for (int col = unsolved.get_ordinal() - 1; empty == -1 && col > -1; col--)
      if (is_empty(unsolved.get_ordinal() - 1, col))
        empty = col;
  return empty;
}

/**
 * Setts automatically the next valid Number for a given field.
 * When there is no next valid number, it setts a zero in the field.
 * When it is the first column, it setts a -1 to show. That the Sudoku
 * can not be solved.
 *
 * @param row       Row of the field.
 * @param col       Column of the field.
 * @param first_col First column of the field.
 *
 * @return true when it was possible to set a next number.
 *         false when it was not possible to set a next number.
 */
bool Sudoku::auto_set_field(int row, int col, int first_col)
{
  bool valid = false;
  int ordinal = solved.get_ordinal();
  if (solved[row][col] < ordinal)
    for (int i = solved[row][col] + 1; !valid && i < ordinal + 1; i++)
      valid = set_field(row, col, i, solved);
  if (!valid && row == 0 && col == first_col)
    solved[row][col] = -1;
  else if (!valid)
    solved[row][col] = 0;
  return valid;
}

/**
 * Returns a string representation of the unsolved Sudoku.
 *
 * @return string representation of the unsolved Sudoku.
 */
string Sudoku::str() const
{
  ostringstream modifier(ios::out);
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      modifier << setw(3) << unsolved[i][j];
      if ((j + 1) % 3 == 0)
        modifier << " ";
    }
    modifier << endl;
    if ((i + 1) % 3 == 0)
      modifier << endl;
  }
  return modifier.str();
}

/**
 * Returns a string representation of the solved Sudoku.
 *
 * @return string representation of the solved Sudoku.
 */
string Sudoku::str_solved() const
{
  ostringstream modifier(ios::out);
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      modifier << setw(3) << solved[i][j];
      if ((j + 1) % 3 == 0)
        modifier << " ";
    }
    modifier << endl;
    if ((i + 1) % 3 == 0)
      modifier << endl;
  }
  return modifier.str();
}

/**
 * Generates a random unique Sudoku of a given ordinal number.
 *
 * @param ordinal  Ordinal number of the generated Sudoku.
 */
void Sudoku::generate_unique(int ordinal)
{
  do
  {
    unsolved = Square(9);
    generate(ordinal);
    solved = unsolved;
  } while(!solve());
  solved = unsolved;
}

/**
 * Generates a random Sudoku of a given ordinal number. The generated
 * Sudoku has not to be unique nor solvable.
 *
 * @param oridnal  Ordinal number of the generated Sudoku.
 */
void Sudoku::generate(int oridnal)
{
  int number = 0;
  int col = 0;
  int row = 0;
  for (int i = 0; i < oridnal; i++)
  {
    do
    {
      number = (1 + char(9 * (rand() / (RAND_MAX + 1.0))));
      col = (char(9 * (rand() / (RAND_MAX + 1.0))));
      row = (char(9 * (rand() / (RAND_MAX + 1.0))));
    } while (!is_empty(row, col) || !set_field(row, col, number));
  }
}

/**
 * Checks if a given field is empty (in the unsolved sudoku) or not.
 *
 * @param row  Row of the field.
 * @param col  Column of the field.
 *
 * @return true when the field is empty.
 *         false when the field is not empty.
 */
bool Sudoku::is_empty(int row, int col) const
{
  return unsolved[row][col] == 0;
}

/**
 * Validates if a given column from a Square fullfills the sudoku column rule.
 *
 * @param col     Column to check.
 * @param square  Square in which to check.
 *
 * @return true when the column fullfills the rule.
 */
bool Sudoku::validate_col(int col, Square& square)
{
  bool valid = true;
  bool numbers[10] = {
    false, false, false, false, false,
    false, false, false, false, false
  };
  int tmp_number = 0;
  for (int row = 0; valid && row < 9; row++)
  {
    tmp_number = square[row][col];
    valid = numbers[tmp_number] != true || tmp_number == 0;
    numbers[tmp_number] = true;
  }
  return valid;
}

/**
 * Validates if a given row of a Square fullfills the sudoku row rule.
 *
 * @param row     Row to check.
 * @param square  Square in which to check.
 *
 * @return true when the row fullfills the rule.
 */
bool Sudoku::validate_row(int row, Square& square)
{
  bool valid = true;
  bool numbers[10] = {
    false, false, false, false, false,
    false, false, false, false, false
  };
  int tmp_number = 0;
  for (int col = 0; valid && col < 9; col++)
  {
    tmp_number = square[row][col];
    valid = numbers[tmp_number] != true || tmp_number == 0;
    numbers[tmp_number] = true;
  }
  return valid;
}

/**
 * Validates if a subsquare fullfills the sudoku subsquare rule.
 * The subsuqre gets identified by a given field of the Sudoku.
 *
 * @param row     Row of a field inside the subsquare.
 * @param col     Column of a field inside the subsquare.
 * @param square  The sudoku square to check in.
 *
 * @return true when the subsquare fullfills the rule.
 */
bool Sudoku::validate_square_by_field(int x, int y, Square& square)
{
  bool valid = true;
  bool numbers[10] = {
    false, false, false, false, false,
    false, false, false, false, false
  };
  int ranges[3][3] = {{0, 1, 2},{3, 4, 5},{6, 7, 8}};
  int x_range = range_number(x);
  int y_range = range_number(y);
  int tmp_number = 0;
  for (int i = 0; valid && i < 3; i++)
    for (int j = 0; valid && j < 3; j++)
    {
      tmp_number = square[ranges[x_range][i]][ranges[y_range][j]];
      valid = numbers[tmp_number] != true || tmp_number == 0;
      numbers[tmp_number] = true;
    }
  return valid;
}

int Sudoku::range_number(int number) const
{
  int range = 0;
  if (number > 2 && number < 6)
    range = 1;
  else if (number > 5)
    range = 2;
  return range;
}

/**
 * Initializes srand and sets the flag to guarantee that srand gets
 * initialized just once.
 */
void Sudoku::seed_rand()
{
  if(!rand_seeded)
  {
    srand(time(0));
    rand_seeded = true;
  }
}
