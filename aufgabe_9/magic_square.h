#ifndef MAGIC_SQUARE_H
#define MAGIC_SQUARE_H

#include <string>
#include <stdexcept>

using namespace std;

class MagicSquare
{
  private:
    int ordinal_number;
    int **square;

  public:
    MagicSquare();
    MagicSquare(int a_ordinal_number);
    MagicSquare(const MagicSquare& original); // copy-constructor

    ~MagicSquare();

    MagicSquare switch_rows(int index) throw(const out_of_range);
    MagicSquare switch_columns(int index) throw(const out_of_range);
    MagicSquare switch_diagonal_top_left();
    MagicSquare switch_diagonal_top_right();
    MagicSquare rotate_90();
    string str() const;

    MagicSquare& operator=(const MagicSquare& other);
    bool operator==(const MagicSquare& other) const;
    bool operator!=(const MagicSquare& other) const;

  private:
    void init_square();
    void init_square(int **the_square);
    void clear_square();
    void calculate();
    bool is_top_right(int& row, int& column) const;
    bool is_in_first_row(int& row, int& column) const;
    bool is_in_right_column(int& row, int& column) const;
    bool is_empty(int column, int row) const;
};

#endif
