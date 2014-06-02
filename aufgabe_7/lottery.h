#ifndef LOTTERY_H
#define LOTTERY_H

#include "lottery_win.h"
#include <string>

using namespace std;

typedef int (LotteryWin::*StatFunction)() const;
typedef bool (LotteryWin::*StatBoolFnc)() const;

class Lottery
{
  private:
    int number_of_winnings;
    LotteryWin *winnings;

  public:
    Lottery();
    Lottery(int a__number_of_winnings);
    Lottery(const Lottery& original); // copy constructor

    ~Lottery();

    int get_number_of_winnings() const;
    string str_years_to_play() const;
    string str_frequency_scale();
    string str_minimum();
    string str_maximum();
    string str_length();
    string str_count_length_in_win();
    string str_count_odd();
    string str_count_even();
    string str_count_prim();
    string str_count_not_prim();
    string str_count_street_types();
    string tip() const;
    string autotip() const;

    Lottery& operator=(const Lottery& a_lottery);

  private:
    void init_winnings();
    void init_winnings(const LotteryWin *the_winnings);
    void clear_int_array(unsigned int *array, int length) const;
    int get_max_index(unsigned int *statistics) const;
    int get_min_index(unsigned int *statistics) const;
    int statistic_number(StatBoolFnc fnc) const;
    int years_to_play() const;
    int rest_months_to_play() const;
    double percentage_of_all(int number) const;
    string statistic_table(StatFunction fnc, int from, int to) const;
    string statistic_number(const string& text, StatBoolFnc fnc) const;
};

#endif
