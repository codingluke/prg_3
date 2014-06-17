#include "magic_square.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

using namespace std;

/**
 * Default constructor. Initializises a MagicSquare with
 * an ordinal number of 5.
 */
MagicSquare::MagicSquare()
{
  ordinal_number = 5;
  init_square();
  calculate();
}

/**
 * Initializies a MagicSquare with a odd ordnial number.
 *
 * @param a_ordinal_number      The ordinal number of the MagicSquare.
 *
 * @throw const invalid_argument when ordinal number is even.
 */
MagicSquare::MagicSquare(int a_ordinal_number) throw(const invalid_argument)
{
  if ((a_ordinal_number % 2) == 0)
    throw invalid_argument("Nur ungerade Zahlen sind erlaubt");
  ordinal_number = a_ordinal_number;
  init_square();
  calculate();
}

/**
 * Copy constructor. Deep copy of a new MagicSquare.
 *
 * @param original The original MagicSquare to copy.
 */
MagicSquare::MagicSquare(const MagicSquare& original)
{
  ordinal_number = original.ordinal_number;
  init_square(original.square);
}

/**
 * Dekonstructor. Cleans up memory.
 */
MagicSquare::~MagicSquare()
{
  clear_square();
}

/**
 * Returns the ordinal number of the MagicSquare.
 *
 * @return  the ordinal number.
 */
int MagicSquare::get_ordinal_number() const
{
  return ordinal_number;
}

/**
 * Calculates and returns the magic number of the MagicSquare.
 *
 * @return the magic number of the MagicSquare.
 */
int MagicSquare::get_magic_number() const
{
  return 0.5 * (ordinal_number * ordinal_number + 1) * ordinal_number;
}

/**
 * Generates and returns the string representation of a MagicSquare.
 * \n\n
 * 11   2  25  18   9\n
 * 23  14   7   5  16\n
 *  4  20  13   6  22\n
 * 10  21  19  12   3\n
 * 17   8   1  24  15\n
 *
 * @return string representation fo a MagicScrqare.
 */
string MagicSquare::str() const
{
  ostringstream modifier(ios::out);
  for (int row = 0; row < ordinal_number; row++)
  {
    for (int col = 0; col < ordinal_number; col++)
      modifier << setw(4) << internal << square[row][col];
    modifier << endl;
  }
  return modifier.str();
}

/**
 * Overrides the assignment operator=. Guarantees a correct
 * assignement of a MagicSquare to an other.
 *
 * @param other  The MagicSquare to copy.
 *
 * @return Reference of the copied MagicSquare.
 */
MagicSquare& MagicSquare::operator=(const MagicSquare& other)
{
  if (this != &other)
  {
    clear_square();
    ordinal_number = other.ordinal_number;
    init_square(other.square);
  }
  return *this;
}

bool MagicSquare::operator==(const MagicSquare& other) const
{
  bool equal = false;
  if (ordinal_number == other.ordinal_number)
  {
    equal = true;
    for (int row = 0; equal && row < ordinal_number; row++)
      for (int col = 0; col < ordinal_number; col++)
        if (square[row][col] != other.square[row][col])
          equal = false;
  }
  return equal;
}

bool MagicSquare::operator!=(const MagicSquare& other) const
{
  return !(other == *this);
}


/**
 * Switches two rows which have the same distance from the
 * center.
 *
 * @param index  Distance form top/bottom border.
 *
 * @return a new MagicSquare with switched rows.
 *
 * @throw const out_of_range when index is not valid.
 */
MagicSquare MagicSquare::switch_rows(int index) throw(const out_of_range)
{
  if (index > (ordinal_number / 2))
    throw out_of_range("Nicht erlaubt");
  int *tmp_row = square[index - 1];
  square[index - 1] = square[ordinal_number - index];
  square[ordinal_number - index] = tmp_row;
  return *this;
}

/**
 * Switches two columns which have the same distance from the
 * center.
 *
 * @param index  Distance form left/right border.
 *
 * @return a new MagicSquare with switched columns.
 *
 * @throw const out_of_range when index is not valid.
 */
MagicSquare MagicSquare::switch_columns(int index) throw(const out_of_range)
{
  if (index > (ordinal_number / 2))
    throw out_of_range("Nicht erlaubt");
  int tmp_entry = 0;
  for (int row = 0; row < ordinal_number; row++)
  {
    tmp_entry = square[row][index - 1];
    square[row][index - 1] = square[row][ordinal_number - index];
    square[row][ordinal_number - index] = tmp_entry;
  }
  return *this;
}

/**
 * Mirrors the MagicSquare at the diagonal line form
 * top left to bottom right.
 *
 * @return a new MagicSquare mirrored at the diagonal.
 */
