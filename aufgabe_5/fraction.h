#ifndef FRACTION_H
#define FRACTION_H

#include <string>

class Fraction
{
  private:
    int numerator;
    unsigned int denominator;

  public:
    Fraction(int a_counter, int a_denominator);

    std::string str() const;
    std::string str_normed() const;
    int compare(const Fraction& frc) const;

    Fraction operator+(const Fraction& frc) const;
    Fraction operator+(const int& number) const;
    Fraction operator-(const Fraction& frc) const;
    Fraction operator-(const int& number) const;
    Fraction operator*(const Fraction& frc) const;
    Fraction operator*(const int& number) const;
    Fraction operator/(const Fraction& frc) const;
    Fraction operator/(const int& number) const;
    bool operator==(const Fraction& frc) const;
    bool operator<(const Fraction& frc) const;
    bool operator>(const Fraction& frc) const;
    bool operator<=(const Fraction& frc) const;
    bool operator>=(const Fraction& frc) const;

  private:
    int gcd(unsigned int a, unsigned int b) const;
    int lcm(unsigned int a, unsigned int b) const;
    void shorten();
    Fraction extend(unsigned int a_denominator) const;
};

Fraction operator+(const int& number, const Fraction& frc);
Fraction operator-(const int& number, const Fraction& frc);
Fraction operator*(const int& number, const Fraction& frc);
Fraction operator/(const int& number, const Fraction& frc);

#endif
