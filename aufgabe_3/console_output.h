#ifndef _console_output_h
#define _console_output_h

#include <iostream>

void write_number(long number, ios_base::fmtflags format[], int anzahl_formate);
void write_number(long number, ios_base::fmtflags format);
void write_number(long number, streamsize feldbreite,
                   ios_base::fmtflags format[], int anzahl_formate);
void write_number(long number, streamsize feldbreite, ios_base::fmtflags format);
void write_number(long number, streamsize feldbreite, char fuellzeichen,
                   ios_base::fmtflags format[], int anzahl_formate);
void write_number(long number, streamsize feldbreite, char fuellzeichen,
                   ios_base::fmtflags format);
void write_number(long double number, ios_base::fmtflags format[],
                   int anzahl_formate);
void write_number(long double number, ios_base::fmtflags format);
void write_number(long double number, streamsize feldbreite,
                   ios_base::fmtflags format[], int anzahl_formate);
void write_number(long double number, streamsize feldbreite,
                   ios_base::fmtflags format);
void write_number(long double number, streamsize feldbreite, char fuellzeichen,
                   ios_base::fmtflags format[], int anzahl_formate);
void write_number(long double number, streamsize feldbreite,
                   char fuellzeichen, ios_base::fmtflags format);

#endif
