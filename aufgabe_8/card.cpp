#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "card.h"

using namespace std;

Card::Card()
{
  type = "Herz";
  id = 7;
}

Card::Card(string a_type, int a_id)
{
  if (!validate_type(a_type))
    throw invalid_argument("Der Typ existiert nicht!");
  if (!validate_id(a_id))
    throw invalid_argument("Der Wert ist existiert nicht!");
  type = a_type;
  id = a_id;
}

string Card::get_type() const
{
  return type;
}

int Card::get_id() const
{
  return id;
}

Card::Color Card::get_color() const
{
  return color;
}

//Card::Sign Card::get_sign() const
//{
  //return sign;
//}

string Card::get_sign() const
{
  string signs[] = {
    "7", "8", "9", "10",
    "Bube", "Dame", "Koenig", "Ass"
  };
  return signs[id - 7];
}

int Card::get_eyes() const
{
  int eyes[] = { 0, 0, 0, 10, 2, 3, 4, 11 };
  return eyes[id - 7];
}

string Card::str() const
{
  ostringstream modifier(ios::out);
  modifier << type << " " << get_sign();
  return modifier.str();
}

bool Card::validate_id(int a_id) const
{
  return (a_id > 6 && a_id < 15);
}

bool Card::validate_type(string a_type) const
{
  return (a_type == "Karo" || a_type == "Herz" ||
          a_type == "Pik" || a_type == "Kreuz");
}

int operator==(const Card& left, const Card& right)
{
  bool same_id = left.get_eyes() == right.get_eyes();
  bool same_type = left.get_type() == right.get_type();
  bool result = false;
  if (same_id && same_type)
    result = true;
  return result;
}

int operator!=(const Card& left, const Card& right)
{
  return !(left == right);
}

ostream& operator<<(ostream& output, const Card& a_card)
{
  output << a_card.str();
  return output;
}
