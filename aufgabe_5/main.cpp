#include <iostream>
#include <iomanip>
#include <string.h>
#include <cstdlib>
#include <vector>
#include "fraction.h"
#include "main.h"
#include "calculator.h"

/**
 * Entrypoint to the program "tabelle". Tabelle is a program to generate
 * value-tables for the mathematical functions
 * cos, sin, tan, acos, asin, atan, exp, log, log10, sqrt and pow.
 *
 * @param argc        Length of the arguments array.
 * @param *argv[]     Arguments array form the program execution.
 */
int main(int argc, char *argv[])
{
  try
  {
    actionHandling(argc, argv);
  }
  catch(const char* msg)
  {
    std::cout << msg;
  }
}

void actionHandling(int argc, char *argv[])
{
  Calculator calc;
  if (argc == 5)
  {
    bool num_first_int = atoi(argv[1]) && atoi(argv[3]) && atoi(argv[4]);
    bool frc_first_int = atoi(argv[1]) && atoi(argv[2]) && atoi(argv[4]);
    if (num_first_int && !atoi(argv[2]))
    {
      Fraction f(atoi(argv[3]), atoi(argv[4]));
      calc.calculate(atoi(argv[1]), f, argv[2]);
    }
    else if (frc_first_int && !atoi(argv[3]))
    {
      Fraction f(atoi(argv[1]), atoi(argv[2]));
      calc.calculate(f, atoi(argv[1]), argv[3]);
    }
  }
  else if (argc == 6)
  {
    bool check_int = atoi(argv[1]) && atoi(argv[2]) &&
                     atoi(argv[4]) && atoi(argv[5]);
    if (check_int && !atoi(argv[3]))
    {
      Fraction f1(atoi(argv[1]), atoi(argv[2]));
      Fraction f2(atoi(argv[4]), atoi(argv[5]));
      std::string op = argv[3];
      if (op == "-v")
        calc.compare(f1, f2);
      else
        calc.calculate(f1, f2, op);
    }
  }
  else if (argc == 9)
  {
    bool check_int = atoi(argv[1]) && atoi(argv[3]) && atoi(argv[4]) &&
                     atoi(argv[5]) && atoi(argv[6]);
    bool check_operator = strcmp(argv[8], "-") == 0 ||
                          strcmp(argv[8], "+") == 0;
    if (check_int && check_operator)
    {
      bool asc = strcmp(argv[8], "+") == 0;
      random_handler(atoi(argv[1]), atoi(argv[3]),
                     atoi(argv[4]), atoi(argv[5]),
                     atoi(argv[6]), asc);
    }
  }
}

void random_handler(int n, int a, int b, int c, int d, bool asc)
{
  std::vector<Fraction> fractions = random_fractions(n, a, b, c, d);
  std::cout << "Unsoriert" << std::endl;
  for (int i = 0; i < n; i++)
    std::cout << fractions[i] << std::endl;
  std::cout << "Soriert" << std::endl;
  sort(fractions, n, asc);
  for (int i = 0; i < n; i++)
    std::cout << fractions[i] << std::endl;
}

std::vector<Fraction> random_fractions(int n, int low_numerator,
                                       int low_denominator, int high_numerator,
                                       int high_denominator)
{
  srand(time(0));
  std::vector<Fraction> fractions (n);
  for (int i = 0; i < n; i++)
    fractions[i] = Fraction(low_numerator, low_denominator,
                            high_numerator, high_denominator, rand());
  return fractions;
}

void sort(std::vector<Fraction> &array, int length, bool asc)
{
  int index_max = 0;
  Fraction ablage;
  for (int i = length - 1; i > 0; i--)
  {
    index_max = 0;
    for (int j = 0; j <= i; j++)
    {
      if ((asc && array[j] > array[index_max]) ||
          (!asc && array[j] < array[index_max]))
        index_max = j;
    }
    if ((asc && array[index_max] > array[i]) ||
        (!asc && array[index_max] < array[i]))
    {
      ablage = array[i];
      array[i] = array[index_max];
      array[index_max] = ablage;
    }
  }
}