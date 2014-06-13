#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "maumau.h"
#include "card_set.h"
#include "player.h"
#include "card.h"
#include "console_input.h"
#include "time.h"

bool Maumau::seeded = false;

/**
 * Default constructor. Initializes four players and gives out five
 * cards to all players.
 */
Maumau::Maumau()
{
  Maumau(4);
}

/**
 * Constructor to initialize Maumau with a given number of players and
 * gives out five carts to all the players.
 * cards to all players.
 *
 * @param number_of_players   The number of players to play the game.
 */
Maumau::Maumau(int number_of_players)
{
  // TODO : EXCEPTION!!!
  if (number_of_players > 6)
    cout << "TOO MANY PLAYERS!";
  seed_rand();
  init_players(number_of_players);
  give_cards(5);
  clear_rules();
  skip_round = false;
  played_rounds = 0;
}

void Maumau::start(bool manually)
{
  int num_players = players.size();
  int start_offset = get_random_number(0, num_players);
  played_cards.push_back(cards.pop());
  do
  {
    for (int i = 0; i < num_players; i++)
    {
      int player_number = (i + start_offset) % num_players;
      if (winner() == -1)
        round_for(players[player_number], manually);
    }
  } while (winner() == -1);
  cout << endl << endl << "Der Gewinner ist " << players[winner()] << endl;
  print_loosers_eyes();
}

/**
 * Handles the logic to play a round by a Player. It counts the rounds,
 * checks the special rules, prints the situation.
 *
 * @param actor     Player for the round.
 * @param manually  Boolen to play manually or automatic.
 */
void Maumau::round_for(Player& actor, bool manually)
{
  skip_round = false;
  played_rounds++;
  skip_rule(actor);
  collect_rule(actor);
  print_situation(manually);
  if (!skip_round)
  {
    cout << ">> Aktueller Spieler: " << actor << endl;
    if (manually && actor.get_number() == 1)
    {
      play_card(actor);
      swap_when_cards_empty();
      whish_rule(actor);
    }
    else
    {
      auto_play_card(actor);
      swap_when_cards_empty();
      auto_whish_rule();
    }
  }
}

/**
 * Prints to the console the sum of the "eyes" for every
 * player which doesn't win the game.
 */
void Maumau::print_loosers_eyes() const
{
  int winner_id = winner();
  for (int i = 0; i < (int)players.size(); i++)
    if (i != winner_id)
      cout << players[i] << ": " << players[i].get_cards_sum() << endl;
}

/**
 * Definition of the skip rule. When the last played card is a ace, the
 * player has to skip a round or also play an ace, so the future next
 * player has to skip, and so on.
 *
 * @param actor   Player to check if he has to skip.
 */
void Maumau::skip_rule(Player& actor)
{
  Card last_played = played_cards.back();
  if ((last_played.get_sign() == Card::ASS) && !ace_played)
  {
    skip_round = true;
    int card_index = actor.has_card(Card::ASS);
    if (card_index > -1)
    {
      played_cards.push_back(actor.play(card_index + 1));
      cout << endl << "REGEL: Ass gespielt von "
           << actor << endl;
    }
    else
    {
      cout << endl << "REGEL: Ass abgesessen von "
           << actor << endl;
      ace_played = true;
    }
  }
}

/**
 * Definition of the collect rule. When the last played card is a seven,
 * the player has to collect two cards from the collection or also play
 * a 7. When he also plays a 7 the next player has to collect 4 cards and
 * so on.
 *
 * @param actor   Player to check if he has to collect cards.
 */
void Maumau::collect_rule(Player& actor)
{
  Card last_played = played_cards.back();
  if (last_played.get_sign() == Card::SIEBEN && seven_played > 0)
  {
    int card_index = actor.has_card(Card::SIEBEN);
    if (card_index > -1)
    {
      played_cards.push_back(actor.play(card_index + 1));
      seven_played++;
      skip_round = true;
      cout << endl << "REGEL: Aufnehmen erhöht auf " << (seven_played * 2)
           << " von " << actor << endl;
    }
    else
    {
      for (int i = 0; i < seven_played * 2; i++)
      {
        actor.add(cards.pop());
        swap_when_cards_empty();
      }
      cout << endl << "REGEL: Es wurden " << seven_played * 2
           << "Karten von " << actor << " aufgenommen." << endl;
      seven_played = 0;
    }
  }
}

