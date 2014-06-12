#include "card_set.h"
#include "time.h"
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <iomanip>

bool CardSet::seeded = false;

CardSet::CardSet()
{
  seed_rand();
  init_32_set();
  mix(3);
}

CardSet::CardSet(vector<Card> the_cards)
{
  seed_rand();
  cards = the_cards;
  mix(3);
}

Card CardSet::pop()
{
  Card last = cards.back();
  cards.pop_back();
  return last;
}

int CardSet::push(Card a_card)
{
  cards.push_back(a_card);
  return cards.size();
}

bool CardSet::is_empty() const
{
  return (cards.size() == 0);
}

string CardSet::show_cards() const
{
  ostringstream modifier(ios::out);
  for (unsigned int i = 0; i < cards.size(); i++)
    modifier << "(" << i + 1 << ") " << cards[i] << endl;
  return modifier.str();
}

unsigned int CardSet::size() const
{
  return cards.size();
}

Card CardSet::operator[](int key) const
{
  return cards[key];
}

void CardSet::init_32_set()
{
  cards.clear();
  string types[] = { "Karo", "Pik", "Herz", "Kreuz" };
  for (int i = 0; i < 4; i++)
    for (int j = 7; j < 15; j++)
      cards.push_back(Card(types[i], j));
}

void CardSet::mix(int n)
{
  for (unsigned int i = 0; i < cards.size() * n; i++)
  {
    int random_index = int((cards.size()) * (rand() / (RAND_MAX + 1.0)));
    Card tmp = cards[random_index];
    cards.erase(cards.begin() + random_index);
    cards.push_back(tmp);
  }
}

void CardSet::seed_rand()
{
  if(!seeded)
  {
    srand(time(0));
    seeded = true;
  }
}
