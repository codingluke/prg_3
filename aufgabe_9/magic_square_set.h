#ifndef MAGIC_SQUARE_SET_H
#define MAGIC_SQUARE_SET_H

#include "magic_square.h"

class MagicSquareSet
{
  private:
    MagicSquare *squares;
    int length;

  public:
    MagicSquareSet();
    int add(const MagicSquare& a_magic_square);
    int size() const;

    MagicSquare operator[](int key);

  private:
    bool is_unique(const MagicSquare& a_magic_square) const;
};

#endif
