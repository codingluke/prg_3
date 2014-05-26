#ifndef PRICE_COMPUTER_H
#define PRICE_COMPUTER_H

#include <vector>

using namespace std;

class PriceComputer
{
  private:
    vector<double> coin_stack;
    double price;

  public:
    PriceComputer(double a_price);

    double add(double a_coin);
    double state() const;

  private:
    double sum_coin_stack() const;
};
#endif