/**
 * Definition of the whish rule. When a player played a "Bube" he can
 * which the color to play next.
 *
 * @param actor   Player to check if he can chose a color.
 */
void Maumau::whish_rule(Player& actor)
{
  Card last_played = played_cards.back();
  if (last_played.get_sign() == Card::BUBE && !whish_played)
  {
    cout << endl << actor << " darf eine Farbe waehlen"
         << endl << "Moegliche Farben sind: " << endl;
    for (int i = 0; i < 4; i++)
      cout << i + 1 << " " << last_played.get_colors()[i] << endl;
    int index = read_int("Bitte Farbe waehlen: ", 1, 4);
    whished_color = static_cast<Card::Color>(index - 1);
    whish_played = true;
  }
}

/**
 * Automatically whiches a color. Used for autoplay.
 */
void Maumau::auto_whish_rule()
{
  Card last_played = played_cards.back();
  if (last_played.get_sign() == Card::BUBE && !whish_played)
  {
    whished_color = Card::Color(get_random_number(0, 4));
    whish_played = true;
    cout << "Gewuenschte Farbe: " << last_played.get_colors()[whished_color];
  }
}

/**
 * Clears the rules for a new round.
 */
void Maumau::clear_rules()
{
  ace_played = false;
  seven_played = 1;
  whish_played = false;
}

/**
 * Iterates over the actual players cards an checks which can be played.
 * When no card can be played, it collects a card from the cards collection.
 * After a card was played, it clears also the rules.
 *
 * @param actor   Actual player to play.
 */
void Maumau::auto_play_card(Player& actor)
{
  Card played;
  bool entry_ok = false;
  int counter = 0;
  do
  {
    played = actor.play(1);
    counter++;
    if (validate_card(played))
    {
      entry_ok = true;
      played_cards.push_back(played);
      cout << "Gespielte karte: " << played << endl;
      clear_rules();
    }
    else
    {
      actor.add(played);
      if (counter == actor.get_cards_count())
      {
        entry_ok = true;
        actor.add(cards.pop());
        swap_when_cards_empty();
        cout << actor << " hat eine Karte aufgenommen" << endl;
      }
    }
  } while (!entry_ok);
}

/**
 * Handles the logic to play a card manually. It checks if the played card
 * is valid. When no played card is valid the player can collect a card
 * from the cards collection by enter 0.
 *
 * @param actor   Actual player to play.
 */
void Maumau::play_card(Player& actor)
{
  bool entry_ok = false;
  int cards_count = actor.get_cards_count();
  do
  {
    int card_number = read_int("Bitte Karte spielen: ", 0, cards_count);
    if (card_number == 0)
    {
      entry_ok = true;
      actor.add(cards.pop());
      swap_when_cards_empty();
    }
    else
    {
      Card played = actor.play(card_number);
      cout << "Gespielt: " << played << endl;
      if (validate_card(played))
      {
        entry_ok = true;
        played_cards.push_back(played);
        clear_rules();
      }
      else
      {
        cout << "Ungueltige Karte!" << endl;
        actor.add(card_number - 1, played);
      }
    }
  } while(!entry_ok);
}

/**
 * Checks if a card can be played at the moment. When a color is whished
 * the card has to be in this color but no "Bube".
 * When no color is whished the card has to be from the same color or
 * the same sign.
 *
 * @param a_card  Card to be checked.
 *
 * @return true when the card can be played.
 *         false when the card can not be played.
 */
bool Maumau::validate_card(const Card& a_card) const
{
  Card reverence = played_cards.back();
  bool same_type = a_card.get_color() == reverence.get_color();
  bool same_id = a_card.get_sign() == reverence.get_sign();
  bool no_boy = a_card.get_sign() != Card::BUBE;
  bool whished_type = a_card.get_color() == whished_color;
  bool result = false;
  if (whish_played)
    result = whished_type && no_boy;
  else
    result = (same_type || same_id);
  return result;
}

/**
 * Checks if the cards collection is empty. When this is the case
 * the last played card is saved, then the last played card are
 * assigned to the cards collection, the cards collection gets mixes, and
 * the last played card gets assinged back to the last played cards
 * collection.
 */
void Maumau::swap_when_cards_empty()
{
  if (cards.is_empty())
  {
    Card last_played = played_cards.back();
    played_cards.erase(played_cards.end());
    cards = CardSet(played_cards);
    played_cards.clear();
    played_cards.push_back(last_played);
  }
}

