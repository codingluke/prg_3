#include "magic_square.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

using namespace std;

MagicSquare::MagicSquare()
{
  ordinal_number = 5;
  init_square();
  calculate();
}

MagicSquare::MagicSquare(int a_ordinal_number)
{
  ordinal_number = a_ordinal_number;
  init_square();
  calculate();
}

MagicSquare::MagicSquare(const MagicSquare& original)
{
  ordinal_number = original.ordinal_number;
  init_square(original.square);
}

MagicSquare::~MagicSquare()
{
  clear_square();
}


MagicSquare MagicSquare::switch_rows(int index) throw(const out_of_range)
{
  if (index > (ordinal_number / 2))
    throw out_of_range("Nicht erlaubt");
  int *tmp_row = square[index - 1];
  square[index - 1] = square[ordinal_number - index];
  square[ordinal_number - index] = tmp_row;
  return *this;
}

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

string MagicSquare::str() const
{
  ostringstream modifier(ios::out);
  for (int i = 0; i < ordinal_number; i++)
  {
    for (int j = 0; j < ordinal_number; j++)
      modifier << setw(4) << internal << square[i][j];
    modifier << endl;
  }
  return modifier.str();
}

MagicSquare& MagicSquare::operator=(const MagicSquare& other)
{
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

void MagicSquare::clear_square()
{
  for (int i = 0; i < ordinal_number; i++)
    delete [] square[i];
  delete [] square;
}

void MagicSquare::calculate()
{
  int row = 0;
  int column = ordinal_number / 2;
  square[row][column] = 1;
  for (int i = 2; i <= ordinal_number * ordinal_number; i++)
  {
    if (is_top_right(row, column))
      square[++row][column] = i;
    else if (is_in_first_row(row, column))
    {
      row = ordinal_number - 1;
      square[row][++column] = i;
    }
    else if (is_in_right_column(row, column))
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

bool MagicSquare::is_top_right(int& row, int& column) const
{
  return row == 0 && column == (ordinal_number - 1);
}

bool MagicSquare::is_in_first_row(int& row, int& column) const
{
  return row == 0 && !is_top_right(row, column);
}

bool MagicSquare::is_in_right_column(int& row, int& column) const
{
  return column == (ordinal_number - 1) && !is_top_right(column, row);
}

bool MagicSquare::is_empty(int row, int column) const
{
  return square[row][column] == 0;
}
