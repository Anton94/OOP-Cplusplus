#pragma once

#include <fstream>
#include <string>

using std::ifstream;
using std::string;

// Gets the number of lines in the given file(name).
size_t getNumberOfLinesFromFile(const string& name);