#ifndef GREGORIAN_CALENDAR_H
#define GREGORIAN_CALENDAR_H

#include "date.h"

int calc_days_of_month(int month, int year);
bool is_leap_year(int year);
int calc_days_since_the_beginning(int day, int month, int year);
int calc_start_column(int month, int year);
int calc_days_between_dates(date date1, date date2);
void print_line(int start_column, int num_days, int month, int year);
void print_days(int start_column, int num_days);
void print_line(char* sign, int length);
void print_calendar(int month, int year);

#endif
