#include <iostream>
#include "MyString.h"

int main()
{
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	{
		MyString str1("aba1a");
		MyString str2("abaa");

		str1 += "t";

		std::cout << str1 << " and " << str2 << std::endl;
		std::cout << (str1 == str2) << std::endl;

		int a = 5, b = 7;

	}

	_CrtMemCheckpoint(&s2);

	if (_CrtMemDifference(&s3, &s1, &s2))
	{
		std::cout << "Memory leak detected!" << std::endl;
		_CrtMemDumpStatistics(&s3);
	}
	return 0;
}