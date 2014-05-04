#include <iostream>
#include "io_util.h"

using namespace std;

void write_number(long number, ios_base::fmtflags format[], int anzahl_formate)
{
  for (int i = 0; i < anzahl_formate; i++)
    setze_schalter(format[i]);
  cout << number;
  for (int i = 0; i < anzahl_formate; i++)
    cout.unsetf(format[i]);
}

void write_number(long number, ios_base::fmtflags format)
{
  ios_base::fmtflags format_array[] = {format};
  write_number(number, format_array, 1);
}

void write_number(long number, streamsize feldbreite,
                   ios_base::fmtflags format[], int anzahl_formate)
{
  streamsize alte_feldbreite = cout.width();
  cout.width(feldbreite);
  write_number(number, format, anzahl_formate);
  cout.width(alte_feldbreite);
}

void write_number(long number, streamsize feldbreite, ios_base::fmtflags format)
{
  ios_base::fmtflags format_array[] = {format};
  write_number(number, feldbreite, format_array, 1);
}

void write_number(long number, streamsize feldbreite, char fuellzeichen,
                   ios_base::fmtflags format[], int anzahl_formate)
{
  char altes_fuellzeichen = cout.fill();
  cout.fill(fuellzeichen);
  write_number(number, feldbreite, format, anzahl_formate);
  cout.fill(altes_fuellzeichen);
}

void write_number(long number, streamsize feldbreite, char fuellzeichen,
                   ios_base::fmtflags format)
{
 ios_base::fmtflags format_array[] = {format};
 write_number(number, feldbreite, fuellzeichen, format_array, 1);
}

void write_number(long double number, ios_base::fmtflags format[],
                   int anzahl_formate)
{
  for (int i = 0; i < anzahl_formate; i++)
    setze_schalter(format[i]);
  cout << number;
  for (int i = 0; i < anzahl_formate; i++)
    cout.unsetf(format[i]);
}

void write_number(long double number, ios_base::fmtflags format)
{
  ios_base::fmtflags format_array[] = {format};
  write_number(number, format_array, 1);
}

void write_number(long double number, streamsize feldbreite,
                   ios_base::fmtflags format[], int anzahl_formate)
{
  streamsize alte_feldbreite = cout.width();
  cout.width(feldbreite);
  write_number(number, format, anzahl_formate);
  cout.width(alte_feldbreite);
}

void write_number(long double number, streamsize feldbreite,
                   ios_base::fmtflags format)
{
  ios_base::fmtflags format_array[] = {format};
  write_number(number, feldbreite, format_array, 1);
}

void write_number(long double number, streamsize feldbreite, char fuellzeichen,
                   ios_base::fmtflags format[], int anzahl_formate)
{
  char altes_fuellzeichen = cout.fill();
  cout.fill(fuellzeichen);
  write_number(number, feldbreite, format, anzahl_formate);
  cout.fill(altes_fuellzeichen);
}

void write_number(long double number, streamsize feldbreite,
                   char fuellzeichen, ios_base::fmtflags format)
{
  ios_base::fmtflags format_array[] = {format};
  write_number(number, feldbreite, fuellzeichen, format_array, 1);
}

