#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cstdlib>
#include <sstream>
#include <string>
#include "file_controller.h"
#include "sudoku.h"
#include "square.h"

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
  }
    //else if (option == "-s")
    //{
      //cout << "Loese Sudoku" << endl;
      //string file = read_file("sudoku.txt");
      //string numbers = "";
      //for(unsigned int i = 0; i < file.length(); i++)
      //{
        //string number = file.substr(i, 1);
        //if (number != " ")
          //numbers += number;
      //}
      //int grid[9][9] = {
        //{0,0,0,0,0,0,0,0,0},
        //{0,0,0,0,0,0,0,0,0},
        //{0,0,0,0,0,0,0,0,0},
        //{0,0,0,0,0,0,0,0,0},
        //{0,0,0,0,0,0,0,0,0},
        //{0,0,0,0,0,0,0,0,0},
        //{0,0,0,0,0,0,0,0,0},
        //{0,0,0,0,0,0,0,0,0},
        //{0,0,0,0,0,0,0,0,0}
      //};
      //int row = -1;
      //int col = 0;
      //if (numbers.length() == 81)
        //for(unsigned int i = 0; i < numbers.length(); i++)
        //{
          //col = i % 9;
          //if (col == 0)
            //row ++;
          //stringstream ss(numbers.substr(i, 1));
          //ss >> grid[row][col];
        //}
      //for (int i = 0; i < 9; i++)
      //{
        //for (int j = 0; j < 9; j++)
          //cout << grid[i][j];
        //cout << endl;
      //}

      ////int grid[9][9] = {
        ////{9,0,3,0,5,0,6,0,0},
        ////{0,8,0,1,0,0,0,0,0},
        ////{0,0,2,0,0,0,0,8,0},
        ////{0,1,0,0,0,9,0,2,4},
        ////{0,0,0,0,0,0,9,0,0},
        ////{0,4,0,3,0,0,0,0,7},
        ////{0,0,0,0,0,0,4,5,9},
        ////{0,0,0,7,0,0,0,1,0},
        ////{0,6,0,0,8,0,0,0,0}
      ////};
      //Sudoku s(grid);
      //cout << "Sudoku:" << endl;
      //cout << s.str() << endl;
      ////s.solve();
      ////cout << "Sudoku solved:" << endl;
      ////cout << s.str_solved();
    //}
    //else
    //{
      //cout << "Beschreibung" << endl;

    //}
  //}
}
