#include <iostream>
#include <climits>
#include <string>
#include "io_util.h"

using namespace std;

long read_long_0()
{
  long entry = 0;
  bool entry_ok = false;
  cin.clear();
  do
  {
    cin >> entry;
    entry_ok = cin.good();
    cin.clear();
    cin.ignore(static_cast<streamsize>(LONG_MAX), '\n');
    if (!entry_ok)
      cout << "Bitte eine ganze Zahl eingeben: ";
  } while (!entry_ok);
  return entry;
}

long read_long(long min, long max)
{
  if (max < min)
    swap(min, max);
  long entry = 0;
  bool entry_ok = false;
  cin.clear();
  cin.unsetf(cin.skipws);
  do
  {
   cin >> entry;
   entry_ok = cin.good() && min <= entry && entry <= max;
   cin.clear();
   cin.ignore(static_cast<streamsize>(LONG_MAX), '\n');
   if (!entry_ok)
   {
     cout << "Bitte eine ganze Zahl eingeben [";
     cout << min << " - " << max << "]: ";
   }
  } while (!entry_ok);
  cin.setf(cin.skipws);
  return entry;
}

long read_long()
{
  return read_long(LONG_MIN, LONG_MAX);
}

long read_long(string text)
{
  cout << text;
  return read_long();
}

long read_long(string text, long min, long max)
{
  cout << text;
  return read_long(min, max);
}

int read_int(int min, int max)
{
  return static_cast<int>(read_long(min, max));
}

int read_int()
{
  return static_cast<int>(read_long(INT_MIN, INT_MAX));
}

int read_int(string text)
{
  cout << text;
  return read_int();
}

int read_int(string text, int min, int max)
{
  cout << text;
  return read_int(min, max);
}
