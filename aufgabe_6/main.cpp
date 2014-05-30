#include "ticket_machine.h"

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
  vector<double> coins;
  coins.push_back(50);
  coins.push_back(20);
  coins.push_back(10);
  coins.push_back(5);
  coins.push_back(2);
  coins.push_back(1);
  coins.push_back(0.5);
  coins.push_back(0.1);
  coins.push_back(0.0);
  TicketMachine bvg("Luki Menschentransport e.V.", "Euro", coins);
  bvg.run();
}

/**
 * Reads a file according a given filename and prints the content
 * to the console.
 *
 * @param filename Name of the file to print to the console.
 */
//void show_manual()
//{
  //std::string line;
  //std::string filename = "manual.txt";
  //std::ifstream infile(filename.c_str());
  //if (!infile)
    //std::cout << "File '" << filename << "' existiert nicht!" << std::endl;
  //while (getline(infile, line))
    //std::cout << line << std::endl;
//}
