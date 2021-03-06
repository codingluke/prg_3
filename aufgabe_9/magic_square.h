#ifndef MAGIC_SQUARE_H
#define MAGIC_SQUARE_H

#include <string>
#include <stdexcept>
#include "square.h"

using namespace std;

/**
 * Difinition of a MagicSquare. Has all the algorithms to generate
 * a MagicSquare out of a ordinal number and also to mutate the basic
 * MagicSquare to other valid MagicSquares.
 */
class MagicSquare : public Square
{
  public:
    MagicSquare();
    MagicSquare(int a_ordinal) throw(const invalid_argument);

    MagicSquare switch_rows(int index) throw(const out_of_range);
    MagicSquare switch_columns(int index) throw(const out_of_range);
    MagicSquare switch_diagonal_top_left();
    MagicSquare switch_diagonal_top_right();
    MagicSquare rotate_90();
    int get_magic_number() const;
    string str() const;

  private:
    void calculate();
    bool is_top_right(int& row, int& column) const;
    bool is_in_first_row(int& row) const;
    bool is_in_right_column(int& column) const;
    bool is_empty(int column, int row) const;
};

#endif
