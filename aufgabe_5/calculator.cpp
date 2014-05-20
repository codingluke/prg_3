#include <iostream>
#include <string>
#include "fraction.h"
#include "calculator.h"

Calculator::Calculator()
{
  operator_names[0] = "+";
  operator_names[1] = "-";
  operator_names[2] = "*";
  operator_names[3] = "/";
  operators_frc_frc[0] = &Fraction::operator+;
  operators_frc_frc[1] = &Fraction::operator-;
  operators_frc_frc[2] = &Fraction::operator*;
  operators_frc_frc[3] = &Fraction::operator/;
  operators_frc_num[0] = &Fraction::operator+;
  operators_frc_num[1] = &Fraction::operator-;
  operators_frc_num[2] = &Fraction::operator*;
  operators_frc_num[3] = &Fraction::operator/;
  operators_num_frc[0] = operator+;
  operators_num_frc[1] = operator-;
  operators_num_frc[2] = operator*;
  operators_num_frc[3] = operator/;
}

void Calculator::calculate(Fraction f1, Fraction f2, std::string op) const
{
  int index = get_op_index(op);
  if (index == -1)
    throw "Opertor nicht vorhanden!";
  Fraction result = (f1.*operators_frc_frc[index])(f2);
  std::cout << f1 << " " << op << " " << f2
            << " = " << result.str_normed();
}

void Calculator::calculate(int number, Fraction f, std::string op) const
{
  int index = get_op_index(op);
  if (index == -1)
    throw "Opertor nicht vorhanden!";
  Fraction result = operators_num_frc[index](number, f);
  std::cout << number << " " << op << " " << f << " = "
            << result.str_normed();
}

void Calculator::calculate(Fraction f, int number, std::string op) const
{
  int index = get_op_index(op);
  if (index == -1)
    throw "Opertor nicht vorhanden!";
  Fraction result = (f.*operators_frc_num[index])(number);
  std::cout << f << " " << op << " " << number << " = "
            << result.str_normed();
}

void Calculator::compare(Fraction f1, Fraction f2) const
{
  std::string op = "<";
  if (f1 == f2)
    op = "=";
  else if (f1 > f2)
    op = ">";
  std::cout << f1 << " " << op << " " << f2 << std::endl;
}

/**
 * Returns the index of a string inside an array of strings.
 *
 * @param item    String to be searched in the array.
 * @param items   Array which contains the item.
 *
 * @return int index of the item in the array.
 *             -1 if not in the array.
 */
int Calculator::get_op_index(std::string op) const
{
  int index = -1;
  for (int i = 0; i < 4; i++)
    if (operator_names[i] == op)
      index = i;
  return index;
}