MagicSquare MagicSquare::switch_diagonal_top_left()
{
  int tmp_entry = 0;
  for (int row = 1; row < ordinal_number; row++)
  {
    for (int col = 0; col < row; col++)
    {
      tmp_entry = square[row][col];
      square[row][col] = square[col][row];
      square[col][row] = tmp_entry;
    }
  }
  return *this;
}

/**
 * Mirrors the MagicSquare at the diagonal line form
 * top right to bottom left.
 *
 * @return a new MagicSquare mirrored at the diagonal.
 */
MagicSquare MagicSquare::switch_diagonal_top_right()
{
  int tmp_entry = 0;
  int size = ordinal_number - 1;
  for (int row = 0; row < size; row++)
  {
    for (int col = 0; col < size - row; col++)
    {
      tmp_entry = square[row][col];
      square[row][col] = square[size - col][size - row];
      square[size - col][size - row] = tmp_entry;
    }
  }
  return *this;
}

/**
 * Rotates a MagicSquare 90 degrees in clockwise direction.
 *
 * @return a new MagicSquare rotated 90 degrees clockwise.
 */
MagicSquare MagicSquare::rotate_90()
{
  int size = ordinal_number - 1;
  int **tmp_square = new int*[ordinal_number];
  for (int i = 0; i < ordinal_number; i++)
  {
    tmp_square[i] = new int[ordinal_number];
    for (int j = 0; j < ordinal_number; j++)
      tmp_square[i][j] = 0;
  }
  for (int row = 0; row < ordinal_number; row++)
    for (int col = 0; col < ordinal_number; col++)
      tmp_square[col][size - row] = square[row][col];
  clear_square();
  init_square(tmp_square);
  for (int i = 0; i < ordinal_number; i++)
    delete [] tmp_square[i];
  delete [] tmp_square;
  return *this;
}

/**
 * Initializes the square form a given square.
 *
 * @param **the_square The 2D square array to initialize.
 */
void MagicSquare::init_square(int **the_square)
{
  square = new int*[ordinal_number];
  for (int i = 0; i < ordinal_number; i++)
  {
    square[i] = new int[ordinal_number];
    for (int j = 0; j < ordinal_number; j++)
      square[i][j] = the_square[i][j];
  }
}

/**
 * Initializes a empty (filled with zeros) square.
 */
void MagicSquare::init_square()
{
  square = new int*[ordinal_number];
  for (int i = 0; i < ordinal_number; i++)
  {
    square[i] = new int[ordinal_number];
    for (int j = 0; j < ordinal_number; j++)
      square[i][j] = 0;
  }
}

/**
 * Cleans the square and its sub arrays form memory.
 */
void MagicSquare::clear_square()
{
  for (int i = 0; i < ordinal_number; i++)
    delete [] square[i];
  delete [] square;
}

/**
 * Generates the basic MagicSquare of an odd ordinal number
 * with the "Simon de la Loubère" algorithm.
 */
void MagicSquare::calculate()
{
  int row = 0;
  int column = ordinal_number / 2;
  square[row][column] = 1;
  for (int i = 2; i <= ordinal_number * ordinal_number; i++)
  {
    if (is_top_right(row, column))
      square[++row][column] = i;
    else if (is_in_first_row(row))
    {
      row = ordinal_number - 1;
      square[row][++column] = i;
    }
    else if (is_in_right_column(column))
    {
      column = 0;
      square[--row][column] = i;
    }
    else
    {
      if (is_empty(row - 1, column + 1))
        square[--row][++column] = i;
      else
        square[++row][column] = i;
    }
  }
}

/**
 * Checks if a given field of the square is the field in the
 * top right corner.
 *
 * @param row     Row of the field.
 * @param column  Column of the filed.
 *
 * @return true when the field is in the top right corner.
 *         false when the fiel is not in the top right corner.
 */
bool MagicSquare::is_top_right(int& row, int& column) const
{
  return row == 0 && column == (ordinal_number - 1);
}

/**
 * Checks if a given field of the square is in the first row.
 *
 * @param row     Row of the field.
 *
 * @return true when the field is in the first row.
 *         false when the field is not in the first row.
 */
bool MagicSquare::is_in_first_row(int& row) const
{
  return row == 0;
}

/**
 * Checks if a given field of the square is in the outher right column.
 *
 * @param row     Row of the field.
 * @param column  Column of the filed.
 *
 * @return true when the field is in the right column.
 *         false when the field is not in the right column.
 */
bool MagicSquare::is_in_right_column(int& column) const
{
  return column == (ordinal_number - 1);
}

/**
 * Checks if a field is empty (filled with zero).
 *
 * @param row     Row of the field.
 * @param column  Column of the filed.
 *
 * @return true when the field is empty.
 *         false when the field is not empty.
 */
bool MagicSquare::is_empty(int row, int column) const
{
  return square[row][column] == 0;
}
