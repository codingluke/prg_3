#include "lottery_win.h"
#include "lottery.h"

Lottery::Lottery()
{
  number_of_winnings = 100;
  init_winnings();
}

Lottery::Lottery(int a_number_of_winnings)
{
  number_of_winnings = a_number_of_winnings;
  init_winnings();
}

Lottery::Lottery(const Lottery& original)
{
  number_of_winnings = original.number_of_winnings;
  init_winnings(original.winnings);
  init_numbers_count(original.numbers_count);
}

Lottery::~Lottery()
{
  delete [] winnings;
  delete [] numbers_count;
}

int Lottery::get_number_of_winnings() const
{
  return number_of_winnings;
}

int Lottery::get_years_to_play() const
{
  double years = static_cast<double>(number_of_winnings) / 52.0;
  return static_cast<int>(years);
}

int Lottery::get_rest_months_to_play() const
{
  int years = get_years_to_play();
  int rest_weeks = number_of_winnings - (years * 52);
  return rest_weeks / 4.3;
}

Lottery& Lottery::operator=(const Lottery& a_lottery)
{
  if (this != &a_lottery)
  {
    delete [] winnings;
    delete [] numbers_count;
    number_of_winnings = a_lottery.number_of_winnings;
    init_winnings(a_lottery.winnings);
    init_numbers_count(a_lottery.numbers_count);
  }
  return *this;
}

void Lottery::init_winnings()
{
  numbers_count = new int[49];
  winnings = new LotteryWin[number_of_winnings];
  for (int i = 0; i < number_of_winnings; i++)
  {
    winnings[i] = LotteryWin();
    for (int j = 0; j < 6; j++)
      numbers_count[winnings[i][j] - 1]++;
  }
}

void Lottery::init_winnings(const LotteryWin *the_winnings)
{
  winnings = new LotteryWin[number_of_winnings];
  for (int i = 0; i < number_of_winnings; i++)
    winnings[i] = the_winnings[i];
}


void Lottery::init_numbers_count(const int *the_numbers_count)
{
  numbers_count = new int[49];
  for (int i = 0; i < 49; i++)
    numbers_count[i] = the_numbers_count[i];
}

