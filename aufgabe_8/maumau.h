#ifndef MAUMAU_H
#define MAUMAU_H

#include "card_set.h"
#include "player.h"
#include "card.h"

class Maumau
{
  private:
    CardSet cards;
    vector<Player> players;
    vector<Card> played_cards;
    int played_rounds;
    int seven_played;
    bool ace_played;
    bool skip_round;
    bool whish_played;
    Card::Color whished_color;
    static bool seeded;

  public:
    Maumau();
    Maumau(int number_of_players);

    void start(bool manual = false);

  private:
    void seed_rand();
    void init_players(int number_of_players);
    void give_cards(int number_of_cards);
    void swap_when_cards_empty();
    int get_highest_cards_count() const;
    int winner() const;
    int get_random_number(int begin, int end) const;
    bool validate_card(const Card& a_card) const;

    void print_situation(bool manually = false) const;
    void print_player_cards() const;
    void print_other_cards() const;
    void print_other_cards_full() const;
    void print_loosers_eyes() const;

    void round_for(Player& actor, bool manually);
    void play_card(Player& actor);
    void auto_play_card(Player& actor);
    void skip_rule(Player& actor);
    void collect_rule(Player& actor);
    void whish_rule(Player& actor);
    void auto_whish_rule();
    void clear_rules();
};

#endif
