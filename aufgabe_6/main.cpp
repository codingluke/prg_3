#include <iostream>
#include <iomanip>
#include <string.h>
#include <sstream>
#include <fstream>
#include "main.h"
#include "destination_collection.h"
#include "coin.h"
#include "price_computer.h"
#include "refound_computer.h"

using namespace std;

/**
 * Entrypoint to the program "Bruch". Bruch lets you calculate and
 * compare Fractions directly in the console.
 * There is also the possibility to generate random Fraction in a
 * certain range. It prompts the user while inserting wrong Fractions
 * where the denominator is zero.
 *
 * @param argc        Length of the arguments array.
 * @param *argv[]     Arguments array form the program execution.
 */
int main()
{
  RefoundComputer ref(20);
  //DestinationCollection dest;
  //dest.add("Fahrziel 1", 1.23);
  //dest.add("Fahrziel 2", 234);
  //dest.add("Fahrziel 3", 2.3);
  //dest.add("Fahrziel 5", 9.20);
  //dest.add("Fahrziel 6", 8.9);
  //dest.add("Fahrziel 7", 60);
  //cout << endl << dest << endl;
  //Coin c;
  //cin >> c;
  //cout << endl << c;
  //PriceComputer pc((float)1.20);

  //while(pc.state() < 0)
  //{
    //cout << "Zu bezahlen " << pc.state() * -1 << endl;
    //cin >> c;
    //pc.add(c.get_value());
  //}
  //cout << "Guthaben" << pc.state();

}


/**
 * Checks whether an array of chars represents an integer or not.
 * Solfs atoi problem that returns a 0 for a char which is not a number.
 *
 * @param text[] Array of chars.
 *
 * @return true when text[] represents a number.
 *         false when text[] doesn't represent a number.
 */
bool isi(char text[])
{
  int i;
  std::istringstream in(text);
  return in >> i && in.eof();
}


/**
 * Reads a file according a given filename and prints the content
 * to the console.
 *
 * @param filename Name of the file to print to the console.
 */
void show_manual()
{
  std::string line;
  std::string filename = "manual.txt";
  std::ifstream infile(filename.c_str());
  if (!infile)
    std::cout << "File '" << filename << "' existiert nicht!" << std::endl;
  while (getline(infile, line))
    std::cout << line << std::endl;
}
