#include <iostream>
#include "Calculator.h"

Calculator::Calculator()
{
	// for now empty...
}


//Prints the words of the dictionary to the 'cout' stream.
void Calculator::printDictionaryToCout() const
{
	std::cout << "Dictionary...\n";

	for (size_t i = 0; i < dictionary.size(); ++i)
	{
		std::cout << "\"" << dictionary[i] << "\" " << std::endl;
	}

	std::cout << std::endl;
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
		radixTrie.insert((char*)dictionary[i], value);

		// Skip the new line.
		inDictionary.get();
		++i;
	}

	inDictionary.close();

	return true;
}

// Some test to find word TO DO Delete it...
void Calculator::testFind() const
{
	std::cout << "Test find...\n";

	std::cout << "Find ab " << radixTrie.find("ab") << std::endl;
	std::cout << "Find a " << radixTrie.find("a") << std::endl;
	std::cout << "Find abb " << radixTrie.find("abb") << std::endl;
	std::cout << "Find ac " << radixTrie.find("ac") << std::endl;
	std::cout << "Find abbbb " << radixTrie.find("abbbb") << std::endl;
	std::cout << "Find acqwdqd " << radixTrie.find("acqwdqd") << std::endl;
	std::cout << "Find aaaaaaaaaaaaaaaaaaaaaaa " << radixTrie.find("aaaaaaaaaaaaaaaaaaaaaaa") << std::endl;

	std::cout << std::endl;
}

// Some test to get the all words values by given prefix. TO DO Delete it...
void Calculator::testPrefix() const
{
	std::cout << "Test prefix...\n";

	std::cout << "Prefix a has value: " << sumOfVectorNumbers(radixTrie.getAllWithPrefix("a")) << std::endl;
	std::cout << "Prefix ab has value: " << sumOfVectorNumbers(radixTrie.getAllWithPrefix("ab")) << std::endl;
	std::cout << "Prefix aaaaaaaaaaaaaaaaaaaaaaa has value: " << sumOfVectorNumbers(radixTrie.getAllWithPrefix("aaaaaaaaaaaaaaaaaaaaaaa")) << std::endl;

	std::cout << std::endl;
}

// Deletes the memory for the dictionary.
Calculator::~Calculator()
{
	for (int i = 0; i < dictionary.size(); ++i)
		delete[] dictionary[i];
}