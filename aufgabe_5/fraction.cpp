#include <sstream>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "console_input.h"
#include "fraction.h"

Fraction::Fraction()
{
  numerator = 0;
  denominator = 1;
}

Fraction::Fraction(int a_numerator, int a_denominator)
{
  if (a_denominator == 0)
    throw "Nenner darf nicht 0 sein!";
  numerator = a_numerator;
  denominator = a_denominator;
  normalize();
}

Fraction::Fraction(int low_numerator, int low_denominator,
                   int high_numerator, int high_denominator,
                   int random)
{
  if (low_denominator == 0 || high_denominator == 0)
    throw "Nenner darf nicht 0 sein!";
  Fraction lower(low_numerator, low_denominator);
  Fraction higher(high_numerator, high_denominator);
  denominator = lcm(lower.denominator, higher.denominator);
  int low = lower.extend(denominator).numerator;
  int high = higher.extend(denominator).numerator;
  int range = 11;
  if (low < 0 && high > 0)
    range = (high + abs(low)) + 1;
  else if (low <= 0)
    range = high - low + 1;
  numerator = (random % range) + low;
  shorten();
  normalize();
}

std::string Fraction::str() const
{
  std::ostringstream modifier(std::ios::out);
  if (numerator == 0)
    modifier << 0;
  else
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
  int new_denominator = lcm(denominator, other.denominator);
  std::cout << "denominator: " << new_denominator << "\n";
  Fraction tmp1 = extend(new_denominator);
  std::cout << "tmp1: " << tmp1 << "\n";
  Fraction tmp2 = other.extend(new_denominator);
  std::cout << "tmp2: " << tmp2 << "\n";
  Fraction result(tmp1.numerator + tmp2.numerator, new_denominator);
  std::cout << "result: " << result << "\n";
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
  int new_denominator = lcm(denominator, other.denominator);
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
  int new_denominator = denominator * other.denominator;
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


int Fraction::gcd(int a, int b) const
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

int Fraction::lcm(int a, int b) const
{
  return (a * b) / gcd(a, b);
}

void Fraction::shorten()
{
  int tmp = gcd(abs(numerator), denominator);
  if (numerator < 0)
  {
    numerator *= -1;
    numerator /= tmp;
    numerator *= -1;
  }
  else
    numerator /= tmp;
  denominator /= tmp;
}

void Fraction::normalize()
{
  if (denominator < 0)
  {
    numerator *= -1;
    denominator *= -1;
  }
}

Fraction Fraction::extend(int a_denominator) const
{
  int new_numerator = (a_denominator / denominator) * numerator;
  return Fraction(new_numerator, a_denominator);
}

Fraction operator+(const int& number, const Fraction& frc)
{
  Fraction tmp(number, number);
  std::cout << tmp << "\n";
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

istream& operator>>(istream& entry, Fraction& frc)
{
  int numerator = 0;
  int denominator = 0;
  bool entry_ok = false;
  do
  {
    try
    {
      numerator = read_int("Bitte den Zaehler eingeben: ");
      denominator = read_int("Bitte den Nenner eingeben: ");
      frc = Fraction(numerator, denominator);
      entry_ok = true;
    }
    catch(const char* msg)
    {
      cout << msg << endl;
    }
  } while (!entry_ok);
  return entry;
}


std::ostream& operator<<(std::ostream& output, const Fraction& frc)
{
  output << frc.str();
  return output;
}
