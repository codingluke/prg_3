#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "coin_slot.h"
#include "console_input.h"

using namespace std;

/**
 * Empty constructor, initializes a CoinSlot with the
 * currency "Euro" and accepts no coins.
 */
CoinSlot::CoinSlot()
{
  value = 0;
  currency = "Euro";
}

/**
 * Constructor, initializes a CoinSlot with a given currency.
 * It accepts no coins.
 *
 * @param a_currency currency of the coins.
 */
CoinSlot::CoinSlot(string a_currency)
{
  value = 0;
  currency = a_currency;
}

/**
 * Constructor, inizializes a CoinSlot with a given currency
 * and a list of accepted coins.
 *
 * @param a_currency          Currency of the coins.
 * @param accepted_coins_list List of accepted coins.
 */
CoinSlot::CoinSlot(string a_currency, vector<double> accepted_coins_list)
{
  value = 0;
  currency = a_currency;
  accepted_coins = accepted_coins_list;
}

/**
 * Insert a coin into the coin slot. Checks if the coin is accepted.
 *
 * @param a_coin  Coin to insert into the coin slot.
 *
 * @throws std::invalid_argument when coin is not accepted.
 */
void CoinSlot::insert(double a_coin) throw(const invalid_argument)
{
  if (validate(a_coin))
    value = a_coin;
  else
    throw invalid_argument("Nicht akzeptierte Zahlungseinheit!");
}

/**
 * Represents the CoinSlot as a string. It shows a list of the
 * accepted coins.
 *
 * Moegliche Zahlungseinehten:
 * 50.00 Euro
 * 20.00 Euro
 * ...
 *
 * @return String with the list of the accepted coins.
 */
string CoinSlot::str() const
{
  ostringstream modifier(ios::out);
  modifier << "Moegliche Zahlungseinheiten:" << endl;
  for (unsigned int i = 0; i < accepted_coins.size(); i++)
    modifier << setprecision(2) << fixed << accepted_coins[i]
             << " " << currency << endl;
  modifier << endl;
  return modifier.str();
}

/**
 * Returns the value of the inserted coin.
 *
 * @return value of the inserted coin.
 */
double CoinSlot::get_value() const
{
  return value;
}

/**
 * Adds a coin to the list of accepted coins.
 *
 * @param a_coin  Coin which should be accepted by the CoinSlot.
 */
void CoinSlot::add_accepted(double a_coin)
{
  accepted_coins.push_back(a_coin);
}

/**
 * Checks if a coin is accepted.
 *
 * @param a_value value of the coin to check.
 *
 * @return true if the coin is in the accepted list.
 *         false if the coin is not int accepted list.
 */
bool CoinSlot::validate(double a_value) const
{
  bool value_ok = false;
  for (unsigned int i = 0; i < accepted_coins.size(); i++)
    if (accepted_coins[i] == a_value)
      value_ok = true;
  return value_ok;
}

/**
 * Overrides the operator>> "get from". Handels the console input
 * of a coin.
 *
 * @param input       IO Input stream.
 * @param coin_slot   CoinSlot instance to insert a coin from the console.
 *
 * @return inputstream
 */
istream& operator>>(istream& input, CoinSlot& coin_slot)
{
  double a_value;
  bool entry_ok = false;
  do
  {
    try
    {
      a_value = read_double("Bitte eine Münze oder Note einwerfen: ");
      coin_slot.insert(a_value);
      entry_ok = true;
    }
    catch(const invalid_argument& e)
    {
      cout << e.what() << endl;
      cout << coin_slot;
    }
  } while(!entry_ok);
  return input;
}

/**
 * Overrides the operator<< "put to". Handels standard string representation
 * of a coin_slot when "put to" an output stream.
 *
 * @param output      io output stream.
 * @param coin_slot   CoinSlot to print to the output stream.
 *
 * @return
 */
ostream& operator<<(ostream& output, const CoinSlot& coin_slot)
{
  cout << coin_slot.str();
  return output;
}
