#include <iostream>
#include <string>
#include <fstream>
#include "console_input.h"
#include "file_controller.h"

void write_to_file(string filename, string text)
{
  ofstream outfile(filename.c_str());
  outfile << text;
}

void write_to_file(string text)
{
  string filename = read_secure_filename();
  write_to_file(filename, text);
}

bool file_exists(const std::string& filename) {
  ifstream ifile(filename.c_str());
  return ifile;
}

string read_secure_filename()
{
  string filename;
  bool file_ok;
  do
  {
    filename = read_text("Bitte Dateiname angeben: ");
    file_ok = !file_exists(filename);
    if (!file_ok)
    {
      cout << "Achtung! Datei " << filename << " bereits vorhanden." << endl;
      file_ok = read_yes_no("ueberschreiben?");
    }
  } while (!file_ok);
  return filename;
}
