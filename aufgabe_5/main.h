#ifndef MAIN_H
#define MAIN_H

#include "fraction.h"
#include <string>
#include <vector>


typedef Fraction (Fraction::*fptr)(const Fraction&) const;
typedef Fraction (Fraction::*fptr2)(const int&) const;
typedef Fraction (*fptr3)(const int&, const Fraction&);

void handle_five(char *argv[]);
void handle_six(char *argv[]);
void handle_nine(char *argv[]);
void sort(std::vector<Fraction> &array, int length, bool asc);
std::vector<Fraction> random_fractions(int amounth, int low_numerator,
                                       int low_denominator, int high_numerator,
                                       int high_denominator);
void random_handler(int n, int a, int b, int c, int d, bool asc);
bool isi(char text[]);
void show_manual();

#endif
