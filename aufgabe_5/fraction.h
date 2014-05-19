#ifndef FRACTION_H
#define FRACTION_H

#include <string>

class Fraction
{
  private:
    int numerator;
    int denominator;

  public:
    Fraction(int a_counter, int a_denominator);
    Fraction(int a, int b, int c, int d);

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
    Fraction operator/(const int& number) const;
    bool operator==(const Fraction& other) const;
    bool operator<(const Fraction& other) const;
    bool operator>(const Fraction& other) const;
    bool operator<=(const Fraction& other) const;
    bool operator>=(const Fraction& other) const;

  private:
    int gcd(int a, int b) const;
    int lcm(int a, int b) const;
    Fraction extend(int a_denominator) const;
    void shorten();
    void normalize();
};

Fraction operator+(const int& number, const Fraction& frc);
Fraction operator-(const int& number, const Fraction& frc);
Fraction operator*(const int& number, const Fraction& frc);
Fraction operator/(const int& number, const Fraction& frc);

#endif
