#include <iostream>
#include <iomanip>
#include <string.h>
#include <cstdlib>
#include <vector>
#include "fraction.h"
#include "main.h"


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
  if (argc == 5)
  {
    bool num_first_int = atoi(argv[1]) && atoi(argv[3]) && atoi(argv[4]);
    bool frc_first_int = atoi(argv[1]) && atoi(argv[2]) && atoi(argv[4]);
    if (num_first_int && !atoi(argv[2]))
    {
      Fraction f(atoi(argv[3]), atoi(argv[4]));
      calculate(atoi(argv[1]), f, argv[2]);
    }
    else if (frc_first_int && !atoi(argv[3]))
    {
      Fraction f(atoi(argv[1]), atoi(argv[2]));
      calculate(f, atoi(argv[1]), argv[3]);
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
        compare(f1, f2);
      else
        calculate(f1, f2, op);
    }
  }
  else if (argc == 9)
  {
    bool check_int = atoi(argv[1]) && atoi(argv[3]) && atoi(argv[4]) &&
                     atoi(argv[5]) && atoi(argv[6]);
    bool check_brackets = strcmp(argv[2], "[") == 0 &&
                          strcmp(argv[7], "]") == 0;
    bool check_operator = strcmp(argv[8], "-") == 0 ||
                          strcmp(argv[8], "+") == 0;
    if (check_int && check_brackets && check_operator)
    {
      std::vector<Fraction> fractions = random_fractions(atoi(argv[1]),
                                                         atoi(argv[3]),
                                                         atoi(argv[4]),
                                                         atoi(argv[5]),
                                                         atoi(argv[6]));
    }
  }
}

std::vector<Fraction> random_fractions(int amounth, int low_numerator,
                                       int low_denominator, int high_numerator,
                                       int high_denominator)
{
  srand(time(0));
  std::vector<Fraction> fractions (amounth);
  for (int i = 0; i < amounth; i++)
    fractions[i] = Fraction(low_numerator, low_denominator,
                            high_numerator, high_denominator, rand());
  return fractions;
}

void calculate(Fraction f1, Fraction f2, std::string op)
{
  Fraction result;
  if (op == "+")
    result = f1 + f2;
  else if (op == "-")
    result = f1 - f2;
  else if (op == "*")
    result = f1 * f2;
  else if (op == "/")
    result = f1 / f2;
  std::cout << f1 << " " << op << " " << f2
            << " = " << result.str_normed();
}

void compare(Fraction f1, Fraction f2)
{
  std::string op = "<";
  if (f1 == f2)
    op = "=";
  else if (f1 > f2)
    op = ">";
  std::cout << f1 << " " << op << " " << f2;
}

void calculate(int number, Fraction f, std::string op)
{
  Fraction result;
  if (op == "+")
    result = number + f;
  else if (op == "-")
    result = number - f;
  else if (op == "*")
    result = number * f;
  else if (op == "/")
    result = number / f;
  else
    throw "Fehler!";
  std::cout << number << " " << op << " " << f << " = "
            << result.str_normed();
}

void calculate(Fraction f, int number, std::string op)
{
  Fraction result;
  if (op == "+")
    result = f + number;
  else if (op == "-")
    result = f - number;
  else if (op == "*")
    result = f * number;
  else if (op == "/")
    result = f / number;
  else
    throw "Fehler!";
  std::cout << f << " " << op << " " << number << " = "
            << result.str_normed();
}

void sort(Fraction array[], int length)
{
  int index_max = 0;
  Fraction store;
  for (int i = length - 1; i < 0; i--)
  {
    index_max = 0;
    for (int j = 0; j <= i; j++)
      if (array[j] < array[index_max])
        index_max = j;
    if (array[index_max] > array[i])
    {
      store = array[i];
      array[i] = array[index_max];
      array[index_max] = store;
    }
  }
}

