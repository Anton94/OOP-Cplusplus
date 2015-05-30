#include <iostream>
#include <string>
#include "SuffixArray.h"

using std::string;

// Searches the pattern and print the suffixes, which has preffix the given pattern(if has some).
void printInforForPattern(std::ostream& out, const SuffixArray& sa, const char* pattern)
{
	out << "Pattern: " << pattern << "\n";
	out << "Suffix of: \n";
	sa.printAllSuffixesWithStart(out, sa.search(pattern));
	out << "\n";
}

int main()
{
	// Memory leaks cheching...
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	{
		string text;
		//std::cin >> text;

		text = "abcabdescaabadcsasqsdqsaqqdas";

		SuffixArray sa(text.c_str());

		sa.print(std::cout);

		printInforForPattern(std::cout, sa, "a");
		printInforForPattern(std::cout, sa, "ab");
		printInforForPattern(std::cout, sa, "s");
		printInforForPattern(std::cout, sa, "g");
		printInforForPattern(std::cout, sa, "ca");
		printInforForPattern(std::cout, sa, "caa");
		printInforForPattern(std::cout, sa, "q");
		printInforForPattern(std::cout, sa, "qs");
		printInforForPattern(std::cout, sa, "aabadcsasqsdqsaqqdas");
		printInforForPattern(std::cout, sa, "sqsdqsaqqdas");
	}

	_CrtMemCheckpoint(&s2);

	if (_CrtMemDifference(&s3, &s1, &s2))
	{
		std::cout << "Memory leak detected!" << std::endl;
		_CrtMemDumpStatistics(&s3);
	}

	return 0;
}
