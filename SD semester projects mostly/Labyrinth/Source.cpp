#include <iostream>
#include "../Vector/Vector.h"


#define HEIGHT 500
#define WIDTH 500

int main()
{
	_CrtMemState s1, s2, s3;
	_CrtMemCheckpoint(&s1);
	{
		
		try
		{

			Vector<Vector<double> > array2D;

			// Set up sizes. (HEIGHT x WIDTH)
			array2D.resize(HEIGHT);
			array2D.getSize();
			for (int i = 0; i < HEIGHT; ++i)
				array2D[i].resize(WIDTH);
		}
		catch (const char * str)
		{
			std::cerr << "Error: " << str << "\n";
		}

	}

	_CrtMemCheckpoint(&s2);

	if (_CrtMemDifference(&s3, &s1, &s2))
	{
		std::cout << "Memory leak detected!" << std::endl;
		_CrtMemDumpStatistics(&s3);
	}
	return 0;
}