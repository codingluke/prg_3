#include <iostream>
#include <string>
#include <fstream>
#include "console_input.h"
#include "file_controller.h"

/**
 * Writes given text into a file with the given filename.
 *
 * @param filename Name of the file to wirte.
 * @param text     Text to write into the file.
 */
void write_to_file(string filename, string text, bool secure)
{
  if (secure && file_exists(filename))
  {
    cout << "Achtung! Datei " << filename << " bereits vorhanden." << endl;
    if (read_yes_no("ueberschreiben?"))
      write_to_file(filename, text, false);
    else
      cout << "Abgebrochen";
  }
  else
  {
    ofstream outfile(filename.c_str());
    outfile << text;
  }
}

/**
 * Writes a given text into a file. The name of the
 * file has to be entered by the user. When the file
 * already exists. The user gets prompted to overwrite
 * or entering a new name.
 *
 * @param text     Text to write into the file.
 */
void write_to_file(string text)
{
  string filename = read_secure_filename();
  write_to_file(filename, text, false);
}

/**
 * Checks if a file already exists by its name.
 *
 * @param filename Filename to check for existence.
 *
 * @return true   when the file exists.
 *         false  when the file don't exists.
 */
bool file_exists(const std::string& filename) {
  ifstream ifile(filename.c_str());
  return ifile;
}

/**
 * Promts the user to enter a filename. The filename gets checked
 * for existance. When there is already an existing file for
 * the enterd filename, the user gets promted to override
 * or reenter e new name.
 *
 * @return a filename of a new file or of an existing file which
 *         can be overwritten.
 */
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

/**
 * Reads a file according a given filename and prints the content
 * to the console.
 *
 * @param filename Name of the file to print to the console.
 */
void show_file(string filename)
{
  string line;
  ifstream infile(filename.c_str());
  if (!infile)
    cout << "File '" << filename << "' existiert nicht!" << endl;
  while (getline(infile, line))
    cout << line << endl;
}
