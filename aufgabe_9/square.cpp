#include "square.h"
#include <string>
#include <sstream>
#include <cstdlib>

/**
 * Initializes a Square with the ordinal number 9.
 */
Square::Square()
{
  ordinal = 9;
  init();
}

/**
 * Initializes a Square with a given ordinal number.
 *
 * @param the_ordinal  Ordinal number of the square.
 */
Square::Square(int the_ordinal)
{
  ordinal = the_ordinal;
  init();
}

/**
 * Initializes a Square with a given ordinal number and
 * a given dataset.
 *
 * @param the_ordinal  Ordinal number of the Square.
 * @param the_data     Data for the Square.
 */
Square::Square(int the_ordinal, int **the_data)
{
  ordinal = the_ordinal;
  init(the_data);
}

/**
 * Initializes a Square with a given ordinal number and
 * a given dataset as string out of numbers.
 *
 * @param the_ordinal   Ordinal number of the Square.
 * @param the_data      Data for the Square.
 *
 * @throw const invalid_argument when the ordinal and data are not consistent.
 */
Square::Square(int the_ordinal, string the_data) throw(const invalid_argument)
{
  if (the_data.length() != (unsigned int)(the_ordinal * the_ordinal))
    throw invalid_argument("Laenge der Daten stimmen nicht mit der Ordinalzahl ueberein");
  ordinal = the_ordinal;
  data = new int*[ordinal];
  for (int i = 0; i < ordinal; i++)
  {
    data[i] = new int[ordinal];
    for (int j = 0; j < ordinal; j++)
    {
      stringstream ss(the_data.substr(i * 9 + j, 1));
      ss >> data[i][j];
    }
  }
}

/**
 * copy-constructor.
 *
 * @param original The Square to copy.
 */
Square::Square(const Square& original)
{
  ordinal = original.ordinal;
  init(original.data);
}

/**
 * Deconstructor. Clears the heap.
 */
Square::~Square()
{
  clear();
}

/**
 * Returns the ordinal of the Square.
 *
 * @return ordinal of the square.
 */
int Square::get_ordinal() const
{
  return ordinal;
}

/**
 * Overloads assignment operator=. Defines how to copy a Square
 * to an other.
 *
 * @param other The square to copy.
 *
 * @return a reference to itself.
 */
Square& Square::operator=(const Square& other)
{
  if (this != &other)
  {
    for (int i = 0; i < ordinal; i++)
      delete [] data[i];
    delete [] data;
    init(other.data);
  }
  return *this;
}

/**
 * Overloads access operator[]. Defines how to access single entries
 * of the Square. As it gives back a pointer it is possible to access
 * also the columns like this. square[0][0].
 *
 * @param key   Key to the row to access.
 *
 * @return pointer to a certain row of the square.
 */
int* Square::operator[](const int& key) const
{
  return data[key];
}

/**
 * Initializes an empty square. (filled with 0)
 */
void Square::init()
{
  data = new int*[ordinal];
  for (int i = 0; i < ordinal; i++)
  {
    data[i] = new int[ordinal];
    for (int j = 0; j < ordinal; j++)
      data[i][j] = 0;
  }
}

/**
 * Cleans the square and its sub arrays form memory.
 */
void Square::clear()
{
  for (int i = 0; i < ordinal; i++)
    delete [] data[i];
  delete [] data;
}

/**
 * Initializes the square with a given 2d array.
 *
 * @param the_data the data to fill the Square.
 */
void Square::init(int **the_data)
{
  data = new int*[ordinal];
  for (int i = 0; i < ordinal; i++)
  {
    data[i] = new int[ordinal];
    for (int j = 0; j < ordinal; j++)
      data[i][j] = the_data[i][j];
  }
}

/**
 * Overloads the operator?=. Checks if a MagicSquare is equal an other.
 *
 * @param other  Other MagicSquare to compare.
 *
 * @return true when they are equal.
 *         false when they are not equal.
 */
bool Square::operator==(const Square& other) const
{
  bool equal = false;
  if (ordinal == other.ordinal)
  {
    equal = true;
    for (int row = 0; equal && row < ordinal; row++)
      for (int col = 0; equal && col < ordinal; col++)
        equal = data[row][col] == other.data[row][col];;
  }
  return equal;
}

/**
 * Overloads the operator!=. Checks if a MagicSquare is not equal an other.
 *
 * @param other  Other MagicSquare to compare.
 *
 * @return true when they are not equal.
 *         false when they are equal.
 */
bool Square::operator!=(const Square& other) const
{
  return !(other == *this);
}
