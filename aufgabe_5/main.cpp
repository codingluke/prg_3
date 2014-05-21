#include <iostream>
#include <iomanip>
#include <string.h>
#include <sstream>
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
  if (argc == 5)
    handle_five(argv);
  else if (argc == 6)
    handle_six(argv);
  else if (argc == 9)
    handle_nine(argv);
}

void handle_five(char *argv[])
{
  Calculator calc;
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
    calc.calculate(f, atoi(argv[1]), argv[3]);
  }
}

void handle_six(char *argv[])
{
  Calculator calc;
  bool check_int = isi(argv[1]) && isi(argv[2]) &&
                   isi(argv[4]) && isi(argv[5]);
  if (check_int && !isi(argv[3]))
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

void handle_nine(char *argv[])
{
  bool check_int = isi(argv[1]) && isi(argv[3]) && isi(argv[4]) &&
                   isi(argv[5]) && isi(argv[6]);
  bool check_operator = strcmp(argv[8], "-") == 0 ||
                        strcmp(argv[8], "+") == 0;
  bool check_range = 0 < atoi(argv[1]) && atoi(argv[1]) < 10001;
  if (check_int && check_operator && check_range)
  {
    bool asc = strcmp(argv[8], "+") == 0;
    random_handler(atoi(argv[1]), atoi(argv[3]),
                   atoi(argv[4]), atoi(argv[5]),
                   atoi(argv[6]), asc);
  }
}

bool isi(char text[])
{
  int i;
  std::istringstream in(text);
  return in >> i && in.eof();
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
