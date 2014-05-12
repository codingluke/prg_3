#ifndef TABELLE_MAIN_H
#define TABELLE_MAIN_H

#include <string>

using namespace std;

typedef double (*ptMathFunction)(double);
int main(int argc, char *argv[]);
void print_actions();
void handle_action(int action);
void handle_action(int argc, char *argv[]);
bool validate_input(int argc, char *argv[]);
bool validate_function_name(string function_name);
bool validate_params_length(string function_name, int argc);
bool validate_param_types(string function_name, char *argv[]);
int get_function_index(string function_name);

#endif
