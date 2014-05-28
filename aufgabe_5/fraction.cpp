/**
 * Implementation of a Fraction. Gives the possibility to represent
 * Fractions and calculate with them. As the defaut mathematical operators
 * are overwridden, the class can be used the same way as standard c++ classes.
 */

#include <sstream>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <exception>
#include "console_input.h"
#include "fraction.h"


/**
 * Initializes a Fraction 0/1 which represents 0.
 */
Fraction::Fraction()
{
  numerator = 0;
  denominator = 1;
}

/**
 * Initializes a fraction out of a given integer.
 *
 * @param number numerator of the fraction.
 */
Fraction::Fraction(int number)
{
  numerator = number;
  denominator = 1;
  normalize();
}

/**
 * Initializes a fraction with a given numerator and denominator.
 * numerator / denominator.
 *
 * @param a_numerator   numerator of the fraction.
 * @param a_denominator denominator of the fraction.
 *
 * @throws an Exception when denominator is 0.
 */
Fraction::Fraction(int a_numerator, int a_denominator) throw (const char*)
{
  if (a_denominator == 0)
    throw "Nenner darf nicht 0 sein!";
  numerator = a_numerator;
  denominator = a_denominator;
  normalize();
}

/**
 * Initializes a random fraction between the fractions
 * low_numerator/low_denumerator and high_numerator/high_denominator.
 *
 * @param low_numerator     numerator of the lower bound fraction.
 * @param low_denominator   denominator of the lower bound fraction.
 * @param high_numerator    numerator of the higher bound fraction.
 * @param high_denominator  denominator of the higher boud fraction.
 * @param random            a random number for example the result of rand().
 *
 * @throws an Exception when low_denominator or high_denominator is 0.
 */
Fraction::Fraction(int low_numerator, int low_denominator,
                   int high_numerator, int high_denominator,
                   long random) throw (const char *)
{
  if (low_denominator == 0 || high_denominator == 0)
    throw "Nenner darf nicht 0 sein!";
  Fraction lower(low_numerator, low_denominator);
  Fraction higher(high_numerator, high_denominator);
  denominator = lcm(lower.denominator, higher.denominator) * 128;
  int low = lower.extend(denominator).numerator;
  int high = higher.extend(denominator).numerator;
  int range = 0;
  if (low < 0 && high > 0)
    range = (high + abs(low)) + 1;
  else
    range = high - low + 1;
  int r = range * (random / (RAND_MAX + 1.0));
  numerator = r + low;
  shorten();
  normalize();
}

/**
 * Returns the fraction as a string.
 *
 * @return fraction as a string "nominator/denominator"
 */
std::string Fraction::str() const
{
  std::ostringstream modifier(std::ios::out);
  if (numerator == 0)
    modifier << 0;
  else
    modifier << numerator << "/" << denominator;
  return modifier.str();
}

/**
 * Returns the fraction as a nomed string.
 * 0/1            => 0
 * 1/1, 3/3, ...  => 1
 *
 * @return fraction as a normed string.
 */
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

/**
 * Compares the fraction with an other fraction.
 *
 * @param other Other Fraction to compare with the Fraction.
 *
 * @return  0   Fraction have the same value.
 *          1   Fraction is bigger then other fraction.
 *          -1  Fraction is smaller than other facton.
 */
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

/**
 * Overloading of the operator+. Defines the addition of
 * two Fractions.
 *
 * @param other Other Fraction to add to the Fraction.
 *
 * @return a new Fraction representing the sum of the two Fraction.
 */
Fraction Fraction::operator+(const Fraction& other) const
{
  int new_denominator = lcm(denominator, other.denominator);
  Fraction tmp1 = extend(new_denominator);
  Fraction tmp2 = other.extend(new_denominator);
  Fraction result(tmp1.numerator + tmp2.numerator, new_denominator);
  result.shorten();
  return result;
}

/**
 * Overloading of the operator+. Defines the addition of
 * a Fraction and a number.
 *
 * @param number The number to add to the Fraction.
 *
 * @return a new Fraction with the sum of the number and the Fraction.
 */
Fraction Fraction::operator+(const int& number) const
{
  Fraction tmp(number, number);
  return tmp + *this;
}

