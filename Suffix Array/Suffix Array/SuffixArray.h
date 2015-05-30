#pragma once

#include <vector>
#include <algorithm>

/// TO DO: start from 1 to length.

using std::vector;

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
		// Default values(in any case. the first memory allocation may fail)
		setDefaultValues();

		// Get the length of the text.
		length = strlen(text);

		// Make a copy of the given text and keep it as member variable(pointer).
		this->text = new char[length + 1];
		strcpy(this->text, text);

		// Create the array with the start of every suffix (so from 0 to length-1)
		suffixes = new unsigned[length];
		for (unsigned i = 0; i < length; ++i)
			suffixes[i] = i;

		// Sort the suffixes- lexical.
		sortSuffixes();
	}

	// Returns a vector of start positions of the suffixes, which has prefix the given pattern.  
	vector<int> search(const char* pattern) const
	{
		vector<int> res;

		int lowerBound = lowerBoundOfSuffixesWithPattern(pattern),
			   upperBound = upperBoundOfSuffixesWithPattern(pattern);

		std::cout << "Lower bound is " << lowerBound << std::endl;
		std::cout << "Upper bound is " << upperBound << std::endl;

		return res;
	}

	// Prints all suffixes of the SuffixArray to the given ostream.
	void print(std::ostream& out) const
	{
		out << "Suffixes: \n";
		for (unsigned i = 0; i < length; ++i)
		{
			out << i << " " << (text + suffixes[i]) << "\n";
		}
	}

	// Prints all suffixes with start positions are in the given vector(the values in the vector, are the start positions of the suffixes) to the given ostream.
	void printAllSuffixesWithStart(std::ostream& out, const vector<int>& v) const
	{
		size_t n = v.size();
		for (size_t i = 0; i < n; ++i)
		{
			out << (text + suffixes[v[i]]) << "\n";
		}
	}

	~SuffixArray()
	{
		free();
	}

	// Counts the number of same chars from the start of the two strings
	unsigned compare(const char* s1, const char* s2) const
	{
		unsigned count = 0;
		while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
		{
			++count;
			++s1;
			++s2;
		}

		return count;
	}
private:


	// A Binary search algorithm for lower bound.
	int lowerBoundOfSuffixesWithPattern(const char* pattern) const
	{
		int low = 0;
		int high = length - 1;
		int mid = 0;
		unsigned matchCount = 0;
		unsigned patternLength = strlen(pattern);
		
		while (low < high)
		{
			mid = (low + high) / 2;
			if (strcmp(pattern + matchCount, text + suffixes[mid] + matchCount) <= 0) // TO DO -> partial checking
			{
				high = mid;
				matchCount += compare(text + suffixes[mid] + matchCount, text + suffixes[low] + matchCount);
			}
			else
			{
				low = mid + 1;
				matchCount += compare(text + suffixes[mid + 1] + matchCount, text + suffixes[high] + matchCount);
			}
		}

		return low;
	}

	// A binary search algorithm for upper bound.
	int upperBoundOfSuffixesWithPattern(const char* pattern) const
	{
		int low = 0;
		int high = length - 1;
		int mid = 0;
		unsigned matchCount = 0;
		unsigned patternLength = strlen(pattern);

		while (low < high)
		{

			mid = (low + high + 1) / 2;
			//std::cout << "compares with middle = " << mid << " string: " << text + suffixes[mid] << " and string: " << pattern << std::endl;
			//std::cout << "matchCount = " << matchCount << std::endl;
			if (strstr(text + suffixes[mid], pattern) == text + suffixes[mid] || strcmp(text + suffixes[mid], pattern) <= 0) // TO DO -> partial checking
			{
			//	matchCount += compare(text + suffixes[mid] + matchCount, text + suffixes[high] + matchCount);
			//	std::cout << "matchCount = " << matchCount << std::endl;
			//	std::cout << "true" << std::endl;
				low = mid;
			}
			else
			{
			//	matchCount += compare(text + suffixes[mid] + matchCount, text + suffixes[low] + matchCount); // Mid - 1 == 0?
			//	std::cout << "matchCount = " << matchCount << std::endl;

				high = mid - 1;
			//	std::cout << "false" << std::endl;
			}
		}

		return low;
	}

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