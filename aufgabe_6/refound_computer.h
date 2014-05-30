#ifndef REFOUND_COMPUTER_H
#define REFOUND_COMPUTER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * RefoundComputer represents the sum of a refound with a list of
 * accepted values.
 *
 * @author    Lukas Hodel
 * @version   1.0
 */
class RefoundComputer
{
  private:
    vector<double> accepted_coins;
    vector<double> refound_in_coins;
    double refound;
    string currency;

  public:
    RefoundComputer();
    RefoundComputer(const string& currency,
                    const vector<double>& accepted_coins_list);

    void set_refound(double a_refound);
    string str() const;

  private:
    void init_default_coins();
    void calculate();
    void sort_coins();
    string str_grouped() const;
};

ostream& operator<<(ostream& output, const RefoundComputer& refound);

#endif
