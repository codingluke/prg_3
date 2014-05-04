#include <iostream>
#include <climits>
#include <string>
#include "io_util.h"

using namespace std;

long read_long_0()
{
  long eingabe = 0;
  bool eingabe_ok = false;
  cin.clear();
  do
  {
    cin >> eingabe;
    eingabe_ok = cin.good();
    cin.clear();
    cin.ignore(static_cast<streamsize>(LONG_MAX), '\n');
    if (!eingabe_ok)
      cout << "Bitte eine ganze Zahl eingeben: ";
  } while (!eingabe_ok);
  return eingabe;
}

long read_long(long min, long max)
{
  if (max < min)
    swap(min, max);
  long eingabe = 0;
  bool eingabe_ok = false;
  cin.clear();
  cin.unsetf(cin.skipws);
  do
  {
   cin >> eingabe;
   eingabe_ok = cin.good() && min <= eingabe && eingabe <= max;
   cin.clear();
   cin.ignore(static_cast<streamsize>(LONG_MAX), '\n');
   if (!eingabe_ok)
   {
     cout << "Bitte eine ganze Zahl eingeben [";
     cout << min << " - " << max << "]: ";
   }
  } while (!eingabe_ok);
  cin.setf(cin.skipws);
  return eingabe;
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
