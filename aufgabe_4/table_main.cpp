#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <iomanip>
#include "console_input.h"
#include "table.h"
#include "pt_math_functions.h"
#include "table_main.h"
#include "file_controller.h"

using namespace std;

/**
 * Length of the arrays FUNCTIONS_ONE and FUNCTION_ONE_NAMES.
 */
const int FUNCTIONS_ONE_LENGTH = 10;

/**
 * Pointers to functions available for value-table generation.
 */
const ptMathFunctionOne FUNCTIONS_ONE[FUNCTIONS_ONE_LENGTH] = {
  &cos, &sin, &tan, &acos, &asin, &atan,
  &exp, &log, &log10, &sqrt
};

/**
 * Names of the functions from the array FUNCTIONS_ONE.
 * The names and the functions are mapped by the index.
 * The array must have the same length as FUNCTIONS_ONE.
 */
const string FUNCTION_ONE_NAMES[FUNCTIONS_ONE_LENGTH] = {
  "cos", "sin", "tan", "acos", "asin", "atan",
  "exp", "log", "log10", "sqrt"
};

/**
 * Length of the arrays FUNCTIONS_TWO and FUNCTION_TWO_NAMES.
 */
const int FUNCTIONS_TWO_LENGTH = 1;

/**
 * Pointers to functions available for value-table generation.
 */
const ptMathFunctionTwo FUNCTIONS_TWO[FUNCTIONS_TWO_LENGTH] = { &pow };

/**
 * Names of the functions from the array FUNCTIONS_TWO.
 * The names and the functions are mapped by the index.
 * The array must have the same length as FUNCTIONS_TWO.
 */
const string FUNCTION_TWO_NAMES[FUNCTIONS_TWO_LENGTH] = { "pow" };

/**
 * Entrypoint to the program 'tabelle'. Tabelle is a program to generate
 * value-tables for the mathematical functions cos, sin, tan, acos, asin,
 * atan, exp, log, log10, sqrt and pow.
 *
 * The user can define following parameters:
 * - Start value of the table
 * - End value of the table
 * - Value for the iteration steps
 * - Value for the steps of the column (after how many iteration should start a new column)
 * - Precision of the function output.
 * - Filename of the file to save the table.
 *
 * When a function needs other parameters, the user has to enter these too.
 * e.g. sin(x) => x is for all values between the start value and end value
 *                with the iteration of the step value.
 *      pow(x, exp) => exp has to be entered. the iteration is just for x.
 *
 * @param argc    int   Length of *argv[]
 * @param *argv[] char  Arguments array form the program execution.
 */
int main(int argc, char *argv[])
{
  if (argc == 1)
  {
    int action = 0;
    int end_action = FUNCTIONS_ONE_LENGTH + FUNCTIONS_TWO_LENGTH + 1;
    do
    {
      print_actions();
      action = read_int("Bitte waehlen:\t", 1, end_action);
      if (action < end_action)
        handle_action(action);
    } while (action != end_action);
  }
  else
    if (validate_input(argc, argv))
      handle_action(argv);
    else
      cout << "failure!";
}

/**
 * Handles a given action according the arguments array.
 * Generates the table for the action and writes the table
 * to a file. When the file already exists. The user gets
 * prompted to chose if the file gets overwridden or not.
 *
 * @param argv[] Arguments array from the program execution.
 */
void handle_action(char *argv[])
{
  string type = get_function_type(argv[1]);
  string table;
  string filename;
  int function_index;
  if (type == "ONE")
  {
    function_index = get_array_index(argv[1], FUNCTION_ONE_NAMES, FUNCTIONS_ONE_LENGTH);
    table = generate_table(FUNCTIONS_ONE[function_index], argv[1],
                           atof(argv[2]), atof(argv[3]), atof(argv[4]),
                           atof(argv[5]), atof(argv[6]));
    filename = argv[7];
  }
  else if (type == "TWO")
  {
    function_index = get_array_index(argv[1], FUNCTION_TWO_NAMES, FUNCTIONS_TWO_LENGTH);
    table = generate_table(FUNCTIONS_TWO[function_index], argv[1], atof(argv[2]),
                           atof(argv[3]), atof(argv[4]), atof(argv[5]),
                           atof(argv[6]), atof(argv[7]));
    filename = argv[8];
  }
  cout << table;
  write_to_file(filename, table);
}

