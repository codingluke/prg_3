#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cstdlib>
#include <sstream>
#include <string>
#include "file_controller.h"
#include "sudoku.h"

using namespace std;

/**
 * Entrypoint to the program "Sudoku".
 *
 * @param argc    Number of arguments given.
 * @param argv[]  Array of the given arguments.
 */
int main(int argc, char *argv[])
{
  if (argc == 3)
  {
    string option = argv[1];
    if (option == "-g")
    {
      cout << "Ich erzeuge ein Sudoku. Bitte warten ..." << endl << endl;
      Sudoku s(atoi(argv[2]));
      cout << "Sudoku der Ordnung " << atoi(argv[2]) << ":" << endl << endl;
      cout << s.str() << endl;
      cout << "Loesung:" << endl << endl;
      cout << s.str_solved();
    }
    else if (option == "-s")
    {
      cout << "Loese Sudoku" << endl;
      string file = read_file("sudoku.txt");
      for(unsigned int i = 0; i < file.length(); i++)
      {
        cout << file.substr(i, 1) << endl;
      }

      int grid[9][9] = {
        {9,0,3,0,5,0,6,0,0},
        {0,8,0,1,0,0,0,0,0},
        {0,0,2,0,0,0,0,8,0},
        {0,1,0,0,0,9,0,2,4},
        {0,0,0,0,0,0,9,0,0},
        {0,4,0,3,0,0,0,0,7},
        {0,0,0,0,0,0,4,5,9},
        {0,0,0,7,0,0,0,1,0},
        {0,6,0,0,8,0,0,0,0}
      };
      Sudoku s(grid);
      cout << "Sudoku:" << endl;
      cout << s.str() << endl;
      cout << "Sudoku solved:" << endl;
      cout << s.str_solved();
    }
    else
    {
      cout << "Beschreibung" << endl;

    }
  }
}
