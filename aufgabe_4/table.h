#ifndef TABLE_H
#define TABLE_H

#include <string>
#include "pt_math_functions.h"

using namespace std;

string generate_table(ptMathFunctionTwo function, string name, double start,
                      double end, double steps, double row_steps,
                      int precision, double param_two);
string generate_table(ptMathFunctionOne function, string name, double start,
                      double end, double steps, double row_steps,
                      int precision);
string generate_table(ptMathFunctionOne function, string name);
string generate_table(ptMathFunctionTwo function, string name);
int get_floating_point_length(double number);

#endif
