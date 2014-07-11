#ifndef MAGIC_SQUARE_SET_H
#define MAGIC_SQUARE_SET_H

#include "magic_square.h"
#include <vector>

class MagicSquareSet
{
  private:
    vector<MagicSquare*> squares;

  public:
    MagicSquareSet();
    MagicSquareSet(const MagicSquareSet& original); // copy constructor

    virtual ~MagicSquareSet();

    int add(MagicSquare* a_magic_square);
    int size() const;
    string str() const;

    MagicSquareSet& operator=(const MagicSquareSet& other);
    MagicSquare operator[](int key) const;

  private:
    bool is_unique(const MagicSquare* a_magic_square) const;
};

#endif
