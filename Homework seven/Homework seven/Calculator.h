#pragma once

#include <vector>
#include <fstream>
#include <utility>
#include "RadixTrie.h"
#include "Utility.h"

using std::vector;
using std::ifstream;
using std::ostream;
using std::pair;

/*
	This class is for the purposes of the homework...
*/

class Calculator
{
public:
	Calculator();

	// Extracts the dictionary from the given file name and builds the radix trie. If there are some problems, returns false, otherwise returns true.
	bool build(char * dictionaryFile);
	
	// Get the text from the given file name and checks every word if it is a prefix of word/s in the dictionary and groups their values(if has some). Sorts the output and prints it to the given ostream.
	void calculate(char * textFile, ostream& out) const;

	// Prints the words of the dictionary to the 'cout' stream.
	void printDictionaryToCout() const;
	
	// Some tests TO DO Delete it...
	void testFind() const;
	void testPrefix() const;
	void testRemove();

	// Deletes the memory for the dictionary.
	~Calculator();
private:
	// Deletes the allocated words in the temp vector of pairs <char*,int>.
	void deleteMemoeryForTheTextWords(vector<pair<unsigned char*, int>> & v) const;
private:
	RadixTrie radixTrie;
	vector<unsigned char*> dictionary;
private:
	Calculator(const Calculator& other);
	Calculator& operator=(const Calculator& other);
};