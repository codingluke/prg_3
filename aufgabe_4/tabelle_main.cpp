#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <string>
#include <iomanip>
#include "console_input.h"
#include "tabelle_main.h"

using namespace std;

/**
 * Entrypoint for the calendar application. It includes three different actions:
 * 1. Create a calendar for a any month of a year between 1583 and 1000000.
 * 2. Calculates days between two arbitary dates.
 * 3. Exit the program.
 *
 * It uses the gregorian calendar und is aware of leap years. The user entry
 * is validated, so that it is not possible to enter a wrong date e.g. 30.02.2004
 * or 29.02.2014.
 */
int main()
{
  int action = 0;
  do
  {
    print_actions();
    action = read_int("Bitte waehlen:\t", 1, 12);
    if (action < 12)
      handle_action(action);
  } while (action != 12);
}

/**
 * Prints a description of the available actions to the console.
 */
void print_actions()
{
  cout << "Waehle die Funktion zur Tabellengenerierung:" << endl
       << "1)  cos" << endl << "2)  sin" << endl << "3)  tan" << endl
       << "4)  acos" << endl << "5)  asin" << endl << "6)  atan" << endl
       << "7)  exp" << endl << "8)  log" << endl << "9)  log10" << endl
       << "10) sqrt" << endl << "11) pow" << endl;
}

void handle_action(int action)
{
  action--; // because an array starts with 0
  ptMathFunction functions[] =  {
    &cos, &sin, &tan, &acos, &asin, &atan,
    &exp, &log, &log10, &sqrt
  };
  string function_names[] =  {
    "cos", "sin", "tan", "acos", "asin", "atan",
    "exp", "log", "log10", "sqrt"
  };
  string table;
  if (action < 10)
    table = generate_function_table(functions[action], function_names[action]);
  else if (action == 10)
    cout << "pow!!";

  cout << table;

  // write to file
  string filename = read_secure_filename();
  ofstream outfile(filename.c_str());
  outfile << table;
}

bool file_exists(const std::string& filename) {
  ifstream ifile(filename.c_str());
  return ifile;
}

string read_secure_filename()
{
  string filename;
  bool file_ok;
  do
  {
    filename = read_text("Bitte Dateiname angeben: ");
    file_ok = !file_exists(filename);
    if (!file_ok)
    {
      cout << "Achtung! Datei " << filename << " bereits vorhanden." << endl;
      file_ok = read_yes_no("ueberschreiben?");
    }
  } while (!file_ok);
  return filename;
}

string generate_function_table(double (*pointer_function)(double), string name)
{
  ostringstream wandler(ios::out);

  double start = read_double("Bitte Startwert angeben:\t\t");
  double end = read_double("Bitte Endwert angeben:\t\t");
  double steps = read_double("Bitte Schrittgroesse angeben:\t\t");
  double column_steps = read_double("Bitte Zeilenschrittgroesse angeben:\t\t");
  int precision = read_int("Bitte Nachkommastellen angeben:\t\t");

  wandler << "Funktion:\t" << name << " x" << endl << endl;

  // Table header
  wandler << left << setw(7) << "x";
  for (int i = 0; i < (int)(column_steps / steps); i++)
    wandler << right << setw(precision + 4) << i;
  wandler << endl;

  // Table content
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
