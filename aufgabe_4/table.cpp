#include <iostream>
#include <sstream>
#include <cmath>
#include <limits>
#include <string>
#include <iomanip>
#include "console_input.h"
#include "table.h"
#include "pt_math_functions.h"

#define EPSILON 0.00001

using namespace std;

const double DBL_MAX = numeric_limits<double>::max();
const double DBL_MIN = numeric_limits<double>::min();

/**
 * Generates a value-table of a given function. The parameter of the given
 * function is iterated by 'steps' and lies between the 'start' and 'end' value
 * over the whole table.
 *
 * @param function     Pointer to the function to generate values.
 * @param name         Name of the function.
 * @param start        Start value of the first parameter.
 * @param end          End value of the first parameter.
 * @param steps        Iteration stepts for the values between start, end.
 * @param row_steps Iteration steps for the columns of the table.
 * @param precision    Precision of the calculated values.
 *
 * @return a formatted value-table as a string.
 */
string generate_table(ptMathFunctionOne function, string name,
                      double start, double end, double steps,
                      double row_steps, int precision)
{
  ostringstream wandler(ios::out);
  wandler << "Funktion:\t" << name << " x" << endl << endl;
  wandler << left << setw(6) << "x";
  int num_columns = (int)(row_steps / steps);
  for (int i = 0; i < num_columns; i++)
    wandler << right << setw(precision + 4) << i;
  wandler << endl;
  double index = start;
  while (start <= end)
  {
    if (fabs(index - start) < EPSILON)
    {
      wandler << endl << left << setw(6) << setprecision(1)
              << fixed << index;
      index += row_steps;
    }
    wandler << setprecision(precision) << setw(precision + 4)
            << right << fixed << function(start);
    start += steps;
  }
  wandler << endl << endl;
  return wandler.str();
}

/**
 * Generates a value-table of a given function. The first parameter of the given
 * function is iterated by 'steps' and lies between the 'start' and 'end' value
 * over the whole table. The second parameter 'param_two' is static.
 *
 * @param function     Pointer to the function to generate values.
 * @param name         Name of the function.
 * @param start        Start value of the first parameter.
 * @param end          End value of the first parameter.
 * @param steps        Iteration stepts for the values between start, end.
 * @param row_steps Iteration steps for the columns of the table.
 * @param precision    Precision of the calculated values.
 * @param param_two    Second parameter for the function.
 *
 * @return a formatted value-table as a string.
 */
string generate_table(ptMathFunctionTwo function, string name, double start,
                      double end, double steps, double row_steps,
                      int precision, double param_two)
{
  ostringstream wandler(ios::out);
  wandler << "Funktion:\t" << name << " x, " << param_two << endl << endl;
  wandler << left << setw(6) << "x";
  int num_columns = (int)(row_steps / steps);
  for (int i = 0; i < num_columns; i++)
    wandler << right << setw(precision + 4) << i;
  wandler << endl;
  double index = start;
  while (start <= end)
  {
    if (fabs(index - start) < EPSILON)
    {
      wandler << endl << left << setw(6) << setprecision(1)
              << fixed << index;
      index += row_steps;
    }
    wandler << setprecision(precision) << setw(precision + 4)
            << right << fixed << function(start, param_two);
    start += steps;
  }
  wandler << endl << endl;
  return wandler.str();
}

/**
 * Promts the user to enter all values to generate the value-table for a given
 * function. It then generates the value-table according the entered data.
 *
 * @param function     Pointer to the function to generate values.
 * @param name         Name of the function.
 *
 * @return a formatted value-table as a string.
 */
string generate_table(ptMathFunctionOne function, string name)
{
  double start = read_double("Bitte Startwert angeben: ");
  double end = read_double("Bitte Endwert angeben: ", start, DBL_MAX);
  double steps = read_double("Bitte Schrittgroesse angeben: ");
  double row_steps = read_double("Bitte Zeilenschrittgroesse angeben: ", steps, DBL_MAX);
  int precision = read_int("Bitte Nachkommastellen angeben: ");
  return generate_table(function, name, start, end,
                        steps, row_steps, precision);
}

/**
 * Promts the user to enter all values to generate the value-table for a given
 * function. It then generates the value-table according the entered data.
 *
 * @param function     Pointer to the function to generate values.
 * @param name         Name of the function.
 *
 * @return a formatted value-table as a string.
 */
string generate_table(ptMathFunctionTwo function, string name)
{
  double start = read_double("Bitte Startwert angeben: ");
  double end = read_double("Bitte Endwert angeben: ", start, DBL_MAX);
  double steps = read_double("Bitte Schrittgroesse angeben: ");
  double row_steps = read_double("Bitte Zeilenschrittgroesse angeben: ", steps, DBL_MAX);
  double param_two = read_double("Bitte zweiter Parameter angeben: ");
  int precision = read_int("Bitte Nachkommastellen angeben: ");
  return generate_table(function, name, param_two, start, end,
                        steps, row_steps, precision);
}
