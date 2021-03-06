#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include "lottery.h"
#include "lottery_win.h"

using namespace std;

/**
 * Defaultconstructor. Initializes one LotteryWin.
 */
Lottery::Lottery()
{
  number_of_winnings = 1;
  init_winnings();
}

/**
 * Initializes a given number of winnings.
 *
 * @param a_number_of_winnings  Number how many winning to produce.
 */
Lottery::Lottery(int a_number_of_winnings)
{
  number_of_winnings = a_number_of_winnings;
  init_winnings();
}

/**
 * Copy constructor.
 *
 * @param original The Lottery to copy.
 */
Lottery::Lottery(const Lottery& original)
{
  number_of_winnings = original.number_of_winnings;
  init_winnings(original.winnings);
}

/**
 * Destructor. Cleans up heap.
 */
Lottery::~Lottery()
{
  delete [] winnings;
}

/**
 * Returns the number of initialized winnings.
 *
 * @return number of initialized winnings.
 */
int Lottery::get_number_of_winnings() const
{
  return number_of_winnings;
}

/**
 * Returns a string with the Information about how many years
 * and months it would last, to play all the numbers
 * of winnings, when there would be one lottery win a week.
 *
 * @return String which displays information.
 */
string Lottery::str_years_to_play() const
{
  ostringstream modifier(ios::out);
  modifier << "Um " << number_of_winnings << " Ziehungen zu spielen, " << endl
           << "wobei jede Woche eine Ziehung stattfindet, " << endl
           << "braeuchte man " << years_to_play() << " Jahre und "
           << rest_months_to_play() << " Monate" << endl << endl;
  return modifier.str();
}

/**
 * Returns a table with the information about the frequency scale of all
 * the numbers included in all the initialized winnings. It also shows
 * the most and least common number and the difference of their counts.
 *
 * Haufigkeitsverteilung
 * Maximum ( <anzahl> ) : max_nummer \n
 * Minimum ( <anzahl> ) : min_nummer \n
 * \n
 * 1 : 23532 \n
 * 2 : 3453 \n
 * . \n
 * . \n
 * 49: 45345 \n
 *
 *
 * @return string
 */
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

/**
 * Returns a table with the fequency of the minimum numbers in the
 * winnings. A minimum number is the smallest number in a LotteryWin.
 * \n
 * Minimum verteilung \n
 * 1: 122       12.2 %\n
 * 2: 119       11.9 %\n
 * 3: 90        9 %\n
 * . \n
 * . \n
 * 49: 0        0 % \n
 *
 * @return table with th frequency of the minimum numbers.
 */
string Lottery::str_minimum() const
{
  ostringstream modifier(ios::out);
  modifier << "Minimum verteilung" << endl << endl;
  modifier << statistic_table(&LotteryWin::minimum, 0, 49);
  return modifier.str();
}

/**
 * Returns a table with the fequency of the maximum numbers in the
 * winnings. A maximum number is the biggest number in a LotteryWin.
 * \n
 * Maximum verteilung\n
 * 1: 0         0 %\n
 * ..\n
 * ..\n
 * 48: 110       11 %\n
 * 49: 120       12 %\n
 *
 * @return a table with the frequency of the maximum numbers.
 */
string Lottery::str_maximum() const
{
  ostringstream modifier(ios::out);
  modifier << "Maximum verteilung" << endl << endl;
  modifier << statistic_table(&LotteryWin::maximum, 0, 49);
  return modifier.str();
}

/**
 * Returns a table with the fequency of the lengths of the winnings.
 * The lengts of a LotteryWin is the difference between the maximum
 * number and the minimum number of a LotteryWin.
 * \n
 * Laenge verteilung\n
 * 5: 0         0 %\n
 * ..\n
 * 21: 10        1 % \n
 * ..\n
 * 39: 57        5.7 %\n
 * 48: 13        1.3 %\n
 * .\n
 *
 * @return a table with the frequency of the winnings lengths.
 */
string Lottery::str_length() const
{
  ostringstream modifier(ios::out);
  modifier << "Laenge verteilung" << endl << endl;
  modifier << statistic_table(&LotteryWin::length, 4, 48);
  return modifier.str();
}

/**
 * Returns how many times the length of a LotteryWin is also
 * a number of the lottery win, absolut and in percent.
 *
 * Anzahl Ziehungen, die ihre Laenge enthalten
 * Absolut: 879\n
 * Prozentual: 87.9 %\n
 *
 * @return Number of winnings which has their lengts also as number.
 */
