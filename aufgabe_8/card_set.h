#ifndef CARD_SET_H
#define CARD_SET_H

#include <vector>
#include "card.h"
#include <string>

using namespace std;

class CardSet
{
  private:
    vector<Card> cards;
    static bool seeded;

  public:
    CardSet();
    CardSet(vector<Card> the_cards);

    Card pop();
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
