#ifndef COIN_SLOT_H
#define COIN_SLOT_H

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

class CoinSlot
{
  private:
    vector<double> accepted_coins;
    double value;
    string currency;

  public:
    CoinSlot();
    CoinSlot(string a_currency);
    CoinSlot(string a_currency, vector<double> accepted_coins_list);

    void insert(double a_coin) throw(const invalid_argument);
    void add_accepted(double a_coin);
    double get_value() const;
    string str() const;

  private:
    bool validate(double a_value) const;
};

istream& operator>>(istream& input, CoinSlot& coin_slot);
ostream& operator<<(ostream& output, const CoinSlot& coin_slot);

#endif
