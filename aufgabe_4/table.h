#ifndef TABLE_H
#define TABLE_H

#include <string>

using namespace std;

string generate_function_table(double (*pointer_function)(double, double), string name,
                               double exp, double start, double end, double steps,
                               double column_steps, int precision);
string generate_function_table(double (*pointer_function)(double), string name,
                               double start, double end, double steps,
                               double column_steps, int precision);
string generate_function_table(double (*pointer_function)(double), string name);
string generate_function_table(double (*pointer_function)(double, double), string name);

#endif
