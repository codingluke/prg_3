#include "price_computer.h"

PriceComputer::PriceComputer(double a_price)
{
  if (a_price < 0)
    throw "Es gibt keine negative Preise";
  price = a_price;
}

double PriceComputer::add(double a_coin)
{
  if (a_coin < 0)
    throw "Es gib keine negativen Geldeinheiten";
  coin_stack.push_back(a_coin);
  return sum_coin_stack();
}

double PriceComputer::state() const
{
  return (price - sum_coin_stack()) * -1;
}

double PriceComputer::sum_coin_stack() const
{
  double sum = 0;
  for(unsigned int i = 0; i < coin_stack.size(); i++)
    sum += coin_stack[i];
  return sum;
}
