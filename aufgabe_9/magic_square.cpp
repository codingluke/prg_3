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
  ordinal = 5;
  init();
  calculate();
}

/**
 * Initializies a MagicSquare with a odd ordnial number.
 *
 * @param a_ordinal      The ordinal number of the MagicSquare.
 *
 * @throw const invalid_argument when ordinal number is even.
 */
MagicSquare::MagicSquare(int a_ordinal) throw(const invalid_argument)
{
  if ((a_ordinal % 2) == 0)
    throw invalid_argument("Nur ungerade Zahlen sind erlaubt");
  ordinal = a_ordinal;
  init();
  calculate();
}

/**
 * Calculates and returns the magic number of the MagicSquare.
 *
 * @return the magic number of the MagicSquare.
 */
int MagicSquare::get_magic_number() const
{
  return 0.5 * (ordinal * ordinal + 1) * ordinal;
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
  for (int row = 0; row < ordinal; row++)
  {
    for (int col = 0; col < ordinal; col++)
      modifier << setw(4) << internal << data[row][col];
    modifier << endl;
  }
  return modifier.str();
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
  if (index > (ordinal / 2))
    throw out_of_range("Nicht erlaubt");
  int *tmp_row = data[index - 1];
  data[index - 1] = data[ordinal - index];
  data[ordinal - index] = tmp_row;
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
  if (index > (ordinal / 2))
    throw out_of_range("Nicht erlaubt");
  int tmp_entry = 0;
  for (int row = 0; row < ordinal; row++)
  {
    tmp_entry = data[row][index - 1];
    data[row][index - 1] = data[row][ordinal - index];
    data[row][ordinal - index] = tmp_entry;
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
  for (int row = 1; row < ordinal; row++)
  {
    for (int col = 0; col < row; col++)
    {
      tmp_entry = data[row][col];
      data[row][col] = data[col][row];
      data[col][row] = tmp_entry;
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
  int size = ordinal - 1;
  for (int row = 0; row < size; row++)
  {
    for (int col = 0; col < size - row; col++)
    {
      tmp_entry = data[row][col];
      data[row][col] = data[size - col][size - row];
      data[size - col][size - row] = tmp_entry;
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
  int size = ordinal - 1;
  int **tmp_square = new int*[ordinal];
  for (int i = 0; i < ordinal; i++)
  {
    tmp_square[i] = new int[ordinal];
    for (int j = 0; j < ordinal; j++)
      tmp_square[i][j] = 0;
  }
  for (int row = 0; row < ordinal; row++)
    for (int col = 0; col < ordinal; col++)
      tmp_square[col][size - row] = data[row][col];
  clear();
  init(tmp_square);
  for (int i = 0; i < ordinal; i++)
    delete [] tmp_square[i];
  delete [] tmp_square;
  return *this;
}

/**
 * Generates the basic MagicSquare of an odd ordinal number
 * with the "Simon de la Loubère" algorithm.
 */
void MagicSquare::calculate()
{
  int row = 0;
  int column = ordinal / 2;
  data[row][column] = 1;
  for (int i = 2; i <= ordinal * ordinal; i++)
  {
    if (is_top_right(row, column))
      data[++row][column] = i;
    else if (is_in_first_row(row))
    {
      row = ordinal - 1;
      data[row][++column] = i;
    }
    else if (is_in_right_column(column))
    {
      column = 0;
      data[--row][column] = i;
    }
    else
    {
      if (is_empty(row - 1, column + 1))
        data[--row][++column] = i;
      else
        data[++row][column] = i;
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
  return row == 0 && column == (ordinal - 1);
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
  return column == (ordinal - 1);
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
  return data[row][column] == 0;
}
