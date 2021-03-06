#ifndef SUDOKU_H
#define SUDOKU_H


#include <string>
#include <stdexcept>
#include "square.h"

using namespace std;

/**
 * Definition of the calss Sudoku. Implements the algorithm and rules to
 * solve and/or generate a unique Sudoku.
 */
class Sudoku
{
  private:
    /**
     * Status of the Sudoku. -1 not solved. 0 can not be solved.
     * 1 solved and unique. 2 solved but not unique.
     */
    int status;
    Square unsolved;
    Square solved;
    static bool rand_seeded;

  public:
    Sudoku();
    Sudoku(int ordinal) throw(const invalid_argument);
    Sudoku(const Square& the_unsolved) throw(const invalid_argument);

    bool set_field(int x, int y, int number);
    bool solve();
    string str() const;
    string str_solved() const;
    int get_status() const;

  private:
    void generate_unique(int ordinal);
    void generate(int oridinal);
    bool set_field(int x, int y, int number, Square& square);
    bool auto_set_field(int row, int col, int first_col);
    void seed_rand();
    bool validate_square_by_field(int x, int y, Square& square);
    bool validate_row(int row, Square& square);
    bool validate_col(int col, Square& square);
    bool is_empty(int row, int col) const;
    int range_number(int number) const;
    int prev_empty_col(int row, int col) const;
    int first_empty_col() const;
    int last_empty_col() const;
};

#endif
