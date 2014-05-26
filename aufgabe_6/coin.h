#ifndef COIN_H
#define COIN_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Coin
{
  private:
    vector<double> accepted_coins;
    double value;

  public:
    Coin();
    Coin(double a_value);
    string str() const;
    double get_value() const;

  private:
    void init_default_coins();
    bool validate_value(double a_value);

};

istream& operator>>(istream& input, Coin& coin);
ostream& operator<<(ostream& output, const Coin& coin);

#endif
