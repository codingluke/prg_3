#include <cstdlib>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "card_set.h"
#include "time.h"

bool CardSet::seeded = false;

/**
 * Default constructor. Initializes a set of 32 Cards and shuffels them.
 */
CardSet::CardSet()
{
  seed_rand();
  init_32_set();
  shuffle(3);
}

/**
 * Initializes a card set with given cards and shuffels them.
 *
 * @param the_cards  The cards for the set.
 */
CardSet::CardSet(vector<Card> the_cards)
{
  seed_rand();
  cards = the_cards;
  shuffle(3);
}

/**
 * Takes out the last card from the stack.
 *
 * @return the last card in the stack.

 * @throws std::length_error when empty.
 */
Card CardSet::pop() throw (const length_error)
{
  if (is_empty())
    throw length_error("Card set is empty!");
  Card last = cards.back();
  cards.pop_back();
  return last;
}

/**
 * Adds a card at the end of the set and returns
 * the new size.
 *
 * @param a_card  Card to add.
 *
 * @return the new size of the set.
 */
int CardSet::push(Card a_card)
{
  cards.push_back(a_card);
  return cards.size();
}

/**
 * Checks if the card set is empty.
 *
 * @return true when the card set is empty.
 *         false when the card set is not empty.
 */
bool CardSet::is_empty() const
{
  return (cards.size() == 0);
}

/**
 * Gives back the numbers of cards in set.
 *
 * @return number of cards in the set.
 */
unsigned int CardSet::size() const
{
  return cards.size();
}

/**
 * Overwrides the acces operator[]. Defines how to access a card
 * of a given key.
 *
 * @param key  Key (index) of the card.
 *
 * @return the Card on the place of a given key.
 */
Card CardSet::operator[](int key) const
{
  return cards[key];
}

/**
 * Generates 32 unique cards of a skatt set.
 */
void CardSet::init_32_set()
{
  cards.clear();
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 8; j++)
      cards.push_back(Card(static_cast<Card::Color>(i),
                           static_cast<Card::Sign>(j)));
}

/**
 * Shuffles the cards n times.
 *
 * @param n  How many times the cards should get shuffled.
 */
void CardSet::shuffle(int n)
{
  for (unsigned int i = 0; i < cards.size() * n; i++)
  {
    int random_index = int((cards.size()) * (rand() / (RAND_MAX + 1.0)));
    Card tmp = cards[random_index];
    cards.erase(cards.begin() + random_index);
    cards.push_back(tmp);
  }
}

/**
 * Seeds the srand for random number generation just one time.
 */
void CardSet::seed_rand()
{
  if(!seeded)
  {
    srand(time(0));
    seeded = true;
  }
}
