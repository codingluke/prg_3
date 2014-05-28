#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include "price_computer.h"
#include "refound_computer.h"

PriceComputer::PriceComputer(double a_price, string a_currency)
{
  if (a_price < 0)
    throw "Es gibt keine negative Preise";
  price = a_price;
  currency = a_currency;
  abordet = false;
}

double PriceComputer::add(double a_coin)
{
  if (a_coin < 0)
    throw "Es gib keine negativen Geldeinheiten";
  else if (a_coin == 0)
    abordet = true;
  coin_stack.push_back(a_coin);
  return sum_coin_stack();
}

int PriceComputer::state() const
{
  double result = 2;
  double sum_coins = sum_coin_stack();
  if (abordet)
    result = 0;
  else if (price > sum_coins)
    result = -1;
  else if (fabs(price - sum_coins) < 0.0001)
    result = 1;
  return result;
}

double PriceComputer::remainder() const
{
  return price - sum_coin_stack();
}

string PriceComputer::str() const
{
  ostringstream modifier(ios::out);
  int state_tmp = state();
  if (state_tmp == -1)
    modifier << "Noch zu bezahlen: " << remainder()
             << " " << currency << " " << endl;
  else if (state_tmp == 0)
    modifier << RefoundComputer(coin_stack, sum_coin_stack(), currency);
  else if (state() == 2)
    modifier << RefoundComputer(remainder() * - 1, currency);
  return modifier.str();
}

double PriceComputer::sum_coin_stack() const
{
  double sum = 0;
  for(unsigned int i = 0; i < coin_stack.size(); i++)
    sum += coin_stack[i];
  return sum;
}

ostream& operator<<(ostream& output, const PriceComputer& pc)
{
  output << pc.str();
  return output;
}
