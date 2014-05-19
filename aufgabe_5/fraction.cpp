#include <sstream>
#include <iostream>
#include "fraction.h"

Fraction::Fraction(int a_numerator, int a_denominator)
{
  numerator = a_numerator;
  denominator = a_denominator;
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

int Fraction::compare(const Fraction& frc) const
{
  int new_denominator = denominator * frc.denominator;
  Fraction tmp = extend(new_denominator);
  Fraction tmp1 = frc.extend(new_denominator);
  int result = 0;
  if (tmp.numerator > tmp1.numerator)
    result = 1;
  else if (tmp.numerator < tmp1.numerator)
    result = -1;
  return result;
}

Fraction Fraction::operator+(const Fraction& frc) const
{
  unsigned int new_denominator = lcm(denominator, frc.denominator);
  Fraction tmp1 = extend(new_denominator);
  Fraction tmp2 = frc.extend(new_denominator);
  Fraction result(tmp1.numerator + tmp2.numerator, new_denominator);
  result.shorten();
  return result;
}

Fraction Fraction::operator+(const int& number) const
{
  Fraction tmp(number, number);
  return tmp + *this;
}

Fraction Fraction::operator-(const Fraction& frc) const
{
  unsigned int new_denominator = lcm(denominator, frc.denominator);
  Fraction tmp1 = extend(new_denominator);
  Fraction tmp2 = frc.extend(new_denominator);
  Fraction result(tmp1.numerator - tmp2.numerator, new_denominator);
  result.shorten();
  return result;
}

Fraction Fraction::operator-(const int& number) const
{
  Fraction tmp(number, number);
  return *this - tmp;
}

Fraction Fraction::operator*(const Fraction& frc) const
{
  int new_numerator = numerator * frc.numerator;
  unsigned int new_denominator = denominator * frc.denominator;
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

Fraction Fraction::operator/(const Fraction& frc) const
{
  return *this * Fraction(frc.denominator, frc.numerator);
}

bool Fraction::operator==(const Fraction& frc) const
{
  bool result = true;
  if (compare(frc) != 0)
    result = false;
  return result;
}

bool Fraction::operator<(const Fraction& frc) const
{
  bool result = true;
  if (compare(frc) != -1)
    result = false;
  return result;
}

bool Fraction::operator>(const Fraction& frc) const
{
  return !(*this <= frc);
}

bool Fraction::operator<=(const Fraction& frc) const
{
  return (*this < frc) || (*this == frc);
}

bool Fraction::operator>=(const Fraction& frc) const
{
  return (*this > frc) || (*this == frc);
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
