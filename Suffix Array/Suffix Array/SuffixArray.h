#pragma once

#include <iostream>
#include <cstring>
#include <algorithm>

using std::string;
using std::cin;
using std::cout;



class SuffixArray
{
	struct SorterHelper
	{
		SuffixArray * owner;
		SorterHelper(SuffixArray * o) : owner(o) {}
		bool operator()(int a, int b)
		{
			return strcmp(owner->text + a, owner->text + b) < 0;
		}
	};
public:
	SuffixArray(const char* text)
	{
		setDefaultValues();

		// Get the length of the text.
		length = strlen(text);

		// Make a copy of the given text and keep it as member variable(pointer).
		this->text = new char[length + 1];
		strcpy(this->text, text);

		// Create the array with the start of every suffix (so from 0 to length-1)
		suffixes = new unsigned[length + 1];
		for (unsigned i = 0; i < length; ++i)
			suffixes[i] = i;

		// Sort the suffixes- lexical.
		sortSuffixes();
	}

	void print(std::ostream& out) const
	{
		out << "Suffixes: \n";
		for (unsigned i = 0; i < length; ++i)
		{
			out << (text + suffixes[i]) << "\n";
		}
	}

	~SuffixArray()
	{
		free();
	}
private:
	// Sets the default values for the object member datas.
	void setDefaultValues()
	{
		suffixes = NULL;
		text = NULL;
		length = 0;
	}
	
	// Creates an object of SorterHelpwe, which has overloaded operator() and a pointer to the owner(to the text) and makes the lexical sort.
	// Sort them with O(N * N*logN) where N is @length
	void sortSuffixes()
	{
		SorterHelper sh(this);

		std::sort(suffixes, suffixes + length, sh);
	}

	// Deletes the allocated memory. NOTE: does not set the pointers to NULL...
	void free()
	{
		delete[] suffixes;
		delete[] text;
	}
private:
	unsigned * suffixes;
	char * text;
	size_t length;
};