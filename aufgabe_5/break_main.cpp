#include <iostream>
#include <iomanip>
#include "fraction.h"

/**
 * Entrypoint to the program 'tabelle'. Tabelle is a program to generate
 * value-tables for the mathematical functions
 * cos, sin, tan, acos, asin, atan, exp, log, log10, sqrt and pow.
 *
 * @param argc        Length of the arguments array.
 * @param *argv[]     Arguments array form the program execution.
 */
//int main(int argc, char *argv[])
int main() {
  Fraction f(2, 2);
  Fraction f2(2, 2);
  std::cout << (f == f2);

  //Fraction f3 = f + f2;
  //Fraction f4 = f - f2;
  //Fraction f5 = f * f2;
  //Fraction f6 = f / f2;
  //Fraction f7 = 3 + f;
  //Fraction f8 = 3 - f;
  //Fraction f9 = 3 * f;
  //Fraction f10 = 3 / f;

  //std::cout << f3.str() << std::endl;
  //std::cout << f4.str() << std::endl;
  //std::cout << f5.str() << std::endl;
  //std::cout << f6.str() << std::endl;
  //std::cout << f7.str() << std::endl;
  //std::cout << f8.str() << std::endl;
  //std::cout << f9.str() << std::endl;
  //std::cout << f10.str() << std::endl;
}

