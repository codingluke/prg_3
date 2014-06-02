#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include "lottery.h"
#include "lottery_win.h"

using namespace std;

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
}

Lottery::~Lottery()
{
  delete [] winnings;
}

int Lottery::get_number_of_winnings() const
{
  return number_of_winnings;
}

string Lottery::str_years_to_play() const
{
  ostringstream modifier(ios::out);
  modifier << "Um " << number_of_winnings << " Ziehungen zu spielen, " << endl
           << "wobei jede Woche eine Ziehung stattfindet, " << endl
           << "braeuchte man " << years_to_play() << " Jahre und "
           << rest_months_to_play() << " Monate" << endl << endl;
  return modifier.str();
}

string Lottery::str_frequency_scale() const
{
  ostringstream modifier(ios::out);
  modifier << "Haeufigkeitsvereilung" << endl << endl;
  unsigned int *statistics = new unsigned int[49];
  clear_int_array(statistics, 49);
  for (int i = 0; i < number_of_winnings; i++)
    for (int j = 0; j < 6; j++)
      statistics[winnings[i][j] - 1]++;

  int max_number = get_max_index(statistics) + 1;
  int max_count = statistics[get_max_index(statistics)];
  int min_number = get_min_index(statistics) + 1;
  int min_count = statistics[get_min_index(statistics)];
  modifier << "Maximum" << " (" << max_count << ") : " << max_number << endl;
  modifier << "Minimum" << " (" << min_count << ") : " << min_number << endl;
  int diff = statistics[get_max_index(statistics)] - statistics[get_min_index(statistics)];

  modifier << "Differenz: " << diff << endl;
  for (int i = 0; i < 49; i++)
    modifier << (i + 1) << ": " << setw(10) << left << statistics[i] << endl;
  delete [] statistics;
  return modifier.str();
}

string Lottery::str_minimum() const
{
  ostringstream modifier(ios::out);
  modifier << "Minimum verteilung" << endl << endl;
  modifier << statistic_table(&LotteryWin::minimum, 0, 49);
  return modifier.str();
}

string Lottery::str_maximum() const
{
  ostringstream modifier(ios::out);
  modifier << "Maximum verteilung" << endl << endl;
  modifier << statistic_table(&LotteryWin::maximum, 0, 49);
  return modifier.str();
}

string Lottery::str_length() const
{
  ostringstream modifier(ios::out);
  modifier << "Laenge verteilung" << endl << endl;
  modifier << statistic_table(&LotteryWin::length, 4, 48);
  return modifier.str();
}

string Lottery::str_count_length_in_win() const
{
  string txt = "Anz. welche die Laenge als Zahl beinhalten:";
  return statistic_number(txt, &LotteryWin::has_length_in_win);
}

string Lottery::str_count_odd() const
{
  string txt = "Anzahl ungerade Ziehungen:";
  return statistic_number(txt, &LotteryWin::is_odd);
}

string Lottery::str_count_even() const
{
  string txt = "Anzahl gerade Ziehungen:";
  return statistic_number(txt, &LotteryWin::is_even);
}

string Lottery::str_count_prim() const
{
  string txt = "Anzahl Primziehungen:";
  return statistic_number(txt, &LotteryWin::is_prim);
}

string Lottery::str_count_not_prim() const
{
  string txt = "Anzahl Noichtprimziehungen:";
  return statistic_number(txt, &LotteryWin::is_not_prim);
}

string Lottery::str_count_street_types() const
{
  ostringstream modifier(ios::out);
  modifier << "K-ling verteilung:" << endl << endl;
  modifier << statistic_table(&LotteryWin::street_type, 0, 6);
  return modifier.str();
}

