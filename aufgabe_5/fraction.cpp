#include <sstream>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "fraction.h"

Fraction::Fraction(int a_numerator, unsigned int a_denominator)
{
  numerator = a_numerator;
  denominator = a_denominator;
}

Fraction::Fraction(int a, unsigned int b, int c, unsigned int d)
{
  denominator = lcm(b, d);
  srand(time(0));
  Fraction lower(a, b);
  Fraction higher(c, d);
  int low = lower.extend(denominator).numerator;
  int high = higher.extend(denominator).numerator;
  numerator = rand() % (high - low + 1) + low;
  shorten();
}

std::string Fraction::str() const
{
  std::ostringstream modifier(std::ios::out);
  modifier << numerator << "/" << denominator;
  return modifier.str();
}

std::string Fraction::str_normed() const
{
  std::ostringstream modifier(std::ios::out);
  if (denominator == 1)
    modifier << numerator;
  else if (numerator == (int)denominator)
    modifier << 1;
  else
    modifier << numerator << "/" << denominator;
  return modifier.str();
}

int Fraction::compare(const Fraction& other) const
{
  int new_denominator = denominator * other.denominator;
  Fraction tmp = extend(new_denominator);
  Fraction tmp1 = other.extend(new_denominator);
  int result = 0;
  if (tmp.numerator > tmp1.numerator)
    result = 1;
  else if (tmp.numerator < tmp1.numerator)
    result = -1;
  return result;
}

Fraction Fraction::operator+(const Fraction& other) const
{
  unsigned int new_denominator = lcm(denominator, other.denominator);
  Fraction tmp1 = extend(new_denominator);
  Fraction tmp2 = other.extend(new_denominator);
  Fraction result(tmp1.numerator + tmp2.numerator, new_denominator);
  result.shorten();
  return result;
}

Fraction Fraction::operator+(const int& number) const
{
  Fraction tmp(number, number);
  return tmp + *this;
}

Fraction Fraction::operator-(const Fraction& other) const
{
  unsigned int new_denominator = lcm(denominator, other.denominator);
  Fraction tmp1 = extend(new_denominator);
  Fraction tmp2 = other.extend(new_denominator);
  Fraction result(tmp1.numerator - tmp2.numerator, new_denominator);
  result.shorten();
  return result;
}

Fraction Fraction::operator-(const int& number) const
{
  Fraction tmp(number, number);
  return *this - tmp;
}

Fraction Fraction::operator*(const Fraction& other) const
{
  int new_numerator = numerator * other.numerator;
  unsigned int new_denominator = denominator * other.denominator;
  Fraction result(new_numerator, new_denominator);
  result.shorten();
  return result;
}

Fraction Fraction::operator*(const int& number) const
{
  return number * *this;
}

Fraction Fraction::operator/(const int& number) const
{
  Fraction tmp(number, number);
  return *this / tmp;
}

Fraction Fraction::operator/(const Fraction& other) const
{
  return *this * Fraction(other.denominator, other.numerator);
}

bool Fraction::operator==(const Fraction& other) const
{
  bool result = true;
  if (compare(other) != 0)
    result = false;
  return result;
}

bool Fraction::operator<(const Fraction& other) const
{
  bool result = true;
  if (compare(other) != -1)
    result = false;
  return result;
}

bool Fraction::operator>(const Fraction& other) const
{
  return !(*this <= other);
}

bool Fraction::operator<=(const Fraction& other) const
{
  return (*this < other) || (*this == other);
}

bool Fraction::operator>=(const Fraction& other) const
{
  return (*this > other) || (*this == other);
}


int Fraction::gcd(unsigned int a, unsigned int b) const
{
  while (a != 0 && b != 0)
  {
    if (a > b)
      a -= b;
    else
      b -= a;
  }
  int gcd = a;
  if (a == 0)
    gcd = b;
  return gcd;
}

int Fraction::lcm(unsigned int a, unsigned int b) const
{
  return (a * b) / gcd(a, b);
}

void Fraction::shorten()
{
  unsigned int tmp = gcd(numerator, denominator);
  numerator /= tmp;
  denominator /= tmp;
}

Fraction Fraction::extend(unsigned int a_denominator) const
{
  unsigned int new_numerator = (a_denominator / denominator) * numerator;
  return Fraction(new_numerator, a_denominator);
}

Fraction operator+(const int& number, const Fraction& frc)
{
  Fraction tmp(number, number);
  return frc + tmp;
}

Fraction operator-(const int& number, const Fraction& frc)
{
  Fraction tmp(number, number);
  return tmp - frc;
}

Fraction operator*(const int& number, const Fraction& frc)
{
  Fraction tmp(number, number);
  return tmp * frc;
}

Fraction operator/(const int& number, const Fraction& frc)
{
  Fraction tmp(number, number);
  return tmp / frc;
}
