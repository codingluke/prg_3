#ifndef TABELLE_MAIN_H
#define TABELLE_MAIN_H

#include <string>

using namespace std;

typedef double (*ptMathFunctionOne)(double);
typedef double (*ptMathFunctionTwo)(double, double);
int main(int argc, char *argv[]);
void print_actions();
void handle_action(int action);
void handle_action(char *argv[]);
bool validate_input(int argc, char *argv[]);
bool validate_function_name(string function_name);
bool validate_params_length(string function_type, int argc);
bool validate_param_types(string function_type, char *argv[]);
int get_array_index(string name, const string names[], int length);
string get_function_type(string name);

#endif
