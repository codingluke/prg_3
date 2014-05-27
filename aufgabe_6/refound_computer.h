#ifndef REFOUND_COMPUTER_H
#define REFOUND_COMPUTER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class RefoundComputer
{
  private:
    vector<double> accepted_coins;
    vector<double> refound_in_coins;
    double refound;
    string currency;

  public:
    RefoundComputer(double refound, string currency);
    string str() const;

  private:
    void init_default_coins();
    void calculate();
};

ostream& operator<<(ostream& output, const RefoundComputer& refound);

#endif
