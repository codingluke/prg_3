#ifndef MAIN_H
#define MAIN_H

#include "fraction.h"
#include <string>
#include <vector>

void actionHandling(int argc, char *argv[]);
void sort(Fraction array[], int length);
void calculate(Fraction f1, Fraction f2, std::string op);
void calculate(int number, Fraction f, std::string op);
void calculate(Fraction f, int number, std::string op);
void compare(Fraction f1, Fraction f2);
std::vector<Fraction> random_fractions(int amounth, int low_numerator,
                                       int low_denominator, int high_numerator,
                                       int high_denominator);

#endif
