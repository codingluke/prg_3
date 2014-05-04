#include <iostream>

using namespace std;

void setze_schalter(ios_base::fmtflags format)
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

void swap(int* x, int* y)
{
  int t;
  t = *y;
  *y = *x;
  *x = t;
}
