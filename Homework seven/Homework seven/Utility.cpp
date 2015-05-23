#include "Utility.h"
#include <string>

/*
Returns the number of lines in the input stream.
If the last row (or rows) is empty in the input file , it will count them, but it`s ok...
*/
size_t getNumberOfLines(ifstream& in)
{
	if (!in)
		return 0;

	size_t n = 0;
	int cur = in.tellg();

	char ch;

	while (in)
	{
		in.get(ch);
		if (!in)
		{
			if (ch != '\n') // If the last taken symbol before the broken file is not new line, increment the number of lines, so I can have empty line after the dictionary values in the file.
				++n;

			break;
		}

		if (ch == '\n')
			++n;
	}

	in.clear();
	in.seekg(cur);

	return n;
}

/*
Returns the number of words in the input stream. I will use string object just because I don`t need to take care for the blank symbols.
*/
size_t getNumberOfWords(ifstream& in)
{
	if (!in)
		return 0;

	size_t n = 0;
	int cur = in.tellg();

	std::string word;

	while (in)
	{
		in >> word;
		if (!in)
		{
			break;
		}

		++n;
	}

	in.clear();
	in.seekg(cur);

	return n;
}

/*
	Get the length of next word in the input stream given as argument @in. 
*/
size_t getLengthOfTheWord(ifstream& in)
{
	if (!in)
		return 0;

	size_t length = 0;
	int cur = in.tellg();

	char ch;

	while (in)
	{
		in.get(ch);
		if (!in)
			break;

		if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
			break;
		++length;
	}

	in.clear();
	in.seekg(cur);

	return length;
}


/*
Extracts a word from the in, creates the array and puts the data in it.
*/
bool getWord(ifstream& in, unsigned char *& word)
{
	// Get length of the word.
	size_t len = getLengthOfTheWord(in);
	if (!in)
		return false;

	word = new unsigned char[len + 1];

	// Read the word and save it in the dictionary.
	for (int i = 0; i < len; ++i)
	{
		word[i] = in.get();

		if (!in)
			return false;

	}

	word[len] = '\0';

	return true;
}


/*
Gives the i-th bit of the given string (as char*).
*/
unsigned char getIthBitOfString(const unsigned char* word, int bit)
{
	return (word[bit / 8] & 1 << (7 - (bit % 8))) != 0;
}


/*
Gives the i-th bit of the given char.
*/
unsigned char getIthBitOfSymbol(unsigned char ch, int bit)
{
	return ch & 1 << (7 - bit) != 0;
}

/*
Returns the sum of all numbers in the given vector.
*/
int sumOfVectorNumbers(const vector<int>& v)
{
	int res = 0;
	
	for (size_t i = 0; i < v.size(); ++i)
	{
		res += v[i];
	}

	return res;
}