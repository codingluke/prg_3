#include "magic_square_set.h"
#include "magic_square.h"
#include <iostream>
#include <iomanip>

MagicSquareSet::MagicSquareSet()
{
  squares = new MagicSquare[0];
  length = 0;
}

int MagicSquareSet::add(const MagicSquare& a_magic_square)
{
  if (is_unique(a_magic_square))
  {
    MagicSquare *tmp = new MagicSquare[length];
    for (int i = 0; i < length; i++)
      tmp[i] = squares[i];
    delete [] squares;
    squares = new MagicSquare[length + 1];
    for (int i = 0; i < length; i++)
      squares[i] = tmp[i];
    squares[length++] = a_magic_square;
  }
  return length;
}

int MagicSquareSet::size() const
{
  return length;
}

MagicSquare MagicSquareSet::operator[](int key)
{
  MagicSquare m = squares[key];
  return m;
}

bool MagicSquareSet::is_unique(const MagicSquare& a_magic_square) const
{
  bool unique = true;
  for (int i = 0; unique && i < length; i++)
    unique = squares[i] != a_magic_square;
  return unique;
}
