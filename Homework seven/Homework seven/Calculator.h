#pragma once

#include <vector>
#include <fstream>
#include "RadixTrie.h"
#include "Utility.h"

using std::vector;
using std::ifstream;

/*
	This class is for the purposes of the homework...
*/

class Calculator
{
public:
	Calculator();

	// Extracts the dictionary from the given file name and builds the radix trie. If there are some problems, returns false, otherwise returns true.
	bool build(char * dictionaryFile);

	// Prints the words of the dictionary to the 'cout' stream.
	void printDictionaryToCout() const;
	
	// Some test to find word TO DO Delete it...
	void testFind() const;

	// Deletes the memory for the dictionary.
	~Calculator();
private:
	RadixTrie radixTrie;
	vector<unsigned char*> dictionary;
private:
	Calculator(const Calculator& other);
	Calculator& operator=(const Calculator& other);
};