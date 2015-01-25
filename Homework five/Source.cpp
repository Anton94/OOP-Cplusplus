#include <iostream>
#include <fstream>
#include "StreetMap.h"

/*

#71488 FMI
Homework five

Github repository: https://github.com/Anton94/OOP-Cplusplus
Github project:	   https://github.com/Anton94/OOP-Cplusplus/tree/master/Homework%20five

*/

int main()
{
	
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	{
		std::ifstream in("input.txt");
		if (!in)
		{
			std::cerr << "Can`t open the input file" << std::endl;
			return -1;
		}

		try
		{
			StreetMap map1, map2;
			map1.setFlow(1);
			map1.setHeightBounds(-100, 1000);
			map1.deserialize(in);
			map1.printStreetMapWithHeights(std::cout);
			map1.printStreetMapWithWater(std::cout);
			map1.printIterations(std::cout);
			std::cout << std::endl;
			std::cout << std::endl;

			map1.executeIterations(std::cout);

			/*map2 = map1;
			map2.printStreetMapWithHeights(std::cout);
			map2.printStreetMapWithWater(std::cout);
			map1.printIterations(std::cout);
			std::cout << std::endl;

			StreetMap map3 = map2;
			map3.printStreetMapWithHeights(std::cout);
			map3.printStreetMapWithWater(std::cout);
			map1.printIterations(std::cout);
			std::cout << std::endl;*/
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