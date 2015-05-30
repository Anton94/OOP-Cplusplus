#pragma once

#include <vector>
#include <ostream>
#include <algorithm>
#include "Utility.h"

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
	// Help structure for sort comparing...
	struct SorterHelper
	{
		SuffixArray * owner;
		SorterHelper(SuffixArray * o) : owner(o) {}
		bool operator()(size_t a, size_t b)
		{
			return strcmp(owner->text + a, owner->text + b) < 0;
		}
	};
public:
	// Constructs the array from the given text and it`s now immutable.
	SuffixArray(const char* text);

	// Returns a vector of start positions of the suffixes, which has prefix the given pattern.  
	// NOTE: Indexes start from 0 to length - 1!
	vector<int> search(const char* pattern) const;

	// Prints all suffixes of the SuffixArray to the given ostream.
	void print(std::ostream& out) const;

	// Prints all suffixes with start positions are in the given vector(the values in the vector, are the start positions of the suffixes) to the given ostream.
	void printAllSuffixesWithStart(std::ostream& out, const vector<int>& v) const;

	// Destructor.
	~SuffixArray();
private:
	// A Binary search algorithm for lower bound.
	int lowerBoundOfSuffixesWithPattern(const char* pattern) const;

	// A binary search algorithm for upper bound. 
	int upperBoundOfSuffixesWithPattern(const char* pattern, unsigned patternLength) const;

	// Sets the default values for the object member datas.
	void setDefaultValues();
	
	// Creates an object of SorterHelpwe, which has overloaded operator() and a pointer to the owner(to the text) and makes the lexical sort.
	// Sort them with O(N * N*logN) where N is @length
	void sortSuffixes();

	// Deletes the allocated memory. NOTE: does not set the pointers to NULL...
	void free();
private:
	unsigned * suffixes;
	char * text;
	size_t length;
private:
	// This homework needs only construction and searching.
	SuffixArray(const SuffixArray& other);
	SuffixArray& operator=(const SuffixArray& other);
};