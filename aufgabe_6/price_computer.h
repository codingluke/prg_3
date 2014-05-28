#ifndef PRICE_COMPUTER_H
#define PRICE_COMPUTER_H

#include <vector>
#include <string>

using namespace std;

class PriceComputer
{
  private:
    vector<double> coin_stack;
    double price;
    bool abordet;
    string currency;

  public:
    PriceComputer(double a_price, string a_currency);

    double add(double a_coin);
    int state() const;
    double remainder() const;
    string str() const;

  private:
    double sum_coin_stack() const;
};

ostream& operator<<(ostream& output, const PriceComputer& pc);

#endif
