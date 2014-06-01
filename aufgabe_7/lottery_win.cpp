#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "time.h"
#include "lottery_win.h"

using namespace std;

bool LotteryWin::seeded = false;

LotteryWin::LotteryWin()
{
  seed_rand();
  generate_win();
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

int LotteryWin::operator[](const int& key)
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
  for (int i = 0; i < 6; i++)
    numbers[i] = (1 + char(49 * (rand() / (RAND_MAX + 1.0))));
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
  cout << a_lottery_win.str();
  return output;
}
