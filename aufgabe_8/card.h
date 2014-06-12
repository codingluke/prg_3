#ifndef CARD_H
#define CARD_H

#include <string>

using namespace std;

class Card
{
  private:
    string type;
    int id;

  public:
    Card();
    Card(string a_type, int a_id);

    int get_id() const;
    int get_eyes() const;
    string get_color() const;
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
