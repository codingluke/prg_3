#ifndef TABELLE_MAIN_H
#define TABELLE_MAIN_H

#include <string>

typedef double (*ptMathFunction)(double);
int main();
void print_actions();
void handle_action(int action);
string read_secure_filename();
string generate_function_table(double (*pointer_function)(double), string name);

#endif
