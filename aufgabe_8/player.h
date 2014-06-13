#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <stdexcept>
#include "card.h"

using namespace std;

/**
 * Defines a card Player. Can hold many cards and play them form any index.
 * Every Player has a unique id which gets generated automatically.
 */
class Player
{
  private:
    /** cards in the hand of the player */
    vector<Card> cards;
    /** unique number of the player */
    int number;
    /** Name of the player, at the moment not in use */
    string name;
    /** number of all players */
    static int player_count;

  public:
    Player();
    Player(string a_name);
    Player(vector<Card> the_cards);
    Player(string name, vector<Card> the_cards);

    void add(int index, const Card& a_card) throw(const out_of_range);
    void add(const Card& a_card);
    Card play(int index) throw(const out_of_range);
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
