#include <iostream>
#include <fstream>
#include "../Vector/Vector.h"
#include "Board.h"

#define HEIGHT 10
#define WIDTH 1000

int main()
{
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	{
		
		try
		{
			std::ifstream in("levelOne.txt");
			if (!in)
				throw "Can`t open the file for the level!";

			Board board;
			board.deserialize(in);
			board.printBoard(std::cout);
			board.printDoorKeyPairs(std::cout);
			
			board.tempPath();
			board.printBoard(std::cout);
			board.printDoorKeyPairs(std::cout);

		}
		/*catch (const char * str)
		{
			std::cerr << "Error: " << str << "\n";
		}*/
		catch (std::bad_alloc e)
		{
			std::cerr << "Error: " << e.what() << "\n";
		}
		// catch outside of the bounds array...
	}

	_CrtMemCheckpoint(&s2);

	if (_CrtMemDifference(&s3, &s1, &s2))
	{
		std::cout << "Memory leak detected!" << std::endl;
		_CrtMemDumpStatistics(&s3);
	}
	return 0;
}