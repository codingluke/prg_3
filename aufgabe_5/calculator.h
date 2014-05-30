#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <vector>
#include <stdexcept>
#include "fraction.h"

typedef Fraction (Fraction::*fptr)(const Fraction&) const;
typedef Fraction (Fraction::*fptr2)(const int&) const;
typedef Fraction (*fptr3)(const int&, const Fraction&);

class Calculator
{
  private:
    fptr operators_frc_frc[4];
    fptr2 operators_frc_num[4];
    fptr3 operators_num_frc[4];
    std::string operator_names[4];

  public:
    Calculator();

    void calculate(Fraction left, Fraction right,
                   std::string op) const throw(const std::invalid_argument);
    void calculate(int left, Fraction right,
                   std::string op) const throw(const std::invalid_argument);
    void calculate(Fraction left, int right,
                   std::string op) const throw(const std::invalid_argument);
    void compare(Fraction f1, Fraction f2) const;

  private:
    void init_default_operators();
    int get_op_index(std::string op) const;
};

#endif
