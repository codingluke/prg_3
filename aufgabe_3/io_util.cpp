#include <iostream>

using namespace std;

/**
 * Sets cout flags in a save way. Garanties that there is just the flag set given
 * by the parameter format.
 *
 * @param format  flag to set.
 */
void set_flag(ios_base::fmtflags format)
{
  if (format == cout.dec || format == cout.oct || format == cout.hex)
    cout.setf(format, ios_base::basefield);
  else
    if (format == cout.left || format == cout.right || format == cout.internal)
      cout.setf(format, ios_base::adjustfield);
    else
      if (format == cout.scientific || format == cout.fixed)
        cout.setf(format, ios_base::floatfield);
      else
        cout.setf(format);
}

/**
 * Swaps two integer variables.
 * After the function x has the value of y and y the value of x.
 * y
 *
 * @param x first variable to swap.
 * @param y second variable to swap.
 */
void swap(int* x, int* y)
{
  int t;
  t = *y;
  *y = *x;
  *x = t;
}
