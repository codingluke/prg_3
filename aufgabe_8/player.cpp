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
  name = "Hans Ueli Meier";
}

Player::Player(string a_name)
{
  init();
  name = a_name;
}

void Player::add(const Card& a_card)
{
  cards.push_back(a_card);
}

Card Player::play(int index)
{
  Card card_to_play = cards[index - 1];
  cards.erase(cards.begin());
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

string Player::show_cards() const
{
  ostringstream modifier(ios::out);
  modifier << "Karten des Player" << number << ":" << endl;
  for (unsigned int i = 0; i < cards.size(); i++)
    modifier << "(" << i + 1 << ") " << cards[i] << endl;
  return modifier.str();
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

//istream& operator>>(istream& input, Player& a_player)
//{
  //string name = read_text("Bitte Name angeben: ");
  //a_player = a_player(name);
  //do
  //{
    //try
    //{
      //cout << "Bitte Ziffer " << i + 1 << " eingeben: ";
      //number = read_int(1, 49);
      //for (int j = 0; j < i; j++)
        //if (number == static_cast<int>(numbers[j]))
          //throw "Ziffer Bereits vorhanden!";
      //numbers[i] = static_cast<char>(number);
      //entry_ok = true;
    //}
    //catch(const char* msg)
    //{
      //cout << msg << endl;
    //}
  //} while(!entry_ok);
    //entry_ok = false;
  //}
  //a_lottery_win = LotteryWin(numbers);
  //return input;

  //return input;
//}
