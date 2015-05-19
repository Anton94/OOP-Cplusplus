#include <iostream>
#include <fstream>
#include "Dictionary.h"



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

			std::ifstream inDictionary(argv[1]);
			if (!inDictionary)
				return 1;
			std::ifstream inText(argv[2]);
			if (!inText)
				return 1;

			std::cout << argv[1] << " " << argv[2] << std::endl;


			Dictionary<int> d;
			if (!d.deserialize(inDictionary))
				std::cout << "Wrong input file!" << std::endl;

			d.print();

			inDictionary.close();
			inText.close();
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