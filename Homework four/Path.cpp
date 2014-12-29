#include "Path.h"

// Adds all directories to the vector and sets the current dir to first one(ziro).

Path::Path(const MyString& str)
{
	const char* pStr = str.getString();

	MyString temp;

	while (*pStr)
	{
		if (*pStr == '/')
		{
			path.push(temp);
			temp = "";
		}
		else
		{
			temp += *pStr;
		}
		++pStr;
	}


	path.push(temp);

	current = 0;
}

MyString Path::getCurrent()
{
	if (!hasNext())
	{
		return MyString(""); // no more directories.
	}
	else
	{
		return path[current];
	}
}

void Path::increment()
{
	if (hasNext())
		++current;
}

bool Path::hasNext() const
{
	return current + 1 <= path.getSize();
}
