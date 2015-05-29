#include <iostream>
#include <string>
#include <cstdlib>
#include "Calculator.h"

using std::string;

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

	size_t n = getNumberOfLines(inDictionary);
	dictionary.resize(n, NULL);

	size_t i = 0, len = 0;
	int value = -1;

	while (inDictionary && i < n)
	{
		// Get the word.
		if (!getWord(inDictionary, dictionary[i]) || !inDictionary) // If the allocation fails, the destructor will remove my memory.
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

// Get the text from the given file name and checks every word if it is a prefix of word/s in the dictionary and groups their values(if has some). Sorts the output and prints it to the given ostream.
// I will use the push functionality of the vector in this method and I will use string object just because I don`t need to take care for the blank symbols.
// I make a vector of char* and int - for the words and sum value of prefixed words. Other solution is to keep the position of the word in the file and word length (and sum value),
// but for now it`s some kind of OK.
void Calculator::calculate(char * textFile, ostream& out) const
{
	ifstream inText(textFile);
	if (!inText)
		return;

	size_t n = getNumberOfWords(inText);
	vector<pair<unsigned char*, int>> result(n, pair<unsigned char*, int>(NULL, 0)); // resize the vector and makes the default values.

	string word;

	for (size_t i = 0; i < n; ++i) // I know how many words are in the file(@n).
	{
		inText >> word;
		if (!inText)
		{
			break;
			// The file brokes, but I will make the calculations for the getted part...
			n = i; // this count of words are OK. (on i-th word brokes, so i - 1 words are OK, but i starts from zero)
		}

		try
		{
			result[i].first = new unsigned char[word.length() + 1];
		}
		catch (std::bad_alloc& e)
		{
			deleteMemoeryForTheTextWords(result);
			return;
		}
		strcpy((char*)result[i].first, word.c_str());

		result[i].second = sumOfVectorNumbers(radixTrie.getAllWithPrefix((const char*)result[i].first));
	}

	// If there is no elements, quits...
	if (n <= 0)
		return;


	qsort(&result[0], result.size(), sizeof(pair<unsigned char*, int>), compareTwoPairsBySecondValue);

	for (size_t i = 0; i < n; ++i)
	{
		std::cout << result[i].first << " " << result[i].second << std::endl;
	}

	// Remove the taken memory for the text words.
	deleteMemoeryForTheTextWords(result);
}

// Deletes the allocated words in the temp vector of pairs <char*,int>.
void Calculator::deleteMemoeryForTheTextWords(vector<pair<unsigned char*, int>> & v) const
{
	for (size_t i = 0; i < v.size(); ++i)
	{
		delete[] v[i].first;
	}
}

// Some test to find word TO DO Delete it...
void Calculator::testFind() const
{
	std::cout << "Test find...\n";

	std::cout << "Find ab " << radixTrie.find("ab") << std::endl;
	std::cout << "Find abc " << radixTrie.find("abc") << std::endl;
	std::cout << "Find abd " << radixTrie.find("abd") << std::endl;
	std::cout << "Find a " << radixTrie.find("a") << std::endl;
	std::cout << "Find c " << radixTrie.find("c") << std::endl;
	std::cout << "Find abde " << radixTrie.find("abde") << std::endl;
	std::cout << "Find ac " << radixTrie.find("ac") << std::endl;
	std::cout << "Find abbbb " << radixTrie.find("abbbb") << std::endl;
	std::cout << "Find acqwdqd " << radixTrie.find("acqwdqd") << std::endl;
	std::cout << "Find absadqw " << radixTrie.find("absadqw") << std::endl;
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


void Calculator::testRemove()
{
	std::cout << "Test remove...\n";

	//std::cout << "Remove a " << (int)radixTrie.remove("a") << std::endl;
	//std::cout << "Remove ac " << (int)radixTrie.remove("ac") << std::endl;
	std::cout << "Remove abd " << (int)radixTrie.remove("abd") << std::endl;
	//std::cout << "Remove aaaaaaaaaaaaaaaaaaaaaaa " << (int)radixTrie.remove("aaaaaaaaaaaaaaaaaaaaaaa") << std::endl;

	std::cout << std::endl;
}

// Deletes the memory for the dictionary.
Calculator::~Calculator()
{
	for (size_t i = 0; i < dictionary.size(); ++i)
		delete[] dictionary[i];
}