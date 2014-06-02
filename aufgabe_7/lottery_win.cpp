#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "time.h"
#include "lottery_win.h"
#include "console_input.h"

using namespace std;

bool LotteryWin::seeded = false;

LotteryWin::LotteryWin()
{
  seed_rand();
  generate_win();
}

LotteryWin::LotteryWin(const char *the_numbers)
{
  numbers = new char[6];
  for (int i = 0; i < 6; i++)
    numbers[i] = the_numbers[i];
}

LotteryWin::LotteryWin(const LotteryWin& original)
{
  for (int i = 0; i < 6; i++)
    numbers[i] = original.numbers[i];
}

LotteryWin::~LotteryWin()
{
  delete [] numbers;
}

string LotteryWin::str() const
{
  ostringstream modifier(ios::out);
  for (int i = 0; i < 6; i++)
    modifier << static_cast<short>(numbers[i]) << " ";
  modifier << endl;
  return modifier.str();
}

int LotteryWin::minimum() const
{
  char minimum = 49;
  for (int i = 0; i < 6; i++)
    if (numbers[i] < minimum)
      minimum = numbers[i];
  return static_cast<int>(minimum);
}

int LotteryWin::maximum() const
{
  char maximum = 0;
  for (int i = 0; i < 6; i++)
    if (numbers[i] > maximum)
      maximum = numbers[i];
  return static_cast<int>(maximum);
}

int LotteryWin::length() const
{
  return maximum() - minimum();
}

bool LotteryWin::has_length_in_win() const
{
  if (is_valid_number(static_cast<char>(length())))
    return true;
  else
    return false;
}

bool LotteryWin::is_even() const
{
  for (int i = 0; i < 6; i++)
    if (static_cast<short>(numbers[i]) % 2)
      return false;
  return true;
}

bool LotteryWin::is_odd() const
{
  for (int i = 0; i < 6; i++)
    if ((static_cast<short>(numbers[i]) % 2) == 0)
      return false;
  return true;
}

bool LotteryWin::is_prim() const
{
  for (int i = 0; i < 6; i++)
    if (!is_primnumber(static_cast<int>(numbers[i])))
      return false;
  return true;
}

bool LotteryWin::is_not_prim() const
{
  for (int i = 0; i < 6; i++)
    if (is_primnumber(static_cast<int>(numbers[i])))
      return false;
  return true;
}

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


//void LotteryWin::count_numbers(unsigned int *numbers_count) const
//{
  //for (int i = 0; i < 6; i++)
    //numbers_count[numbers[i] - 1]++;
//}

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

int LotteryWin::operator[](const int& key) const
{
  return static_cast<int>(numbers[key]);
}

void LotteryWin::seed_rand()
{
  if(!seeded)
  {
    srand(time(0));
    seeded = true;
  }
}

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

bool LotteryWin::is_valid_number(char number) const
{
  bool valid = true;
  for (int i = 0; i < 6; i++)
    if (number == numbers[i])
      valid = false;
  return valid;
}

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
 * @return
 */
ostream& operator<<(ostream& output, const LotteryWin& a_lottery_win)
{
  output << a_lottery_win.str();
  return output;
}

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

