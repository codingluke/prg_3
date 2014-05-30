#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include "price_computer.h"
#include "refound_computer.h"

/**
 * Constructor to initialize a PriceComputer with a given prive
 * and a given currency.
 *
 * @param a_price     Price to count to.
 * @param a_currency  Currency of the price.
 */
PriceComputer::PriceComputer(double a_price, const string& a_currency)
  throw(const invalid_argument)
{
  if (a_price < 0)
    throw invalid_argument("Es gibt keine negative Preise.");
  price = a_price;
  currency = a_currency;
  abordet = false;
}

/**
 * Adds a coin "value" to the PriceComputer. Gets summed by
 * previous added coins.
 *
 * @param a_coin Coin "value" to add.
 *
 * @return sum of all added coins until now.
 */
double PriceComputer::add(double a_coin) throw(const invalid_argument)
{
  if (a_coin < 0)
    throw invalid_argument("Es gib keine negativen Geldeinheiten");
  else if (a_coin == 0)
    abordet = true;
  coin_stack.push_back(a_coin);
  sort_coins();
  return sum_coin_stack();
}

/**
 * Returns the state of the PriceComputer. There are four
 * different states represented as integers (-1, 0, 1 and 2).
 *
 * @return state as Integer
 *         -1   The sum of all added coins is less than the price.
 *         0    Abordet, as soon as a 0.00 value coin gets added.
 *         1    The sum of all added coins is exactly the price.
 *         2    The sum of all added coins is more than the price.
 */
int PriceComputer::state() const
{
  double result = 2;
  double sum_coins = sum_coin_stack();
  if (abordet)
    result = 0;
  else if (price > sum_coins)
    result = -1;
  else if (fabs(price - sum_coins) < 0.0001)
    result = 1;
  return result;
}

/**
 * Returns the remainder from the sum of all added coins
 * to the price. Can be negative, when the sum of all coins is
 * higher then the price.
 *
 * @return remainder from the sum of all added coins to the price.
 */
double PriceComputer::remainder() const
{
  return price - sum_coin_stack();
}

/**
 * Representation of a PriceComputer object as a string.
 * Has a differen output for every state.
 *
 * when state is -1:
 *    Noch zu bezahlen: remainder currency
 * when state is 0:
 *    Rückgabe: sum of all entered coins
 *    Zalungseinheiten: 1 * 50.00 Euro 2 * 5.00 Euro ...
 * When state is 1:
 *    Nothing
 * When state is 2:
 *    Zu viel bezahlt! 3.30 Euro
 *
 * @return Stringrepresentation according the different states.
 */
string PriceComputer::str() const
{
  ostringstream modifier(ios::out);
  int state_tmp = state();
  if (state_tmp == -1)
    modifier << "Noch zu bezahlen: " << setprecision(2) << fixed
             << remainder() << " " << currency << endl;
  else if (state_tmp == 0)
    modifier << "Rückgabe: " << sum_coin_stack()
             << " " << currency << endl
             << "Zahlungseinheiten: " << str_grouped();
  else if (state() == 2)
    modifier << "Zuviel bezahlt! " << remainder() * -1
             << " " << currency << endl;
  return modifier.str();
}

/**
 * Represents the inserted coins grouped by value. For example
 * when we have this coins in the list (50.00, 50,00, 00.10, 00.10)
 * it will generate a string like this "2 * 50.00 Euro 1 * 00.10 Euro".
 *
 * @return the added coins grouped and counted by their value.
 */
string PriceComputer::str_grouped() const
{
  ostringstream modifier(ios::out);
  int n = 1;
  if (coin_stack.size() == 1)
    modifier << n << " * " << setprecision(2) << fixed
             << coin_stack[0] << " " << currency << " ";
  for(unsigned int i = 1; i < coin_stack.size(); i++)
  {
    if (coin_stack[i] != coin_stack[i - 1])
    {
      modifier << n << " * " << setprecision(2) << fixed
               << coin_stack[i - 1] << " " << currency << " ";
      n = 1;
    }
    else
    {
      n++;
      if (i == coin_stack.size() - 1)
        modifier << n << " * " << setprecision(2)
               << coin_stack[i] << " " << currency << " ";
    }
  }
  return modifier.str();
}

/**
 * Returns the sum of all added coins.
 *
 * @return sum of all added coins.
 */
double PriceComputer::sum_coin_stack() const
{
  double sum = 0;
  for(unsigned int i = 0; i < coin_stack.size(); i++)
    sum += coin_stack[i];
  return sum;
}

/**
 * Sorts the inserted coins with the entry sort algorithm ascendent.
 */
void PriceComputer::sort_coins()
{
  int index_max = 0;
  double tmp;
  for (int i = coin_stack.size() - 1; i > 0; i--)
  {
    index_max = 0;
    for (int j = 0; j <= i; j++)
    {
      if (coin_stack[j] < coin_stack[index_max])
        index_max = j;
    }
    if (coin_stack[index_max] < coin_stack[i])
    {
      tmp = coin_stack[i];
      coin_stack[i] = coin_stack[index_max];
      coin_stack[index_max] = tmp;
    }
  }
}


/**
 * Overrides the global operator<< "put to". Represents a PriceComputer
 * when put to an output stream.
 *
 * @param output  io output stream.
 * @param pc      PriceComputer to put to the output stream.
 *
 * @return the io output stream.
 */
ostream& operator<<(ostream& output, const PriceComputer& pc)
{
  output << pc.str();
  return output;
}
