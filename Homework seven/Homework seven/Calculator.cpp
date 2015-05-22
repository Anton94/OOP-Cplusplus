#include <iostream>
#include "Calculator.h"

Calculator::Calculator()
{
	// for now empty...
}


//Prints the words of the dictionary to the 'cout' stream.
void Calculator::printDictionaryToCout() const
{
	for (size_t i = 0; i < dictionary.size(); ++i)
	{
		std::cout << "\"" << dictionary[i] << "\" " << std::endl;
	}
}

// Extracts the dictionary from the given file name and builds the radix trie. If there are some problems, returns false, otherwise returns true.
bool Calculator::build(char * dictionaryFile)
{
	ifstream inDictionary(dictionaryFile);
	if (!inDictionary)
		return false;

	size_t n = getNumberOfWords(inDictionary);
	dictionary.resize(n, NULL);

	size_t i = 0, len = 0;
	int value = -1;

	while (inDictionary && i < n)
	{
		// Get the word.
		if (!getWord(inDictionary, dictionary[i]) || !inDictionary)
			return false;

		// Get the value of thr word.
		inDictionary >> value;
		if (!inDictionary)
			return false;

		// Insert the word in the radix trie.
		radixTrie.insert(dictionary[i], value);

		// Skip the new line.
		inDictionary.get();
		++i;
	}

	inDictionary.close();

	return true;
}

// Deletes the memory for the dictionary.
Calculator::~Calculator()
{
	for (int i = 0; i < dictionary.size(); ++i)
		delete[] dictionary[i];
}