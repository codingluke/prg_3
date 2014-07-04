#ifndef SQUARE_H
#define SQUARE_H

#include <string>
#include <stdexcept>

using namespace std;

class Square
{
  private:
    int ordinal;
    int **data;

  public:
    Square();
    Square(int the_ordinal);
    Square(const Square& original); // copy constructor
    Square(int the_ordinal, int **the_data);
    Square(int the_ordinal, string the_data) throw(const invalid_argument);

    ~Square();

    int get_ordinal() const;

    Square& operator=(const Square& other);
    int* operator[](const int& key) const;

  private:
    void init(int **the_data);
    void init();
};

bool operator==(const Square& left, const Square& right);
//ostream& operator<<(ostream& output, const Square& a_square);
//istream& operator>>(istream& input, Square& a_square);

#endif
