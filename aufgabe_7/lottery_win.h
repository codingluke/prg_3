#ifndef LOTTERY_WIN_H
#define LOTTERY_WIN_H

#include <string>

using namespace std;

class LotteryWin
{
  private:
    char *numbers;
    static bool seeded;

  public:
    LotteryWin();
    LotteryWin(const char *the_numbers);
    LotteryWin(const LotteryWin& original); // copy constructor

    ~LotteryWin();

    string str() const;
    int minimum() const;
    int maximum() const;
    int length() const;
    int street_type() const;
    bool has_length_in_win() const;
    bool is_even() const;
    bool is_odd() const;
    bool is_prim() const;
    bool is_not_prim() const;

    //void count_numbers(unsigned int *numbers_count) const;

    LotteryWin& operator=(const LotteryWin& a_lottery_win);
    int operator[](const int& key) const;

  private:
    void seed_rand();
    void generate_win();
    bool is_valid_number(char number) const;
    bool is_primnumber(const int& number) const;
};

int operator==(const LotteryWin& left, const LotteryWin& right);
ostream& operator<<(ostream& output, const LotteryWin& a_lottery_win);
istream& operator>>(istream& input, LotteryWin& a_lottery_win);

#endif