/**
 * Prints out the actual situation of the game.
 *
 * @param manually  Boolend whether to show full stacks or not.
 */
void Maumau::print_situation(bool manually) const
{
  cout << endl << endl << "Spielsituation "
       << played_rounds << endl << setw(players.size() * 15 - 1)
       << setfill('-') << "-" << setfill(' ') << endl << endl;
  print_player_cards();
  cout << endl;
  for (unsigned int i = 0; i < players.size(); i++)
    cout << right << setw(15) << setfill('-') << "  " << setfill(' ');
  cout << endl;
  if (manually)
    print_other_cards();
  else
    print_other_cards_full();
  cout << endl;
}

/**
 * Prints out the cards all the players horizontally to the console.
 */
void Maumau::print_player_cards() const
{
  for (unsigned int i = 0; i < players.size(); i++)
    cout << left << setw(15) << players[i].get_name() + ":";
  cout << endl << endl;
  for (int i = 0; i < get_highest_cards_count(); i++)
  {
    for (unsigned int j = 0; j < players.size(); j++)
    {
      if (players[j].get_cards_count() > i)
        cout << left << setw(15) << players[j][i];
      else
        cout << setw(15) << " ";
    }
    cout << endl;
  }
}

/**
 * Prints out the already played cards and the cards from
 * the cards collection horizonally.
 */
void Maumau::print_other_cards_full() const
{
  unsigned int size = 0;
  size = (cards.size() > played_cards.size()) ? cards.size() :
                                                played_cards.size();
  cout << left << setw(20) << "abgelgte Karten:"
       << left << setw(20) << "Talon:" << endl << endl;
  for (unsigned int i = 0; i < size; i++)
  {
    if (played_cards.size() > i)
      cout << left << setw(20) << played_cards[i];
    else
      cout << setw(20) << " ";
    if (cards.size() > i)
      cout << left << setw(20) << cards[i];
    else
      cout << setw(20) << " ";
    cout << endl;
  }
}

/**
 * Prints out the last played card and the last card from
 * the cards collection. Then it shows just the number of additional
 * cards on the two collections.
 */
void Maumau::print_other_cards() const
{
  ostringstream modifier1(ios::out);
  ostringstream modifier2(ios::out);
  modifier1 << "und " << played_cards.size() - 1 << " weitere";
  modifier2 << "und " << cards.size() - 1 << " weitere";
  cout << left << setw(20) << "abgelgte Karten:"
       << left << setw(20) << "Talon:" << endl << endl
       << left << setw(20) << played_cards.back()
       << left << setw(20) << cards[cards.size() -1] << endl << endl
       << left << setw(20) << modifier1.str()
       << left << setw(20) << modifier2.str();
}

/**
 * Gives back the highest number of cards one player has.
 *
 * @return highest number of cards in the hands of one player.
 */
int Maumau::get_highest_cards_count() const
{
  int max = 0;
  for (unsigned int i = 0; i < players.size(); i++)
    if (max < players[i].get_cards_count())
      max = players[i].get_cards_count();
  return max;
}

/**
 * Initiates a given number of players.
 *
 * @param number_of_players  Number of players to initialize.
 */
void Maumau::init_players(int number_of_players)
{
  for (int i = 0; i < number_of_players; i++)
    players.push_back(Player());
}

/**
 * Gives to every player a given number of cards from the cards collection.
 *
 * @param number_of_cards   Number of cards to share.
 */
void Maumau::give_cards(int number_of_cards)
{
  for (int i = 0; i < number_of_cards; i++)
    for (unsigned int j = 0; j < players.size(); j++)
      players[j].add(cards.pop());
}

/**
 * Gives back the index of the winning player. When the index is -1 there
 * is no winner.
 *
 * @return index of the winning player or -1
 */
int Maumau::winner() const
{
  int winner = -1;
  for (unsigned int i = 0; i < players.size(); i++)
    if (players[i].get_cards_count() == 0)
      winner = i;
  return winner;
}

/**
 * Seeds the srand for random number generation just one time.
 */
void Maumau::seed_rand()
{
  if(!seeded)
  {
    srand(time(0));
    seeded = true;
  }
}

/**
 * Gives back a random number in between a given range.
 *
 * @param begin   Start number of the range.
 * @param end     End number of the range.
 *
 * @return a random number between begin and end.
 */
int Maumau::get_random_number(int begin, int end) const
{
  return begin + int(end * (rand() / (RAND_MAX + 1.0)));
}
