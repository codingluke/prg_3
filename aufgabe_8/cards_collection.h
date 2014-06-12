#ifndef CARDS_COLLECTION_H
#define CARDS_COLLECTION_H

#include "card.h"

class CardsCollection
{
  private:
    Card *cards;

  public:
    CardsCollection(const Cart *cards);
    CardsCollection(const CardsCollection& other); // copy constructor

    ~CardsCollection();

    int push(Card a_card);
    Card pop();
    void mix();

    CardsCollection& operator=(const CardsCollection& other);
};

#endif

