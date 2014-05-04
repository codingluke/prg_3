#include <iostream>
#include "console_input.h"
#include "console_output.h"

using namespace std;

int main()
{
  cout << "Bitte eine ganze Zahl eingeben: ";
  long eingabe = read_long_0();
  cout << "Ihre Eingabe: ";
  cout << eingabe << "\n";
  cout << "Bitte noch eine ganze Zahl eingeben: ";
  eingabe = read_long_0();
  cout << "Ihre Eingabe: ";
  cout << eingabe << "\n";
}
