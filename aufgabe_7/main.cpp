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

  //LotteryWin test;
  //LotteryWin test2;
  //cout << test << endl << test2 << endl << (test == test2);



  //char prim_numbers[] = { 2, 7, 11, 13, 17, 19 };
  //LotteryWin test(prim_numbers);
  //cout << test;
  //if (test.is_prim())
    //cout << "is prime!" << endl;

  //char no_prim_numbers[] = { 4, 6, 8, 10, 12, 14, 16 };
  //LotteryWin test(no_prim_numbers);
  //cout << test;
  //if (test.is_not_prim())
    //cout << "is prime!" << endl;

  //char odd_numbers[] = { 1, 3, 5, 7, 9, 11 };
  //test = LotteryWin(odd_numbers);
  //cout << test;
  //if (test.is_odd())
    //cout << "is odd!" << endl;

  //char even_numbers[] = { 1, 4, 6, 8, 10, 12 };
  //test = LotteryWin(even_numbers);
  //cout << test;
  //if (test.is_even())
    //cout << "is even!" << endl;
    //

  //char street_one[] = { 1, 9, 4, 5, 10, 7 };
  //LotteryWin test(street_one);
  //cout << test << "street: " << test.street_type() << endl;

  Lottery toto(1000000);
  cout << toto.str_years_to_play() << endl;
  //cout << toto.tip();

  //cout << "Ziehen..." << endl;
  //toto = Lottery(20000000);
  //cout << toto.autotip() << endl;

  //cout << "Ziehen..." << endl;
  //toto = Lottery(30000000);
  //cout << toto.autotip() << endl;

  //Lottery kukuk = toto;
  //toto = Lottery(1000);

  //cout << toto.str_frequency_scale() << endl;
  //cout << toto.str_minimum() << endl;
  //cout << toto.str_maximum() << endl;
  //cout << toto.str_length() << endl;
  //cout << toto.str_count_length_in_win();
  //cout << toto.str_count_odd();
  //cout << toto.str_count_even();
  //cout << toto.str_count_prim();
  //cout << toto.str_count_not_prim();
  //cout << kukuk.str_count_street_types();
  //cout << toto.str_count_street_types();

  //cout << toto.get_max_number() << endl;
  //cout << toto.get_min_number() << endl;
  //cout << totto.get_10000000est_months_to_play();
  //cout << totto.get_number_of_winnings();

  //LotteryWin win;
  //cout << win;
  //cout << win[3];
}
