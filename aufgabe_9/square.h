#ifndef SQUARE_H
#define SQUARE_H

#include <string>
#include <stdexcept>

using namespace std;

/**
 * Definition of the Class Square. A Square is a array where the columns
 * and the rows have the same size.
 */
class Square
{
  protected:
    int ordinal;
    int **data;

  public:
    Square();
    Square(int the_ordinal);
    Square(const Square& original); // copy constructor
    Square(int the_ordinal, int **the_data);
    Square(int the_ordinal, string the_data) throw(const invalid_argument);

    virtual ~Square();

    int get_ordinal() const;

    Square& operator=(const Square& other);
    int* operator[](const int& key) const;
    bool operator==(const Square& other) const;
    bool operator!=(const Square& other) const;

  protected:
    void init();
    void init(int **the_data);
    void clear();
};

#endif
