#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "card.h"

using namespace std;

class Player
{
  private:
    vector<Card> cards;

    int number;
    string name;
    static int player_count;

  public:
    Player();
    Player(string a_name);
    Player(vector<Card> the_cards);
    Player(string name, vector<Card> the_cards);

    void add(int index, const Card& a_card);
    void add(const Card& a_card);
    Card play(int index);
    Card play();
    string show_cards() const;
    string get_name() const;
    int get_cards_count() const;
    int get_cards_sum() const;
    int has_card(Card::Sign a_sign) const;
    int get_number() const;

    Card operator[](int key) const;

  private:
    void init();
};

ostream& operator<<(ostream& output, const Player& a_player);
istream& operator>>(istream& input, Player& a_player);

#endif