/**
 * Generates the table for e certain action given by the id.
 * prints the table to the console and writes the table in a
 * file chosen by the users input. If the file already exists,
 * it promts the user to chose wheather to override it or to abord.
 *
 * @param action int The action for witch to generate the table.
 */
void handle_action(int action)
{
  action--; // because an array starts with 0
  string table;
  if (action < FUNCTIONS_ONE_LENGTH)
    table = generate_table(FUNCTIONS_ONE[action], FUNCTION_ONE_NAMES[action]);
  else if (action > (FUNCTIONS_ONE_LENGTH - 1))
  {
    int index = action - FUNCTIONS_ONE_LENGTH;
    table = generate_table(FUNCTIONS_TWO[index], FUNCTION_TWO_NAMES[index]);
  }
  cout << endl << table;
  write_to_file(table);
}

/**
 * Prints a description of the available actions to the console.
 */
void print_actions()
{
  cout << endl << "Waehle die Funktion zur Tabellengenerierung:" << endl;
  for (int i = 0; i < FUNCTIONS_ONE_LENGTH ; i++)
    cout << setw(3) << left << i + 1 << FUNCTION_ONE_NAMES[i] << endl;
  for (int i = 0; i < FUNCTIONS_TWO_LENGTH ; i++)
    cout << setw(3) << left << i + FUNCTIONS_ONE_LENGTH + 1
         << FUNCTION_TWO_NAMES[i] << endl;
  cout << setw(3) << left << FUNCTIONS_TWO_LENGTH + FUNCTIONS_ONE_LENGTH + 1
       << "Programm beenden" << endl;
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
 * There are two defined types ("ONE" and "TWO").
 *
 * @param name String Name of the function to be checked.
 *
 * @return String ONE ptMathFunctionOne: double (*)(double)
 *                TWO ptMathFunctionTwo: double (*)(double, double)
 */
string get_function_type(string name)
{
  string type = "ONE";
  for (int i = 0; i < FUNCTIONS_TWO_LENGTH ; i++)
    if (FUNCTION_TWO_NAMES[i] == name)
      type = "TWO";
  return type;
}

/**
 * Validates the input arguments.
 * Checks if the function is available.
 * Checks if there are enough argumends for the given function type.
 * Checks if the arguments are in the right types.
 *
 * @param argc     int  lenght of the argument array.
 * @param *argv[]  char argument array.
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
 * @param function_type String Type of the function ("ONE" ore "TWO")
 * @param argv[]        *char  input arguments.
 *
 * @return true  when the argument types fit the functions type.
 *         false when the argument types don't fit the functions type.
 */
bool validate_param_types(string function_type, char *argv[])
{
  bool valid = false;
  if (function_type == "ONE" && atof(argv[2]) && atof(argv[3])
           && atof(argv[4]) && atof(argv[4]) && atof(argv[5])
           && atof(argv[6]) && !atof(argv[7]))
    valid = true;
  else if (function_type == "TWO" && atof(argv[2]) && atof(argv[3])
      && atof(argv[4]) && atof(argv[4]) && atof(argv[5])
      && atof(argv[6]) && atof(argv[7]) && !atof(argv[8]))
    valid = true;
  return valid;
}

/**
 * Validates the argument length according a given function type.
 *
 * @param function_type String Type of the function ("ONE" ore "TWO")
 * @param argc          int    Length of the argument array.
 *
 * @return true   if the argument length fit the function type
 *         false  if the argument length don fit the function type.
 */
bool validate_params_length(string function_type, int argc)
{
  bool valid = false;
  cout << function_type << argc;
  if ((function_type == "ONE" && argc == 8) ||
      (function_type == "TWO" && argc == 9))
    valid = true;
  return valid;
}

/**
 * Checks if a function (by its name) is defined.
 *
 * @param name String function by name, to be checked.
 *
 * @return true   if the function exists.
 *         fales  if the function don't exists.
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
