#ifndef _CONSOLE_INPUT_H
#define _CONSOLE_INPUT_H

#include <string>

using namespace std;

double read_double(double min, double max);
double read_double(string text);
double read_double(string text, double min, double max);
double read_double();
long read_long(string text, long min, long max);
long read_long(long min, long max);
long read_long(string text);
long read_long();
int read_int(string text, int min, int max);
int read_int(int min, int max);
int read_int(string text);
int read_int();

#endif
