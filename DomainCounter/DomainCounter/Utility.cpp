#include "Utility.h"


// Gets the number of lines in the given file(name). Basic thing...
size_t getNumberOfLinesFromFile(const string& name)
{
	ifstream in(name);
	if (!in)
		return 0;

	size_t count = 0;
	string line;

	while (in.good())
	{
		getline(in, line, '\n'); 
		if (!in)
			break;

		++count;
	}

	in.close();
	return count;
}
