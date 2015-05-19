#pragma once

#include <fstream>
#include <vector>
#include <utility>
#include <string>

using std::vector;
using std::pair;
using std::string;
using std::ifstream;

/*
	A basic structure that stores string (word) and a value in array(vector).
*/
template <class T>
class Dictionary
{
public:
	/*
		Reads the dictionary words from the given input stream.
		It does not make format validation on the input data(but has some kind of validation...) If there are more than one word-value pair on row, it will cut the last row(s).
	*/
	bool deserialize(ifstream& in)
	{
		if (!in)
			return false;

		size_t n = getNumberOfWords(in);
		dictionary.resize(n);

		int i = 0;

		while (in && i < n)
		{
			in >> dictionary[i].first;
			if (!in)
				return false;

			in >> dictionary[i].second;
			if (!in)
				return false;

			++i;
		}
		
		return true;
	}

	void print() const
	{
		for (int i = 0; i < dictionary.size(); ++i)
		{
			std::cout << "[" << dictionary[i].first << "] " << dictionary[i].second << std::endl;
		}
	}
private:
	/*
		Returns the number of lines in the input stream(number of words in the dictionary). 
		If the last row (or rows) is empty in the input file , it will count them, but it`s ok...
	*/
	size_t getNumberOfWords(ifstream& in)
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
private:
	vector<pair<string, T>> dictionary;
};