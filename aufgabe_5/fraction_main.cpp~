#include <iostream>
#include <iomanip>
#include <string.h>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <stdexcept>
#include "fraction_main.h"
#include "fraction.h"
#include "calculator.h"

/**
 * Entrypoint to the program "Bruch". Bruch lets you calculate and
 * compare Fractions directly in the console.
 * There is also the possibility to generate random Fraction in a
 * certain range. It prompts the user while inserting wrong Fractions
 * where the denominator is zero.
 *
 * Possible calculation execution forms (op = +,-,*,/):
 * bruch a b op c d         a/b op c/d = e/f
 * => bruch 1 2 - 1 3       1/2 - 1/3 = 1/6
 * bruch a op c d           a op c/d = e/f
 * => bruch 1 - 1 2         1 - 1/2 = 1/2
 * bruch a b op c           a/b op c = e/f
 * => bruch 1 2 - 1         1/2 - 1 = -1/2
 *
 * Possible compare executions:
 * bruch a b -v c d         a/b [<|>|=] c/d
 * => 1 2 -v 1 3            1/2 > 1/3
 *
 * Possible random number generator
 * bruch n [ a b c d ] +    n numbers between a/b and c/d ascendent sorted.
 * bruch n [ a b c d ] -    n numbers between a/b and c/d descendent sorted.
 *
 * @param argc        Length of the arguments array.
 * @param *argv[]     Arguments array form the program execution.
 */
int main(int argc, char *argv[])
{
  if (argc == 5)
    handle_five(argv);
  else if (argc == 6)
    handle_six(argv);
  else if (argc == 9)
    handle_nine(argv);
  else
    show_manual();
}

/**
 * Handles program when executed with five arguments. Validates
 * input format.
 *
 * Possible actions are:
 * bruch a op c d       a op c/d = e/f
 * => bruch 1 - 1 2     1 - 1/2 = 1/2
 * bruch a b op c       a/b op c = e/f
 * => bruch 1 2 - 1     1/2 - 1 = -1/2
 *
 * @param *argv[]       Arguments array form the program execution.
 */
void handle_five(char *argv[])
{
  try
  {
    Calculator calc = Calculator();
    bool num_first_int = isi(argv[1]) && isi(argv[3]) && isi(argv[4]);
    bool frc_first_int = isi(argv[1]) && isi(argv[2]) && isi(argv[4]);
    if (num_first_int && !isi(argv[2]))
    {
      Fraction f(atoi(argv[3]), atoi(argv[4]));
      calc.calculate(atoi(argv[1]), f, argv[2]);
    }
    else if (frc_first_int && !isi(argv[3]))
    {
      Fraction f(atoi(argv[1]), atoi(argv[2]));
      calc.calculate(f, atoi(argv[4]), argv[3]);
    }
    else
      show_manual();
  }
  catch(const std::invalid_argument& ex)
  {
    std::cout << ex.what() << std::endl;
  }
}

/**
 * Handles program when executed with six arguments. Validates
 * input format.
 *
 * Possible actions are:
 * bruch a b op c d         a/b op c/d = e/f
 * => bruch 1 2 - 1 3       1/2 - 1/3 = 1/6
 * bruch a b -v c d         a/b [<|>|=] c/d
 * => 1 2 -v 1 3            1/2 > 1/3
 *
 * @param *argv[]       Arguments array form the program execution.
 */
void handle_six(char *argv[])
{
  Calculator calc = Calculator();
  bool numerator_ok = isi(argv[1]) && isi(argv[4]);
  bool denumerator_ok = isi(argv[2]) && isi(argv[5]);
  bool operator_ok = !isi(argv[3]);
  if (numerator_ok && denumerator_ok && operator_ok)
  {
    try
    {
      Fraction f1(atoi(argv[1]), atoi(argv[2]));
      Fraction f2(atoi(argv[4]), atoi(argv[5]));
      std::string op = argv[3];
      if (op == "-v")
        calc.compare(f1, f2);
      else
        calc.calculate(f1, f2, op);
    }
    catch(const std::invalid_argument& ex)
    {
      std::cout << ex.what() << std::endl;
    }
  }
  else
    show_manual();
}

/**
 *
 * Handles program when executed with nine arguments. Validates
 * input format.
 *
 * Possible actions are:
 * bruch n [ a b c d ] +    n numbers between a/b and c/d ascendent sorted.
 * bruch n [ a b c d ] -    n numbers between a/b and c/d descendent sorted.
 *
 * @param *argv[]       Arguments array form the program execution.
 */
