#ifndef CARD_H
#define CARD_H

#include <string>

using namespace std;

class Card
{
  public:
    enum Color { KARO, HERZ, PIK, KREUZ };
    enum Sign {
      SIEBEN, ACHT, NEUN, ZEHN,
      BUBE, DAME, KOENIG, ASS
    };

  private:
    Card::Color color;
    Card::Sign sign;
    static vector<string> colors;

  public:
    Card();
    Card(string a_type, int a_id);
    Card(Card::Color a_color, Card::Sign a_sign);

    int get_eyes() const;
    Card::Color get_color() const;
    Card::Sign get_sign() const;
    string get_color_str() const;
    string get_sign_str() const;
    string str() const;
    vector<string> get_colors();

  private:
    static void init_colors();
};

int operator==(const Card& left, const Card& right);
int operator!=(const Card& left, const Card& right);
ostream& operator<<(ostream& output, const Card& a_card);
istream& operator>>(istream& input, Card& a_card);

#endif
