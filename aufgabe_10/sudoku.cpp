#include <iostream>
#include <iomanip>
#include "sudoku.h"
#include <sstream>
#include <string>
#include "time.h"
#include <cstdlib>

using namespace std;

bool Sudoku::rand_seeded = false;

Sudoku::Sudoku()
{
  seed_rand();
  init_grid();
}

Sudoku::Sudoku(int ordinal)
{
  seed_rand();
  init_grid();
  generate_unique(ordinal);
  //prepare_solved_grid();
}

Sudoku::Sudoku(int a_grid[9][9])
{
  seed_rand();
  init_grid(a_grid);
  prepare_solved_grid();
}

Sudoku::Sudoku(const Sudoku& original)
{
  seed_rand();
  init_grid(original.grid);
}

Sudoku::~Sudoku()
{
  clear_grid();
}

bool Sudoku::solve()
{
  bool valid = true;
  int round = 0;
  int tmp_col = 0;
  int first_col = first_empty_col();
  int last_col = last_empty_col();
  for (int row = 0; valid && row < 9; row++)
  {
    for (int col = 0; valid && col < 9; col++)
    {
      if (is_empty(row, col))
      {
        if (!auto_set_field(row, col, first_col))
        {
          if (solved_grid[row][col] == -1)
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
              copy_solved_grid();
          }
        }
      }
    }
  }
  if (round == 1)
    valid = true;
  else if (round == 2)
    valid = are_solved_grids_equal();
  return valid;
}

bool Sudoku::are_solved_grids_equal()
{
  bool equal = true;
  for (int i = 0; equal && i < 9; i++)
    for (int j = 0; equal && j < 9; j++)
      equal = solved_grid2[i][j] == solved_grid[i][j];
  return equal;
}

void Sudoku::copy_solved_grid()
{
  solved_grid2 = new int*[9];
  for (int i = 0; i < 9; i++)
  {
    solved_grid2[i] = new int[9];
    for (int j = 0; j < 9; j++)
      solved_grid2[i][j] = solved_grid[i][j];
  }
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
  return set_field(x, y, number, grid);
}

bool Sudoku::set_field(int x, int y, int number, int **the_grid)
{
  bool valid = true;
  int tmp = the_grid[x][y];
  the_grid[x][y] = number;
  if (!validate_square_by_field(x, y, the_grid) ||
      !validate_col(y, the_grid) || !validate_row(x, the_grid))
  {
    the_grid[x][y] = tmp;
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
  if (solved_grid[row][col] < 9)
    for (int i = solved_grid[row][col] + 1; !valid && i < 10; i++)
      valid = set_field(row, col, i, solved_grid);
  if (!valid && row == 0 && col == first_col)
    solved_grid[row][col] = -1;
  else if (!valid)
    solved_grid[row][col] = 0;
  return valid;
}

string Sudoku::str() const
{
  ostringstream modifier(ios::out);
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      modifier << setw(3) << grid[i][j];
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
      modifier << setw(3) << solved_grid2[i][j];
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
    clear_grid();
    init_grid(other.grid);
  }
  return *this;
}

void Sudoku::prepare_solved_grid()
{
  solved_grid = new int*[9];
  for (int i = 0; i < 9; i++)
  {
    solved_grid[i] = new int[9];
    for (int j = 0; j < 9; j++)
      solved_grid[i][j] = grid[i][j];
  }
}

void Sudoku::init_grid(int **the_grid)
{
  grid = new int*[9];
  for (int i = 0; i < 9; i++)
  {
    grid[i] = new int[9];
    for (int j = 0; j < 9; j++)
      grid[i][j] = the_grid[i][j];
  }
}

void Sudoku::init_grid(int the_grid[9][9])
{
  grid = new int*[9];
  for (int i = 0; i < 9; i++)
  {
    grid[i] = new int[9];
    for (int j = 0; j < 9; j++)
      grid[i][j] = the_grid[i][j];
  }
}

void Sudoku::init_grid()
{
  grid = new int*[9];
  for (int i = 0; i < 9; i++)
  {
    grid[i] = new int[9];
    for (int j = 0; j < 9; j++)
      grid[i][j] = 0;
  }
}

void Sudoku::generate_unique(int ordinal)
{
  do
  {
    init_grid();
    generate(ordinal);
    prepare_solved_grid();
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

void Sudoku::clear_grid()
{
  for (int i = 0; i < 9; i++)
  {
    delete [] grid[i];
    delete [] solved_grid[i];
    delete [] solved_grid2[i];
  }
  delete [] grid;
  delete [] solved_grid;
  delete [] solved_grid2;
}

bool Sudoku::is_empty(int row, int col) const
{
  return grid[row][col] == 0;
}

bool Sudoku::validate_col(int col, int **the_grid)
{
  bool valid = true;
  bool numbers[10] = {
    false, false, false, false, false,
    false, false, false, false, false
  };
  int tmp_number = 0;
  for (int row = 0; valid && row < 9; row++)
  {
    tmp_number = the_grid[row][col];
    valid = numbers[tmp_number] != true || tmp_number == 0;
    numbers[tmp_number] = true;
  }
  return valid;
}

bool Sudoku::validate_row(int row, int **the_grid)
{
  bool valid = true;
  bool numbers[10] = {
    false, false, false, false, false,
    false, false, false, false, false
  };
  int tmp_number = 0;
  for (int col = 0; valid && col < 9; col++)
  {
    tmp_number = the_grid[row][col];
    valid = numbers[tmp_number] != true || tmp_number == 0;
    numbers[tmp_number] = true;
  }
  return valid;
}

bool Sudoku::validate_square_by_field(int x, int y, int **the_grid)
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
      tmp_number = the_grid[ranges[x_range][i]][ranges[y_range][j]];
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


