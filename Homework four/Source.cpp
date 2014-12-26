#include <iostream>
#include "String.h"

int main()
{
	String str1("aba1a");
	String str2("abaa");

	str1 = "Tony";

	std::cout << str1 << " and " << str2 << std::endl;
	std::cout << (str1 == str2) << std::endl;


	return 0;
}