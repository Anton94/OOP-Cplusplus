#pragma once

#include <vector>
#include <algorithm>

/* 
	#	Anton Vasilev Dudov
	#	FN: 71488
	#
	#
	#   The building of the suffix array:
	#		Copy the given text as private member(pointer to dynamic array) so I can keep it and work with it after that- O(n), where n is length of the text.
	#		Make the array of start indexes: the firs element is 0, second is 1, .... , "N-th - 1" element is n - 1    (from 0 to n - 1) - O(n)
	#       Sort the suffixes with stl-sort, so O(n*log n) but every compare is O(n), so sort is O(n*n*log n)
	#
	#
	#	The searching for the suffixes which has preffix the given pattern. Let`s the length of pattern is m.
	#		I use binary search for the bounds, so I will find the left and right bounds (as indexes of the sorted array of suffixes). (lower and upper bounds).
	#		Finding a bound- complexity  O(log n) but every compare is O(m) so it`s O(m*log n). But I keep the number of same chars in the range I work with 
	#		and this compares are smaller and it can do it for O(m + log n).
	#		But this is best case, with good pattern, the matching chars in the range will be zero and the complexity will be O(m*log n).
	#		So finding the bounds is 2*O(m*log n) worst case and 2*O(m + log n) best case.
	#		After that I go through every element in that range, so complexity O(k) where k is the number of matches.
	#		Worst case (with bad input data) of searching O(m*log n + k) and best case O(m + log n + k)
	#		(I make some compares maybe more so it will be in rare condition best case..)
	#
*/

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
	// NOTE: Indexes start from 0 to length - 1!
	vector<int> search(const char* pattern) const 
	{
		vector<int> res;

		unsigned patternLength = strlen(pattern);
		int lowerBound = lowerBoundOfSuffixesWithPattern(pattern),
			   upperBound = upperBoundOfSuffixesWithPattern(pattern, patternLength);

		// If the lower bound is valid one (the right one will be the lower or someone bigger...)
		if (numOfMatchesChars(text + suffixes[lowerBound], pattern) >= patternLength)
		{
			res.resize(upperBound - lowerBound + 1); // example : [3,3] -> 1 element, [3,4] -> 2 elements...
			for (unsigned i = lowerBound, counter = 0; i <= upperBound; ++i, ++counter)
			{
				res[counter] = i;
			}
		}

		return res;
	}

	// Prints all suffixes of the SuffixArray to the given ostream.
	void print(std::ostream& out) const
	{
		out << "Suffixes: \n";
		for (unsigned i = 0; i < length; ++i)
		{
			out << i << "\t" << (text + suffixes[i]) << "\n";
		}
		out << "\n";
	}

	// Prints all suffixes with start positions are in the given vector(the values in the vector, are the start positions of the suffixes) to the given ostream.
	void printAllSuffixesWithStart(std::ostream& out, const vector<int>& v) const
	{
		size_t n = v.size();
		if (n == 0)
		{
			out << "\tNo suffixes...\n";
		}
		else
		{
			for (size_t i = 0; i < n; ++i)
			{
				out << "\t" << (text + suffixes[v[i]]) << "\n";
			}
		}
	}

	~SuffixArray()
	{
		free();
	}
private:
	// A Binary search algorithm for lower bound.
	int lowerBoundOfSuffixesWithPattern(const char* pattern) const
	{
		int low = 0;
		int high = length - 1;
		int mid = 0;
		unsigned matchCount = 0;
		
		while (low < high)
		{
			mid = (low + high) / 2;
			if (strcmp(pattern + matchCount, text + suffixes[mid] + matchCount) <= 0)
			{
				matchCount += numOfMatchesChars(text + suffixes[mid] + matchCount, text + suffixes[low] + matchCount);
				high = mid;
			}
			else
			{
				matchCount += numOfMatchesChars(text + suffixes[mid + 1] + matchCount, text + suffixes[high] + matchCount);
				low = mid + 1;
			}
		}

		return low;
	}

	// A binary search algorithm for upper bound. 
	int upperBoundOfSuffixesWithPattern(const char* pattern, unsigned patternLength) const
	{
		int low = 0;
		int high = length - 1;
		int mid = 0;
		unsigned matchCount = 0;

		while (low < high)
		{
			mid = (low + high + 1) / 2;
			// If the pattern is prefix of the  middle string OR...
			if (numOfMatchesChars(text + suffixes[mid] + matchCount, pattern + matchCount) + matchCount >= patternLength || strcmp(text + suffixes[mid] + matchCount, pattern + matchCount) <= 0) // TO DO -> partial checking
			{
				matchCount += numOfMatchesChars(text + suffixes[mid] + matchCount, text + suffixes[high] + matchCount);
				low = mid;
			}
			else
			{
				matchCount += numOfMatchesChars(text + suffixes[mid - 1] + matchCount, text + suffixes[low] + matchCount); // Mid - 1 == 0?  mid bigger than @low, maybe safe...
				high = mid - 1;
			}
		}

		return low;
	}

	// Counts the number of same characters from the start of the two strings(given start).
	unsigned numOfMatchesChars(const char* s1, const char* s2) const
	{
		//unsigned count = 0;
		const char * keepS1 = s1;
		while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
		{
			//++count;
			++s1;
			++s2;
		}

		return s1 - keepS1;
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