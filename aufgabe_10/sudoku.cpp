#include <iostream>
#include <iomanip>
#include "sudoku.h"
#include <sstream>
#include <string>
#include "time.h"
#include <cstdlib>

using namespace std;

bool Sudoku::rand_seeded = false;

Sudoku::Sudoku() : unsolved(9), solved(9)
{
  seed_rand();
}

Sudoku::Sudoku(int ordinal) : unsolved(9), solved(9)
{
  seed_rand();
  //init_grid();
  generate_unique(ordinal);
}

//Sudoku::Sudoku(int a_grid[9][9])
//{
  //seed_rand();
  //init_grid(a_grid);
  //prepare_solved_grid();
//}

Sudoku::Sudoku(const Sudoku& original)
{
  seed_rand();
  solved = original.solved;
  unsolved = original.unsolved;
  //init_grid(original.grid);
}

Sudoku::~Sudoku()
{
  //clear_grid();
}

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
  {
    for (int col = 0; valid && col < ordinal; col++)
    {
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
          if (row == 8 && col == last_col)
          {
            round++;
            if (round < 2)
              col -= 2;
            if (round == 1)
              tmp_solved = solved;
          }
        }
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

bool Sudoku::set_field(int x, int y, int number)
{
  return set_field(x, y, number, unsolved);
}

bool Sudoku::set_field(int x, int y, int number, Square& square)
{
  bool valid = true;
  int tmp = square[x][y];
  square[x][y] = number;
  if (!validate_square_by_field(x, y, square) ||
      !validate_col(y, square) || !validate_row(x, square))
  {
    square[x][y] = tmp;
    valid = false;
  }
  return valid;
}

int Sudoku::first_empty_col() const
{
  int empty = -1;
  for (int col = 0; empty == -1 && col < 9; col++)
    if (is_empty(0, col))
      empty = col;
  return empty;
}

int Sudoku::last_empty_col() const
{
  int empty = -1;
    for (int col = 8; empty == -1 && col > -1; col--)
      if (is_empty(8, col))
        empty = col;
  return empty;
}

bool Sudoku::auto_set_field(int row, int col, int first_col)
{
  bool valid = false;
  if (solved[row][col] < 9)
    for (int i = solved[row][col] + 1; !valid && i < 10; i++)
      valid = set_field(row, col, i, solved);
  if (!valid && row == 0 && col == first_col)
    solved[row][col] = -1;
  else if (!valid)
    solved[row][col] = 0;
  return valid;
}

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

Sudoku& Sudoku::operator=(const Sudoku& other)
{
  if (this != &other)
  {
    solved = other.solved;
    unsolved = other.unsolved;
    //clear_grid();
    //init_grid(other.grid);
  }
  return *this;
}

void Sudoku::generate_unique(int ordinal)
{
  do
  {
    unsolved = Square(9);
    generate(ordinal);
    solved = unsolved;
  } while(!solve());
}

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

bool Sudoku::is_empty(int row, int col) const
{
  return unsolved[row][col] == 0;
}

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
