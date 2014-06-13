#ifndef CARD_H
#define CARD_H

#include <string>

using namespace std;

class Card
{
  public:
    enum Color { KARO, HERZ, PIK, KREUZ };
    enum Sign {
      SIEBEN = 0, ACHT = 0, NEUN = 0, ZEHN = 10,
      BUBE = 2, DAME = 3, KOENIG = 4, ASS = 11
    };

  private:
    string type;
    int id;
    Card::Color color;
    Card::Sign sign;

  public:
    Card();
    Card(string a_type, int a_id);
    Card(Card::Color a_color, Card::Sign a_sign);

    int get_id() const;
    int get_eyes() const;
    Card::Color get_color() const;
    //Card::Sign get_sign() const;
    string get_type() const;
    string get_sign() const;
    string str() const;

  private:
    bool validate_id(int a_id) const;
    bool validate_type(string a_type) const;
};

int operator==(const Card& left, const Card& right);
int operator!=(const Card& left, const Card& right);
ostream& operator<<(ostream& output, const Card& a_card);
istream& operator>>(istream& input, Card& a_card);

#endif
