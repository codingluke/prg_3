#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include "refound_computer.h"

/**
 * Initializes a RefoundComputer instance with a refound of zero,
 * the currency "Euro" and a empty list of accepted values.
 */
RefoundComputer::RefoundComputer()
{
  refound = 0;
  currency = "Euro";
}

/**
 * Initializes a RefoundCoumputer instance with a given currency
 * and a given list of accepted values.
 *
 * @param a_currency          the currency for string representation.
 * @param accepted_coins_list list of accepted values to represent the refound.
 */
RefoundComputer::RefoundComputer(const string& a_currency,
                                 const vector<double>& accepted_coins_list)
{
  refound = 0;
  currency = a_currency;
  accepted_coins = accepted_coins_list;
}

/**
 * Sets the refound to represent through the accepted values.
 * and calculates the the sum out of the accepted values.
 *
 * @param a_refound Refound to calculate.
 */
void RefoundComputer::set_refound(double a_refound)
{
  refound = a_refound;
  calculate();
}

/**
 * Returns the representation of the RefoundComputer as a string.
 * When there are no values calculated for the refound, there will
 * be a empty string. When there is a combination of values calculated,
 * it will return a string like this:
 *
 * Rückgabe: 10.10
 * Zahlungseinheigen: 1 * 10 Euro 1 * 0.00 Euro.
 *
 * @return string representation of the RefoundComputer.
 */
string RefoundComputer::str() const
{
  ostringstream modifier(ios::out);
  if (refound_in_coins.size() > 0)
    modifier << "Rückgabe: " << refound << " " << currency << endl
             << "Zahlungseinheiten: " << str_grouped();
  modifier << endl;
  return modifier.str();
}

/**
 * Represents the calculated value combinations grouped
 * and counted by value. For example, when we have this values
 * in the list (50.00, 50,00, 00.10, 00.10)
 * it will generate a string like this "2 * 50.00 Euro 1 * 00.10 Euro".
 *
 * @return the calculated values grouped and counted by their value.
 */
string RefoundComputer::str_grouped() const
{
  ostringstream modifier(ios::out);
  int n = 1;
  if (refound_in_coins.size() == 1)
    modifier << 1 << " * " << setprecision(2) << fixed
             << refound_in_coins[0] << " " << currency << " ";
  for(unsigned int i = 1; i < refound_in_coins.size(); i++)
  {
    if (refound_in_coins[i] != refound_in_coins[i - 1])
    {
      modifier << n << " * " << setprecision(2) << fixed
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
  return modifier.str();
}

/**
 * Calculates the combination of accepted values to represent the
 * refound. Garantees that the representation is made of the least
 * possoble count of values. (Take the biggest possible values first).
 */
void RefoundComputer::calculate()
{
  double refound_tmp = refound;
  refound_in_coins.clear();
  for(unsigned int i = 0; i < accepted_coins.size(); i++)
    while (refound_tmp >= accepted_coins[i] && accepted_coins[i] > 0)
    {
      refound_in_coins.push_back(accepted_coins[i]);
      refound_tmp -= accepted_coins[i];
    }
}

/**
 * Overrides the global operatro<< "put to", for the default string
 * representation of a RecoundComputer in a output stream. Uses
 * the representation defined with PriceComputer::str().
 *
 * @param output    io output stream.
 * @param refound   RefouncComputer to put to the output stream.
 *
 * @return io output stream.
 */
ostream& operator<<(ostream& output, const RefoundComputer& refound)
{
  cout << refound.str();
  return output;
}

