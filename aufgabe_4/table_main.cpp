#include <iostream>
#include <cmath>
#include <string>
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
  cout << "Waehle die Funktion zur Tabellengenerierung:" << endl;
  for (int i = 0; i < 11 ; i++)
    cout << setw(2) << left << i + 1 << ") " << function_names[i] << endl;
}

void handle_action(int action)
{
  action--; // because an array starts with 0
  string table;
  if (action < 10)
    table = generate_function_table(functions[action], function_names[action]);
  else if (action == 10)
    table = generate_function_table(&pow, function_names[action]);
  cout << table;
  write_to_file(table);
}
