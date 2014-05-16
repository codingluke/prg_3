#ifndef CONSOLE_INPUT_H
#define CONSOLE_INPUT_H

#include <string>
#include "date.h"

using namespace std;

long read_long_0();
long read_long(string text, long min, long max);
long read_long(long min, long max);
long read_long(string text);
long read_long();
int read_int(string text, int min, int max);
int read_int(int min, int max);
int read_int(string text);
int read_int();
Date read_date(string text);

#endif
