#ifndef _console_input_h
#define _console_input_h

#include <string>

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

#endif