string Lottery::str_count_length_in_win() const
{
  string txt = "Anz. welche die Laenge als Zahl beinhalten:";
  return statistic_number(txt, &LotteryWin::has_length_in_win);
}

/**
 * Returns the number of odd winnings absolut and in percent.
 * A LotteryWin is odd when all the numbers are odd.
 *
 * Anzahl ungerade Ziehungen
 * Absolut: <anzahl>\n
 * Prozentual: <prozent>\n
 *
 * @return Number of odd winnings.
 */
string Lottery::str_count_odd() const
{
  string txt = "Anzahl ungerade Ziehungen:";
  return statistic_number(txt, &LotteryWin::is_odd);
}

/**
 * Returns the number of even winnings absolut and in percent.
 * A LotteryWin is even when all the numbers are even.
 *
 * Anzahl gerade Ziehungen
 * Absolut: <anzahl>\n
 * Prozentual: <prozent>\n
 *
 * @return Number of even winnings.
 */
string Lottery::str_count_even() const
{
  string txt = "Anzahl gerade Ziehungen:";
  return statistic_number(txt, &LotteryWin::is_even);
}

/**
 * Returns the number of prim winnings absolut and in percent.
 * A LotteryWin is a prim win, when all the numbers are primnumbers.
 *
 * Anzahl Primziehungen
 * Absolut: <anzahl>\n
 * Prozentual: <prozent>\n
 *
 * @return Number of prim winnings.
 */
string Lottery::str_count_prim() const
{
  string txt = "Anzahl Primziehungen:";
  return statistic_number(txt, &LotteryWin::is_prim);
}

/**
 * Returns the number of not-prim-winnings absolut and in percent.
 * A LotteryWin is a not-prim-win, when non of the numbers is a primnumber.
 *
 * Anzahl Nichtprimziehungen
 * Absolut: <anzahl>\n
 * Prozentual: <prozent>\n
 *
 * @return Number of not-prim-winnings.
 */
string Lottery::str_count_not_prim() const
{
  string txt = "Anzahl Noichtprimziehungen:";
  return statistic_number(txt, &LotteryWin::is_not_prim);
}

/**
 * Returns the number of k-street-winnings absolut and in percent.
 * The k is definded with the numbers which !!!
 *
 * K-ling verteilung:\n
 * 1: 928       92.8 %\n
 * 2: 71        7.1 %\n
 * 3: 1         0.1 %\n
 * 4: 0         0 %\n
 * 5: 0         0 %\n
 * 6: 0         0 %\n
 *
 * @return Number of not-prim-winnings.
 */
string Lottery::str_count_street_types() const
{
  ostringstream modifier(ios::out);
  modifier << "K-ling verteilung:" << endl << endl;
  modifier << statistic_table(&LotteryWin::street_type, 0, 6);
  return modifier.str();
}

/**
 * Promts the user to enter a tip. After this it compairs the tip
 * with the existing winnings. It will then show how many times
 * you would have won with the hits between 0 and 6. It also shows
 * the percentage of all winnings.
 *
 * @return string with the statistic of hits by the entered tip.
 */
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

/**
 * It will generate a random tip and compairs this hit with all the
 * winnings. It will then show how many times the tip would have won
 * with hits between 0 and 6. It also shows the percentage of all winnings.
 *
 * @return string with the statistic of hits by the random tip.
 */
string Lottery::autotip() const
{
  ostringstream modifier(ios::out);
  int counter = 1;
  int six = -1;
  LotteryWin tip;
  do
  {
    tip = LotteryWin();
    for (int i = 0; i < number_of_winnings; i++)
      if ((winnings[i] == tip) == 6)
        six = i;
    counter++;
  } while (six < 0);
  modifier << "Der Sechser war der Tipp " << counter << ": " << tip << endl
           << "Getroffen wurde die Nummer " << six << ": "
           << winnings[six] << endl;
  return modifier.str();
}

/**
 * Overloading of the assignment operator=. Defines how to deep copy a
 * Lottery instance.
 *
 * @param other   The Lottery instance to copy into the object.
 *
 * @return the adress of itself.
 */
Lottery& Lottery::operator=(const Lottery& other)
{
  if (this != &other)
  {
    delete [] winnings;
    number_of_winnings = other.number_of_winnings;
    init_winnings(other.winnings);
  }
  return *this;
}

