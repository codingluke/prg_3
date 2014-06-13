#include "player.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "card.h"
#include "time.h"

int Player::player_count = 0;

/**
 * Default constructor. Initializes a player with a number, automatically
 * generated by the number of already existing players.
 */
Player::Player()
{
  init();
}

/**
 * Add a card to the player in a given index.
 *
 * @param index     Index where to add the card.
 * @param a_card    The card to add.
 */
void Player::add(int index, const Card& a_card)
{
  cards.insert(cards.begin() + index, a_card);
}

/**
 * Adds a given card at the end of the players
 * cards.
 *
 * @param a_card  The card to add.
 */
void Player::add(const Card& a_card)
{
  add(cards.size(), a_card);
}

/**
 * Plays a card of a given index from the player. The played
 * card getts also removed for the players cards.
 *
 * @param index  Index of the card to play.
 *
 * @return the card in the place of a given index.
 */
Card Player::play(int index)
{
  Card card_to_play = cards[index - 1];
  cards.erase(cards.begin() + (index - 1));
  return card_to_play;
}

/**
 * Checks if a player has a card of a given Sign.
 *
 * @param a_sign  Card::Sign to search for.
 *
 * @return index of the first matched card or -1.
 */
int Player::has_card(Card::Sign a_sign) const
{
  int has_it = -1;
  for (unsigned int i = 0; i < cards.size(); i++)
    if (cards[i].get_sign() == a_sign)
      has_it = i;
  return has_it;
}

/**
 * Returns the sum of the eyes of all the cards in the
 * players hand.
 *
 * @return sum of the eyes of the cards.
 */
int Player::get_cards_sum() const
{
  int sum = 0;
  for (unsigned int i = 0; i < cards.size(); i++)
    sum += cards[i].get_eyes();
  return sum;
}

/**
 * Returns the name of the player. Depends on the number of the player
 *
 * Spieler <nummer>
 *
 * @return name of the player.
 */
string Player::get_name() const
{
  ostringstream modifier(ios::out);
  modifier << "Spieler " << number;
  return modifier.str();
}

/**
 * Returns the number of cards the player has in his hand.
 *
 * @return the number of cards.
 */
int Player::get_cards_count() const
{
  return cards.size();
}

/**
 * Returns the number of the player. All players have a unique number.
 *
 * @return number of the player.
 */
int Player::get_number() const
{
  return number;
}

/**
 * Increments the static player count and gives it to the actual player.
 */
void Player::init()
{
  player_count++;
  number = player_count;
}

/**
 * Overwrides the acces operator[]. Defines how to access a card
 * of a given key.
 *
 * @param key  Key (index) of the card.
 *
 * @return the Card on the place of a given key.
 */
Card Player::operator[](int key) const
{
  return cards[key];
}

/**
 * Global put to operator<<. Defines how to represent a player when
 * put to a output stream. It shows the players name.
 *
 * @param output  The output stream.
 * @param a_player The Player to put to the output stream.
 *
 * @return The output stream.
 */
ostream& operator<<(ostream& output, const Player& a_player)
{
  output << a_player.get_name();
  return output;
}