string Lottery::tip() const
{
  ostringstream modifier(ios::out);
  unsigned int *statistics = new unsigned int[7];
  clear_int_array(statistics, 7);
  LotteryWin tip;
  cin >> tip;
  cout << "calculating..." << endl;
  for (int i = 0; i < number_of_winnings; i++)
    statistics[winnings[i] == tip]++;
  for (int i = 0; i < 7; i++)
    modifier << i << ": " << setw(10) << left << statistics[i]
             << percentage_of_all(statistics[i]) << "%" << endl;
  delete [] statistics;
  return modifier.str();
}

string Lottery::autotip() const
{
  ostringstream modifier(ios::out);
  unsigned int *statistics = new unsigned int[7];
  clear_int_array(statistics, 7);
  int counter = 1;
  int six = 0;
  LotteryWin tip;
  do
  {
    tip = LotteryWin();
    for (int i = 0; i < number_of_winnings; i++)
      if ((winnings[i] == tip) == 6)
        six = i;
    counter++;
  } while (six < 1);
  modifier << "Der sechser war der Tipp " << counter << ": " << tip << endl
           << "Getroffen wurde die Nummer " << six << ": "
           << winnings[six] << endl;
  delete [] statistics;
  return modifier.str();

}
Lottery& Lottery::operator=(const Lottery& a_lottery)
{
  if (this != &a_lottery)
  {
    delete [] winnings;
    number_of_winnings = a_lottery.number_of_winnings;
    init_winnings(a_lottery.winnings);
  }
  return *this;
}

void Lottery::init_winnings()
{
  winnings = new LotteryWin[number_of_winnings];
  for (int i = 0; i < number_of_winnings; i++)
    winnings[i] = LotteryWin();
}

void Lottery::init_winnings(const LotteryWin *the_winnings)
{
  winnings = new LotteryWin[number_of_winnings];
  for (int i = 0; i < number_of_winnings; i++)
    winnings[i] = the_winnings[i];
}

void Lottery::clear_int_array(unsigned int *array, int length) const
{
  for (int i = 0; i < length; i++)
    array[i] = 0;
}

string Lottery::statistic_table(StatFunction fnc, int from, int to) const
{
  ostringstream modifier(ios::out);
  unsigned int *statistics = new unsigned int[50];
  clear_int_array(statistics, 49);
  for (int i = 0; i < number_of_winnings; i++)
    statistics[(winnings[i].*fnc)() - 1]++;
  for (int i = from; i < to; i++)
    modifier << (i + 1) << ": " << setw(10) << left << statistics[i]
             << percentage_of_all(statistics[i]) << " %" << endl;
  delete [] statistics;
  return modifier.str();
}

int Lottery::statistic_number(StatBoolFnc fnc) const
{
  int count = 0;
  for (int i = 0; i < number_of_winnings; i++)
    if ((winnings[i].*fnc)())
      count++;
  return count;
}

string Lottery::statistic_number(const string& text, StatBoolFnc fnc) const
{
  ostringstream modifier(ios::out);
  int count = statistic_number(fnc);
  modifier << text << endl
           << "Absolut: " << count << endl
           << "Prozentual: " << percentage_of_all(count) << " %" << endl;
  return modifier.str();
}

int Lottery::get_max_index(unsigned int *statistics) const
{
  int maximum = 0;
  for (int i = 0; i < 49; i++)
    if (statistics[maximum] < statistics[i])
      maximum = i;
  return maximum;
}

int Lottery::get_min_index(unsigned int *statistics) const
{
  int minimum = 0;
  for (int i = 0; i < 49; i++)
    if (statistics[minimum] > statistics[i])
      minimum = i;
  return minimum;
}

int Lottery::years_to_play() const
{
  double years = static_cast<double>(number_of_winnings) / 52.0;
  return static_cast<int>(years);
}

int Lottery::rest_months_to_play() const
{
  int years = years_to_play();
  int rest_weeks = number_of_winnings - (years * 52);
  return rest_weeks / 4.3;
}

double Lottery::percentage_of_all(int number) const
{
  return (number / static_cast<double>(number_of_winnings)) * 100;
}

