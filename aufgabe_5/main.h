#ifndef MAIN_H
#define MAIN_H

#include "fraction.h"
#include <string>
#include <vector>


typedef Fraction (Fraction::*fptr)(const Fraction&) const;
typedef Fraction (Fraction::*fptr2)(const int&) const;
typedef Fraction (*fptr3)(const int&, const Fraction&);

void actionHandling(int argc, char *argv[]);
void sort(std::vector<Fraction> &array, int length, bool asc);
void calculate(Fraction f1, Fraction f2, std::string op);
void calculate(int number, Fraction f, std::string op);
void calculate(Fraction f, int number, std::string op);
void compare(Fraction f1, Fraction f2);
std::vector<Fraction> random_fractions(int amounth, int low_numerator,
                                       int low_denominator, int high_numerator,
                                       int high_denominator);
void random_handler(int n, int a, int b, int c, int d, bool asc);

#endif
