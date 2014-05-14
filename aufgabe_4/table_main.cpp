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

const int FUNCTIONS_ONE_LENGTH = 10;
const ptMathFunctionOne FUNCTIONS_ONE[FUNCTIONS_ONE_LENGTH] = {
  &cos, &sin, &tan, &acos, &asin, &atan,
  &exp, &log, &log10, &sqrt
};
const string FUNCTION_ONE_NAMES[FUNCTIONS_ONE_LENGTH] = {
  "cos", "sin", "tan", "acos", "asin", "atan",
  "exp", "log", "log10", "sqrt"
};
const int FUNCTIONS_TWO_LENGTH = 1;
const ptMathFunctionTwo FUNCTIONS_TWO[FUNCTIONS_TWO_LENGTH] = { &pow };
const string FUNCTION_TWO_NAMES[FUNCTIONS_TWO_LENGTH] = { "pow" };

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
      handle_action(argv);
    else
      cout << "failure!";
}

void handle_action(char *argv[])
{
  string type = get_function_type(argv[1]);
  string table;
  string filename;
  int function_index;
  if (type == "one")
  {
    function_index = get_array_index(argv[1], FUNCTION_ONE_NAMES, FUNCTIONS_ONE_LENGTH);
    table = generate_table(FUNCTIONS_ONE[function_index],
                           argv[1], atof(argv[2]), atof(argv[3]),
                           atof(argv[4]), atof(argv[5]), atof(argv[6]));
    filename = argv[7];
  }
  else if (type == "two")
  {
    function_index = get_array_index(argv[1], FUNCTION_TWO_NAMES, FUNCTIONS_TWO_LENGTH);
    table = generate_table(FUNCTIONS_TWO[function_index], argv[1], atof(argv[2]), atof(argv[3]),
                           atof(argv[4]), atof(argv[5]), atof(argv[6]),
                           atof(argv[7]));
    filename = argv[8];
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

void handle_action(int action)
{
  action--; // because an array starts with 0
  string table;
  if (action < 10)
    table = generate_table(FUNCTIONS_ONE[action], FUNCTION_ONE_NAMES[action]);
  else if (action > 9)
    table = generate_table(FUNCTIONS_TWO[action - 10], FUNCTION_TWO_NAMES[action - 10]);
  cout << table;
  write_to_file(table);
}

/**
 * Prints a description of the available actions to the console.
 */
void print_actions()
{
  cout << "Waehle die Funktion zur Tabellengenerierung:" << endl;
  for (int i = 0; i < FUNCTIONS_ONE_LENGTH ; i++)
    cout << setw(2) << left << i + 1 << ") " << FUNCTION_ONE_NAMES[i] << endl;
  for (int i = 0; i < FUNCTIONS_TWO_LENGTH ; i++)
    cout << setw(2) << left << i + 11 << ") " << FUNCTION_TWO_NAMES[i] << endl;
}

/**
 * Returns the index of a string inside an array of strings.
 *
 * @param item  String to be searched in the array.
 * @param items Array which contains the item.
 *
 * @return int index of the item in the array.
 *             -1 if not in the array.
 */
int get_array_index(string item, const string items[], int length)
{
  int index = -1;
  for (int i = 0; i < length ; i++)
    if (items[i] == item)
      index = i;
  return index;
}

/**
 * Returns a string representing the type of a function by its name.
 * There are two defined types ("one" and "two").
 *
 * @param name String Name of the function to be checked.
 *
 * @return String one ptMathFunction:  double (*)(double)
 *                two ptMathFunction2: double (*)(double, double)
 */
string get_function_type(string name)
{
  string type = "one";
  for (int i = 0; i < FUNCTIONS_TWO_LENGTH ; i++)
    if (FUNCTION_TWO_NAMES[i] == name)
      type = "two";
  return type;
}

/**
 * Validates the input arguments.
 * Checks if the function is available.
 * Checks if there are enough argumends for the
 * given function type.
 * Checks if the arguments are in the right types.
 *
 * @param argc    int lenght of the argument array.
 * @param argv[]  *char argument array.
 *
 * @return true   when the arguments are valid.
 *         false  when the arguments are invalid.
 */
bool validate_input(int argc, char *argv[])
{
  bool valid = false;
  valid = validate_function_name(argv[1]);
  string function_type = get_function_type(argv[1]);
  valid = valid && validate_params_length(function_type, argc);
  valid = valid && validate_param_types(function_type, argv);
  return valid;
}

/**
 * Validates the type of the arguments according the type of the given
 * function to be called.
 *
 * @param function_type String Type of the function ("one" ore "two")
 * @param argv[]        *char  input arguments.
 *
 * @return true  when the argument types fit the functions type.
 *         false when the argument types don't fit the functions type.
 */
bool validate_param_types(string function_type, char *argv[])
{
  bool valid = false;
  if (function_type == "one" && atof(argv[2]) && atof(argv[3])
           && atof(argv[4]) && atof(argv[4]) && atof(argv[5])
           && atof(argv[6]) && !atof(argv[7]))
    valid = true;
  else if (function_type == "two" && atof(argv[2]) && atof(argv[3])
      && atof(argv[4]) && atof(argv[4]) && atof(argv[5])
      && atof(argv[6]) && atof(argv[7]) && !atof(argv[8]))
    valid = true;
  return valid;
}

/**
 * Validates the argument length according a given function type.
 *
 * @param function_type String Type of the function ("one" ore "two")
 * @param argc          int    Length of the argument array.
 *
 * @return true   if the argument length fit the function type
 *         false  if the argument length don fit the function type.
 */
bool validate_params_length(string function_type, int argc)
{
  bool valid = false;
  if ((function_type == "one" && argc == 8) ||
      (function_type == "two" && argc == 9))
    valid = true;
  return valid;
}

/**
 * Checks if a function (by its name) is defined.
 *
 * @param name String function by name, to be checked.
 *
 * @return true   if function exists.
 *         fales  if function don't exists.
 */
bool validate_function_name(string name)
{
  bool valid = false;
  for (int i = 0; i < FUNCTIONS_ONE_LENGTH ; i++)
    if (FUNCTION_ONE_NAMES[i] == name)
      valid = true;
  for (int i = 0; i < FUNCTIONS_TWO_LENGTH ; i++)
    if (FUNCTION_TWO_NAMES[i] == name)
      valid = true;
  if (!valid)
    cout << "Nicht gueltige Funktion '" << name << "'" << endl;
  return valid;
}
