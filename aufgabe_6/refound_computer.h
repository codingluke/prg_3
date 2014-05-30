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
    RefoundComputer();
    RefoundComputer(string currency, vector<double> accepted_coins_list);

    void set_refound(double a_refound);
    string str() const;

  private:
    void init_default_coins();
    void calculate();
    string str_grouped() const;
};

ostream& operator<<(ostream& output, const RefoundComputer& refound);

#endif
