#ifndef PRICE_COMPUTER_H
#define PRICE_COMPUTER_H

#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

/**
 * PriceComputer is a state machine for counting monetary units
 * up to a certain value.
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
