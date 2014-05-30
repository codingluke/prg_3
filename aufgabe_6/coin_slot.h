#ifndef COIN_SLOT_H
#define COIN_SLOT_H

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

/**
 * CoinSlot represents a coin slot of a ticket machine. You can define
 * certain accepted coins. When inserting a coin (double), it
 * validates for acceptance. The class also overrides the global
 * operators >> "get from" and << "put to" for easy console input handling.
 *
 * @author  Lukas Hodel
 * @version 1.0
 */
class CoinSlot
{
  private:
    vector<double> accepted_coins;
    double value;
    string currency;

  public:
    CoinSlot();
    CoinSlot(const string& a_currency);
    CoinSlot(const string& a_currency,
             const vector<double>& accepted_coins_list);

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
