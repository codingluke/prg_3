#ifndef _console_output_h
#define _console_output_h

#include <iostream>
#include <string>

void write_number(long number, ios_base::fmtflags format[], int num_formats);
void write_number(long number, ios_base::fmtflags format);
void write_number(long number, streamsize fieldwith,
                   ios_base::fmtflags format[], int num_formats);
void write_number(long number, streamsize fieldwith, ios_base::fmtflags format);
void write_number(long number, streamsize fieldwith, char fillsign,
                   ios_base::fmtflags format[], int num_formats);
void write_number(long number, streamsize fieldwith, char fillsign,
                   ios_base::fmtflags format);
void write_number(long double number, ios_base::fmtflags format[],
                   int num_formats);
void write_number(long double number, ios_base::fmtflags format);
void write_number(long double number, streamsize fieldwith,
                   ios_base::fmtflags format[], int num_formats);
void write_number(long double number, streamsize fieldwith,
                   ios_base::fmtflags format);
void write_number(long double number, streamsize fieldwith, char fillsign,
                   ios_base::fmtflags format[], int num_formats);
void write_number(long double number, streamsize fieldwith,
                   char fillsign, ios_base::fmtflags format);
void write_text(char *text, streamsize fieldwith,
                   ios_base::fmtflags direction);
void write_text(string text, streamsize fieldwith,
                   ios_base::fmtflags direction);

#endif
