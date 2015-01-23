#include <iostream>
#include <fstream>
#include "StreetMap.h"



int main()
{
	
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	{
		StreetMap map;

		std::ifstream in("input.txt");
		if (!in)
		{
			std::cerr << "Can`t open the input file" << std::endl;
			return -1;
		}

		try
		{
			map.deserialize(in);
			map.printStreetMapWithHeights(std::cout);
		}
		catch (const char * str)
		{
			std::cerr << "Error: " << str << "\n";
		}


		in.close();
	}

	_CrtMemCheckpoint(&s2);

	if (_CrtMemDifference(&s3, &s1, &s2))
	{
		std::cout << "Memory leak detected!" << std::endl;
		_CrtMemDumpStatistics(&s3);
	}
	return 0;
}