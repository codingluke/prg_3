#include "lottery_win.h"
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
  LotteryWin hallo;
  cout << hallo.str();
  LotteryWin kukuk;
  cout << kukuk.str();
  kukuk = hallo;
  cout << kukuk.str();
  cout << hallo.str();

}
