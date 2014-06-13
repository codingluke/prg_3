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

Maumau::Maumau()
{
  seed_rand();
  init_players(4);
  give_cards(5);
  clear_rules();
  skip_round = false;
  played_rounds = 0;
}

Maumau::Maumau(int number_of_players)
{
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

void Maumau::round_for(Player& actor, bool manually)
{
  skip_round = false;
  played_rounds++;
  ace_rule(actor);
  seven_rule(actor);
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

void Maumau::print_loosers_eyes() const
{
  int winner_id = winner();
  for (int i = 0; i < (int)players.size(); i++)
    if (i != winner_id)
      cout << players[i] << ": " << players[i].get_cards_sum() << endl;
}

void Maumau::ace_rule(Player& actor)
{
  Card last_played = played_cards.back();
  if ((last_played.get_sign() == "Ass") && !ace_played)
  {
    skip_round = true;
    int card_index = actor.has_card("Ass");
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

void Maumau::seven_rule(Player& actor)
{
  Card last_played = played_cards.back();
  if (last_played.get_sign() == "7" && seven_played > 0)
  {
    int card_index = actor.has_card("7");
    if (card_index > -1)
    {
      played_cards.push_back(actor.play(card_index + 1));
      seven_played++;
      skip_round = true;
      cout << endl << "REGEL: Sieben erhöht auf " << seven_played
           << " von " << actor << endl;
    }
    else
    {
      for (int i = 0; i < seven_played * 2; i++)
      {
        actor.add(cards.pop());
        swap_when_cards_empty();
      }
      seven_played = 0;
      cout << endl << "REGEL: Sieben wurde abgesessen von "
           << actor << endl;
    }
  }
}

void Maumau::whish_rule(Player& actor)
{
  Card last_played = played_cards.back();
  if (last_played.get_sign() == "Bube" && whished_sign == "")
  {
    string signs[] = { "Karo", "Herz", "Pik", "Kreuz" };
    cout << endl << actor << " darf eine Farbe waehlen"
         << endl << "Moegliche Farben sind: " << endl;
    for (int i = 0; i < 4; i++)
      cout << i + 1 << " " << signs[i] << endl;
    int index = read_int("Bitte Farbe waehlen: ", 1, 4);
    whished_sign = signs[index - 1];
  }
}

void Maumau::auto_whish_rule()
{
  Card last_played = played_cards.back();
  if (last_played.get_sign() == "Bube" && whished_sign == "")
  {
    string signs[] = { "Karo", "Herz", "Pik", "Kreuz" };
    whished_sign = signs[get_random_number(0, 4)];
    cout << "Gewuenschte Farbe: " << whished_sign;
  }
}

void Maumau::clear_rules()
{
  ace_played = false;
  seven_played = 1;
  whished_sign = "";
}

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

bool Maumau::validate_card(const Card& a_card) const
{
  Card reverence = played_cards.back();
  bool same_type = a_card.get_type() == reverence.get_type();
  bool same_id = a_card.get_id() == reverence.get_id();
  bool no_boy = a_card.get_sign() != "Bube";
  bool whished_type = a_card.get_type() == whished_sign;
  bool result = false;
  if (whished_sign != "")
    result = whished_type && no_boy;
  else
    result = (same_type || same_id);
  return result;
}

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

int Maumau::get_highest_cards_count() const
{
  int max = 0;
  for (unsigned int i = 0; i < players.size(); i++)
    if (max < players[i].get_cards_count())
      max = players[i].get_cards_count();
  return max;
}

void Maumau::init_players(int number_of_players)
{
  for (int i = 0; i < number_of_players; i++)
    players.push_back(Player());
}

void Maumau::give_cards(int number_of_cards)
{
  for (int i = 0; i < number_of_cards; i++)
    for (unsigned int j = 0; j < players.size(); j++)
      players[j].add(cards.pop());
}

int Maumau::winner() const
{
  int winner = -1;
  for (unsigned int i = 0; i < players.size(); i++)
    if (players[i].get_cards_count() == 0)
      winner = i;
  return winner;
}

void Maumau::seed_rand()
{
  if(!seeded)
  {
    srand(time(0));
    seeded = true;
  }
}

int Maumau::get_random_number(int begin, int end) const
{
  return begin + int(end * (rand() / (RAND_MAX + 1.0)));
}
