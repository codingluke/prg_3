#ifndef _gregorian_calender_h
#define _gregorian_calender_h

int calculate_days_of_month(int month, int year);
bool is_leap_year(int year);
int calculate_days_from_the_beginning(int day, int month, int year);
int calculate_start_column(int month, int year);
void print_line(int start_column, int num_days, int month, int year);
void print_days(int start_column, int num_days);
void print_line(char* sign, int length);
void print_calender(int start_column, int num_days, int month, int year);
void print_calender(int month, int year);

#endif
