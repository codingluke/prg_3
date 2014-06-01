#include "lottery.h"
#include <iostream>
#include <iomanip>

/**
 * Entrypoint to the program "Fahrkartenautomat".
 * Creates and starts an Instance of TicketMachine with
 * Euro as currency and a list of accepted coins for
 * the paiment.
 */
int main()
{
  Lottery totto(10000000);
  //cout << totto.get_years_to_play() << endl;
  //cout << totto.get_rest_months_to_play();
  //cout << totto.get_number_of_winnings();

  LotteryWin win;
  cout << win;
  cout << win[3];
}
