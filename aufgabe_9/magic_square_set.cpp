#include "magic_square_set.h"
#include "magic_square.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

MagicSquareSet::MagicSquareSet()
{
  length = 0;
  //squares = new MagicSquare[0];
}

//MagicSquareSet::MagicSquareSet(const MagicSquareSet& original)
//{
  //length = original.length;
  //squares = new MagicSquare[length];
  //for (int i = 0; i < length; i++)
    //squares[i] = original.squares[i];
//}

//MagicSquareSet::~MagicSquareSet()
//{
  //delete [] squares;
//}

int MagicSquareSet::add(const MagicSquare& a_magic_square)
{
  if (is_unique(a_magic_square))
  {
    length++;
    squares.push_back(a_magic_square);
    //squares.resize(length);
    //MagicSquare *tmp = new MagicSquare[length];
    //for (int i = 0; i < length; i++)
      //tmp[i] = squares[i];
    //delete [] squares;
    //squares = new MagicSquare[length + 1];
    //for (int i = 0; i < length; i++)
      //squares[i] = tmp[i];
    //squares[length++] = a_magic_square;
  }
  return length;
}

int MagicSquareSet::size() const
{
  return length;
}

string MagicSquareSet::str() const
{
  ostringstream modifier(ios::out);
  for (int i = 0; i < size(); i++)
    modifier << squares[i].str() << endl << endl;
  modifier << "Size: " << size() << endl
           << "Magic number: " << squares[0].magic_number() << endl;
  return modifier.str();
}

//MagicSquareSet& MagicSquareSet::operator=(const MagicSquareSet& other)
//{
  //if (this != &other)
  //{
    //delete [] squares;
    //length = other.length;
    //for (int i = 0; i < length; i++)
      //squares[i] = other.squares[i];
  //}
  //return *this;
//}

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
