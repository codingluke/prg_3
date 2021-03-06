#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "time.h"
#include "lottery_win.h"
#include "console_input.h"

using namespace std;

/**
 * Parameter to flag when random is seeded.
 */
bool LotteryWin::seeded = false;

/**
 * Default constructor. Initializes a LotteryWin with random numbers.
 */
LotteryWin::LotteryWin()
{
  seed_rand();
  generate_win();
}

/**
 * Constructor to initialize a LotteryWin with given numbers.
 *
 * @param the_numbers  The numbers for the LotteryWin.
 */
LotteryWin::LotteryWin(const char *the_numbers)
{
  numbers = new char[6];
  for (int i = 0; i < 6; i++)
    numbers[i] = the_numbers[i];
}

/**
 * Copy-constructor. Defines how to deep copy LotteryWin.
 *
 * @param original  Instance of LotteryWin to copy.
 */
LotteryWin::LotteryWin(const LotteryWin& original)
{
  for (int i = 0; i < 6; i++)
    numbers[i] = original.numbers[i];
}

/**
 * Destructor of the LotteryWin. Deletes all references in the heap.
 */
LotteryWin::~LotteryWin()
{
  delete [] numbers;
}

/**
 * Defines how a lottery win gets pared to a string.
 *
 * 1 2 3 4 5 6
 *
 * @return the LotteryWin as a string.
 */
string LotteryWin::str() const
{
  ostringstream modifier(ios::out);
  for (int i = 0; i < 6; i++)
    modifier << static_cast<short>(numbers[i]) << " ";
  modifier << endl;
  return modifier.str();
}

/**
 * Gives back the smallest number of the LotteryWin.
 *
 * @return smallest number.
 */
int LotteryWin::minimum() const
{
  char minimum = 49;
  for (int i = 0; i < 6; i++)
    if (numbers[i] < minimum)
      minimum = numbers[i];
  return static_cast<int>(minimum);
}

/**
 * Gives back the biggest number in the LotteryWin.
 *
 * @return the biggest number.
 */
int LotteryWin::maximum() const
{
  char maximum = 0;
  for (int i = 0; i < 6; i++)
    if (numbers[i] > maximum)
      maximum = numbers[i];
  return static_cast<int>(maximum);
}

/**
 * Gives back the length of the LotteryWin. The length is
 * the difference between the biggest and the smallest number.
 *
 * @return length of the LotteryWin.
 */
int LotteryWin::length() const
{
  return maximum() - minimum();
}

/**
 * Gives back whether the length of the LotteryWin is also
 * one of its numbers or not.
 *
 * @return true when the length is also a number.
 *         false when the length is not a included number.
 */
bool LotteryWin::has_length_in_win() const
{
  bool has_length = false;
  if (!is_valid_number(static_cast<char>(length())) && !has_length)
    has_length = true;
  return has_length;
}

/**
 * Gives back if the LotteryWin is even. A LotteryWin is even when
 * all included numbers are even.
 *
 * @return true when all numbers are even.
 *         false when min one number is not even.
 */
bool LotteryWin::is_even() const
{
  bool even = true;
  for (int i = 0; i < 6 && even; i++)
    if (static_cast<short>(numbers[i]) % 2)
      even = false;
  return even;
}

/**
 * Gives back if the LotteryWin is odd. A LotteryWin is odd when
 * all included numbers are odd.
 *
 * @return true when all numbers are odd.
 *         false when min one number is not odd.
 */
bool LotteryWin::is_odd() const
{
  bool odd = true;
  for (int i = 0; i < 6 && odd; i++)
    if ((static_cast<short>(numbers[i]) % 2) == 0)
      odd = false;
  return odd;
}

/**
 * Gives back if the LotteryWin is prim. A LotteryWin is prim when
 * all included numbers are primnumbers.
 *
 * @return true when all numbers are prim numbers.
 *         false when min one number is not prim numbers.
 */
bool LotteryWin::is_prim() const
{
  bool prime = true;
  for (int i = 0; i < 6 && prime; i++)
    if (!is_primnumber(static_cast<int>(numbers[i])))
      prime = false;
  return prime;
}

/**
 * Gives back if the LotteryWin is not prim. A LotteryWin isn not prim when
 * non of the included numbers are primnumbers.
 *
 * @return true when non of the numbers are prim numbers.
 *         false when min one number is a prim numbers.
 */
bool LotteryWin::is_not_prim() const
{
  bool not_prime = true;
  for (int i = 0; i < 6 && not_prime; i++)
    if (is_primnumber(static_cast<int>(numbers[i])))
      not_prime = false;
  return not_prime;
}

/**
 * Gibes back the number of "street" the LotteryWin is. A street is defined
 * up on the neighbour numbers which have a difference of 1.
 * e.g. 1 2 3 4 5 6 is a 6 Street, because all 6 numbers have difference
 * of one in between. 1 4 5 6 23 43 would be a 3 street (4 5 6).
 *
 * @return the street type defined by the number of numbers which have a
 * difference of one between the neighbours.
 */
