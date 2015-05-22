#include <iostream>
#include <fstream>
#include "Calculator.h"



int main(int argc, char** argv)
{

	// Memory leaks cheching...
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	{
		try
		{
			if (argc < 3) // If more than 3 I don`t care..
				return 1; // Not enough input data.

			Calculator calculator;

			if (!calculator.build(argv[1]))
			{
				std::cout << "Wrong input data for the dictionary!" << std::endl;
				return 1;
			}

			calculator.printDictionaryToCout();

		}
		catch (const char* msg)
		{
			std::cerr << "What? " << msg << std::endl;
		}

	}

	_CrtMemCheckpoint(&s2);

	if (_CrtMemDifference(&s3, &s1, &s2))
	{
		std::cout << "Memory leak detected!" << std::endl;
		_CrtMemDumpStatistics(&s3);
	}
	//else
	//{
	//	std::cout << "Memory is OK!" << std::endl;
	//}

	return 0;
}