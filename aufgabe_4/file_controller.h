#ifndef FILE_CONTROLLER_H
#define FILE_CONTROLLER_H

#include <string>

using namespace std;

void write_to_file(string text);
bool file_exists(const std::string& filename);
string read_secure_filename();

#endif
