#include "player.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "card.h"
#include "time.h"

int Player::player_count = 0;

Player::Player()
{
  init();
}

void Player::add(int index, const Card& a_card)
{
  cards.insert(cards.begin() + index, a_card);
}

void Player::add(const Card& a_card)
{
  add(0, a_card);
}

Card Player::play(int index)
{
  Card card_to_play = cards[index - 1];
  cards.erase(cards.begin() + (index - 1));
  return card_to_play;
}

int Player::has_card(string a_sign) const
{
  int has_it = -1;
  for (unsigned int i = 0; i < cards.size(); i++)
    if (cards[i].get_sign() == a_sign)
      has_it = i;
  return has_it;
}

int Player::get_cards_sum() const
{
  int sum = 0;
  for (unsigned int i = 0; i < cards.size(); i++)
    sum += cards[i].get_eyes();
  return sum;
}

string Player::get_name() const
{
  ostringstream modifier(ios::out);
  modifier << "Spieler " << number;
  return modifier.str();
}

int Player::get_cards_count() const
{
  return cards.size();
}

int Player::get_number() const
{
  return number;
}

void Player::init()
{
  player_count++;
  number = player_count;
}

Card Player::operator[](int key) const
{
  return cards[key];
}

ostream& operator<<(ostream& output, const Player& a_player)
{
  output << a_player.get_name();
  return output;
}
