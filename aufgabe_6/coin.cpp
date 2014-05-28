#include "coin.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include "console_input.h"

using namespace std;

Coin::Coin()
{
  init_default_coins();
  value = accepted_coins[1];
}

Coin::Coin(double a_value)
{
  init_default_coins();
  if (validate_value(a_value))
    value = a_value;
  else
    throw "Nicht akzeptierte Zahlungseinheit";
}

string Coin::str() const
{
  ostringstream modifier(ios::out);
  modifier << setprecision(2) << value;
  return modifier.str();
}

double Coin::get_value() const
{
  return value;
}

void Coin::init_default_coins()
{
  accepted_coins.push_back(50);
  accepted_coins.push_back(20);
  accepted_coins.push_back(10);
  accepted_coins.push_back(5);
  accepted_coins.push_back(1);
  accepted_coins.push_back(0.5);
  accepted_coins.push_back(0.1);
  accepted_coins.push_back(0.0);
}

bool Coin::validate_value(double a_value)
{
  bool value_ok = false;
  for (unsigned int i = 0; i < accepted_coins.size(); i++)
    if (accepted_coins[i] == a_value)
      value_ok = true;
  return value_ok;
}

istream& operator>>(istream& input, Coin& coin)
{
  double a_value;
  bool entry_ok = false;
  do
  {
    try
    {
      a_value = read_double("Bitte eine Münze oder Note einwerfen: ");
      coin = Coin(a_value);
      entry_ok = true;
    }
    catch(const char* msg)
    {
      cout << msg << endl;
    }
  } while(!entry_ok);
  return input;
}

ostream& operator<<(ostream& output, const Coin& coin)
{
  cout << coin.str();
  return output;
}