/**
 * Generates as many LotteryWin instances as defined.
 */
void Lottery::init_winnings()
{
  winnings = new LotteryWin[number_of_winnings];
  for (int i = 0; i < number_of_winnings; i++)
    winnings[i] = LotteryWin();
}

/**
 * Overrides the actual LotteryWin instances with given
 * new LotteryWins.
 *
 * @param the_winnings  The winnings to overtake.
 */
void Lottery::init_winnings(const LotteryWin *the_winnings)
{
  winnings = new LotteryWin[number_of_winnings];
  for (int i = 0; i < number_of_winnings; i++)
    winnings[i] = the_winnings[i];
}

/**
 * Fills a given array with 0. Useful to really empty an array.
 *
 * @param array   The array to fill with zeros.
 * @param length  The length of the array.
 */
void Lottery::clear_int_array(unsigned int *array, int length) const
{
  for (int i = 0; i < length; i++)
    array[i] = 0;
}

/**
 * Generates a formatted table for statistics of the Numbers between 0 to 49
 * by a given statistic function.
 *
 * As an example:
 *
 * Minimum verteilung
 * 1: 610871  12.2174 %
 * 2: 548581  10.9716 %
 * ..
 * 49: 0      0 %
 *
 * @param fnc     Pointer to the calculation function.
 * @param from    Startpoint has to be between 0 and 49.
 * @param to      Endpoint has to be between 0 and 49.
 *
 * @return a well formatted table of the given statistic functions.
 */
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

/**
 * Gives back the number of winnings which archive a given condition by
 * a given function.
 *
 * @param fnc Function for the condition.
 *
 * @return number of winnings which archive the given condition.
 */
int Lottery::statistic_number(StatBoolFnc fnc) const
{
  int count = 0;
  for (int i = 0; i < number_of_winnings; i++)
    if ((winnings[i].*fnc)())
      count++;
  return count;
}

/**
 * Calculates the number of winnings which archive a given condition
 * by a given function, also calculates the percentage of all winnings
 * and gives it back in a well formatted string. The number can be descibed
 * by a given text.
 *
 * @param text    Text to describe the numbers.
 * @param fnc     Function which defines the condition.
 *
 * @return well formatted string with the numbers of winnings and percentages
 *         of all, which archives a given condition.
 */
string Lottery::statistic_number(const string& text, StatBoolFnc fnc) const
{
  ostringstream modifier(ios::out);
  int count = statistic_number(fnc);
  modifier << text << endl
           << "Absolut: " << count << endl
           << "Prozentual: " << percentage_of_all(count) << " %" << endl;
  return modifier.str();
}

/**
 * Gives back the index of the biggest element in a array.
 *
 * @param statistics  Array of the elements.
 *
 * @return index of the max-value in the given array.
 */
int Lottery::get_max_index(unsigned int *statistics) const
{
  int maximum = 0;
  for (int i = 0; i < 49; i++)
    if (statistics[maximum] < statistics[i])
      maximum = i;
  return maximum;
}

/**
 * Gives back the index of the smallest element in a array.
 *
 * @param statistics  Array of the elements.
 *
 * @return index of the min-value in the given array.
 */
int Lottery::get_min_index(unsigned int *statistics) const
{
  int minimum = 0;
  for (int i = 0; i < 49; i++)
    if (statistics[minimum] > statistics[i])
      minimum = i;
  return minimum;
}

/**
 * Calculates how many years needed to play a certain amouth of LotteryWins
 * under the condition that a year has 52 weeks.
 *
 * @return years to play a certain amouth of LotteryWins.
 */
int Lottery::years_to_play() const
{
  double years = static_cast<double>(number_of_winnings) / 52.0;
  return static_cast<int>(years);
}

/**
 * Calculates the rest months in the last year needed to play a certain
 * amouth of LotteryWins under the condition that a year has 52 weeks and
 * a month has 4.3 Weeks. (52 / 12)
 *
 * @return month of the last year to play.
 */
int Lottery::rest_months_to_play() const
{
  int years = years_to_play();
  int rest_weeks = number_of_winnings - (years * 52);
  return rest_weeks / 4.3;
}

/**
 * Calculates the percentage of a number with the actual number of winnings.
 *
 * @param number    Number to take percentage of.
 *
 * @return the percentage of the number by the number of winnings.
 */
double Lottery::percentage_of_all(int number) const
{
  return (number / static_cast<double>(number_of_winnings)) * 100;
}