int LotteryWin::street_type() const
{
  short max = 0;
  short index = 0;
  short counts[5] = { 1, 1, 1, 1, 1 };
  for (int i = 1; i < 6; i++)
    if (numbers[i] == (numbers[i - 1] + 1))
      counts[index]++;
    else
      index++;
  for (int i = 0; i < index; i++)
    if (counts[i] > max)
      max = counts[i];
  return max;
}

/**
 * Gives back whether a given number is a prim number or not.
 *
 * @param number  Number to check.
 *
 * @return true if the number is a prim number.
 *         false if the number is not a prim number.
 */
bool LotteryWin::is_primnumber(const int& number) const
{
  bool is_prim = true;
  if (number == 1)
    is_prim = false;
  else
    for (int i = 2; i < number; i++ )
      if (number % i == 0)
        is_prim = false;
  return is_prim;
}

/**
 * Overwrites the assignment operator=. Defines the deep copy of a LotteryWin
 * instance.
 *
 * @param a_lottery_win  The LotteryWin instance to overtake.
 *
 * @return the adress of itself.
 */
LotteryWin& LotteryWin::operator=(const LotteryWin& a_lottery_win)
{
  if (this != &a_lottery_win)
  {
    delete [] numbers;
    numbers = new char[6];
    for (int i = 0; i < 6; i++)
      numbers[i] = a_lottery_win.numbers[i];
  }
  return *this;
}

/**
 * Overwrites the operator[]. Defines the acces to a certain number by the key.
 *
 * @param key  Key of the number to access.
 *
 * @return the number under the given key.
 */
int LotteryWin::operator[](const int& key) const
{
  return static_cast<int>(numbers[key]);
}

/**
 * Initializes srand and sets the flag to guarantee that srand gets
 * initialized just once.
 */
void LotteryWin::seed_rand()
{
  if(!seeded)
  {
    srand(time(0));
    seeded = true;
  }
}

/**
 * Generates a random numbercombination. and saves them into the numbers.
 * Guarantees that the numbers are unique.
 */
void LotteryWin::generate_win()
{
  numbers = new char[6];
  char number;
  for (int i = 0; i < 6; i++)
  {
    do
      number = (1 + char(49 * (rand() / (RAND_MAX + 1.0))));
    while (!is_valid_number(number));
    numbers[i] = number;
  }
}

/**
 * Checks if a given number don't exist already.
 *
 * @param number  Number to check for uniqueness.
 *
 * @return true if the number doesn't exist already.
 *         false if the number exists already.
 */
bool LotteryWin::is_valid_number(char number) const
{
  bool valid = true;
  for (int i = 0; i < 6; i++)
    if (number == numbers[i])
      valid = false;
  return valid;
}

/**
 * Overwrides the compair operator==. Gives back the number of numbers
 * which are equal in both LotteryWin instances.
 *
 * @param left    Left LotteryWin instance to compair.
 * @param right   Right LotteryWin instance to compair.
 *
 * @return  0 to 6, depends up on how many number are equal.
 */
int operator==(const LotteryWin& left, const LotteryWin& right)
{
  int count = 0;
  for (int i = 0; i < 6; i++)
    for (int j = 0; j < 6; j++)
      if (left[i] == right[j])
        count ++;
  return count;
}

/**
 * Overrides the operator<< "put to". Handels standard string representation
 * of a LotteryWin when "put to" an output stream.
 *
 * @param output          io output stream.
 * @param a_lottery_win   LotteryWin to put to the output stream.
 *
 * @return the output stream.
 */
ostream& operator<<(ostream& output, const LotteryWin& a_lottery_win)
{
  output << a_lottery_win.str();
  return output;
}

/**
 * Overwrides the operator>>. Handles user interaction by the console
 * to enter a valid LotteryWin out of 6 unique Numbers.
 *
 * @param input           Input stream.
 * @param a_lottery_win   The LotteryWin instance to fill with the user entry.
 *
 * @return the input stream.
 */
istream& operator>>(istream& input, LotteryWin& a_lottery_win)
{
  int number;
  bool entry_ok = false;
  char numbers[6] = { 0, 0, 0, 0, 0, 0 };
  for (int i = 0; i < 6; i++)
  {
    do
    {
      try
      {
        cout << "Bitte Ziffer " << i + 1 << " eingeben: ";
        number = read_int(1, 49);
        for (int j = 0; j < i; j++)
          if (number == static_cast<int>(numbers[j]))
            throw "Ziffer Bereits vorhanden!";
        numbers[i] = static_cast<char>(number);
        entry_ok = true;
      }
      catch(const char* msg)
      {
        cout << msg << endl;
      }
    } while(!entry_ok);
    entry_ok = false;
  }
  a_lottery_win = LotteryWin(numbers);
  return input;
}