/**
 * Overloading of the operator-. Defines the subtraction of
 * two Fractions.
 *
 * @param other Other Fraction to subtract to the Fraction.
 *
 * @return a new Fraction with the difference of the two Fraction.
 */
Fraction Fraction::operator-(const Fraction& other) const
{
  int new_denominator = lcm(denominator, other.denominator);
  Fraction tmp1 = extend(new_denominator);
  Fraction tmp2 = other.extend(new_denominator);
  Fraction result(tmp1.numerator - tmp2.numerator, new_denominator);
  result.shorten();
  return result;
}

/**
 * Overloading of the operator-. Defines the subtraction of
 * a Fraction and a number.
 *
 * @param number The number to subtract to the Fraction.
 *
 * @return a new Fraction with the diffecence of the number and the Fraction.
 */
Fraction Fraction::operator-(const int& number) const
{
  Fraction tmp(number, number);
  return *this - tmp;
}

/**
 * Overloading of the operator*. Defines the multiplication of
 * two Fractions.
 *
 * @param other Other Fraction to multiply to the Fraction.
 *
 * @return a new Fraction representing the multiplication
 *         of the two Fraction.
 */
Fraction Fraction::operator*(const Fraction& other) const
{
  int new_numerator = numerator * other.numerator;
  int new_denominator = denominator * other.denominator;
  Fraction result(new_numerator, new_denominator);
  result.shorten();
  return result;
}

/**
 * Overloading of the operator*. Defines the multiplication of
 * a Fraction and a number.
 *
 * @param number The number to multiply to the Fraction.
 *
 * @return a new Fraction with the diffecence of the number and the Fraction.
 */
Fraction Fraction::operator*(const int& number) const
{
  return number * *this;
}

/**
 * Overloading of the operator/. Defines the division of
 * two Fractions.
 *
 * @param other Other Fraction to divide the Fraction with.
 *
 * @return a new Fraction with the quotion form the division
 *         of the Fraction with the other (right) Fraction.
 */
Fraction Fraction::operator/(const Fraction& other) const
{
  return *this * Fraction(other.denominator, other.numerator);
}

/**
 * Overloading of the operator/. Defines the division of
 * a Fraction and a number.
 *
 * @param number The number to devide the Fraction with.
 *
 * @return a new Fraction with the quotion from the division
 *         of the Fraction with the number (right).
 *
 * @throws exception when divisor number is 0.
 */
Fraction Fraction::operator/(const int& number) const throw (const char*)
{
  if (number == 0)
    throw "Division durch 0 ist nicht erlaubt!";
  Fraction tmp(number, number);
  return *this / tmp;
}

/**
 * Defines the equalness of two Fractions.
 *
 * @param other The Other Fraction to compare equalness.
 *
 * @return true  The fractions are equal, represent the same rational number.
 *         false The Fractions are not equal.
 */
bool Fraction::operator==(const Fraction& other) const
{
  bool result = true;
  if (compare(other) != 0)
    result = false;
  return result;
}

/**
 * Defines when a Fraction is smaller than an other Fraction.
 *
 * @param other Other Fraction to compare "smaller then"
 *
 * @return true when the Fraction is smaller than the other Fraction.
 */
bool Fraction::operator<(const Fraction& other) const
{
  bool result = true;
  if (compare(other) != -1)
    result = false;
  return result;
}

/**
 * Defines when a Fraction is bigger than an other Fraction.
 *
 * @param other Other Fraction to compare "bigger then"
 *
 * @return true   when the Fraction is bigger than the other Fraction.
 *         false  when the Fraction is smaller or equal than the other Fraction.
 */
bool Fraction::operator>(const Fraction& other) const
{
  return !(*this <= other);
}

/**
 * Defines when a Fraction is smaller or equal than an other Fraction.
 *
 * @param other Other Fraction to compare "smaller or equal than"
 *
 * @return true   when the Fraction is smaller or equal than the other Fraction.
 *         false  when the Fraction is bigger than the other Fraction.
 */
bool Fraction::operator<=(const Fraction& other) const
{
  return (*this < other) || (*this == other);
}

