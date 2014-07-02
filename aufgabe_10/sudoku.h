#ifndef SUDOKU_H
#define SUDOKU_H

#include <string>

using namespace std;

class Sudoku
{
  private:
    int **grid;
    int **solved_grid;
    int **solved_grid2;
    static bool rand_seeded;

  public:
    Sudoku();
    Sudoku(int ordinal);
    Sudoku(int a_grid[9][9]);
    Sudoku(const Sudoku& original); // copy-constructor

    ~Sudoku();

    bool set_field(int x, int y, int number);
    bool solve();
    string str() const;
    string str_solved() const;

    Sudoku& operator=(const Sudoku& other);

  private:
    void generate_unique(int ordinal);
    bool set_field(int x, int y, int number, int **the_grid);
    bool auto_set_field(int row, int col, int first_col);
    void seed_rand();
    void init_grid(int **the_grid);
    void init_grid(int the_grid[9][9]);
    void init_grid();
    void prepare_solved_grid();
    void generate(int oridinal);
    void clear_grid();
    bool validate_square_by_field(int x, int y, int **the_grid);
    bool validate_row(int row, int **the_grid);
    bool validate_col(int col, int **the_grid);
    bool is_empty(int row, int col) const;
    int range_number(int number) const;
    int prev_empty_col(int row, int col) const;
    int first_empty_col() const;
    int last_empty_col() const;
    void copy_solved_grid();
    bool are_solved_grids_equal();
};

#endif
