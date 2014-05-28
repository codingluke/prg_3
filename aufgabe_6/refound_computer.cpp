#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include "refound_computer.h"

// TODO : SORT THE COINS!

RefoundComputer::RefoundComputer(double a_refound, string a_currency)
{
  refound = a_refound;
  currency = a_currency;
  init_default_coins();
  calculate();
}

RefoundComputer::RefoundComputer(const vector<double>& coins, double sum, string a_currency)
{
  refound = sum;
  currency = a_currency;
  refound_in_coins = coins;
  init_default_coins();
}

string RefoundComputer::str() const
{
  ostringstream modifier(ios::out);
  int n = 1;
  if (refound_in_coins.size() > 0)
  {
    modifier << "Rückgabe: " << refound << " " << currency << endl
             << "Zahlungseinheiten: ";
    if (refound_in_coins.size() == 1)
      modifier << n << " * " << setprecision(2)
               << refound_in_coins[0] << " " << currency << " ";
    else
      for(unsigned int i = 1; i < refound_in_coins.size(); i++)
      {
        if (refound_in_coins[i] != refound_in_coins[i - 1])
        {
          modifier << n << " * " << setprecision(4)
                   << refound_in_coins[i - 1] << " " << currency << " ";
          n = 1;
        }
        else
        {
          n++;
          if (i == refound_in_coins.size() - 1)
            modifier << n << " * " << setprecision(2)
                   << refound_in_coins[i] << " " << currency << " ";
        }
      }
  }
  modifier << endl;
  return modifier.str();
}

void RefoundComputer::init_default_coins()
{
  accepted_coins.push_back(50);
  accepted_coins.push_back(20);
  accepted_coins.push_back(10);
  accepted_coins.push_back(5);
  accepted_coins.push_back(1);
  accepted_coins.push_back(0.5);
  accepted_coins.push_back(0.1);
}

void RefoundComputer::calculate()
{
  double refound_tmp = refound;
  refound_in_coins.clear();
  for(unsigned int i = 0; i < accepted_coins.size(); i++)
    while (refound_tmp >= accepted_coins[i])
    {
      refound_in_coins.push_back(accepted_coins[i]);
      refound_tmp -= accepted_coins[i];
    }
}

ostream& operator<<(ostream& output, const RefoundComputer& refound)
{
  cout << refound.str();
  return output;
}