/**
 * Defines when a Fraction is bigger or equal than an other Fraction.
 *
 * @param other Other Fraction to compare "bigger or equal than"
 *
 * @return true   when the Fraction is bigger or equal than the other Fraction.
 *         false  when the Fraction is smaller han the other Fraction.
 */
bool Fraction::operator>=(const Fraction& other) const
{
  return (*this > other) || (*this == other);
}


/**
 * Algorithm for the gratest common divisor of two given numbers.
 * Also known as the Euklid Algorithmus.
 *
 * @param a   First number to calculate its divisor.
 * @param b   Second number to calculate its divisor.
 *
 * @return the grates common divisor of the given numbers a and b.
 */
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

/**
 * Algorithm for the lowest common multiple of two given numbers.
 *
 * @param a   First number to find the lowest common multible with.
 * @param b   Second number to find the lowest common multiple with.
 *
 * @return The lowest common multiple of the tow given numbers a and b.
 */
int Fraction::lcm(int a, int b) const
{
  return (a * b) / gcd(a, b);
}

/**
 * Shortens the Fraction so that it has the lowest possible denominator.
 */
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

/**
 * Makes sure that the denominator is not nevagive.
 */
void Fraction::normalize()
{
  if (denominator < 0)
  {
    numerator *= -1;
    denominator *= -1;
  }
}

/**
 * Extends the Fraction to a certain denominator.
 *
 * @param a_denominator the denominator to extend to.
 *
 * @return a new Fraction extended to the given denominator.
 *
 * @throws Exceotion when a_denominator is 0.
 */
Fraction Fraction::extend(int a_denominator) const throw (const char*)
{
  if (a_denominator == 0)
    throw "Nenner darf nicht 0 sein!";
  int new_numerator = (a_denominator / denominator) * numerator;
  return Fraction(new_numerator, a_denominator);
}

/**
 * Overloads global operatr+. Defines how to add a Fraction
 * to an integer and returns the sum as a new Fraction.
 *
 * @param left  Integer to which the Fraction gets added.
 * @param right Fraction which gets added.
 *
 * @return a Fraction with the sum of the integer and Fraction.
 */
Fraction operator+(const int& left, const Fraction& right)
{
  return Fraction(left) + right;
}

/**
* Overloads the global operator-. Defines how to subtract a Fraction
* from an integer and returns the difference as a new Fraction.
*
* @param left  Integer from which the Fraction gets subtracted.
* @param right Fraction to subtract from the Integer.
*
* @return a Fraction with the sum of the integer and Fraction.
*/
Fraction operator-(const int& left, const Fraction& right)
{
  return Fraction(left) - right;
}

/**
* Overloads the global operator*. Defines how to multiply an Integer
* and a Fraction and returns the multiplication as a new Fraction.
*
* @param left  Integer as multiplicator
* @param right Fraction as multiplicator
*
* @return a Fraction with the multiplication of the integer and Fraction.
*/
Fraction operator*(const int& left, const Fraction& right)
{
  return Fraction(left) * right;
}

/**
* Overloads the global operator/. Defines how to divide an Integer
* by a Fraction and returns the division as a new Fraction.
*
* @param left  Integer as numerator.
* @param right Fraction as denumerator.
*
* @return a Fraction with the division of the integer by the Fraction.
*/
Fraction operator/(const int& left, const Fraction& right)
{
  return Fraction(left) / right;
}

/**
 * Overloads the global operator>> "get from". Defines the entry of a fraction
 * from the user by the console.
 *
 * @param entry Input Stream.
 * @param frc   Fraction to save the userinput into.
 *
 * @return the given inputstream entry.
 */
istream& operator>>(istream& input, Fraction& frc)
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
  return input;
}

/**
 * Overloads the global operator<< "put to". Defines how a Fraction gets
 * printed out to the outputstream.
 *
 * Format:  numerator/denominator
 *          1/1, 0/3, 89/2, -9/7
 *
 * @param entry Outputstream.
 * @param frc   Fraction to print to the outputstream.
 *
 * @return the given outputstream output.
 */
std::ostream& operator<<(std::ostream& output, const Fraction& frc)
{
  output << frc.str();
  return output;
}
