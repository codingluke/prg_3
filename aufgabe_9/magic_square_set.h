#ifndef MAGIC_SQUARE_SET_H
#define MAGIC_SQUARE_SET_H

#include "magic_square.h"
#include <vector>

class MagicSquareSet
{
  private:
    //MagicSquare *squares;
    vector<MagicSquare> squares;
    int length;

  public:
    MagicSquareSet();
    //MagicSquareSet(const MagicSquareSet& original);

    //~MagicSquareSet();

    int add(const MagicSquare& a_magic_square);
    int size() const;
    string str() const;

    //MagicSquareSet& operator=(const MagicSquareSet& other);
    MagicSquare operator[](int key);

  private:
    bool is_unique(const MagicSquare& a_magic_square) const;
};

#endif
