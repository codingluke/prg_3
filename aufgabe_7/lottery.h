#ifndef LOTTERY_H
#define LOTTERY_H

#include "lottery_win.h"

class Lottery
{
  private:
    int number_of_winnings;
    LotteryWin *winnings;
    int *numbers_count;

  public:
    Lottery();
    Lottery(int a__number_of_winnings);
    Lottery(const Lottery& original); // copy constructor

    ~Lottery();

    int get_number_of_winnings() const;
    int get_years_to_play() const;
    int get_rest_months_to_play() const;

    Lottery& operator=(const Lottery& a_lottery);

  private:
    void init_winnings();
    void init_winnings(const LotteryWin *the_winnings);
    void init_numbers_count(const int *the_numbers_count);
    void count_number(int a_number);
};

#endif
