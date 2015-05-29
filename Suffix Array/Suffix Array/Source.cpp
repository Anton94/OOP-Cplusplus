#include <iostream>
#include <string>
#include "SuffixArray.h"

int main()
{
	string text;
	cin >> text;

	SuffixArray sa(text.c_str());

	sa.print(std::cout);

	return 0;
}
