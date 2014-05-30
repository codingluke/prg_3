#ifndef FRACTION_H
#define FRACTION_H

#include <string>
#include <stdexcept>

class Fraction
{
  private:
    int numerator;
    int denominator;

  public:
    Fraction();
    Fraction(int number);
    Fraction(int a_counter, int a_denominator) throw(const std::invalid_argument);
    Fraction(int low_numerator, int low_denominator,
             int high_numerator, int high_denominator,
             long random) throw(const std::invalid_argument);

    std::string str() const;
    std::string str_normed() const;
    int compare(const Fraction& other) const;

    Fraction operator+(const Fraction& other) const;
    Fraction operator+(const int& number) const;
    Fraction operator-(const Fraction& other) const;
    Fraction operator-(const int& number) const;
    Fraction operator*(const Fraction& other) const;
    Fraction operator*(const int& number) const;
    Fraction operator/(const Fraction& other) const;
    Fraction operator/(const int& number) const throw(const std::invalid_argument);
    bool operator==(const Fraction& other) const;
    bool operator<(const Fraction& other) const;
    bool operator>(const Fraction& other) const;
    bool operator<=(const Fraction& other) const;
    bool operator>=(const Fraction& other) const;

  private:
    int gcd(int a, int b) const;
    int lcm(int a, int b) const;
    Fraction extend(int a_denominator) const throw(const std::invalid_argument);
    void shorten();
    void normalize();
};

Fraction operator+(const int& left, const Fraction& right);
Fraction operator-(const int& left, const Fraction& right);
Fraction operator*(const int& left, const Fraction& right);
Fraction operator/(const int& left, const Fraction& right);
std::istream& operator>>(std::istream& input, Fraction& right);
std::ostream& operator<<(std::ostream& output, const Fraction& frc);

#endif
