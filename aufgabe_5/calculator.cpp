#include <iostream>
#include <string>
#include <stdexcept>
#include "fraction.h"
#include "calculator.h"

/**
 * Initializes Calculator with the default operators.
 */
Calculator::Calculator()
{
  init_default_operators();
}

/**
 * Calculates a given operation with two Fractions. Prints out
 * the result to the console.
 *
 * @param left  Left Fraction of the operation.
 * @param right Right Fraction of the operation.
 * @param op    Operator of hte operation.
 *
 * @throws std::invalid_argument when the operator op don't exists.
 */
void Calculator::calculate(Fraction left, Fraction right, std::string op) const throw(const std::invalid_argument)
{
  int index = get_op_index(op);
  if (index == -1)
    throw std::invalid_argument("Opertor nicht vorhanden!");
  Fraction result = (left.*operators_frc_frc[index])(right);
  std::cout << left << " " << op << " " << right
            << " = " << result.str_normed() << std::endl;
}

/**
 * Calculates a given operation with a integer and a Fraction. Prints out
 * the result to the console.
 *
 * @param left  Left integer of the operation.
 * @param right Right Fraction of the operation.
 * @param op    Operator of the operation.
 *
 * @throws std::invalid_argument exception when the operator op doesn't exists.
 */
void Calculator::calculate(int left, Fraction right, std::string op) const 
  throw(const std::invalid_argument)
{
  int index = get_op_index(op);
  if (index == -1)
    throw std::invalid_argument("Opertor nicht vorhanden!");
  Fraction result = operators_num_frc[index](left, right);
  std::cout << left << " " << op << " " << right << " = "
            << result.str_normed() << std::endl;
}

/**
 * Calculates a given operation with a Fraction and an integer. Prints out
 * the result to the console.
 *
 * @param left  Left Fraction of the operation.
 * @param right Right integer of the operation.
 * @param op    Operator of the operation.
 *
 * @throws invalid_argument when the operator doesn't exists.
 */
void Calculator::calculate(Fraction left, int right, std::string op) const 
  throw(const std::invalid_argument)
{
  int index = get_op_index(op);
  if (index == -1)
    throw std::invalid_argument("Opertor nicht vorhanden!");
  Fraction result = (left.*operators_frc_num[index])(right);
  std::cout << left << " " << op << " " << right << " = "
            << result.str_normed() << std::endl;
}

/**
 * Compares two Fractions and prints out the result to the console.
 *
 * @param left 	First Fraction to compare.
 * @param right Secont Fraction to compare.
 */
void Calculator::compare(Fraction left, Fraction right) const
{
  std::string op = "<";
  if (left == right)
    op = "=";
  else if (left > right)
    op = ">";
  std::cout << left << " " << op << " " << right << std::endl;
}


/**
 * Initializes/maps the default names and pointers for calculation.
 */
void Calculator::init_default_operators()
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
