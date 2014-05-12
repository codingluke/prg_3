#include <iostream>
#include <sstream>
#include <cmath>
#include <string>
#include <iomanip>
#include "console_input.h"
#include "table.h"
#include "table_main.h"
#include "file_controller.h"

using namespace std;

string generate_table(double (*pointer_function)(double, double), string name,
                               double exp, double start, double end, double steps,
                               double column_steps, int precision)
{
  ostringstream wandler(ios::out);
  wandler << "Funktion:\t" << name << " x, " << exp << endl << endl;
  wandler << left << setw(7) << "x";
  for (int i = 0; i < (int)(column_steps / steps); i++)
    wandler << right << setw(precision + 4) << i;
  wandler << endl;
  double index = start;
  while (start <= end)
  {
    if (fabs(index - start) < 0.00001)
    {
      wandler << endl << left << setw(7) << index;
      index += column_steps;
    }
    wandler << setprecision(precision) << setw(precision + 4)
         << right << pointer_function(start, exp);
    start += steps;
  }
  wandler << endl << endl;
  return wandler.str();
}

string generate_table(double (*pointer_function)(double), string name,
                               double start, double end, double steps,
                               double column_steps, int precision)
{
  ostringstream wandler(ios::out);
  wandler << "Funktion:\t" << name << " x" << endl << endl;
  wandler << left << setw(7) << "x";
  for (int i = 0; i < (int)(column_steps / steps); i++)
    wandler << right << setw(precision + 4) << i;
  wandler << endl;
  double index = start;
  while (start <= end)
  {
    if (fabs(index - start) < 0.00001)
    {
      wandler << endl << left << setw(7) << index;
      index += column_steps;
    }
    wandler << setprecision(precision) << setw(precision + 4)
         << right << pointer_function(start);
    start += steps;
  }
  wandler << endl << endl;
  return wandler.str();
}

string generate_table(double (*pointer_function)(double), string name)
{
  double start = read_double("Bitte Startwert angeben:\t\t");
  double end = read_double("Bitte Endwert angeben:\t\t");
  double steps = read_double("Bitte Schrittgroesse angeben:\t\t");
  double column_steps = read_double("Bitte Zeilenschrittgroesse angeben:\t\t");
  int precision = read_int("Bitte Nachkommastellen angeben:\t\t");
  return generate_table(pointer_function, name, start, end,
                                 steps, column_steps, precision);
}

string generate_table(double (*pointer_function)(double, double), string name)
{
  double exp = read_double("Bitte Exponent angeben:\t\t");
  double start = read_double("Bitte Startwert angeben:\t\t");
  double end = read_double("Bitte Endwert angeben:\t\t");
  double steps = read_double("Bitte Schrittgroesse angeben:\t\t");
  double column_steps = read_double("Bitte Zeilenschrittgroesse angeben:\t\t");
  int precision = read_int("Bitte Nachkommastellen angeben:\t\t");
  return generate_table(pointer_function, name, exp, start, end,
                                 steps, column_steps, precision);
}