void handle_nine(char *argv[])
{
  bool denumerator_ok = isi(argv[4]) && isi(argv[6]);
  bool integers_ok = isi(argv[1]) && isi(argv[3]) && isi(argv[4]) &&
                     isi(argv[5]) && isi(argv[6]);
  bool direction_ok = strcmp(argv[8], "-") == 0 ||
                      strcmp(argv[8], "+") == 0;
  bool range_ok = 0 < atoi(argv[1]) && atoi(argv[1]) < 10001;
  if (denumerator_ok && integers_ok && direction_ok && range_ok)
  {
    try
    {
    bool asc = strcmp(argv[8], "+") == 0;
    random_handler(atoi(argv[1]), atoi(argv[3]),
                   atoi(argv[4]), atoi(argv[5]),
                   atoi(argv[6]), asc);
    }
    catch(const std::invalid_argument& ex)
    {
      std::cout << ex.what() << std::endl;
    }
  }
  else
    show_manual();
}

/**
 * Checks whether an array of chars represents an integer or not.
 * Solfs atoi problem that returns a 0 for a char which is not a number.
 *
 * @param text[] Array of chars.
 *
 * @return true when text[] represents a number.
 *         false when text[] doesn't represent a number.
 */
bool isi(char text[])
{
  int i;
  std::istringstream in(text);
  return in >> i && in.eof();
}

/**
 * Generates n random Fractions in between the Fractions a/b and c/d,
 * sorts them eigther ascendent or descendent according the parameter
 * asc and prints the sorted and unsorted result to the console.
 *
 * @param n   Number of random fractions.
 * @param a   Numerator of the low bound fraction.
 * @param b   Denominator of the low bound fraction.
 * @param c   Numerator of the high bound fraction.
 * @param d   Denominator of the high bound fraction.
 * @param asc Deriction to sort, true => asc, false => desc.
 */
void random_handler(int n, int a, int b, int c, int d, bool asc)
{
  try
  {
    std::vector<Fraction> fractions = random_fractions(n, a, b, c, d);
    std::cout << "unsoriert:" << std::endl;
    for (int i = 0; i < n; i++)
      std::cout << fractions[i] << std::endl;
    if (asc)
      std::cout << std::endl << "aufsteigend soriert:" << std::endl;
    else
      std::cout << std::endl << "absteigend soriert:" << std::endl;
    sort(fractions, n, asc);
    for (int i = 0; i < n; i++)
      std::cout << fractions[i] << std::endl;
  }
  catch(const std::invalid_argument& ex)
  {
    throw std::invalid_argument(ex.what());
  }
}

/**
 * Generates n random Fractions with value in between the Fractions a/b and c/d
 * and gives them back in a vector.
 *
 * @param n   		    Number of random fractions.
 * @param low_numerator     Numerator of the low bound fraction.
 * @param low_denominator   Denominator of the low bound fraction.
 * @param high_numerator    Numerator of the high bound fraction.
 * @param high_denominator  Denominator of the high bound fraction.
 *
 * @return vector with the fractions.
 */
std::vector<Fraction> random_fractions(int n, int low_numerator,
                                       int low_denominator, int high_numerator,
                                       int high_denominator) throw(const std::invalid_argument)
{
  srand((unsigned)time(0));
  std::vector<Fraction> fractions (n);
  for (int i = 0; i < n; i++)
    fractions[i] = Fraction(low_numerator, low_denominator,
                            high_numerator, high_denominator, rand());

  return fractions;
}

/**
 * Sorts an vector of fractions with the entry sort algorithm in according
 * to the param asc ascendent or descendent.
 *
 * @param fractions   Vector with the fraction to sort.
 * @param length      Length of the vector.
 * @param asc         Direction to sort. true => asc, false => desc.
 */
void sort(std::vector<Fraction> &fractions, int length, bool asc)
{
  int index_max = 0;
  Fraction ablage;
  for (int i = length - 1; i > 0; i--)
  {
    index_max = 0;
    for (int j = 0; j <= i; j++)
    {
      if ((asc && fractions[j] > fractions[index_max]) ||
          (!asc && fractions[j] < fractions[index_max]))
        index_max = j;
    }
    if ((asc && fractions[index_max] > fractions[i]) ||
        (!asc && fractions[index_max] < fractions[i]))
    {
      ablage = fractions[i];
      fractions[i] = fractions[index_max];
      fractions[index_max] = ablage;
    }
  }
}

/**
 * Reads the file "manual.txt" and prints it`s content to the console.
 */
void show_manual()
{
  std::string line;
  std::string filename = "manual.txt";
  std::ifstream infile(filename.c_str());
  if (!infile)
    std::cout << "File '" << filename << "' existiert nicht!" << std::endl;
  while (getline(infile, line))
    std::cout << line << std::endl;
}
