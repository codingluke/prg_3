#include <iostream>
#include "io_util.h"

using namespace std;

void write_number(long number, ios_base::fmtflags format[], int num_formats)
{
  for (int i = 0; i < num_formats; i++)
    setze_schalter(format[i]);
  cout << number;
  for (int i = 0; i < num_formats; i++)
    cout.unsetf(format[i]);
}

void write_number(long number, ios_base::fmtflags format)
{
  ios_base::fmtflags format_array[] = {format};
  write_number(number, format_array, 1);
}

void write_number(long number, streamsize fieldwith,
                   ios_base::fmtflags format[], int num_formats)
{
  streamsize old_fieldwith = cout.width();
  cout.width(fieldwith);
  write_number(number, format, num_formats);
  cout.width(old_fieldwith);
}

void write_number(long number, streamsize fieldwith, ios_base::fmtflags format)
{
  ios_base::fmtflags format_array[] = {format};
  write_number(number, fieldwith, format_array, 1);
}

void write_number(long number, streamsize fieldwith, char fillsign,
                   ios_base::fmtflags format[], int num_formats)
{
  char old_fillsign = cout.fill();
  cout.fill(fillsign);
  write_number(number, fieldwith, format, num_formats);
  cout.fill(old_fillsign);
}

void write_number(long number, streamsize fieldwith, char fillsign,
                   ios_base::fmtflags format)
{
 ios_base::fmtflags format_array[] = {format};
 write_number(number, fieldwith, fillsign, format_array, 1);
}

void write_number(long double number, ios_base::fmtflags format[],
                   int num_formats)
{
  for (int i = 0; i < num_formats; i++)
    setze_schalter(format[i]);
  cout << number;
  for (int i = 0; i < num_formats; i++)
    cout.unsetf(format[i]);
}

void write_number(long double number, ios_base::fmtflags format)
{
  ios_base::fmtflags format_array[] = {format};
  write_number(number, format_array, 1);
}

void write_number(long double number, streamsize fieldwith,
                   ios_base::fmtflags format[], int num_formats)
{
  streamsize old_fieldwith = cout.width();
  cout.width(fieldwith);
  write_number(number, format, num_formats);
  cout.width(old_fieldwith);
}

void write_number(long double number, streamsize fieldwith,
                   ios_base::fmtflags format)
{
  ios_base::fmtflags format_array[] = {format};
  write_number(number, fieldwith, format_array, 1);
}

void write_number(long double number, streamsize fieldwith, char fillsign,
                   ios_base::fmtflags format[], int num_formats)
{
  char old_fillsign = cout.fill();
  cout.fill(fillsign);
  write_number(number, fieldwith, format, num_formats);
  cout.fill(old_fillsign);
}

void write_number(long double number, streamsize fieldwith,
                   char fillsign, ios_base::fmtflags format)
{
  ios_base::fmtflags format_array[] = {format};
  write_number(number, fieldwith, fillsign, format_array, 1);
}

