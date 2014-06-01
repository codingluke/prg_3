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
    LotteryWin(const LotteryWin& original); // copy constructor

    ~LotteryWin();

    string str() const;

    LotteryWin& operator=(const LotteryWin& a_lottery_win);
    int operator[](const int& key);

  private:
    void seed_rand();
    void generate_win();
};

ostream& operator<<(ostream& output, const LotteryWin& a_lottery_win);

#endif
