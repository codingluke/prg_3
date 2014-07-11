#include "magic_square_set.h"
#include "magic_square.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

/**
 * Default constructor. Initializes a empty vectors of squares.
 */
MagicSquareSet::MagicSquareSet()
{
}

/**
 * Copy-constructor for a MagicSquareSet. Implements the deep copy.
 *
 * @param original  The MagicSquareSet to copy from.
 */
MagicSquareSet::MagicSquareSet(const MagicSquareSet& original)
{
  squares = original.squares;
}

/**
 * Deconstructor for the MagicSquareSet.
 */
MagicSquareSet::~MagicSquareSet()
{
  for (int i = 0; i < size(); i++)
    delete [] squares[i];
}

/**
 * Adds a MagicSquare to the set when it's not already in the set.
 * When its already in the set, it just ignores it.
 *
 * @param a_magic_square  The MagicSquare to add to the set.
 *
 * @return the new size of the set.
 */
int MagicSquareSet::add(MagicSquare *a_magic_square)
{
  if (is_unique(a_magic_square))
    squares.push_back(a_magic_square);
  return squares.size();
}

/**
 * Returns the size of the set.
 *
 * @return size of the set.
 */
int MagicSquareSet::size() const
{
  return squares.size();
}

/**
 * Generates and returns the string representation of a set.
 * \n\n
 * 11   2  25  18   9\n
 * 23  14   7   5  16\n
 *  4  20  13   6  22\n
 * 10  21  19  12   3\n
 * 17   8   1  24  15\n
 * \n
 * 11   2  25  18   9\n
 * 23  14   7   5  16\n
 *  4  20  13   6  22\n
 * 10  21  19  12   3\n
 * 17   8   1  24  15\n
 * \n
 * Ordnung: 5
 * Anzahl: 2
 * Magic number: 65
 *
 * @return the string representation of a set.
 */
string MagicSquareSet::str() const
{
  ostringstream modifier(ios::out);
  for (int i = 0; i < size(); i++)
    modifier << squares[i]->str() << endl << endl;
  modifier << "Ordnung: " << squares[0]->get_ordinal_number() << endl
           << "Anzahl: " << size() << endl
           << "Magic number: " << squares[0]->get_magic_number() << endl;
  return modifier.str();
}

/**
 * Overloads the assignment operator=. Defines how to assign a MagicSquareSet
 * to an other.
 *
 * @param other  The MagicSquareSet to assign.
 *
 * @return The actual MagicSquareSet.
 */
MagicSquareSet& MagicSquareSet::operator=(const MagicSquareSet& other)
{
  if (this != &other)
  {
    for (int i = 0; i < size(); i++)
      delete [] squares[i];
    for (int j = 0; j < other.size(); j++)
      squares.push_back(new MagicSquare(other[j]));
  }
  return *this;
}

/**
 * Returns a MagicSquare, saved at the position of a key.
 *
 * @param key  Key of the MagicSquare to access.
 *
 * @return the MagicSquare at the position of key.
 */
MagicSquare MagicSquareSet::operator[](int key) const
{
  MagicSquare m = *squares[key];
  return m;
}

/**
 * Checks if a MagicSquare not already exists in the set.
 *
 * @param a_magic_square  The MagicSquare to check for uniqueness.
 *
 * @return true when the MagicSquare doesn't already exists.
 *         false when the MagicSquare already exits.
 */
bool MagicSquareSet::is_unique(const MagicSquare* a_magic_square) const
{
  bool unique = true;
  for (vector<int>::size_type i = 0; unique && i < squares.size(); i++)
    unique = *squares[i] != *a_magic_square;
  return unique;
}
