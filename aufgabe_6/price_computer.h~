#ifndef PRICE_COMPUTER_H
#define PRICE_COMPUTER_H

#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

/**
 * PriceComputer is a state machine for counting monetary units
 * up to a certain value. It gives the possibility to check if he
 * price is reached or even surpassed. The counting can be abordet
 * with inserting the value 0.00. The "put to" operator is globally
 * overwritten so that there is always an accurate stream output
 * presentation as string. 
 *
 * @author  Lukas Hodel
 */
class PriceComputer
{
  private:
    vector<double> coin_stack;
    double price;
    bool abordet;
    string currency;

  public:
    PriceComputer(double a_price, const string& a_currency)
      throw(const invalid_argument);

    double add(double a_coin) throw(const invalid_argument);
    int state() const;
    double remainder() const;
    string str() const;

  private:
    double sum_coin_stack() const;
    string str_grouped() const;
    void sort_coins();
};

ostream& operator<<(ostream& output, const PriceComputer& pc);

#endif
