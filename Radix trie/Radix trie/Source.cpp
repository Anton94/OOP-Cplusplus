#include <iostream>
#include <fstream>
#include "Calculator.h"

/*
Homework seven, SD 2
Anton Dudov, #71488

Github repository: https://github.com/Anton94/OOP-Cplusplus
Github project: https://github.com/Anton94/OOP-Cplusplus/tree/master/Radix%20trie

Command line arguments- two files, first dictionary, second the text. 
Sorts the words and their values.
*/

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

			/*calculator.printDictionaryToCout();
			
			calculator.testFind();
			calculator.testPrefix();
			calculator.testRemove();
			calculator.testFind();*/

			calculator.calculate(argv[2], std::cout);

			/*std::cout << (((int)'a' & 1 << 0) != 0) << std::endl;
			std::cout << (((int)'a' & 1 << 1) != 0) << std::endl;
			std::cout << (((int)'a' & 1 << 2) != 0) << std::endl;
			std::cout << (((int)'a' & 1 << 3) != 0) << std::endl;
			std::cout << (((int)'a' & 1 << 4) != 0) << std::endl;
			std::cout << (((int)'a' & 1 << 5) != 0) << std::endl;
			std::cout << (((int)'a' & 1 << 6) != 0) << std::endl;
			std::cout << (((int)'a' & 1 << 7) != 0) << std::endl;
			*/
			/*for (int i = 0; i < 8; ++i)
			{
				std::cout << (int)getIthBitOfString((const unsigned char*)"a",i) << " ";
			}

			std::cout << std::endl;


			for (int i = 0; i < 8; ++i)
			{
				std::cout << (int)getIthBitOfSymbol('a', i) << " ";
			}

			std::cout << std::endl;*/
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