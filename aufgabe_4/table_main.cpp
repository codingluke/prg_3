#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <iomanip>
#include "console_input.h"
#include "table.h"
#include "table_main.h"
#include "file_controller.h"

using namespace std;

const ptMathFunction functions[10] = {
  &cos, &sin, &tan, &acos, &asin, &atan,
  &exp, &log, &log10, &sqrt
};

const string function_names[11] = {
  "cos", "sin", "tan", "acos", "asin", "atan",
  "exp", "log", "log10", "sqrt", "pow"
};

int main(int argc, char *argv[])
{
  if (argc == 1)
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
  else
    if (validate_input(argc, argv))
      handle_action(argc, argv);
    else
      cout << "failure!";
}

void handle_action(int argc, char *argv[])
{
  int function_index = get_function_index(argv[1]);
  string table;
  string filename;
  if (argc == 9)
  {
    table = generate_table(&pow, argv[1], atof(argv[2]), atof(argv[3]),
                           atof(argv[4]), atof(argv[5]), atof(argv[6]),
                           atof(argv[7]));
    filename = argv[8];
  }
  else if (argc == 8)
  {
    table = generate_table(functions[function_index],
                           argv[1], atof(argv[2]), atof(argv[3]),
                           atof(argv[4]), atof(argv[5]), atof(argv[6]));
    filename = argv[7];
  }
  cout << table;
  if (file_exists(filename))
  {
    cout << "Achtung! Datei " << filename << " bereits vorhanden." << endl;
    if (read_yes_no("ueberschreiben?"))
      write_to_file(filename, table);
    else
      cout << "Abgebrochen";
  }
  else
    write_to_file(filename, table);
}

/**
 * Prints a description of the available actions to the console.
 */
void print_actions()
{
  cout << "Waehle die Funktion zur Tabellengenerierung:" << endl;
  for (int i = 0; i < 11 ; i++)
    cout << setw(2) << left << i + 1 << ") " << function_names[i] << endl;
}

int get_function_index(string function_name)
{
  int index;
  for (int i = 0; i < 11 ; i++)
    if (function_names[i] == function_name)
      index = i;
  return index;
}

void handle_action(int action)
{
  action--; // because an array starts with 0
  string table;
  if (action < 10)
    table = generate_table(functions[action], function_names[action]);
  else if (action == 10)
    table = generate_table(&pow, function_names[action]);
  cout << table;
  write_to_file(table);
}

bool validate_input(int argc, char *argv[])
{
  cout << argc;
  bool valid = false;
  valid = validate_function_name(argv[1]);
  valid = valid && validate_params_length(argv[1], argc);
  valid = valid && validate_param_types(argv[1], argv);
  return valid;
}

bool validate_param_types(string function_name, char *argv[])
{
  bool valid = false;
  if (function_name == "pow" && atof(argv[2]) && atof(argv[3])
      && atof(argv[4]) && atof(argv[4]) && atof(argv[5])
      && atof(argv[6]) && atof(argv[7]) && !atof(argv[8]))
    valid = true;
  else if (function_name != "pow" && atof(argv[2]) && atof(argv[3])
           && atof(argv[4]) && atof(argv[4]) && atof(argv[5])
           && atof(argv[6]) && !atof(argv[7]))
    valid = true;
  return valid;
}

bool validate_params_length(string function_name, int argc)
{
  bool valid = false;
  if (function_name == "pow" && argc == 9)
    valid = true;
  else if (function_name != "pow" && argc == 8)
    valid = true;
  return valid;
}

bool validate_function_name(string function_name)
{
  bool valid = false;
  for (int i = 0; i < 11 ; i++)
    if (function_names[i] == function_name)
      valid = true;
  if (!valid)
    cout << "Nicht gueltige Funktion " << function_name << endl;
  return valid;
}
