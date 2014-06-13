#ifndef CARD_SET_H
#define CARD_SET_H

#include <vector>
#include <string>
#include <stdexcept>
#include "card.h"

using namespace std;

/**
 * Defines a CardSet. Can hold and shuffle many Cards.
 * It is possible to generate a full set of 32 Cards for a
 * Cardgame like Maumau or Skatt.
 */
class CardSet
{
  private:
    vector<Card> cards;
    static bool seeded;

  public:
    CardSet();
    CardSet(vector<Card> the_cards);

    Card pop() throw(const length_error);
    int push(Card a_card);
    unsigned int size() const;
    bool is_empty() const;

    Card operator[](int key) const;

  private:
    void init_32_set();
    void shuffle(int n);
    void seed_rand();
};

#endif
