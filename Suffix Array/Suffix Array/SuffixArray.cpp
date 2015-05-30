#include "SuffixArray.h"

// Constructs the array from the given text and it`s now immutable.
SuffixArray::SuffixArray(const char* text)
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
vector<int> SuffixArray::search(const char* pattern) const
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
void SuffixArray::print(std::ostream& out) const
{
	out << "Suffixes: \n";
	for (unsigned i = 0; i < length; ++i)
	{
		out << i << "\t" << (text + suffixes[i]) << "\n";
	}
	out << "\n";
}

// Prints all suffixes with start positions are in the given vector(the values in the vector, are the start positions of the suffixes) to the given ostream.
void SuffixArray::printAllSuffixesWithStart(std::ostream& out, const vector<int>& v) const
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

// Destructor.
SuffixArray::~SuffixArray()
{
	free();
}

// A Binary search algorithm for lower bound.
int SuffixArray::lowerBoundOfSuffixesWithPattern(const char* pattern) const
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
int SuffixArray::upperBoundOfSuffixesWithPattern(const char* pattern, unsigned patternLength) const
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

// Sets the default values for the object member datas.
void SuffixArray::setDefaultValues()
{
	suffixes = NULL;
	text = NULL;
	length = 0;
}

// Creates an object of SorterHelpwe, which has overloaded operator() and a pointer to the owner(to the text) and makes the lexical sort.
// Sort them with O(N * N*logN) where N is @length
void SuffixArray::sortSuffixes()
{
	SorterHelper sh(this);

	std::sort(suffixes, suffixes + length, sh);
}

// Deletes the allocated memory. NOTE: does not set the pointers to NULL...
void SuffixArray::free()
{
	delete[] suffixes;
	delete[] text;
}