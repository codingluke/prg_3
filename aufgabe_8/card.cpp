#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include "card.h"

using namespace std;

vector<string> Card::colors;

/**
 * Default constructor. Instantiates the card "Herz 7".
 */
Card::Card()
{
  color = Card::HERZ;
  sign = Card::SIEBEN;
  init_colors();
}

/**
 * Instantiates a card out of a given Card::Color and Card::Sign.
 *
 * @param a_color   The color of the card.
 * @param a_sign    The sign of the card.
 */
Card::Card(Card::Color a_color, Card::Sign a_sign)
{
  color = a_color;
  sign = a_sign;
  init_colors();
}

/**
 * Returns the color of the card.
 *
 * @return color of the card.
 */
Card::Color Card::get_color() const
{
  return color;
}

/**
 * Returns the sign of the card.
 *
 * @return sign of the card.
 */
Card::Sign Card::get_sign() const
{
  return sign;
}

/**
 * Returns the sign in its string representation.
 *
 * @return Sign as a string.
 */
string Card::get_sign_str() const
{
  string signs[] = {
    "7", "8", "9", "10", "Bube", "Dame", "Koenig", "Ass"
  };
  return signs[sign];
}

/**
 * Returns all the possible colors of cards. Maybe this
 * can be solved more elegant.
 *
 * @return all possible colors in their string representation.
 */
vector<string> Card::get_colors()
{
  return colors;
}

/**
 * Initializes the colors vector with all the possible colors
 * in their string representation.
 */
void Card::init_colors()
{
  if (colors.size() == 0)
  {
    colors.push_back("Karo");
    colors.push_back("Herz");
    colors.push_back("Pik");
    colors.push_back("Kreuz");
  }
}

/**
 * Returns the color of a card as string.
 *
 * @return string representation of the color of the card.
 */
string Card::get_color_str() const
{
  return colors[color];
}

/**
 * Returns the "eyes" or value of the card. The eyes depends on the
 * sign.
 *
 * @return eyes of the card.
 */
int Card::get_eyes() const
{
  int eyes[] = { 0, 0, 0, 10, 2, 3, 4, 11 };
  return eyes[sign];
}

/**
 * Returns the Stringrepresentation of the card.
 *\n
 * Karo 9\n
 * Herz Bube
 *
 * @return string representation of the card.
 */
string Card::str() const
{
  ostringstream modifier(ios::out);
  modifier << get_color_str() << " " << get_sign_str();
  return modifier.str();
}

/**
 * Overrides the comperator operator==. In this case a card is
 * same to an other card when the sign and the color is same.
 *
 * @param left    Left Card to compare.
 * @param right   Right Card to compare.
 *
 * @return true when they are equal.
 *         false when they are not equal.
 */
int operator==(const Card& left, const Card& right)
{
  bool same_id = left.get_sign() == right.get_sign();
  bool same_type = left.get_color() == right.get_color();
  bool result = false;
  if (same_id && same_type)
    result = true;
  return result;
}

/**
 * Overrides the not-equal operator!=. A card is not equal when
 * a sign or color is not the same.
 *
 * @param left    Left Card to compare.
 * @param right   Right Card to compare.
 *
 * @return true when they are not equal.
 *         false when they are equal.
 */
int operator!=(const Card& left, const Card& right)
{
  return !(left == right);
}

/**
 * Global put to operator<<. Defines how to represent a card when
 * put to a output stream. It just takes the definition of the function str.
 *
 * @param output  The output stream.
 * @param a_card  The Card to put to the output stream.
 *
 * @return The output stream.
 */
ostream& operator<<(ostream& output, const Card& a_card)
{
  output << a_card.str();
  return output;
}
