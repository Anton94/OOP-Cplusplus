#include <iostream>
#include <string>
#include "SuffixArray.h"

using std::string;

int arr[12] = { 1, 2, 3, 4, 5, 5, 5, 6, 6, 7, 8, 9};

// A Binary search algorithm for lower bound.
int lowerBoundOfSuffixesWithPattern(int x)
{
	int low = 0;
	int high = sizeof(arr)/sizeof(int) - 1;
	int mid = 0;

	while (low < high)
	{
		mid = (low + high) / 2;
		if (x <= arr[mid]) // TO DO -> partial checking
			high = mid;
		else
			low = mid + 1;
	}

	return low;
}

// A binary search algorithm for upper bound.
int upperBoundOfSuffixesWithPattern(int x)
{
	int low = 0;
	int high = sizeof(arr) / sizeof(int) - 1;
	int mid = 0;

	while (low < high)
	{
		mid = (low + high + 1) / 2;
		if (arr[mid] <= x) // TO DO -> partial checking
			low = mid;
		else
			high = mid - 1;
	}

	return low;
}


int main()
{
	// Memory leaks cheching...
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	{
		string text;
		//std::cin >> text;

		text = "abcabdescaab";

		SuffixArray sa(text.c_str());

		sa.print(std::cout);

		sa.search("caa");

		std::cout << "Lower bound of 5 -> " << lowerBoundOfSuffixesWithPattern(5) << std::endl;
		std::cout << "Upper bound of 5 -> " << upperBoundOfSuffixesWithPattern(5) << std::endl;

		std::cout << "Lower bound of 7 -> " << lowerBoundOfSuffixesWithPattern(7) << std::endl;
		std::cout << "Upper bound of 7 -> " << upperBoundOfSuffixesWithPattern(7) << std::endl;

		std::cout << "Lower bound of 8 -> " << lowerBoundOfSuffixesWithPattern(8) << std::endl;
		std::cout << "Upper bound of 8 -> " << upperBoundOfSuffixesWithPattern(8) << std::endl;

		std::cout << "Lower bound of 9 -> " << lowerBoundOfSuffixesWithPattern(9) << std::endl;
		std::cout << "Upper bound of 9 -> " << upperBoundOfSuffixesWithPattern(9) << std::endl;

		std::cout << "Lower bound of 165 -> " << lowerBoundOfSuffixesWithPattern(165) << std::endl;
		std::cout << "Upper bound of 165 -> " << upperBoundOfSuffixesWithPattern(165) << std::endl;

		std::cout << "Lower bound of -165 -> " << lowerBoundOfSuffixesWithPattern(-165) << std::endl;
		std::cout << "Upper bound of -165 -> " << upperBoundOfSuffixesWithPattern(-165) << std::endl;

		std::cout << "Compare aba and aba" << sa.compare("aba", "abac") << std::endl;
	}

	_CrtMemCheckpoint(&s2);

	if (_CrtMemDifference(&s3, &s1, &s2))
	{
		std::cout << "Memory leak detected!" << std::endl;
		_CrtMemDumpStatistics(&s3);
	}

	return 0;
}
